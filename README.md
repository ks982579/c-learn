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
+ Implementation-Defined Behaviour - Like number of bits in a bite. Not defined by C standard but it is consistent and documented behaviour.
+ Unspecified Behaviour - Like function parameter storage layout, the standard provides multiple options. 
+ Undefined Behaviour - Like dereferencing an invalid pointer value, typically erroneous and not defined by C standard.
    + Explicit and implicit.

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
+ file
+ block
+ function prototype
+ function