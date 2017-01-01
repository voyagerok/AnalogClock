#include <gtkmm.h>
#include "window.h"

using namespace AnalogClock;

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.sample.app",
                                        Gio::APPLICATION_FLAGS_NONE);
    Window window;
    return app->run(window);
}
