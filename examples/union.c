#include <stdio.h>

// Some I'm thinking we should have them implement
// the object kind first with just something simple like
// integer or float. Then you can see the size of the object.
//
// Then we can add the "coordinate" struct (or just an array directly)
// and then have them guess what the sizeof value should be for that.
//
// This should hopefully illustrate that they all share the same memory space.

typedef enum object_kind {
  INTEGER,
  FLOAT,
  CHAR,
  COORDINATE,
} object_kind;

typedef struct object {
  object_kind kind;
  // Things that are important about unions:
  //    You have different fields to access the different types.
  //
  //    And you need some what to know which of the fields is
  //    the right one to access, this is why we have the "kind" field
  //    above
  //
  // Should we talk about how this is allocated? What does it look like
  // in the actual memory layout?
  //
  // Should make them do some tests with sizeof to make sure their
  // intuition about calculating this makes sense. It will help
  // build confidence on how to think about allocations as we go
  // a bit further into what is going on.
  //
  // (It also makes more sense then why sometimes you will see or HAVE to see
  // using pointers for the items in a union)
  union {
    int int_v;
    float float_v;
    char char_v;
    int coords[3];
  } object_data;
} object;

void print_object(object obj) {
  // They could implement this as part of an exercise.
  // It would be good example of both switch case, enum and union types.
  switch (obj.kind) {
  case INTEGER:
    printf("INTEGER: %d\n", obj.object_data.int_v);
    break;
  case FLOAT:
    printf("FLOAT: %f\n", obj.object_data.float_v);
    break;
  case CHAR:
    printf("CHAR: %c\n", obj.object_data.char_v);
    break;
  case COORDINATE:
    printf("COORDINATE: (%d, %d, %d)\n", obj.object_data.coords[0],
           obj.object_data.coords[1], obj.object_data.coords[2]);

    // Should show how you can still do this... so that's bad!
    // Not really the data you think is gonna be there
    // (I think the intuition from javascript/python land would be that
    //  that this should print out 0 or give an error)
    //
    //  LUL ERRORS IN C OMEGALUL
    printf("  BAD INT : %d\n", obj.object_data.int_v);
    break;
  default:
    printf("Unknown object kind\n");
    break;
  }
}

int main() {
  object obj = {.kind = INTEGER, .object_data = {.int_v = 42}};
  print_object(obj);

  // We can also use "compound literals"
  //    NOTE: you must include the (object) at the beginning for this to work
  print_object((object){.kind = INTEGER, .object_data = {.int_v = 42}});
  print_object((object){.kind = FLOAT, .object_data = {.float_v = 3.14}});
  print_object((object){.kind = CHAR, .object_data = {.char_v = 'a'}});
  print_object(
      (object){.kind = COORDINATE, .object_data = {.coords = {1, 2, 3}}});

  printf("sizeof(object) = %lu\n", sizeof(object));
}
