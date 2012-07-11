# Require

Require is a file loader module. <br />
Using a modular file loader you will improve the speed and quality of your code. <br />
Also the Require provides a minification for file content. <br />
<br />
NOTE: The code tested with GCC 4.2.1

## Use
*For example you could use the following code:*

**Files**:

```javascript
// file_1.js
;(function() {
	console.log('File 1!');
}());
```

```javascript
// file_2.js
;(function() {
	console.log('File 1!');
}());
```

**Code**:

```c++
#include <iostream>
#include "require.hpp"

int main () {
	Require require(true);    // optional, minify
	Require::delimiter = ';'; // optional, delimiter

	std::string path("./");   // optional, path
	std::string file("file_1.js;file_2.js;");

	std::cout << require.load(file, path) << std::endl;

	return 0;
}
```

**Result:**

```javascript
;(function() {console.log('File 1!');}());;(function() {console.log('File 2!');}());
```

* The Require module is licensed under the MIT (MIT_LICENSE.txt) license.

* Copyright (c) 2012 [Alexander Guinness] (https://github.com/monolithed)
