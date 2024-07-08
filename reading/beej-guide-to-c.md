# Beej's Guide To C

## Credit

Original Source: https://beej.us/guide/bgc/html/split/index.html

# 2 - Hello World

Nice way of describing two kinds of comments
- `//` and `/* */`
- `#include` is from the C Preprocessor
	- Pulls the contents of another source file and copies it completely right there.
	- Then talks about two stages of compilation: preprocessor and compiler.
	- Everything after a `#` happens BEFORE the compiler gets a chance to do anything.
- "specialness" of `main` function
- Good to mention very basics of `gcc -o blah blah.c` to point out how compilation happens in real life (altho generally abstracted by some kind of build system)

# 3 - Variables and Statements

- Variables are human readable names that refer to some data in memory
- Memory as a big array of bytes, and data is stored in the array. Things that are too big for one byte are stored in multiple bytes.
	- Is this a good way of phrasing it still? It's probably a fair way of describing it if you qualify that modern memory is... way more complicated than this. But it gives you a good place to start at least, which is helpful for intro to C.
	- Also is nice because then we can use the ideas they already know about indexing into an array and tell them that that is a "memory address" or a "location in memory" or (gasp) "a pointer"

> A variable is a name for some data that's stored in memory at some address


Primary types:
- Integer, Floating point, character, string
- int, float, char, char *

More info then on `printf` and format strings.

Booleans are kind of just a lie (they are really just 0 is false, otherwise it's true)

Arithmetic operators and shorthand variants

Pre and post decrement, don't want to cover too much

boolean operators are good to mention most likely.

Never really thought of `sizeof` as an operator, but I do think that's a nice way to think of it (and probably the right way to think of it instead of just "special function").
- Returns `size_t` is good to mention.
- Oh what! You don't need parens around sizeof??
	- Oh, you don't need it for expressions, but you do need it for types. That's wild. C continues to surprise me :)

Conditionals, show that you can do the no braces thing for if's, but then say that they should always use them. This is my advice. It's just not worth the line savings and too many stupid errors from this. Already plenty of ways to shoot yourself in the foot in C IMO
- Does offer a good explanation though: "C is going to run one thing in an if-statement. Always "one-statement" - just sometimes the statement is a block of statements".
- This does seem to be a good explanation.

Switch statements are very limited - only can compare values directly. Also, don't forget the horrible `break` semantics, which I've already noted I think.
- Really only works for integers? Didn't know that, is that still the case for C23? Would be interesting to check out
- Makes sense then it would also work for `char` and `enum` since those are just integers with extra steps.
# 4 - Functions

Functions accept `arguments` and return a `value`.
- These arguments and types are predeclared
- While it's possible to tell Python that you say you're going to return an int with type hints, you're not really making the same promise you are with C (although there are plenty of other ways to break your promises in C...)

I do like this phrasing of `int n` takes one `int` argument stored in parameter `n`. I think this concept of talking about how things are `stored` is very useful to get them in the mindset of C.
- "A parameter is a special type of local variable into which the arguments are copied"
- I repeat, parameters are a copy of the argument. NOT THE ARGUMENT ITSELF.

`void` can be used to signify "nothing" in a sense - `int f(void)` means that it takes `no arguments`, or `void f(void)` means it returns no value.

They give a nice example of incrementing an integer, but probably would be more illustrative if they had the example first not be part of a function and the copy-pasted into a function - then you would see that the behavior changes because we've made it into a parameter

Function prototypes is the proper name for signatures or declarations. I think I always call them something else, but would be worth double checking that everyone is in agreement on the word "prototype"
- Huh, hadn't realized that it was different to use `void foo()` vs `void foo(void)` - compiler just throws away any type checking if no void is used? 
- [ ] Check out the compiler info for this
- [ ] Update all the empty parameter lists LUL

# 5 - Pointers

Nice point starting out saying that you may be familiar with the broader concept of pointers if you already understand that some variables are actually just a reference, or refers to an object of some type.
- Agreed on C making you have to be more explicit about this than you would have to be in other languages though (like Python, where you just pass it and more-or-less everything is a reference)

> A pointer is a variable that holds an address

I do think this is a pretty good definition.
- Thinking if there is some analogy about a postcard with an address on it or something like that, but i'm not sure.

This is a nice line:
> Just like an `int` variable can hold the value `12`, a pointer variable can hold the address of data.

Ha, I just love the tone of this:

> This means that all these things mean the same thing, i.e. a number that represents a point in memory:
> - Index into memory (if you’re thinking of memory like a big array)
> - Address
> - Location
> I’m going to use these interchangeably. And yes, I just threw _location_ in there because you can never have enough words that mean the same thing.

Last line cracks me up.

