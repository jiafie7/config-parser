#include <iostream>

#include "utility/json.h"
#include "utility/json_parser.h"

using namespace melon::utility;

int main()
{
  
  JsonParser parser;
  parser.load("./../data.json");
  Json data = parser.parse();
  std::cout << data << '\n';

  std::cout << data.get("code") << '\n';
  std::cout << data["message"] << '\n';

  std::cout << data["language"] << '\n';
  data["language"].append("Spanish");
  std::cout << data["language"] << '\n';

  std::cout << data["data"] << '\n';
  std::cout << data["data"]["photo"] << '\n';
  data["data"].remove("photo");
  std::cout << data["data"] << '\n';


  return 0;
}
