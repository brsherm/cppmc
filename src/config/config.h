#if !defined(CONFIG_H)
#define CONFIG_H

#include <string>

namespace config
{
  static std::string title = "mc";
  static std::string monitor_filename = "monitor.txt";
  static const bool debug = false;
}

#endif // CONFIG_H