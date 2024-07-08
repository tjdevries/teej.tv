
This is the first introduction to pointers
- (This one doesn't show addresses, but we'll show it in part 2)

%% START CODE: [[pointers_struct_no_pointer_01.c]] %%
```c
#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

// Finish this function (I KNOW THIS WONT WORK)
void coordinate_update_x(coordinate_t coor, int new_x) {
  printf("  INSIDE BEFORE: coor.x = %d\n", coor.x);

  // TODO(you!): Set x to new_x
  coor.x = new_x;

  printf("  INSIDE AFTER : coor.x = %d\n", coor.x);
}

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};

  // BEFORE YOU RUN THIS, TAKE A GUESS WHAT IT WILL PRINT!
  // WRITE IT DOWN!
  printf("OUTSIDE BEFORE: c.x = %d\n", c.x);
  coordinate_update_x(c, 10);
  printf("OUTSIDE AFTER: c.x = %d\n", c.x);
}
```
%% END CODE %%


In the last section, we saw that when we tried to update the field of a `coordinate_t`, but we found that the value was "lost" once we left the function.

This is quite different from what you expect from Python. Whenever you pass an Object in Python, you pass it by "reference".

But in C, when you pass a struct, you pass it by value. This means that it gets *copied* into the function's scope.

- You can see this by looking at the addresses in

%% START CODE: [[pointers_struct_no_pointer_02.c]] %%
```c
#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

// Finish this function (I KNOW THIS WONT WORK)
void coordinate_update_x(coordinate_t coor, int new_x) {
  printf("  INSIDE address: %p\n", &coor);
  printf("  INSIDE BEFORE: coor.x = %d\n", coor.x);

  // TODO(you!): Set x to new_x
  coor.x = new_x;

  printf("  INSIDE AFTER : coor.x = %d\n", coor.x);
}

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};
  printf("Coordinate address: %p\n", &c);

  // BEFORE YOU RUN THIS, TAKE A GUESS WHAT IT WILL PRINT!
  // WRITE IT DOWN!
  printf("OUTSIDE BEFORE: c.x = %d\n", c.x);
  coordinate_update_x(c, 10);
  printf("OUTSIDE AFTER: c.x = %d\n", c.x);
}
```
%% END CODE %%

This is why when you update the field of a struct, the original value is still there when we leave the function -- we didn't change what was stored in memory for the original value.

So what we need, is some way to pass a *reference* to the structure, so that when we can modify the memory location and have those changes be reflected in the original struct.

This is where pointers come in.

Pointer Syntax: (not sure how I want to say this)
 `&`: Get a reference (or pointer) to something
 `*`: Dereference a pointer

Definitely need to use the word "address" but not sure when
to bring it into the equation for them.

```
(One thing to think about is explaining:
     int *x;

     vs

     void something(int *x);
     something(&x);

 They don't "match" - you use * in declaration, but & in practice
 I think that can sometimes be confusing for newcomers.

 Instead need to find some way to say that the function is saying
```



 ```
 Further notes:
     - Definitely need to talk about int* x, int *x
         - With this, should mention: int* x, y; is not what you expect :)
     - &foo != foo != *foo
```




- Reference vs pointer
	- `t[1]` -> reference )
	- References are essentially an alias for an existing variable, and Pointers are variables that store memory addresses. Thats how i'd explain it



```c
swap(void *vp1, void *vp2, int size)

// char *

char *s1 = strdup("one");
char *s2 = strdup("two");

// Good
swap(&s1, &s2, sizeof(char *));

// Bad
swap(s1, &s2, sizeof(char *));
swap(&s1, s2, sizeof(char *));
swap(s1, s2, sizeof(char *));
```