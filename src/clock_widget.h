#include <gtkmm.h>

namespace AnalogClock {

class ClockWidget : public Gtk::Widget {
public:
    ClockWidget();
    void set_time(int seconds, int minutes, int hours);
protected:
    void get_preferred_width_vfunc(int&, int&) const override;
    void get_preferred_height_vfunc(int&, int&) const override;
    void get_preferred_height_for_width_vfunc(int, int&, int&) const override;
    void get_preferred_width_for_height_vfunc(int, int&, int&) const override;
    void on_size_allocate(Gtk::Allocation&) override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_map() override;
    void on_unmap() override;
    void on_realize() override;
    void on_unrealize() override;
    Gtk::SizeRequestMode get_request_mode_vfunc() const override;
private:
    Glib::RefPtr<Gdk::Window> window;

    Cairo::RefPtr<Cairo::Surface> render_clock();
    Cairo::RefPtr<Cairo::Surface> render_time(int, int, int);
    Cairo::RefPtr<Cairo::Surface> render_time_labels();

    sigc::connection timer_render_time;
    sigc::slot<bool> render_time_slot;
};

}
