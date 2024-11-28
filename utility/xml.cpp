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

Xml::Xml(Xml&& other)
{
  swap(other);
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

Xml& Xml::operator=(Xml&& other) noexcept
{
  if (this == &other)
    return *this;
  swap(other);
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

void Xml::appendChild(Xml&& child)
{
  m_children.push_back(std::move(child));
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
  
  oss << trimText(m_text);
 
  oss << "</" << m_name << ">";
  
  return oss.str();
}

std::string Xml::toString(int depth) const 
{
  if (m_name.empty())
    return "";

  std::ostringstream oss;

  std::string indent(depth * 2, ' ');
  oss << indent << "<" << m_name;

  for (const auto& attr : m_attributes)
    oss << " " << attr.first << "=\"" << attr.second << "\"";

  if (m_children.empty() && trimText(m_text).empty()) 
  {
    oss << "/>\n";
  }
  else 
  {
    oss << ">";

    if (!m_children.empty()) 
    {
      oss << "\n";
      for (const auto& child : m_children)
        oss << child.toString(depth + 1);
      if (!trimText(m_text).empty())
        oss << std::string((depth + 1) * 2, ' ') << trimText(m_text) << "\n";
      oss << indent;
    } 
    else if (!trimText(m_text).empty()) 
    {
      oss << trimText(m_text);
    }

    oss << "</" << m_name << ">\n";
  }

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

std::string Xml::trimText(const std::string& text) 
{
  auto start = text.begin();
  auto end = text.end();

  while (start != end && std::isspace(*start))
    ++ start;
  
  do {
    -- end;
  } while (std::distance(start, end) > 0 && std::isspace(*end));

  return std::string(start, end + 1);
}

std::string Xml::trimText(const std::string& text) const
{
  auto start = text.begin();
  auto end = text.end();

  while (start != end && std::isspace(*start))
    ++ start;

  do {
    -- end;
  } while (std::distance(start, end) > 0 && std::isspace(*end));

  return std::string(start, end + 1);
}

void Xml::swap(Xml& other)
{
  clear();
  m_name.swap(other.m_name);
  m_text.swap(other.m_text);
  m_attributes.swap(other.m_attributes);
  m_children.swap(other.m_children);
}
