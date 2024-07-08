---
permalink: /c-course
---
Use [boot.dev/teej](https://boot.dev/teej) for 25% off :)
## Course Outline:

1. [[Goals of the Course]]
2. [[History of C]]
3. [[Overview of C]]
4. [[Structure of a Simple Program]]
5. [[Simple Types]]
6. [[Control Flow]]
7. [[Operators and Expressions]]
8. [[Simple Functions]]
9. [[Structs]]
10. [[Pointers]]
11. [[Arrays]]
12. [[Strings]]
13. [[Stack and Heap]]
- Pointer-Pointers (not sure if there is better name for this idea)
	- Sometimes called 2-star pointers
- Error Handling
	- How to do "try-catch" in C?
		- There is no language feature for this
	- `goto cleanup`
- Advanced Structs
	- `enum` [[Enums]]
	- `union` [[Unions]]
- Reallocating
- Building out "Objects"
- Implementing the refcount GC
- Implementing the mark-and-sweep GC
- Conclusion:
	- Here's some things you could explore more if you liked this course
		- Multithreading (if you don't value your sanity)
- [[Closing Thoughts]]

## Next steps after the course:
- You either take:
	- Go course
	- Rust course
	- (or both)


## Open Questions

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
- bitwise operations
- How to read C types
	- https://c-faq.com/decl/spiral.anderson.html
- RSS / virtual / reserved memory
- Talk about different types likes size_t, intpr_t, etc
- `typedef unsigned char byte`
	- Using typedef outside of structs
	- Could be good as an example compared to `#define`



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



```c
if ((((x)))) {

}
```