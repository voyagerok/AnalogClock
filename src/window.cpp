#include "window.h"

namespace AnalogClock {

Window::Window() :
    Gtk::Window()
{
    set_title("Main window");
    add(clockWidget);
    show_all();
}

}
