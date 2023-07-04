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

```bash
cc -o hello.out hello.c
```

## Ch.2 Objects, Functions, And Types

