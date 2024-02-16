// Memory layout for `coordinate`
//
//       +-----------------+
// field |  x  |  y  |  z  |
//       |-----|-----|-----|
// size  |  4  |  4  |  4  |
//       +-----------------+
//
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

  // However, kind of annoying to always have to say "struct coordinate" instead
  // of how we have been able to say "int" or "float" normally.
}
