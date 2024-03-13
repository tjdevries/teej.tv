TODO: Think about what int sizes to include, should stick to no includes if we can right now. We haven't introduced that concept yet.

- int
- float
- double
- char
- unsigned stuffz
- (maybe later) int sizes:
	- long int
	- short int
	- size_t


%% START CODE: [[Boot Courses/C/examples/casting.c]] %%
```c
#include <stdio.h>
#include <string.h>

int main() {
  char c = 'c';
  printf("char of 'c': %c -> hex: %x, dec: %d\n", c, c, c);
}
```
%% END CODE %%