#include <stdio.h>

typedef struct {
  int x;
  int y;
} xy_t;

xy_t *xy_new() {
  xy_t new = {.x = 10, .y = 12};
  printf("  new -> %lu\n", &new);
  return &new;
}

int main() {
  xy_t *c = xy_new();
  printf("c -> %lu\n", c);

  int x = 10;
  int y = 12;

  // What do you think is gonna be printed?
  printf("x: %d\n", c->x);
  printf("y: %d\n", c->y);
}
