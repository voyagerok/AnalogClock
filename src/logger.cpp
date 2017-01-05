#include "logger.h"
#include <gtkmm.h>
#include <iostream>

namespace AnalogClock {

void Logger::WriteLog(const std::string &info)
{
    auto currentDate = Glib::DateTime::create_now_local();
    auto format_str = currentDate.format("%F %T");
    std::cout << format_str << " " << info << std::endl;
}

}
