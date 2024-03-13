#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

void coordinate_update_x(coordinate_t *coor, int new_x) {
  printf("  INSIDE address: %p\n", coor);
  printf("  INSIDE BEFORE: coor.x = %d\n", coor->x);

  // Set x to new_x
  // coor->x = new_x;

  printf("  INSIDE AFTER : coor.x = %d\n", coor->x);
}

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};

  printf("Coordinate address: %p\n", &c);

  // BEFORE YOU RUN THIS, TAKE A GUESS WHAT IT WILL PRINT!
  // WRITE IT DOWN!
  printf("OUTSIDE BEFORE: c.x = %d\n", c.x);
  coordinate_update_x(&c, 10);
  printf("OUTSIDE AFTER: c.x = %d\n", c.x);

  // What is different?
}
