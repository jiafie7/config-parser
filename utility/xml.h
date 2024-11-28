#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "utility/value.h"

namespace melon
{
  namespace utility
  {
    class Xml{
    public:
      Xml() = default;
      Xml(const char* name);
      Xml(const std::string& name);
      Xml(const Xml& other);
      Xml(Xml&& other);
      ~Xml();

      Xml& operator=(const Xml& other);
      Xml& operator=(Xml&& other) noexcept;

      std::string getName() const;
      std::string getText() const;
      Value& getAttribute(const std::string& key);

      void setName(const std::string& name);
      void setText(const std::string& name);
      void addAttribute(const std::string& key, const std::string& value);
      
      void appendChild(const Xml& child);
      void appendChild(Xml&& child);
      void removeChild(int index);
      void removeChild(const char* name);
      void removeChild(const std::string& name);
      Xml& operator[](int index);
      Xml& operator[](const char* key);
      Xml& operator[](const std::string& name);
     
      typedef std::vector<Xml>::iterator iterator;
      iterator begin() { return m_children.begin(); }
      iterator end() { return m_children.end(); }
      iterator erase(iterator it) 
      {
        it->clear();
        return m_children.erase(it); 
      }
      
      int size() const;
      bool empty() const;

      std::string toString() const;
      std::string toString(int depth) const;
      friend std::ostream& operator<<(std::ostream& os, const Xml& xml)
      {
        // os << xml.toString();
        os << xml.toString(0);
        return os;
      }

      void save(const std::string& filename);

    private:
      void copy(const Xml& other);
      void clear();
      std::string trimText(const std::string& text);
      std::string trimText(const std::string& text) const;
      void swap(Xml& other);

    private:
      std::string m_name;
      std::string m_text;
      std::map<std::string, Value> m_attributes;
      std::vector<Xml> m_children;
    };
  }
}
