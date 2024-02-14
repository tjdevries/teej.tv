#include <stdio.h>

#define MY_THING 37
#define something(x)

// Memory layout for `coordinate`
//
//         +-----------------------+
// field   |   x   |   y   |   z   |
//         |-------|-------|-------|
// size    |   4   |   4   |   4   |
//         |-------|-------|-------|
// address | 0x100 | 0x104 | 0x108 | (example address)
//         |-------|-------|-------|
// offset  |   0   |   4   |   8   | (example address)
//         +-----------------------+
//
// (Could skip hex for this, but I think it's fine maybe)
typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

// Finish this function (I KNOW THIS WONT WORK)
void coordinate_update_x(coordinate_t coor, int new_x) {
  printf("  INSIDE BEFORE: coor.x = %d\n", coor.x);

  // TODO(you!): Set x to new_x
  coor.x = new_x;

  printf("  INSIDE AFTER : coor.x = %d\n", coor.x);
}

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};
  printf("Coordinate address: %p\n", &c);

  // Should we show them this?...
  // it's kind of cursed haha but gets their heads in the
  // right direction for thinking about memory and memory layout
  //
  // Ok, we keep it for later, but I do think it's good to show
  // them that there is literally just the bytes. Just you and the
  // bytes, no type safety to save you LUL
  //
  // I think this also then helps to push you to understand pointers.
  // They are just a way to reference a memory location.
  int *lies = (int *)&c + 1;
  printf("LIES VALUE: %d\n", *lies);

  // BEFORE YOU RUN THIS, TAKE A GUESS WHAT IT WILL PRINT!
  // WRITE IT DOWN!
  printf("OUTSIDE BEFORE: c.x = %d\n", c.x);
  coordinate_update_x(c, 10);
  printf("OUTSIDE AFTER: c.x = %d\n", c.x);
}

void *generics(void *arg);
