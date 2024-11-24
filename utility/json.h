#pragma once

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace melon
{
  namespace utility
  {
    class Json
    {
      public:
        enum DataType
        {
          json_null = 0,
          json_bool,
          json_int,
          json_double,
          json_string,
          json_array,
          json_object,
        };

        Json();
        Json(DataType type);
        Json(bool value);
        Json(int value);
        Json(double value);
        Json(const char* value);
        Json(const std::string& value);
        Json(const Json& other);
        ~Json();

        friend std::ostream& operator<<(std::ostream& os, const Json& other)
        {
          os << other.str();
          return os;
        }

        operator bool();
        operator bool() const;
        operator int();
        operator int() const;
        operator double();
        operator double() const;
        operator std::string();
        operator std::string() const;

        void clear();

      private:
        std::string str() const;
        void copy(const Json& other);

      private:
        union Value
        {
          bool m_bool;
          int m_int;
          double m_double;
          std::string* m_string;
          std::vector<Json>* m_array;
          std::map<std::string, Json>* m_object;
        };

        DataType m_type;
        Value m_value;
    };
  }
}