- `&` as the `address-of` operator is a great way to say it. I think additionally saying that you should be reading it that way in your head when you see the character `&` is also really powerful to help you understand.

Would be good to do something really simple to introduce this first with the parameter passing stuff, but then go back and do really simple example.

```c
int my_integer;
int *my_integer_pointer;
```

Then can show how we can do: `my_integer_pointer = &my_integer

- lol `de-pointering` is actually a good term though to use when introducing the concept of "de-referencing". This would... actually make things a bit more symmetric. I think it's fair to use it to help get the point across.
- "get access to the original variable" is probably also a nice phrase

```c
i = 10
*p = 20
```

... and eventually we get to the usefuleness of pointers: they are also copied when they are used as function parameters. but the nice thing about copying an address... is it still is the same address!!
- This is very different from copying an entire house! We just copied the way to find the house.
- I do think house is a nice analogy that we can continue using. We could create a struct of house, and then do the same idea I had originally of coordinate
- Oh nice haha, it's the same analogy he ends up using. It's a powerful analogy I think. Very easy to understand. Although I would keep that with the rest of the examples then, instead of moving back to integers. I think it's harder to see what's going on with integers.
	- Although using increment is quite nice.

NULL pointers and undefined behavior.
- Would be an OK time to perhaps introduce the concept of undefined behavior, and just tell them generally it's bad and should be avoided.
- Ha, nice to see billion dollar mistake referenced here as well of course. And a fair mention of it not being the worst sentinel value


# 6 - Arrays

Ha, I'm cracking up. "C only *barely* has arrays" is such a great way of describing the situation.

- When declaring an array, you give it a size. Size must be fixed (except for VLAs, but different day different story)
- Zero indexed

Can't get the length of an array, C doesn't encode the information.
- You would usually have to keep track of that in some other variable
- Can use sizeof... kind of. It will only work in the exact same scope. Doesn't even work as an argument.
- When you pass an array to a function, you just pass the pointer. Sizeof will measure the size of... the pointer.

Array initializers, already wrote a bunch down about this.
- can skip specifying the size if you use initializer

```c
// pointer to the array, or rather the first element of the array
pointer = &array[0]

// same as short hand
pointer = array

```

Don't think we need to do any multi-dimensional array stuff. Very far afield from the main points of what we're working on in C IMO (although it could be a good example of needing to know some stuff about memory layout)

# 7 - Strings

Just like C barely has arrays, C barely has strings :) They are also just pointers. Ha, and he says the same. it's great. Love this guide.

Good to talk about string literals for sure, that's the best place to start.

Assign to variable with not something like `string s = "hello";` but instead `char *s = "hello";` This is... subtly different from `char s[] = "hello";`. But the difference really only comes into play when you're trying to mutate the string. I'm not sure there are really any other meaningful differences they'd run into (and they likely wouldn't even run into this during the course)

Null termination:
- Pretty fair point about having to store the size, and then if you want longer strings you have to include larger size for the byte.
	- This used to be a much bigger deal than it is now
	- And you also still have to do it for every string.
	- Probably would make a different tradeoff now :)

`NUL` terminated - or the `NUL` character. `NUL` is different than `NULL` pointer.

Since strings are just pointers, assigning one to another just... copies the pointer. you have to use strcpy to copy one.

# 8 - Structs

the type name is `struct <name>`, not just `<name>`.

ha, didnt think about showing them, `(*ptr).field = value`. thats a nice stepping stone to the arrow operator.

If you're thinking about how we had to have a special function for strcpy, you might be wondering if we need something like `structcpy` - and the answer is yes and no. If all you want to do is directly copy as-is, you can just do an assignment. C will gladly copy the memory of the struct. The problem would be is that if you wanted to copy strings, pointers, etc inside, you may end up with not what you're looking for. So you'll need to consider what is stored in your struct to determine if you need a special copy function.

And to compare them, you really need to write a custom function that compares the fields.

# 10 - `typedef`

I like typedef for structs, so i guess count me in the 832,000 that disagree with beej on this one haha

I think we'll stick with `typedef struct {...} struct_t` naming for course. I think it's a helpful pattern and i've seen it somewhat regularly.

Agreed (generally speaking) on not typedefing random and crazy things.

# 11 - Pointer Arithmetic

These are equivalent

```c
a[b] == *(a + b)
```

The spec is specific, as always, declaring (in C11 §6.5.2.1¶2):
> `E1[E2]` is identical to `(*((E1)+(E2)))`

Looping over an array, can show with ints and then floats. Would be good to show how we can `add 1` to a float, but we're actually adding `add 1 * sizeof(float type)`.

You can pass either arrays or pointers to a function and it will work just fine. "Array/Pointer equivalence" - Wondering if that's the name everyone uses or not. I'm not sure of any weird edge cases we would run into throughout our course.

## Void Pointers

It's kind of like "generic pointers" in a sense - you don't know what the type of the thing is going to be. Instead, you can do something where you're going to operate on something and you might do it byte-by-byte (for example `memcpy`).

Some differences:
- Cannot do pointer arithmetic with void*
- Cannot dereference void*
- Cannot use arrow operator on void* (this is a secret dereference)
- Cannot do array notation (also a dereference)

That's because when C does all of these things, it **must know the size of the type that is being pointed to**... and we can't know that for void* !

Not sure how deep we want to go here, but it might be good to see how things convert to char * to be single bytes only and then can do pointer stuff again.

Would be fun to show `qsort`, not sure if in scope or not though. I think we'll get a lot of the same ideas from objects, but maybe we could implement qsort for our `object_t` type.

# 12 - Manual Memory Allocation

This is where C is going to start seeming wildly different from Python.
- Python has garbage collection, which means it collects all of the Javascript that you write.

C has some variables (automatic variables) that are allocated and de-allocated when going out of scope. For example, when you have an int that's part of the function stack, it takes up memory. And C makes sure to release that memory when you're done with the function.

But... what if you want something to live longer than a function or a particular block? How do make something last?

This is where manual memory allocation comes in. You can tell C, hey I want this many bytes (yes, you tell it how many bytes you want, not that you want a new record or something like that) and it will give you a pointer to that new block of memory (or NULL if it fails)
- These bytes will remain allocated until you explicitly free them (or your program exits)

`calloc` and `realloc` would probably be useful to show just to illustrate what `malloc` does and does not do. Also gives some good reminders about size in bytes vs size in elements.

# 15 - Conversions

`strto*` functions are nice to use for conversions, would like to use those instead of `atoi`, also, good example of using `out-pointer` style items to get another value back from C function.

# 16 - Type Qualifiers

`const` - make something a constant. can also be used in parameter lists for functions

`const int *p` = `int const *p`, but not equal to `int *const p`.

To not be able to modify the type as well as the variable, you need `const int *const p`

`restrict` definitely not worth it, but maybe `volatile` could be fun to mention, just because it's cool to talk about some hardware type things?

`static` two meanings:
- Block scope: there will only be one instance of this variable created and it will be shared between all calls to the function
- File scope: variable isn't visible outside of the particular source file (why did they use the same name for these?... it doesn't make any sense to me)

# 17 - Multiple Files

```c
#ifndef FILE_H
#define FILE_H

