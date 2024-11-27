#include "utility/xml_parser.h"

using namespace melon::utility;

void XmlParser::load(const std::string& filename)
{
  std::ifstream ifs(filename);
  if (ifs.fail())
    throw std::logic_error("Load file failed: " + filename);
  
  std::ostringstream oss;
  oss << ifs.rdbuf();

  m_content = oss.str();
  m_index = 0;
}

void XmlParser::load(const char* buf, int len)
{
  m_content = buf;
  m_index = 0;
} 

Xml XmlParser::parse()
{
  skipWhiteSpace();
  if (m_content.compare(m_index, 5, "<?xml") == 0)
    if (!parseDeclaration())
      throw std::logic_error("Parse declaration error!\n");

  skipWhiteSpace();  
  while (m_content.compare(m_index, 4, "<!--") == 0)
  {
    if (!parseComment())
      throw std::logic_error("Parse comment error!\n");
    skipWhiteSpace();
  }

  if (m_content[m_index] == '<' && (std::isalpha(m_content[m_index + 1]) || m_content[m_index + 1] == '_'))
    return parseElement();

  throw std::logic_error("Parse element error!\n");
}

void XmlParser::skipWhiteSpace()
{
  while (m_content[m_index] == ' '
      || m_content[m_index] == '\r'
      || m_content[m_index] == '\n'
      || m_content[m_index] == '\t')
    m_index ++ ;
}
        
bool XmlParser::parseDeclaration()
{
  if (m_content.compare(m_index, 5, "<?xml") != 0)
    return false;
  
  m_index += 5; 
  std::size_t pos = m_content.find("?>", m_index);
  if (pos == std::string::npos)
    return false;
  
  m_index = (int)pos + 2;
  return true;
}

bool XmlParser::parseComment()
{
  if (m_content.compare(m_index, 4, "<!--") != 0)
    return false;

  int start = m_index;
  m_index += 4;
  std::size_t pos = m_content.find("-->", m_index);
  if (pos == std::string::npos)
    return false;

  m_index = (int)pos + 3;
  return true;
}

Xml XmlParser::parseElement()
{
  Xml element;
  m_index ++ ;
  const std::string name = parseName();
  element.setName(name);

  while (m_content[m_index] != '\0')
  {
    // >
    //  />
    // age = "17"
    // 
    skipWhiteSpace();
    if (m_content[m_index] == '/')
    {
      if (m_content[m_index + 1] == '>')
      {
        m_index += 2;
        break;
      }
      else
        throw std::logic_error("Parse empty element error!\n");
    }
    else if (m_content[m_index] == '>')
    {
      m_index ++ ;
      std::string text = parseText();
      if (!text.empty())
        element.setText(text);
    }
    else if (m_content[m_index] == '<')
    {
      if (m_content[m_index + 1] == '/')
      {
        std::string end_tag = "</" + name + ">";
        std::size_t pos = m_content.find(end_tag, m_index);
        if (pos == std::string::npos)
          throw std::logic_error("Parse end tag error: " + name);
        m_index = (int)(pos + end_tag.size());
        break;
      }
      else if (m_content.compare(m_index, 4, "<!--") == 0)
      {
        if (!parseComment())
          throw std::logic_error("Parse comment error!\n");
      }
      else
      {
        element.appendChild(parseElement());
      }
    }
    else
    {
      std::string key = parseAttrKey();
      skipWhiteSpace();
      if (m_content[m_index] != '=')        
        throw std::logic_error("Parse xml attribute error: " + key);
      m_index ++ ;
      skipWhiteSpace();
      std::string value = parseAttrVal();
      element.addAttribute(key, value);
    }
  }

  return element;
}

std::string XmlParser::parseName()
{
  int pos = m_index;
  if (std::isalpha(m_content[m_index]) || m_content[m_index] == '_')
  {
    m_index ++ ;
    while (std::isalnum(m_content[m_index])
        || m_content[m_index] == '_'
        || m_content[m_index] == '-'
        || m_content[m_index] == ':'
        || m_content[m_index] == '.')
      m_index ++ ;
  }
  return m_content.substr(pos, m_index - pos);
}

std::string XmlParser::parseText()
{
  int pos = m_index;
  while (m_content[m_index] != '<')
    m_index ++ ;
  return m_content.substr(pos, m_index - pos);
}

std::string XmlParser::parseAttrKey()
{
  int pos = m_index;

  if (std::isalpha(m_content[m_index]) || m_content[m_index] == '_')
  {
    m_index ++ ;
    while (std::isalnum(m_content[m_index])
        || m_content[m_index] == '_'
        || m_content[m_index] == '-'
        || m_content[m_index] == ':')
      m_index ++ ;
  }
  return m_content.substr(pos, m_index - pos);
}

std::string XmlParser::parseAttrVal()
{
  if (m_content[m_index] != '"')
    throw std::logic_error("Parse attribute value error!\n");
    
  m_index ++ ;
  int pos = m_index;
  while (m_content[m_index] != '"')
    m_index ++ ;
  
  m_index ++ ;
  return m_content.substr(pos, m_index - pos - 1);
}




