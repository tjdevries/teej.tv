
- Basic Syntax
%% START CODE: [[structs_basic_syntax.c]] %%
```c
struct coordinate {
  int x;
  int y;
  int z;
};

int main() {
  // positional initialiers
  struct coordinate p = {1, 2, 3};

  // Create a new struct, using "designated initializers"
  struct coordinate c = {.x = 1, .y = 2, .z = 3};
}
```
%% END CODE %%
	- However, kind of annoying to always have to say "struct coordinate" instead of how we have been able to say "int" or "float" normally.

- `typedef`

%% START CODE:  [[structs_typedef_example.c]] %%
```c
typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

int main() {
  // positional initializers
  coordinate_t p = {1, 2, 3};

  // Create a new struct, using "designated initializers"
  coordinate_t c = {.x = 1, .y = 2, .z = 3};
  // If you have trouble remembering the `.x` instead of just `x`,
  // think about how you access the field.
  // c.x -> x = { .x = 1, ... }
}
```
%% END CODE %%
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
	- Good resource: http://www.catb.org/esr/structure-packing/