#include "utility/json_parser.h"

using namespace melon::utility;

void JsonParser::load(const std::string& filename)
{
  std::ifstream ifs(filename);
  std::ostringstream oss;
  oss << ifs.rdbuf();
  m_content = oss.str();
  m_index = 0;
}
       
void JsonParser::load(const char* buf, int len)
{
  m_content.assign(buf, len);
  m_index = 0;
}
 
Json JsonParser::parse()
{
  char ch = getNextChar();
  
  switch (ch)
  {
    case 'n':
      m_index -- ;
      return parseNull();
    case 't':
    case 'f':
      m_index -- ;
      return parseBool();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      m_index -- ;
      return parseNumber();
    case '"':
      return parseString();
    case '[':
      return parseArray();
    case '{':
      return parseObject();
    default: break;
  }
  throw std::logic_error("Unexpected Content!\n");
}

void JsonParser::skipWhiteSpace()
{ 
  while (m_content[m_index] == ' '
      || m_content[m_index] == '\r'
      || m_content[m_index] == '\n'
      || m_content[m_index] == '\t')
    m_index ++ ;
}

char JsonParser::getNextChar()
{
  skipWhiteSpace();
  if (m_index == m_content.size())
    throw std::logic_error("Illegal Format!\n");
  return m_content[m_index ++ ];
}

bool JsonParser::inRange(int x, int lower, int upper) const
{
  return (x >= lower) && (x <= upper);
}

Json JsonParser::parseNull()
{
  if (m_content.compare(m_index, 4, "null") == 0)
  {
    m_index += 4;
    return Json();
  }
  throw std::logic_error("Parse Null error!\n");
}
 
Json JsonParser::parseBool()
{
  if (m_content.compare(m_index, 4, "true") == 0)
  {
    m_index += 4;
    return Json(true);
  }
  else if (m_content.compare(m_index, 5, "false") == 0)
  {
    m_index += 5;
    return Json(false);
  }
  throw std::logic_error("Parse bool error!\n");
}

Json JsonParser::parseNumber()
{
  int pos = m_index;
 
  if (m_content[m_index] == '0')
    m_index ++ ;
  else if (inRange(m_content[m_index], '1', '9'))
  {
    m_index ++ ;
    while (inRange(m_content[m_index], '0', '9'))
      m_index ++ ;
  }
  else 
    throw std::logic_error("Invalid character in number.");

  if (m_content[m_index] != '.')
    return Json(std::atoi(m_content.c_str() + pos));

  m_index ++ ;
  if (!inRange(m_content[m_index], '0', '9'))
     throw std::logic_error("Invalid float number.");
  
  while (inRange(m_content[m_index], '0', '9'))
    m_index ++ ;

  return Json(std::atof(m_content.c_str() + pos));
}

std::string JsonParser::parseString()
{
  return "";
}

Json JsonParser::parseArray()
{
    return Json();
}

Json JsonParser::parseObject()
{
  return Json();
}

