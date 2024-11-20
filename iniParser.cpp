#include "utility/ini_parser.h"

using namespace melon::utility;

int main()
{
  IniParser parser;
  parser.load("./../config.ini");

  // Access values
  std::string host = parser.get("Network", "Host");
  int port = parser["Network"]["Port"];
  std::cout << "Host: " << host << "\nPort: " << port << std::endl;

  // Add values
  parser.set("Network", "Host", "localhost");
  parser.set("Network", "Port", 3360);
  std::string host_ = parser.get("Network", "Host");
  int port_ = parser["Network"]["Port"];
  std::cout << "Host: " << host_ << "\nPort: " << port_ << std::endl;

  // Save to file
  parser.save("./../new.ini");

  return 0;
}