// ...

#endif
```

# 18 - Outside environment

It pains me to think we wouldn't do anything with `argc` and `argv`... but it might just have to be the case. I don't really want to go into handling command line stuff and all this other stuff. It would be nice and all, but it seems to be pushing away from what I really want them to be learning.

`main` is also special cased to not have to have return and some other stuff, which i find a bit goofy for C

# 19 - C Preprocessor

Already saw `#include`, but we can do `macros` now :) (which we kind of do with define the header and what not... but whatever, it's still kind of like the first time)

`#include <stdio.h>` -> system library, look where system libraries are
`#include "header.h"` -> my library, local files. Looks where things are relative to current directory.

Defining constants, `#define GREETING "Hello, world"`|

Probably worth showing the simplest of `#ifdef` for conditional compilation stuff, but would not delve into it more. Just to show as another concrete example (or perhaps the first step even before the conditional compilation of header files)

# 20 - Various unions and tricks

```c
union foo {
    struct {       // unnamed!
        int x, y;
    } a;

    struct {       // unnamed!
        int z, w;
    } b;
};
```

# Pointers to Pointers

This is a great chart, which i think does a nice job of demystifying what the operators do.

In terms of type, each time you `&`, that adds another pointer level to the type.

| If you have | Then you run | The result type is |
| ----------- | ------------ | ------------------ |
| `int x`     | `&x`         | `int *`            |
| `int *x`    | `&x`         | `int **`           |
| `int **x`   | `&x`         | `int ***`          |
| `int ***x`  | `&x`         | `int ****`         |

And each time you use dereference (`*`), it does the opposite:

| If you have | Then you run | The result type is |
| ----------- | ------------ | ------------------ |
| `int ****x` | `*x`         | `int ***`          |
| `int ***x`  | `*x`         | `int **`           |
| `int **x`   | `*x`         | `int *`            |
| `int *x`    | `*x`         | `int`              |
Didn't think you could do this:

```c
foo(&(int){3490});
```

LOL `_Generic` - why do they have to pick such ugly looking names?

# 35 - Incomplete Types

This is the correct name for what I've been referring to as "forward declarations" in C. It makes more sense to say completing a type though, if you give the entire definition. Don't know which I'll go with (or if we will even really cover it in the course, because it's more C shenanigans than usefulness for Memory Management)