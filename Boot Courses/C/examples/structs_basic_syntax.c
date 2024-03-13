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
