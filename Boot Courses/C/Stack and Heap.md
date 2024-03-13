
- Can we use a real-world example for both of these first or along the way

Stacks are often described using the analogy of a spring-loaded stack of plates in a cafeteria.[[16]](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)#cite_note-Ball_1978-17)[[1]](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)#cite_note-clrs-2)[[17]](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)#cite_note-Godse_2010-18) Clean plates are placed on top of the stack, pushing down any plates already there. When the top plate is removed from the stack, the one below it is elevated to become the new top plate.

You've already seen the stack data structure - that is *related* to this (in the sense that this is a Last In, First Out kind of structure). But when we're talking about Memory, "The Stack" refers to something more specific than just the data structure.

Analogy:
- A stack of books
	- Yes, I know I'm using "stack" in the analogy of what a "stack" is... I'm AWARE
	- Points:
		- Must take top book off to look at next book (Last In, First Out)
		- Books can be different sizes and contain different data

Going to speak in generalities here, there are a few "excellent footguns C has in its massive collection of various foot-weaponry" - but we're not going to cover those here. I want to give a good feel for what generally happens, not worry about every edge case in C.

Stack Frames 
- Size of the frame is fixed for a particular function and known at compile time.
	- All the declared variables are placed on the stack (with their corresponding sizes)
- "arguments larger than the processor word size are copied, otherwise register/push vs the abi"
- You can think of the arguments getting copied into the stack frame.

Recall our earlier example:

%% START CODE: [[Boot Courses/C/examples/pointers_struct_no_pointer_02.c]] %%
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

You can see that the address of `coor` in the `coordinate_update_x` function IS DIFFERENT than the address in `main`.

So... if you're thinking of the stack as these books that contain the data required to execute a function, when we pop our last function off the stack, that data disappears.

This is why in the next example presented, when did:

%% START CODE: [[Boot Courses/C/examples/pointers_struct_using_pointer.c]] %%
```c
#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

void coordinate_update_x(coordinate_t *coor, int new_x) {
  printf("  INSIDE address: %p\n", coor);
  printf("  INSIDE BEFORE: coor.x = %d\n", coor->x);

  // Set x to new_x
  // coor->x = new_x;

  printf("  INSIDE AFTER : coor.x = %d\n", coor->x);
}

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};

  printf("Coordinate address: %p\n", &c);

  // BEFORE YOU RUN THIS, TAKE A GUESS WHAT IT WILL PRINT!
  // WRITE IT DOWN!
  printf("OUTSIDE BEFORE: c.x = %d\n", c.x);
  coordinate_update_x(&c, 10);
  printf("OUTSIDE AFTER: c.x = %d\n", c.x);

  // What is different?
}
```
%% END CODE %%

when we pass the pointer, it works! Because we copy the pointer value (which is the memory address) and then use that to set the updated value.

`&c` -> a value, the value just happens to be the memory address.

(TODO: Expand on this idea a little more, I think this example is really powerful in demystifying pointers)
# Heap

But we still have a problem. Let's say you have a program that takes a users input to give you a number.
And your goal is to return a repeated string of "MY STRING" times the number the user gave you...

```c
char *repeat_string(char *string, int count) {
  // You don't know how to do this yet!
}
```

In python, this is really easy `"MY STRING" * int(input())`... Not quite so easy in C :)

![[Pasted image 20240305120513.png]]

- What are some ways that won't work:

```c
char *repeat_string(char *string, int count) {
	char *new_string;
	for (int i = 0; i < count; i ++) {
		new_string = new_string + string;
	}
	return new_string;
}
```

This one seems least likely they would come up with
```c
char *repeat_string(char *string, int count) {
	char *new_string;
	for (int i = 0; i < count; i ++) {
		new_string = sprintf("%s%s", new_string, string);
	}
	return new_string;
}
```

```c
char *repeat_string(char *string, int count) {
	char repeated_string[strlen(string) * count]; // Something like this...
	// inside stuff
	return repeated_string
}
```

What if I told you there was a function called `strcpy`:
- https://linux.die.net/man/3/strcpy

```c
char *repeat_string(char *string, int count) {
	char *new_string;
	for (int i = 0; i < count; i ++) {
		strcpy(new_string[strlen(string) * i], string);
	}

	return new_string;
}
```

And so even if any of these actually compiled.... We'd still have the problem that we have shown already. All of the values that you're using with `new_string` are on the Stack. And what happens to the stack, when we're done with this function?
- THEY ALL GONE!!

We need to introduce a new concept - dynamic memory allocation. Up until now, everything you've done in C has all been "stack allocated memory". So, when you declare variables like `int x = 7`, that is stack memory allocation. 

The common way of dynamically allocating memory in C is using `malloc`. 

We definitely need to explain malloc a bit more before we hop into the code:
- `void *malloc(size_t size);`

if we think of the heap as a big block of bytes, then you can imagine malloc as reserving some contiguous region (or a range of indexes) in that array . It returns a pointer to the start of that region.
- You should not assume everything is 0'd in this array (keyword: uninitialized)
- Important to mention something about casting here.
	- `malloc` does not know anything about what you plan on storing in the contiguous region (or maybe: "what the bytes represent). It "simply" allocates the size that you ask it for. It's up to you make sure you've both calculated the size correctly and casted the return value to the correct type 
- Malloc can fail -- should check for NULL when you use malloc

![[Stack and Heap 2024-03-05 13.04.06.excalidraw]]
- Should draw some individual pictures of different `malloc`s that we could do. Definitely want:
	- `int *` -> pointer to a single int (which will only take up one)
	- `char *` -> pointer for a "array of chars". The value is the start address of said list
	- `coordinate_t *` -> pointer to single, dynamically allocated coordinate_t

(chunk vs blob vs array: i think blob might be better)

%% START CODE: [[Boot Courses/C/examples/05_heap.c]] %%
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

char *repeat_string(char *str, int count) {
  // you have, char *str
  //    in memory, that's like:
  //
  //    'h' 'e' 'l' 'l' 'o' '\0'
  //     ^ str

  // So... how do we **dynamically** get to be able to do
  // something like:
  //
  //    'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' '\0'
  //     ^ repeated_str

  // GOTCHA MOMENT!!!!!!!! This isn't big enough
  //    This would be a good multiple choice question here
  //    TODO: Decide if we should do something like sizeof(char) here too
  char *repeated_str = malloc(strlen(str) * count + 1);

  // We can set up this loop, and leave the two indexes unfilled
  // for them to fill out
  int length = strlen(str);
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < length; j++) {
      repeated_str[i * length + j] = str[j];
    }
  }

  repeated_str[count * strlen(str)] = '\0';

  return repeated_str;
}

