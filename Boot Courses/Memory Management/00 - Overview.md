
Thoughts for the course:
- Up until now, the student has only seen garbage collected languages and likely hasn't even considered much about memory (see, all of javascript devs)
- OK... so we need to introduce this to them



- Talk about GC (and a few GC strategies - mark & sweep vs. ref counts)
        - mark & sweep
        - ref counts
        - generational gc (OCaml Kreygasm)
            - smaller heap (survive a generation to get moved to the larger one)
            - larger heap
        - memory arenas
        - jvm gc
            - https://www.baeldung.com/jvm-zgc-garbage-collector
            - https://github.com/Maoni0/mem-doc/blob/master/doc/.NETMemoryPerformanceAnalysis.md
            - https://docs.python.org/3/extending/extending.html#reference-counting-in-python
    - Talk about manual memory management
        - This is somewhat "intro to C"
    - Talk about "lifetime" (sneaky rust)




- Reasons to care about memory:
	- Resources
	- Speed of access (it would be cool to talk about caches)

	
Randall Hyde's "Art of Assembly" or chapter 6 of No Starch's "Writing Great Code vol. 1"

https://www.youtube.com/watch?v=LfaMVlDaQ24&t=32473s

https://pythontutor.com/

Questions
- "Does the compiler decide if a variable will be garbage collected?"



Some older thoughts from before:

(Lane puts "Coming Soon" Courses in the curriculum?)
(Lane puts a "which course made you sign up" selection?)

- malloc and free
- pointers
- stack and heap
- RAII ? Probably too advanced for this

Garbage Collection strategies:
- Mark and sweep
- Reference counting
- Generational GC (OCaml ;))

Probably worth mentioning Rust's strategy and then saying we won't really cover it until you actually get to the rust section of the course materials.


https://www.hboehm.info/gc/