#include <iostream>
#include "utility/xml.h"
#include "utility/xml_parser.h"

using namespace melon::utility;

int main()
{
  XmlParser parser;
  parser.load("./../menu.xml");
  
  Xml menu = parser.parse();

  std::string name = menu["food"]["name"].getText();
  std::cout << "name=" << name << '\n';

  std::string price = menu["food"]["price"].getText();
  std::cout << "price=" << price << '\n';

  int calories = menu["food"]["name"].getAttribute("calories");
  std::cout << "calories=" << calories << '\n';

  for (auto it = menu.begin(); it != menu.end(); it++)
    std::cout << *it;

  return 0;
}
