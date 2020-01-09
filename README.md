# Require

[![Build Status](https://travis-ci.org/monolithed/Require.png)](https://travis-ci.org/monolithed/Require)

Require is a cross-platform file concatenator. <br />
The main objective of this module is to concatenate multiple files into one file or stream. <br />

## NOTE: This project is obsolete!

If you interested at this stuff, feel free to fork one and have a deep look in it!


## Synopsis:

```c++
// Loading data from files
bool load ( const T &file, [, const std::string &path = "" ] );

// Saving data to a file
bool save ( const std::string &name, [, const std::ios_base::openmode &mode = std::ios::binary ] );

// Used to split a string into an array of substrings
void split ( std::string value, const char &token, T result )

// Getting data as a string
std::string data;
```

## Using

**files/file_1.js:**

```javascript
var foo = function() {
	return 1;
};
```

**files/file_2.js:**

```javascript
var bar = function() {
	return 2;
};
```

**main.cpp:**

```c++
#include <iostream>
#include <list>
#include "../require.hpp"

int main()
{
	Require require;

	std::string path("./files/");
	std::string name("file_1.js;file_2.js");

	// Set file names
	std::list<std::string> file;
	require.split(name, ';', std::back_inserter(file));

	// load the file
	if (require.load(file, path)) {

		// Save data into the file
		if (require.save("./file.js"))
			std::cout << require.data << std::endl;
	}

	return 0;
}
```

**Compiling:**

```bash
g++ -Wall -O2 -s -o main main.cpp
./main
```

**Result:**

```javascript
var foo = function() {
	return 1;
};

var bar = function() {
	return 2;
};
```

## Additional info

Use specific flags:

```c++
std::ios_base::openmode mode = std::ios::app | std::ios::trunc | std::ios::ate;
require.save("./file.js", mode);
```

Choose containers you like: <br />

```c++
#include <list>

std::list<std::string> file;

file.push_back("file_1.js");
file.push_back("file_2.js");
```

Prepare strings before using: <br />

```c++
#include <list>

Require require;

std::string name("file_1.js;file_2.js;");
std::list<std::string> file;

require.split(name, ';', std::back_inserter(file));
```

## Tests:

NOTE: The code tested with GCC and Clang

```c++
make -C tests
```

<br />
<br />

* The Require module is licensed under the MIT (MIT_LICENSE.txt) license.

* Copyright (c) 2012 [Alexander Abashkin] (https://github.com/monolithed)
