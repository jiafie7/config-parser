#include <iostream>

#include "utility/json.h"

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

  Json num = "sss";
  Json j1;
  j1 = num;
  std::cout << num << '\n';
  std::cout << j1 << '\n';
  num.clear();
  std::cout << num << '\n';
  std::cout << j1 << '\n';


  return 0;
}
