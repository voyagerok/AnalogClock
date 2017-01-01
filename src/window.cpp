#include "window.h"

namespace AnalogClock {

Window::Window() {
    Gtk::Window();

    set_title("Main window");
    set_default_size(800, 600);
}

}
