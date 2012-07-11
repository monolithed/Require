# Require

Require is a file loader module. <br />
The main objective of this module is to concatenate multiple files into one. <br />
Using a modular file loader you will improve the speed and quality of your code. <br />
Also the Require provides a minification for file content. <br />
<br />
NOTE: The code tested with GCC 4.2.1

## Use
*For example you could use the following code:*

**Files**:

```javascript
// files/file_1.js
;(function() {
	console.log('File 1!');
}());
```

```javascript
// files/file_2.js
;(function() {
	console.log('File 1!');
}());
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
		// Get data
		std::string data(require.data(true));

		// Save data into the file
		if (require.save("./file.js"))
			std::cout << data << std::endl;
	}

	return 0;
}
```

**Result:**

```javascript
;(function() {console.log('File 1!');}());;(function() {console.log('File 2!');}());
```

*Data format 1*

```c++
#include <list>

std::list<std::string> file;
file.push_back("file_1.js");
file.push_back("file_2.js");
```

*Data format 2*

```c++
#include <list>

Require require;

std::string name("file_1.js;file_2.js;");
std::list<std::string> file;
require.split(name, ';', std::back_inserter(file));
```

**NOTE:**
You can use any convenient container like: *array*, *list*, *vector*, *deque* and so on. <br />
If you have a ready string with file names, you can use the "*split*" method <br />

<br />
<br />

* The Require module is licensed under the MIT (MIT_LICENSE.txt) license.

* Copyright (c) 2012 [Alexander Guinness] (https://github.com/monolithed)
