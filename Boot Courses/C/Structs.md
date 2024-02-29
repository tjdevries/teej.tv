
- Basic Syntax
	- [[structs_basic_syntax.c]]
	- However, kind of annoying to always have to say "struct coordinate" instead of how we have been able to say "int" or "float" normally.

%% START CODE: [[01_first_program.c]] %%
```c
#include <stdio.h>
//^^^^^^ This is an "include" which is similar in some ways
//       to import in Python. We will cover some of the other
//       standard library includes later, but for now we will
//       include "stdio.h" which is used for:
//       "standard input and output".
//
//       This is how we get our `printf` function that we use below.

// TODO: How much to explain below? Should we have already explained some
// of the syntax before? They have already written quite a bit of Python,
// so they are at least familiar with running a program by now.
//
// Will need to do some exploration on what we can expect by this point.
int main() {
  printf("Hello, world!\n");
  return 0;
}

```
%% END CODE %%

- `typedef`
	- [[structs_typedef_example.c]]
	- Now we can use `coordinate_t` instead of always typing `struct coordinate`

- Initializers
	- Positional
		- (shown in both example and syntax)
	- Designated
		- (shown in both example and syntax)
	- `{0}` <- zero initialized
		- [[structs_typedef_zeroed.c]]
	
- `sizeof(T)`
- Padding / alignment
	- [[structs_padding.c]]