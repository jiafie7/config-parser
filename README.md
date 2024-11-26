# Ini File Parser

A lightweight and efficient INI file parser implemented in C++ for reading, writing and managing configuration files. This tool supports standard INI syntax, including section, key-value pairs, and comments.

## Features

- **Parse INI Files**: Read configuration files with support for sections and key-value pairs.
- **Section and Key Management**: Add, modify, or delete sections and keys.
- **Lightweight**: Designed with minimal dependencies and optimized for ease of use.

## Getting Started

1. Prerequisites

- C++ 11 or later

2. Clone the Repository

```bash
git clone https://github.com/jiafie7/config-parser.git
cd config-parser
```

3. Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1. Example code

```c
#include "utility/ini_parser.h"

using namespace melon::utility;

int main()
{
  IniParser parser;
  parser.load("./../config.ini");

  // Access values
  std::string host = parser.get("Network", "Host");
  int port = parser["Network"]["Port"];
  std::cout << "Host: " << host << "\nPort: " << port << std::endl;

  // Add values
  parser.set("Network", "Port", 3360);
  port = parser["Network"]["Port"];
  std::cout << "Host: " << host << "\nPort: " << port << std::endl;

  // Save to file
  parser.save("./../new.ini");

  return 0;
}
```

2. Run the Example

```bash
./iniParser
```

3. Output

```bash
Host: 127.0.0.1
Port: 8080
Host: localhost
Port: 3360
```

## API Reference

- bool load(const std::string& filename): Load an INI file.
- bool save(const std::string& filename): Save the current configuration to an INI file.
- std::string get(const std::string& section, const std::string& key): Get a value by section and key.
- void set(const std::string& section, const std::string& key, const std::string& value): Set a value in a section.
- void remove(const std::string& section): Remove an entire section.
- void remove(const std::string& section, const std::string& key): Remove a key from a section.

## INI File Syntax

1. Example INI file

```
[Network]
Host = localhost
Port = 8080

[User]
Name = John Doe
Role = Admin
```

- Sections are defined with square brackets: `[SectionName]`.
- Key-value pairs are formatted as `key = value`.
- Comments begin with `#` or `;`.

# Json File Parser

A lightweight and efficient C++ library for parsing and manipulating JSON files.

## Features

- **JSON Value Types**: Supports all standard JSON value types, Null, Boolean, Number, String, Array, Object.
- **JSON File Parsing**: Reads JSON files and parses them into corresponding in-memory structures.

## Usage

1. Example code

````c
#include <iostream>

#include "utility/json.h"
#include "utility/json_parser.h"

using namespace melon::utility;

int main()
{

  JsonParser parser;
  parser.load("./../data.json");
  Json data = parser.parse();
  std::cout << data << '\n';

  std::cout << data.get("code") << '\n';
  std::cout << data["message"] << '\n';

  std::cout << data["language"] << '\n';
  data["language"].append("Spanish");
  std::cout << data["language"] << '\n';

  std::cout << data["data"] << '\n';
  std::cout << data["data"]["photo"] << '\n';
  data["data"].remove("photo");
  std::cout << data["data"] << '\n';

  return 0;
}```

2. Run the Example

```bash
./jsonParser
````

3. Output

```bash
{"code":123,"data":{"email_verified":1,"isLogin":true,"photo":"https://p5.itc.cn/q_70/images01/20210417/72ee06e84779415b947272df4dfec1f1.jpeg"},"language":["Chineses","English"],"message":"welcome!"}
123
"welcome!"
["Chineses","English"]
["Chineses","English","Spanish"]
{"email_verified":1,"isLogin":true,"photo":"https://p5.itc.cn/q_70/images01/20210417/72ee06e84779415b947272df4dfec1f1.jpeg"}
"https://p5.itc.cn/q_70/images01/20210417/72ee06e84779415b947272df4dfec1f1.jpeg"
{"email_verified":1,"isLogin":true}
```

## API Reference

### Json Class

- void append(const Json& value): Appends a value to a JSON array.
- bool has(int index): Check whether index i in the array is valid.
- Json get(int index): Query the element with index i in the array.
- void remove(int index): Removes the element at index i from the array.
- Json& operator[](int index): Query the element with index i in the array.
- bool has(const std::string& key): Check whether key in the object is exist.
- Json get(const std::string& key): Query the element with key in the obeject.
- void remove(const std::string& key): Removes the key-value with key from the object.
- Json& operator[](const std::string& key): Query the element with key in the object.

### JsonParser Class

- void load(const std::string& filename): Load a JSON file.
- Json parse(): Parses a JSON file and returns a Json object.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature-name"`.
4. Push to your branch: `git push origin feature-name`.
5. Open a pull request.
