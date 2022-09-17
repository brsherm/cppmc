#include "logger.h"

namespace logger {
  std::stringstream contents;
  std::ofstream file;
  std::unordered_map<unsigned int, std::string> message_map;
  void write() {
    file.open(config::monitor_filename);
    file << contents.str();
    file.close();
    contents.str("");
  }
  void init_map() {
    message_map[TIME_SINCE_LAST_UPDATE] = "time since last update";
    message_map[SAMPLE_MESSAGE] = "sample message";
  }
}

