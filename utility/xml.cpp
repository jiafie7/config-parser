#include "utility/xml.h"

using namespace melon::utility;

Xml::Xml(const char* name)
  : m_name(name)
{}

Xml::Xml(const std::string& name)
  : m_name(name)
{}

Xml::~Xml()
{

}

std::string Xml::getName() const
{
  return m_name;
}

std::string Xml::getText() const
{
  return m_text;
}
    
Value& Xml::getAttribute(const std::string& key)
{
  return m_atrributes[key];
}


