# Overview
Baseline hopes to keep its interface as intuitive as possible, and strict conventions are helpful in this sense. If you're contributing to this library, follow these rules when writing code. If not, use them to quicken the API learning process.

In general, everything is made to look as object-oriented as possible.



# Type Definitions
Name structs and typedefs in front-capitalized camel-case form, like this:
```
typedef struct {
	int f1;
	int f2;
	// etc...
} MyStruct;
```



# Function Definitions
Regular camel case, as shown below.
```
void doSomething()
{
	printf("Hello, world!");
}
```

But if the function operates like a method, prefix its name with the type it works on and an underscore.
```
void Array_printContents(Array *self);
```



# Common Functionality
Many data structures are operated on similarly, and it's best to capitalize on similarity with naming conventions. Here are some widely-used terms, where X is an arbitrary type name.
1. X_init(X *self)
2. X_clean(X *self)
3. X_hook(X *self, size_t i)
4. X_fetch(X *self, size_t i, void *destination)


