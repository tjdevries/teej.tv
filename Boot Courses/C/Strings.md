

"Strings" (char array + null terminator)

- `char greeting[] = "hello, world!";`
- `char greeting[x] = "hello, world!";`
	- STOP: What do you think `x` should be? :)
- `printf("%s", greeting);`
- Definitely want to show some of the stdlib string functions and some easy things that can make them fail
	- `strncopy`
	- `strlen`, etc
- Overflows
	- `char greeting[256]`
	- Someone inputs a 300 character string... uh oh :)
	- memcpy into something that's not big enough

- Examples:
	- Put `\0` character in the middle of a string array
	- [[string_examples.c]]
