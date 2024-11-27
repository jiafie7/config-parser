#include <iostream>
#include "utility/xml.h"
#include "utility/xml_parser.h"

using namespace melon::utility;

int main()
{
  Xml xml("students");
  std::cout << xml.getName() << '\n';

  xml.addAttribute("name", "Michael");
  xml.addAttribute("age", "18");
  std::cout << xml.getAttribute("age") << '\n';

  Xml x1("student");
  x1.addAttribute("age", "17");
  x1.setText("Jack");

  Xml x2("student");
  x2.addAttribute("age", "19");
  x2.setText("Maria");

  Xml x3("student");
  x3.addAttribute("age", "21");
  x3.setText("Jane");
  
  xml.appendChild(x1);
  xml.appendChild(x2);
  xml.appendChild(x3);
  std::cout << xml << '\n';

  xml.removeChild(1);
  std::cout << xml << '\n';

  for(auto it = xml.begin(); it != xml.end(); ++ it)
    std::cout << *it << '\n';

  std::cout << "--------------------------------------------" << '\n';

  XmlParser parser;
  parser.load("./../info.xml");
  
  Xml content = parser.parse();

  std::string name = content["student"]["name"].getText();
  std::cout << "name=" << name << std::endl;

  int id = content["student"].getAttribute("id");
  std::cout << "id=" << id << std::endl;

  std::string age = content["student"]["age"].getText();
  std::cout << "age=" << age << std::endl;

  for (auto it = content.begin(); it != content.end(); it++)
    std::cout << *it << std::endl;

  return 0;
}
