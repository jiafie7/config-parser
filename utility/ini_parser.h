#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include "utility/value.h"

namespace melon
{
  namespace utility
  {
    class IniParser
    {
      typedef std::map<std::string, Value> Section;
      public:
        IniParser() = default;
        IniParser(const std::string& filename);
        ~IniParser() = default;
        
        bool load(const std::string& filename);

      private:
        std::string trim(std::string s);

      private:
        std::string m_filename;
        std::map<std::string, Section> m_sections;
    };
  }
}

