
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
