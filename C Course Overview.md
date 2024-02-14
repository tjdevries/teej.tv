## Target Audience:
- Boot.dev user
- They've done:
	- Some python
	- basic data structures / algos
	- some stuff w/ the terminal
	- a few smaller personal projects
	- (This course is planned to be between the JS and Go Courses)
- Will be compiling almost exclusively in browser
	- So focused more on language, rather than local computer setup/build/etc
	- See more about why in the Goals section


NOTE: My expectation is that most of the students will never write C again after the course and almost certainly not write C professionally.

## Goals for the Course

Overarching Idea: I want to **expose** them to C, but I don't need them to **master** C

- This is not:
	- a "Everything you need to be a professional C developer"
	- a "Everything you need to build a C application"
		- This includes compiler flags, build systems, etc
	- a "You now can read random C projects easily"
		- There are a lot of "C idioms" that are regularly used that are powerful but do not lend themselves to easy reading.
- The primary goals are:
	- You get a taste of a non-gc language (i.e. memory UN-safety)
	- (The projects give you) a basic understanding of how a garbage collector works
		- Or more broadly, just thinking about memory at all
		- This is more likely to be a problem for people who have never written a non-GC lang
	- (not how I want to say it) Learning C can help you understand and see its inspiration through many other popular programming languages (syntax/design/naming/etc)
 - Things I'm trying to avoid:
	 - Idiosyncrasies about C that you would discover if you write a lot of C, but are not evident in simple programs
	 - Not going to go deep into build systems (or maybe even cover more than as a mention)
	 - Things like conditional compilation
		 - Don't care about OS specific stuff or managing that kind of complexity in this course
	 
## Next steps after the course:
- You either take:
	- Go course
	- Rust course
	- (or both)

## Course Outline:
- History of C / What's the point?
	- Motivating example and information about the course
	- You're definitely using stuff that's written in C right now!
	- Learning C can help you better understand many programming concepts more explicitly
	- "You'll understand better how computers work"
		- This one i'm always a bit hesitant on, because C is also kind of lying to you :)
		- Cache hits, pipelining, etc
		- Maybe better: "You'll understand better how computer memory works, regarding programming languages"
	- After finishing this course, some potential projects you could try on your own would be:
		- TODO

- Some basic words:
	- Compiled
	- Statically type
	- Manual Memory Management (a.k.a no GC)
- Structure of a simple program
	- `int main() {...}`
- Simple types
	- int
	- char
- Control flow
	- if statements, loops, functions, return
	- switch/case statements

```python
if something():
  stuff()
```

```c
if (something()) {

}
```
- Function Syntax
- Structs
	- Thinking it's nice to do this before pointers, because then we can show how you would update one and contrast that with something like javascript, where you're always passing the object "by reference".
		- IBM uses "pass-by-pointer" instead of "pass-by-reference"
		- https://www.ibm.com/docs/en/xl-c-aix/13.1.2?topic=calls-pass-by-pointer
	- Pass by reference, pass by value
		- Are there better C terms for this?
	- `sizeof(T)`
	- Padding / alignment
- Intro to Pointers
- Arrays
- Strings
	- Would be good to give concrete example, but probably need to show both Pointers & Arrays first before we can get there
	- Definitely want to show some of the stdlib string functions and some easy things that can make them fail
- Pointer-Pointers (not sure if there is better name for this idea)
- Stack / Heap
	- Do we introduce this concept before we introduce malloc/free?
	- Perhaps we introduce them at the same time?
- Error Handling
	- How to do "try-catch" in C?
		- There is no language feature for this
	- `goto cleanup`
- Advanced Structs
	- `enum`
	- `union`
- Implementing the refcount GC
- Implementing the mark-and-sweep GC
- Conclusion:
	- Here's some things you could explore more if you liked this course
		- Multithreading (if you don't value your sanity)


- Open Questions:
	- When should we do `enum` and `union` items?
		- We definitely need them or the GC part
	- When to include `#include` information? We need it basically right at the start to be able to start printing things, but it seems a bit early to explain.
		- I don't love hand-waving things at the beginning. Perhaps we can just include it and explain line-by-line what is going on?
		- I suppose that means we should mention c standard library as well. We'll definitely be referring to it when we do stuff with strings again
	- nully-ifying vs actually freeing
	- man pages
	- gdb / valgrind / etc
	- static / globals / const
	- 10 rules of nasa



I especially mean the difference between:
1. void * returnsAllocated().
2. size_t expectsPointer(void *struct). 
3. expectsAllocatedSize(void *struct, size_t size)… etc…


All of the different alloc functions
- realloc already used in object stuff
- alloca
- calloc

 https://github.com/jart/cosmopolitan
**** 
Notes:
- Should pick a style for naming structs and make sure that we're consistent throughout the course.
	- I don't have a strong preference

- C is high-level and low-level, depending on your vantage point
	- It's a low-level language because you have to think about memory management, you don't have as many language features as other languages, no objects, etc
	- But it's a high-level language in the sense of what it replaces -- writing assembly directly

