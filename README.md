```yaml
title: Effective C
subtitle: An Introduction to Professional C Programming
author: Robert C. Seacord
publisher: No Starch Press
year: 2020
```

## Ch. 1 Getting Started With C

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  if(puts("Hello, world!") == EOF){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
```

The standard library gives access to the exit codes.

```bash
cc -o hello.out hello.c
```

Behaviour:

- Implementation-Defined Behaviour - Like number of bits in a bite. Not defined by C standard but it is consistent and documented behaviour.
- Unspecified Behaviour - Like function parameter storage layout, the standard provides multiple options.
- Undefined Behaviour - Like dereferencing an invalid pointer value, typically erroneous and not defined by C standard.
  - Explicit and implicit.

## Ch.2 Objects, Functions, And Types

An object's _lifetime_ is the time during the program that it exists at an address.

**Parameters** are objects declared as part of the function declaration that acquire a value on entry to the function.
**Arguments** are comma-separated expressions in the function call expression.

You declare the arguments when you write the function, and pass in parameters when you call it.

```c
#include <stdio.h>

void swap(int a, int b) {
  int t = a;
  a=b;
  b=t;
  printf("swap: a=%d, b=%d\n", a, b);
}

int main(void) {
  int a = 21;
  int b = 17;

  swap(a, b);
  printf("main: a = %d, b = %d\n", a, b);
  return 0;
}
```

**Call-by-value** (AKA pass-by-value) means that parameters passed into a function are actually copied for use within that function. The `swap()` function above swaps its arguments, but because they are copies of that parameters passed into it, the original values in the `main()` fuction will remain the same.

A **pointer**, indicated by the unary `*` operator, tells C that we want the memory address of the object. The indirection `*` operator works to both declare pointers and dereference them. The memory address is the "reference", so by **dereference** we mean to obtain the objects assigned value, what is being stored at the address. Well, there might be more complicated scenarios where another address is stored at an address, but lets not run before we walk.

A pointer's variable name is apparently typically prefixed with the letter 'p'.

Additionally, the unary `&` operator does the opposite to a variable and obtains the reference value, or the memory address of the variable.

```C
int number = 42;
int pnumber = &number; // this is the memory address
int samenumber = *pnumber; // This returns value stored at memory address
```

```c
#include <stdio.h>

void swap(int *pa, int *pb) {
  int t = *pa;
  *pa = *pb;
  *pb = t;
  printf("swap: a=%d, b=%d\n", *pa, *pb);
  return;
}

int main(void) {
  int a = 21;
  int b = 17;

  swap(&a, &b);
  printf("main: a = %d, b = %d\n", a, b);
  return 0;
}
```

This works to actually switch the values because they are changing their address. Notice how the `*` operator is continuously used.

C has 4 types of scope:

- file
- block
- function prototype - I think this means arguments of function
- function

_Labels_ are identifiers followed by a colon, but will be covered more later. Just a heads up.

There are 4 storage durations, which determines an object's lifetime:

- automatic - declared in a block or something.
- static - objects delcared in file scope, lasts entire execution of code.
- thread - used in concurrent programming (not covered in this book).
- allocated - deals with dynamically allocated memory (later topic).

Scope applies to identifiers and lifetime applies to objects. Scope is a region and lifetime is a duration. Think space-time.

"However, it is good software engineering practice to limit the scope of an object wherever possible." Why might that be? Performance? Memory leaks?

**Alignment** represents the number of bytes between successive addresses at which a given object can be allocated. I am thinking like an array, one address and known alignment can make for some fast dereferencing. Typically this is not a worry, but there are some circumstances where you may need to override the compiler's default choices.

A stricter alignment, like a larger power of two, can be requested using the `_Alignas` keyword. I will include the example here because it's not apparently used anywhere else really in the book. Although, it looks like it utilizes several unexplained concepts so far...

```c
struct S {
    int i; double d; char c;
};

int main(void) {
    unsigned char bad_buff[sizeof(struct S)];
    _Alignas(struct S) unsigned char good_buff[sizeof(struct S)];

    struct S *bad_s_ptr = (struct S *)bad_buff; // wrong pointer alignment
    struct S *good_s_ptr = (struct S *)good_buff; // correct pointer alignment
}
```

Types include boolean, character, integer, and floating-point. 

```c
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

_Bool guity = 0;
bool innocent = false;

char = "a"; // only A-z & !-@
signed char = "b"; // can represent small signed integers
unsigned char = "c"; // can represent small unsigned values
wchat_t = "A"; // Wide character set for international letters

// You can omit 'int', except for the 'int' itself. (ie. `long` is ok)
short int = 1;
int = 2;
long int = 3;
long long int = 4;

unsigned short int = 1;
unsigned int = 2;
unsigned long int = 3;
unsigned long long int = 4;

enum day {sun = 0, mon = 1, tue, wed, thu, fri, sat };

float = 0.1;
double = 0.001;
long double = 0.0001;
```

You can use `bool` if you import the library. Else, use the `_Bool` keyword. C expects keywords beginning with an underscore to not be taken, so name variables accordingly.

The `<limits.h>` header file is for the numbers, as well as `<stdint.h>` and `<inttypes.h>`. 

**Enumerations**, or `enum`, are my favourite. The `enum` value defaults to 0, and increments for each additional `enum`. You can assign them duplicate values, but why?

Don't forget `void`, to represent absence of value. 

_Function types_ are derived from return type and number of and types of its parameters. Fun fact, the return type cannot be an array apparently. 

```c
int f1(void); 
int *f2(); // returns pointer to int
int f3(int a, int b); // arguments with identifiers
int f4(int, int); // also ok
```

"A function type with a parameter type list is known as a _function prototype_." It informs the compiler. 

Check this out:

```c
int max(int a, int b) {
    return a > b ? a : b;
}
```

Ternary operator `?` is explained later. 

**Derived Types** are types that are constructed from other types. Think pointers, arrays, structures, etc...

You can have a pointer to _void_, `void *vp;`?

You can also do this...

```c
int i = 42;
int *ip = &i;
ip = &*ip;
```

That is trying to find the reference of a dereferenced value. Basically, they cancel out. 

Note: bad things happen if pointers are not pointing to a valid object or function. 

An **array** is a _contiguously_ allocated sequence of objects that all have the same element type. I would have went with _data_ type, but the book says "element". I think because each value in an array is called an _element_. An array's type is denoted by the type of its elements and the number of elements.

```c
int arr[11];
float *afp[17];
```

It gets strange. `arr` apparently already represents the memory address, which is why you need to provide an index to get a value. As such, asking for the memory address at say index 5, `arr[5]` is the same as `arr + 5`. 

```c
int arr[4][2]
```

That's multidimensional arrays. Apparently C is good enough to multiply sizes of the array to store values in memory in one big line. 

The `typedef` keyword creates an alias for an existing type. It's strange, and the C standard reserves identifier that end in `_t`. So, doing that may cause collisions. 

The **Structure** type contains sequentially allocated member objects. Members have their own name and type. Use the _structure member_ `.` (dot) operator to reference property values of the structure. And, use the pointer `->` operator to reference members if you have pointer to a structure. That's interesting.

```c
#include <string.h>

struct dog {
    char name[20];
    int age;
    char error[100];
} doug, *doug_p

doug.age = 5;
strcpy(doug.name, "Doug");
strcpy(doug.error, "Keyboard Interruption");

doug_p = &doug; // we are storing the pointer

doug->age = 5; // store age via pointer
strcpy(doug->name, "Doug");
strcpy(doug->error, "Keyboard Interruption");
```

Not sure if the book forgot to mention, but [GeeksForGeeks](https://www.geeksforgeeks.org/strcpy-in-c/) shows that the `char* strcpy(char* destination, char* source)` is how we assign strings. And strings appear to be an array of characters. 

Sorry, there's also apparently this _null_ character we write as `'\0'`, that signals the termination of the string. Use `%s` to print a string and `%%` to print a "%", in case you ever need to. 
