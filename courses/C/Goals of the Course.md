- [ ] Record a video for this.
	- Ideally should be short and to the point, but want to explain this in words to give the proper pitch why I think it can be very helpful to explore C, even if you're never going to write it again.

Overarching Idea: I want to **expose** them to C, but I don't need them to **master** C

- This is not:
	- a "Everything you need to be a professional C developer"
	- a "Everything you need to build a C application"
		- This includes compiler flags, build systems, etc
	- a "You now can read random C projects easily"
		- There are a lot of "C idioms" that are regularly used that are powerful but do not lend themselves to easy reading.
- The primary goals are:
	- Understand basics of manual memory management
	- Understand basics of garbage collection (via implementing garbage collection projects)
	- Expose students to thinking about memory in a way they haven't up until now
	- Side benefit: Learning C can help students see how it has impacted many other languages
 - Things I'm actively avoiding:
	 - Idiosyncrasies about C that you would discover if you write a lot of C, but are not evident in simple programs
	 - Build systems
		 - They don't serve the primary goals of this course, even though they are required for real-world C usage.
	 - Advanced C Topics
		 - Conditional Compilation
			 - Don't care about OS specific stuff or managing that kind of complexity in this course
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