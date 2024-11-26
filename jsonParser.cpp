#include <iostream>

#include "utility/json.h"
#include "utility/json_parser.h"

using namespace melon::utility;

int main()
{
  // 基本类型相关操作
  Json v1;
  Json v2 = true;
  Json v3 = 123;
  Json v4 = 1.23;
  Json v5 = "hello, world";

  std::cout << v1 << '\n';
  std::cout << v2 << '\n';
  std::cout << v3 << '\n';
  std::cout << v4 << '\n';
  std::cout << v5 << '\n';

  bool b = v2;
  int i = v3;
  double d = v4;
  std::string s = v5;

  std::cout << v2 << '\n';
  std::cout << v3 << '\n';
  std::cout << v4 << '\n';
  std::cout << v5 << '\n';

  // array
  Json v;
  v.append(v1);
  v.append(b);
  v.append(i);
  v.append(d);
  v.append(s);
  
  std::cout << v << '\n';
  std::cout << v.has(3) << ' ' << v.has(5) << '\n';
  std::cout << v.get(3) << ' ' << v[4] << '\n';
  
  v.remove(0);
  std::cout << v << '\n';

  // object
  Json ob;
  std::cout << ob.has("as") << '\n';
  std::cout << ob["as"] << '\n';
  ob["name"] = "Michael";
  ob["age"] = 17;
  std::cout << ob.has("name") << ' ' << ob.has("age") << '\n';
  std::cout << ob["name"] << ' ' << ob.get("age") << '\n';
  ob.remove("age");
  std::cout << ob.has("age") << ' ' << ob["age"] << '\n';
  
  JsonParser parser;
  std::string str = "123 456";
  parser.load(str.c_str(), str.size());
  Json null = parser.parse();
  std::cout << null << '\n';  

  return 0;
}
