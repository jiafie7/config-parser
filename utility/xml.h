#pragma once

#include <map>
#include <string>
#include <vector>

#include "utility/value.h"

namespace melon
{
  namespace utility
  {
    public:
      Xml() = default;
      Xml(const char* name);
      Xml(const std::string& name);
      ~Xml();

      std::string getName() const;
      std::string getText() const;
      Value& getAttribute(const std::string& key);

      void setName(const std::string& name);
      void setText(const std::string& name);
      void addAttribute(const std::string& key, const std::string& value);
      
      void appendChild(const Xml& child);
      void removeChild(int index);
      void removeChild(const char* name);
      void removeChild(const std::string& name);

    private:
      std::string m_name;
      std::string m_text;
      std::map<std::string, Value> m_attributes;
      std::vector<Xml> m_children;
  }
}
