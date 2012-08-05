# Require

<img src="http://habrastorage.org/storage2/b26/0ee/b62/b260eeb62faca9d226da501cdc1fa26d.png" alt="" />

Require is a cross-platform file loader module. <br />
The main objective of this module is to concatenate multiple files into one file or stream. <br />
Using a modular file loader you will improve the speed and quality of your code. <br />
<br />
NOTE: The code tested with GCC 4.2.1

##Synopsis:

```c++
// Loading data from files
bool Require::load ( const T &file, [, const std::string &path = "" ] );

// Saving data to a file
bool Require::save ( const std::string &name, [, const std::ios_base::openmode &mode = std::ios::binary ] );

// Getting data as a string
std::string Require::data;
```

## Using
*For example you could use the following code:*

**Files**:

```javascript
// files/file_1.js
var foo = function() {
	return 1;
};
```

```javascript
// files/file_2.js
var bar = function() {
	return 2;
};
```

**Code**:

```c++
#include <iostream>
#include <list>
#include "../require.hpp"

int main()
{
	Require require;

	std::string path("./files/");
	std::string name("file_1.js;file_2.js;");

	// Set file names
	std::list<std::string> file;
	require.split(name, ';', std::back_inserter(file));

	// load the file
	if (require.load(file, path))
	{
		// Save data into the file
		if (require.save("./file.js"))
			std::cout << require.data << std::endl;
	}

	return 0;
}
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

##Options:

*Data format 1* <br />
*NOTE: You can use any convenient container like: *array*, *list*, *vector*, *deque* and so on.*

```c++
#include <list>

std::list<std::string> file;
file.push_back("file_1.js");
file.push_back("file_2.js");
```

*Data format 2* <br />
*NOTE: If you have a ready string with file names, you can use the "*split*" method:*

```c++
#include <list>

Require require;

std::string name("file_1.js;file_2.js;");
std::list<std::string> file;
require.split(name, ';', std::back_inserter(file));
```

*Getting data*

```c++
require.data;
```

*Save data*

```c++
require.save("./file.js");
```

*Check a file saving*

```c++
if (require.save("./file.js"))
	std::string data(require.data());
```

*Append data*

```c++
require.save("./file.js", std::ios::app);
```

*Other file flags*

```c++
std::ios_base::openmode mode = std::ios::app | std::ios::trunc | std::ios::ate;
require.save("./file.js", mode);
```

*Compiling with GCC*

```bash
g++ -Wall -O2 -s -o main main.cpp
./main
```

<br />
<br />

* The Require module is licensed under the MIT (MIT_LICENSE.txt) license.

* Copyright (c) 2012 [Alexander Guinness] (https://github.com/monolithed)
