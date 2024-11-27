#pragma once

#include "utility/xml.h"

using namespace melon::utility;

namespace melon
{
  namespace utility
  {
    class XmlParser
    {
      public:
        XmlParser() = default;
        ~XmlParser() = default;

        void load(const std::string& filename);
        void load(const char* buf, int len);
        Xml parse();

        std::string content() { return m_content; }

      private:
        void skipWhiteSpace();
        bool parseDeclaration();
        bool parseComment();
        Xml parseElement();
        std::string parseName();
        std::string parseText();
        std::string parseAttrKey();
        std::string parseAttrVal();
        

      private:
        std::string m_content;
        int m_index;
    };
  }
}
