#include "clock_widget.h"
#include <iostream>

namespace AnalogClock {

static const int min_width = 300;
static const int pref_width = 400;
static const int min_height = 300;
static const int pref_height = 400;

ClockWidget::ClockWidget() :
    Glib::ObjectBase("clockwidget"),
    Gtk::Widget()
{
    set_has_window(true);
    timer_render_time = Glib::signal_timeout().connect([this] {
        auto win = get_window();
        if (win)
        {
            Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                    get_allocation().get_height());
            win->invalidate_rect(r, false);
        }
        return true;
    }, 1000);
}

Gtk::SizeRequestMode ClockWidget::get_request_mode_vfunc() const
{
    return Gtk::Widget::get_request_mode_vfunc();
}

void ClockWidget::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const
{
    minimum_height = min_height;
    natural_height = pref_height;
}

void ClockWidget::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const
{
    minimum_width = min_width;
    natural_width = pref_width;
}

void ClockWidget::get_preferred_height_for_width_vfunc(int /*width*/, int &minimum_height, int &natural_height) const
{
    minimum_height = min_height;
    natural_height = pref_height;
}

void ClockWidget::get_preferred_width_for_height_vfunc(int /*width*/, int &minimum_width, int &natural_width) const
{
    minimum_width = min_width;
    natural_width = pref_width;
}

void ClockWidget::on_size_allocate(Gtk::Allocation &size_allocation)
{
    set_allocation(size_allocation);
    if (window)
    {
        window->move_resize(size_allocation.get_x(), size_allocation.get_y(),
                            size_allocation.get_width(), size_allocation.get_height());
    }
}

void ClockWidget::on_map()
{
    Gtk::Widget::on_map();
}

void ClockWidget::on_unmap()
{
    Gtk::Widget::on_unmap();
}

void ClockWidget::on_realize()
{
    set_realized();
    if (!window)
    {
        GdkWindowAttr attributes;
        memset(&attributes, 0, sizeof(attributes));

        Gtk::Allocation alloc = get_allocation();

        attributes.x = alloc.get_x();
        attributes.y = alloc.get_y();
        attributes.width = alloc.get_width();
        attributes.height = alloc.get_height();
        attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;

        window = Gdk::Window::create(get_parent_window(), &attributes, GDK_WA_X | GDK_WA_Y);
        set_window(window);

        window->set_user_data(gobj());
    }
}

void ClockWidget::on_unrealize()
{
    window.reset();
    Gtk::Widget::on_unrealize();
}

Cairo::RefPtr<Cairo::Surface> ClockWidget::render_clock()
{
    auto alloc = get_allocation();
    int width = alloc.get_width();
    int height = alloc.get_height();

    auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, alloc.get_width(),
                                               alloc.get_height());

    auto ctx = Cairo::Context::create(surface);

    ctx->scale(width / 100.0, height / 100.0);

    ctx->rectangle(0, 0, 100, 100);
    ctx->set_source_rgba(0.75, 0.75, 0.75, 1);
    ctx->fill();

    ctx->arc(50, 50, 50, 0, 2 * M_PI);
    ctx->set_source_rgba(0.55, 0.55, 0.55, 1);
    ctx->fill();

    ctx->set_source_rgb(0, 0, 0);
    ctx->set_line_width(1);
    for (int i = 0; i < 60; ++i)
    {
        ctx->move_to(50, 0);
        if (i % 5 == 0)
        {
            ctx->line_to(50, 4);
        }
        else
        {
            ctx->line_to(50, 2);
        }
        ctx->stroke();
        ctx->translate(50, 50);
        ctx->rotate_degrees(6);
        ctx->translate(-50, -50);
    }

    return surface;
}

Cairo::RefPtr<Cairo::Surface> ClockWidget::render_time(int seconds, int minutes, int hours)
{
    auto alloc = get_allocation();
    int width = alloc.get_width();
    int height = alloc.get_height();

    auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
    auto context = Cairo::Context::create(surface);

    context->scale(width / 100.0, height / 100.0);

    context->set_source_rgba(0,0,0,0);
    context->paint();

    auto hours_angle = (hours % 12) * 30;
    if (minutes != 0 || seconds != 0)
    {
        auto overall_seconds = minutes * 60 + seconds;
        hours_angle += (30 / 3600.0) * overall_seconds;
    }
    auto minutes_angle = minutes * 6;
    if (seconds != 0)
    {
        minutes_angle += (6 / 60.0) * seconds;
    }
    auto seconds_angle = seconds * 6;


    context->set_source_rgb(0, 0, 0);
    context->set_line_width(3);
    context->save();
    context->translate(50, 50);
    context->rotate_degrees(hours_angle);
    context->translate(-50, -50);
    context->move_to(50,50);
    context->line_to(50, 10);
    context->stroke();

    context->restore();
    context->set_line_width(2);
    context->save();
    context->translate(50, 50);
    context->rotate_degrees(minutes_angle);
    context->translate(-50, -50);
    context->move_to(50,50);
    context->line_to(50, 10);
    context->stroke();

    context->restore();
    context->set_line_width(1);
    context->translate(50, 50);
    context->rotate_degrees(seconds_angle);
    context->translate(-50, -50);
    context->move_to(50,50);
    context->line_to(50, 10);
    context->stroke();

    return  surface;
}

void ClockWidget::set_time(int seconds, int minutes, int hours)
{

}

bool ClockWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    auto surface = render_clock();
    cr->set_source(surface, 0, 0);
    cr->paint();

    auto date = Glib::DateTime::create_now_local();
    surface = render_time(date.get_second(), date.get_minute(), date.get_hour());
    cr->set_source(surface, 0, 0);
    cr->paint();

    return true;
}

}
