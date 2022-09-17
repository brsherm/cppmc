#if !defined(CONFIG_H)
#define CONFIG_H

#include <string>

namespace config
{
  static std::string title = "mc";
  static std::string monitor_filename = "monitor.txt";
  static const unsigned int chunk_width = 16;
  static const unsigned int chunk_height = 128;
  static const unsigned int chunk_size = chunk_width * chunk_width * chunk_height;
  static const bool debug = false;
}

#endif // CONFIG_H