int main() {
  // Up until now, everything we've done has ONLY been on the `stack`.
  //
  // What's the stack?

  // OR

  // Up until now, we've always had a set amount of structs, items, etc
  // that were allocated on the stack.

  // Ok, up until now, you've always had a set amount of structs, items, etc
  coordinate_t c1 = {.x = 1, .y = 1, .z = 1};
  coordinate_t c2 = {.x = 2, .y = 2, .z = 2};

  // But what if we wanted to have more than these? Does this work
  int count = 5;
  char x[] = "hello";
  char *repeated = repeat_string(x, count);

  // This turns out to be really bad...
  //    Good video opportunity
  //    We can show the memory getting bigger and bigger...
  //    and never going down
  for (int i = 0; i < 1000000; i++) {
    repeat_string(x, count);
  }

  // How can we do what happens in Python?
  //    When we do a loop in python, we don't have to
  //    do anything explicitly to give the memory back
  //
  // Can we show some GC profiling or something else in Python
  // to make it clear that it's not cost-less to do the GC work
  // in Python (don't know if i wanna say Free, cause we're teaching
  // what free() does in C)

  // We need to free the memory
  char *allocated_string = repeat_string("<this is allocated>", 3);
  free(allocated_string);

  // What to talk about with free:

  // - System can reclaim the memory
  //    In this loop now, instead of never releasing the
  //    memory, we're going to release it after each loop
  //    back to the system.
  for (int i = 0; i < 1000000; i++) {
    char *allocated_string = repeat_string("<this is allocated>", 3);
    printf("Allocated: %s\n", allocated_string);

    // This is the important part of what's going on
    free(allocated_string);
  }

  // If we don't call free, the memory will not go back
  // to the system until the program ends
}
```
%% END CODE %%

We want to repeat: "STR" 3 times

`malloc(strlen("STR") * 3 + 1)`

| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| ?   | ?   | ?   | ?   | ?   | ?   | ?   | ?   | ?   | ?   |

After one loop:

| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 'S' | 'T' | 'R' | ?   | ?   | ?   | ?   | ?   | ?   | ?   |

After two loop:

| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 'S' | 'T' | 'R' | 'S' | 'T' | 'R' | ?   | ?   | ?   | ?   |

After three loop:

| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 'S' | 'T' | 'R' | 'S' | 'T' | 'R' | 'S' | 'T' | 'R' | ?   |

Then don't forget to set the last value to `\0`: Finally

| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9    |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | ---- |
| 'S' | 'T' | 'R' | 'S' | 'T' | 'R' | 'S' | 'T' | 'R' | '\0' |

But!... we have a big problem, imagine we do this:

%% START CODE: [[Boot Courses/C/examples/heap_loop_no_free.c]] %%
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *repeat_string(char *str, int count) {}

int main() {
  // But what if we wanted to have more than these? Does this work
  char *repeated = repeat_string("STR", 5);

  // This turns out to be really bad...
  //    Good video opportunity
  //    We can show the memory getting bigger and bigger...
  //    and never going down
  for (int i = 0; i < 1000000; i++) {
    repeat_string("STR", 3);
  }
}
```
%% END CODE %%

TODO: Record something for this and show memory usage growing and growing....

Now we need to introduce you to another important topic.
- When we were discussing the stack, we mentioned that whenever you're done with the current function, it automatically "pops the stack frame" off the top and (roughly) clears everything that was there.
- But... when we allocate something on the heap, no one cleans it up for us. It's gonna stay there until we say "I don't need this anymore" OR your program completes.
	- This is (one of) the causes of memory leaks

So now we need some tool to tell the Operating System that we're all done with this memory.
- the way we do this is with `free()`

Good meme for this exact scenario: https://www.youtube.com/watch?v=1stQbTuUBIE

%% START CODE: [[Boot Courses/C/examples/heap_loop_yes_free.c]] %%
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *repeat_string(char *str, int count) {}

int main() {
  // But what if we wanted to have more than these? Does this work
  char *repeated = repeat_string("STR", 5);

  // Now, since we're freeing on every iteration, we don't explode the memory!
  for (int i = 0; i < 1000000; i++) {
    char *repeated = repeat_string("STR", 3);

    // Do some useful work with the repeated string...
    printf("Repeated: %s\n", repeated);
    // ... and free it when we're done with it

    free(repeated);
  }
}
```
%% END CODE %%

TODO: Could be nice to do an example where we show realloc in a loop instead.
- It's not exactly the same, but we could mention something like object pooling as something fun for them in gc lang type ideas...


-------
Potential Later example:
- Stack is small
- Heap is big
- Don't do `foo[1000000]`, instead allocate that to heap and use it.


Keep away from "fast vs slow" for stack vs heap, at least for now
- Heap allocation is "slow" -> you have to request memory from the OS
- Maybe worth mentioning things like indireciton, cache locality, etc