#if !defined(LOGGER_H)
#define LOGGER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include "src/config/config.h"
#include <unordered_map>

namespace logger
{
  extern std::stringstream contents;
  extern std::ofstream file;
  enum message {
    TIME_SINCE_LAST_UPDATE,
    SAMPLE_MESSAGE
  };
  extern std::unordered_map<unsigned int, std::string> message_map;
  template<class T> unsigned char color(const message key, T& value) {
    switch (key) {
      case TIME_SINCE_LAST_UPDATE:
        return 38;
      default:
        return 200;
    }
  }
  template<class T> void info(const message key, T& value)
  {
    unsigned char x = 27;
    contents << message_map[key] << ": " << x << "[38;5;";
    contents << std::to_string(color(key, value));
    contents << "m" << value << x << "[39;m" << "\n";
  }
  void init_map();
  void write();
};

#endif // LOGGER_H
