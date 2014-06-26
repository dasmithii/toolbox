Baseline provides utilities for C-based software projects. These consist of data structures, functions, and macros chosen by popular necessity.  If you find yourself re-implementing common algorithms or datatypes too frequently, this library may fit your needs.



### Installation
1. Clone this repository.
2. Enter its top-level directory.
3. Configure build scripts with CMake.
4. Install libraries globally.
```
git clone https://github.com/dasmithii/Baseline.git
cd Baseline
cmake .
make install
```


### Usage
When `make` is called, both static and shared libraries are generated. Thus, we have two possibilities:

##### (1) Static Include
1. Embed the archive file in your project somewhere.
2. Link against the included library.
3. `#include` it wherever needed, per usual.

##### (2) Shared Include
1. Link against `/usr/local/bin/baseline.so`.
2. Utilize `#include <baseline/FILE>` at will.
3. `#include <baseline/all.h>` will include all library files.



### Quick Reference
##### Data Structures
+ Dynamic Array
+ Linked List
+ Binary Search Tree
+ Trinary Search Tree
+ Hashtable
+ Bitset
+ Stack
+ Queue
 
##### Miscellaneous Utilities
+ Debugging
+ Error-handling
+ File I/O