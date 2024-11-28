# Getting Started

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

# Project 1. Ini File Parser

A lightweight and efficient INI file parser implemented in C++ for reading, writing and managing configuration files. This tool supports standard INI syntax, including section, key-value pairs, and comments.

## Features

- **Parse INI Files**: Read configuration files with support for sections and key-value pairs.
- **Section and Key Management**: Add, modify, or delete sections and keys.
- **Lightweight**: Designed with minimal dependencies and optimized for ease of use.

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

# Project 2. Json File Parser

A lightweight and efficient C++ library for parsing and manipulating JSON files.

## Features

- **JSON Value Types**: Supports all standard JSON value types, Null, Boolean, Number, String, Array, Object.
- **JSON File Parsing**: Reads JSON files and parses them into corresponding in-memory structures.

## Usage

1. Example code

```c
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
}
```

2. Run the Example

```bash
./jsonParser
```

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

# Project 3. XML File Parser

A powerful and versatile C++ library for parsing and manipulating XML files. This project provides two main classes:

1. Xml Class: Represents an XML node with attributes, child nodes, and text content.
2. XmlParser Class: Handles reading and parsing XML files into a structured Xml object.

## Features

- **XML Node Representation**

  - **Node Name and Text Content**: Get and set the name and text content of an XML node.
  - **Attributes**: Add, retrieve, and manage attributes by key.
  - **Child Nodes**: Append, access, and remove child nodes using index or name.
  - **Iteration**: Supports iteration over child nodes with standard iterators.
  - **Serialization**: Convert the XML node to a string with customizable indentation levels.

- **XML Parsing**
  - **Load XML Content**: Load XML content from a file or a string buffer.
  - **Parse XML Content**: Convert loaded XML content into an Xml object, representing the hierarchical structure of the XML file.
  - **Comments and Declarations**: Skips XML comments and declarations during parsing.

## Usage

1. Example code

```c
#include <iostream>
#include "utility/xml.h"
#include "utility/xml_parser.h"

using namespace melon::utility;

int main()
{
  XmlParser parser;
  parser.load("./../menu.xml");

  Xml menu = parser.parse();

  std::string name = menu["food"]["name"].getText();
  std::cout << "name=" << name << '\n';

  std::string price = menu["food"]["price"].getText();
  std::cout << "price=" << price << '\n';

  int calories = menu["food"]["name"].getAttribute("calories");
  std::cout << "calories=" << calories << '\n';

  for (auto it = menu.begin(); it != menu.end(); it++)
    std::cout << *it;

  return 0;
}
```

2. Run the Example

```bash
./xmlParser
```

3. Output

```bash
name=Belgian Waffles
price=$5.95
calories=650
<food>
  <name calories="650">Belgian Waffles</name>
  <price>$5.95</price>
  <description>Two of our famous Belgian Waffles with plenty of real maple syrup</description>
</food>
...
```

## API Reference

### Xml Class

- std::string getName() const: Get the node’s name.
- std::string getText() const: Get the node’s text content.
- void setName(const std::string& name): Set the node’s name.
- void setText(const std::string& text): Set the node’s text content.
- void addAttribute(const std::string& key, const std::string& value): Add an attribute to the node.
- Xml& operator[](const std::string& name): Access a child node by name.
- void appendChild(const Xml& child): Append a new child node.
- std::string toString(int depth) const: Convert the XML node to a string with customizable indentation levels.
- void save(const std::string& filename): Save the XML structure to a file.

### XmlParser Class

- void load(const std::string& filename): Load XML content from a file.
- void load(const char\* buf, int len): Load XML content from a string buffer.
- Xml parse(): Parse the loaded XML content and return an Xml object.

# Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature-name"`.
4. Push to your branch: `git push origin feature-name`.
5. Open a pull request.
