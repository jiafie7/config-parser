#include "utility/xml.h"

using namespace melon::utility;

Xml::Xml(const char* name)
  : m_name(name)
{}

Xml::Xml(const std::string& name)
  : m_name(name)
{}

Xml::Xml(const Xml& other)
{
  copy(other);
}

Xml::~Xml()
{
  clear();
}

Xml& Xml::operator=(const Xml& other)
{
  if (this == &other)
    return *this;
  copy(other);
  return *this;
}

void Xml::copy(const Xml& other)
{
  clear();
  m_name = other.m_name;
  m_text = other.m_text;
  m_attributes = other.m_attributes;
  m_children = other.m_children;
}

void Xml::clear()
{
  m_name.clear();
  m_text.clear();
  m_attributes.clear();
  m_children.clear();
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
  return m_attributes[key];
}

void Xml::setName(const std::string& name)
{
  m_name = name;
}

void Xml::setText(const std::string& text)
{
  m_text = text;
}

void Xml::addAttribute(const std::string& key, const std::string& value)
{
  m_attributes[key] = value;
}

void Xml::appendChild(const Xml& child)
{
  m_children.push_back(child);
}

void Xml::removeChild(int index)
{
  if (m_children.empty())
    return;
  
  if (index < 0 || index >= m_children.size())
    return;

  m_children.erase(m_children.begin() + index);
}

void Xml::removeChild(const char* name)
{
  for (auto it = m_children.begin(); it != m_children.end(); )
    if (it->getName() == name)
      it = m_children.erase(it);
    else
      ++ it;
}

void Xml::removeChild(const std::string& name)
{
  removeChild(name.c_str());
}

Xml& Xml::operator[](int index)
{
  return m_children.at(index);
}

Xml& Xml::operator[](const char* name)
{
  for (auto it = m_children.begin(); it != m_children.end(); ++ it)
    if (it->getName() == name)
      return *it;

  m_children.push_back(Xml(name));
  return m_children.back();
}

Xml& Xml::operator[](const std::string& name)
{
  return (*this)[name.c_str()];
}

int Xml::size() const
{
  return m_children.size();
}
      
bool Xml::empty() const
{
  return m_children.empty();
}

std::string Xml::toString() const
{
  if (m_name.empty())
    return "";

  std::ostringstream oss; 
  oss << "<" << m_name;
  for (auto it = m_attributes.begin(); it != m_attributes.end(); ++ it)
    oss << " " << it->first << "=\"" << it->second << "\""; 
  oss << ">";

  for (auto it = m_children.begin(); it != m_children.end(); ++ it)
    oss << it->toString();

  oss << m_text;

  oss << "</" << m_name << ">";
  
  return oss.str();
}

void Xml::save(const std::string& filename)
{
  std::ofstream ofs(filename);
  if (ofs.fail())
    throw std::logic_error("Open file failed: " + filename);

  ofs << toString();
  ofs.close();
}





