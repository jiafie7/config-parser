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

