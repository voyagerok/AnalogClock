#include <gtkmm.h>
#include "clock_widget.h"

namespace AnalogClock {

class Window : public Gtk::Window {
public:
    Window();
private:
    ClockWidget clockWidget;
};

}
