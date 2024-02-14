#include <stdbool.h>
#include <stdio.h>

struct example_struct {
  int x;
  int y;
};

typedef struct example_struct example_t;

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

void this_doesnt_do_anything(coordinate_t coor) { coor.x = 42; }
void this_does_something(coordinate_t *coor) { coor->x = 42; }

int main() {
  // This is kind of annoying, you have to write struct
  // every time that you want to reference the type.
  struct example_struct ex = {1, 2};

  // This is where typedef comes in
  //    Notice how we don't have to write `struct example_struct`
  //    anymore, but we can just use `example_t` like we would
  //    for any of the other primitive types.
  example_t ex2 = {1, 2};

  // Should probably talk about sizeof at some point here.
  //    This is a very important concept in C, which they will
  //    have never encountered before.
  //
  //    We must know the size of everything that is on the stack.
  //        (Is this actually true? C is so good at 99% true LUL)
  printf("sizeof(int) = %lu\n", sizeof(int));
  printf("sizeof(coordinate_t) = %lu\n", sizeof(coordinate_t));

  // Designated initializers vs Positional initializers
  coordinate_t c = {.x = 1, .y = 2, .z = 3};
  coordinate_t _ = {1, 2, 3};
  printf("c.x = %d\n", c.x);
  printf("c.y = %d\n", c.y);
  printf("c.z = %d\n", c.z);

  // What do you expect to have happen?
  //    What would happen in Python here?
  // Why doesn't this change to 42?
  this_doesnt_do_anything(c);
  printf("c.x = %d\n", c.x);

  // What do you expect to have happen?
  //    What's different about this compared to the previous function?
  this_does_something(&c);
  printf("c.x = %d\n", c.x);

  // Should also mention that Go copied the dumb design decision to just
  // put 0 in everything if you don't put it in.... smh....
  // Can't we just have nice things? You can forgive C because they didn't
  // know how bad things could get
  coordinate_t d = {.x = 1, .y = 2};
  printf("d.z = %d\n", d.z); // d.z = 0

  // These are equivalent (as long as your C compiler understands them)
  coordinate_t zeroed_1 = {0}; // recommended
  coordinate_t zeroed_2 = {};  // sometimes works, depends on compiler
                               // Maybe just don't even include this,
                               // since it doesn't always work. Probably
                               // better to just use the 0 explicitly.

  // printf("NULL = %d\n", NULL);
  // printf("0 == NULL -> %d\n", 0 == NULL);

  return 0;
}
