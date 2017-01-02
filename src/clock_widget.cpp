#include "clock_widget.h"

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

bool ClockWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    Gtk::Allocation alloc = get_allocation();
    cr->rectangle(alloc.get_x(),alloc.get_y(), alloc.get_width(), alloc.get_height());
    cr->set_source_rgb(0,0,0);
    cr->fill();

    return true;
}

}
