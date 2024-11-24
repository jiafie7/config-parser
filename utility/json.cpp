#include "utility/json.h"

using namespace melon::utility;

Json::Json()
  : m_type(json_null)
{
}

Json::Json(DataType type)
  : m_type(type)
{
  switch (type)
  {
    case json_null:
      break;
    case json_bool:
      m_value.m_bool = false;
      break;
    case json_int:
      m_value.m_int = 0;
      break;
    case json_double:
      m_value.m_double = 0.0;
      break;
    case json_string:
      m_value.m_string = new std::string("");
      break;
    case json_array:
      m_value.m_array = new std::vector<Json>();
      break;
    case json_object:
      m_value.m_object = new std::map<std::string, Json>();
      break;
    default:
      break;
  }
}

Json::Json(bool value)
  : m_type(json_bool)
{
  m_value.m_bool = value;
}

Json::Json(int value)
  : m_type(json_int)
{
  m_value.m_int = value;
}

Json::Json(double value)
  : m_type(json_double)
{
  m_value.m_double = value;
}

Json::Json(const char* value)
  : m_type(json_string)
{
  m_value.m_string = new std::string(value);
}

Json::Json(const std::string& value)
  : m_type(json_string)
{
  m_value.m_string = new std::string(value);
}

Json::Json(const Json& other)
  : m_type(json_null)
{
  copy(other); 
}


Json::~Json()
{
}

std::string Json::str() const
{
  std::stringstream ss; 

  switch (m_type)
  {
    case json_null:
      ss << "null";
      break;
    case json_bool:
      ss << (m_value.m_bool ? "true" : "false");
      break;
    case json_int:
      ss << m_value.m_int;
      break;
    case json_double:
      ss << m_value.m_double;
      break;
    case json_string:
      ss << "\"" << *(m_value.m_string) << "\"";
      break;
    case json_array:
      ss << "[";
      for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); ++ it)
      {
        if (it != (m_value.m_array)->begin())
          ss << ",";
        ss << (*it).str();
      }
      ss << "]";
      break;
    case json_object:
      ss << "{";
      for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); ++ it)
      {
        if (it != (m_value.m_object)->begin())
          ss << ",";
        ss << "\"" << it->first << "\"" << ":" << it->second.str();
      }
      ss << "}";
      break;
    default:
      break;
  }
  return ss.str();
}

void Json::clear()
{
  switch (m_type)
  {
    case json_null:
    case json_bool:
    case json_int:
    case json_double:
      break;
    case json_string:
      if (m_value.m_string != nullptr)
      {
        delete m_value.m_string;
        m_value.m_string = nullptr;
      }
      break;
    case json_array:
      if (m_value.m_array != nullptr)
      {
        for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); ++ it)
          it->clear();
        delete m_value.m_array;
        m_value.m_array = nullptr;
      }
      break;
    case json_object:
      if (m_value.m_object != nullptr)
      {
        for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); ++ it)
          it->second.clear();
        delete m_value.m_object;
        m_value.m_object = nullptr;
      }
      break;
    default: break;
  }
  m_type = json_null;
}

void Json::copy(const Json& other)
{
  // clear();
  m_type = other.m_type;

  switch (m_type)
  {
    case json_null:
    case json_bool:
    case json_int:
    case json_double:
      m_value = other.m_value;
      break;
    case json_string:
      if (other.m_value.m_string != nullptr)
        m_value.m_string = new std::string(*(other.m_value.m_string));
      break;
    case json_array:
      if (other.m_value.m_array != nullptr)
      { 
        m_value.m_array = new std::vector<Json>();
        for (auto it = (other.m_value.m_array)->begin(); it != (other.m_value.m_array)->end(); ++ it)
          (m_value.m_array)->push_back(*it);
      }
      break;
    case json_object:
      if (other.m_value.m_object != nullptr)
      {
        m_value.m_object = new std::map<std::string, Json>();
        for (auto it = (other.m_value.m_object)->begin(); it != (other.m_value.m_object)->end(); ++ it)
          (*(m_value.m_object))[it->first] = it->second;
      }
      break;
    default: break;
  }
}

        
Json::operator bool()
{
  if (m_type != json_bool)
    throw std::logic_error("Type error, not bool.");
  return m_value.m_bool;
}

Json::operator bool() const
{
  if (m_type != json_bool)
    throw std::logic_error("Type error, not bool.");
  return m_value.m_bool;
}

Json::operator int()
{
  if (m_type != json_int)
    throw std::logic_error("Type error, not int.");
  return m_value.m_int;
}

Json::operator int() const
{
  if (m_type != json_int)
    throw std::logic_error("Type error, not int.");
  return m_value.m_int;
}

Json::operator double()
{
  if (m_type != json_double)
    throw std::logic_error("Type error, not double.");
  return m_value.m_double;
}

Json::operator double() const
{
  if (m_type != json_double)
    throw std::logic_error("Type error, not double.");
  return m_value.m_double;
}

Json::operator std::string()
{
  if (m_type != json_string)
    throw std::logic_error("Type error, not string.");
  return *(m_value.m_string);
}

Json::operator std::string() const
{
  if (m_type != json_string)
    throw std::logic_error("Type error, not string.");
  return *(m_value.m_string);
}


