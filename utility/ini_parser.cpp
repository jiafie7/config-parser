#include "utility/ini_parser.h"

using namespace melon::utility;

IniParser::IniParser(const std::string& filename)
{
  load(filename);
}

std::string IniParser::trim(std::string s)
{
  if (s.empty()) return s;
  s.erase(0, s.find_first_not_of(" \n\r"));
  s.erase(s.find_last_not_of(" \n\r") + 1);
  return s;
}

bool IniParser::load(const std::string& filename)
{
  m_sections.clear();
  m_filename = filename;

  std::ifstream fin(filename);
  if (fin.fail())
    throw std::logic_error("loading ini file failed: " + filename);

  std::string line;
  while (std::getline(fin, line))
  {
    line = trim(line);
    std::cout << line << '\n';
  }

  return true;
}

