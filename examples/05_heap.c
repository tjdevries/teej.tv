
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

char *repeat_string(char *str, int count) {
  // HOW TO DO??
  // In python: we can do str * count
  // ... this doesn't work in C :)
  // ... like not even close.

  // you have, char *str
  //    in memory, that's like:
  //
  //    'h' 'e' 'l' 'l' 'o' '\0'
  //     ^ str

  // So... how do we **dynamically** get to be able to do
  // something like:
  //
  //    'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' '\0'
  //     ^ repeated_str
  char something[] = "hello";
  char *other = "other";

  // So you're stuck! C can't do it!...
  // OF COURSE NOT!

  // Introducing.... `malloc`!
  // char *repeated_str = malloc(strlen(str) * count);

  // GOTCHA MOMENT!!!!!!!! This isn't big enough
  //    This would be a good multiple choice question here
  //    TODO: Decide if we should do something like sizeof(char) here too
  char *repeated_str = malloc(strlen(str) * count + 1);

  // After malloc
  //    '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?'
  //     ^ repeated_str

  // After first loop
  //    'h' 'e' 'l' 'l' 'o' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?' '?'
  //     ^ repeated_str

  // After second loop
  //    'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' '?' '?' '?' '?' '?' '?'
  //     ^ repeated_str

  // After third loop
  //    'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' 'h' 'e' 'l' 'l' 'o' '?'
  //     ^ repeated_str

  // We can set up this loop, and leave the two indexes unfilled
  // for them to fill out
  int length = strlen(str);
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < length; j++) {
      repeated_str[i * length + j] = str[j];
    }
  }

  repeated_str[count * strlen(str)] = '\0';

  return repeated_str;
}

int main() {
  // Up until now, everything we've done has ONLY been on the `stack`.
  //
  // What's the stack?

  // OR

  // Up until now, we've always had a set amount of structs, items, etc
  // that were allocated on the stack.

  // Ok, up until now, you've always had a set amount of structs, items, etc
  coordinate_t c1 = {.x = 1, .y = 1, .z = 1};
  coordinate_t c2 = {.x = 2, .y = 2, .z = 2};

  // But what if we wanted to have more than these? Does this work
  int count = 5;
  char x[] = "hello";
  char *repeated = repeat_string(x, count);

  // This turns out to be really bad...
  //    Good video opportunity
  //    We can show the memory getting bigger and bigger...
  //    and never going down
  for (int i = 0; i < 1000000; i++) {
    repeat_string(x, count);
  }

  // How can we do what happens in Python?
  //    When we do a loop in python, we don't have to
  //    do anything explicitly to give the memory back
  //
  // Can we show some GC profiling or something else in Python
  // to make it clear that it's not cost-less to do the GC work
  // in Python (don't know if i wanna say Free, cause we're teaching
  // what free() does in C)

  // We need to free the memory
  char *allocated_string = repeat_string("<this is allocated>", 3);
  free(allocated_string);

  // What to talk about with free:

  // - System can reclaim the memory
  //    In this loop now, instead of never releasing the
  //    memory, we're going to release it after each loop
  //    back to the system.
  for (int i = 0; i < 1000000; i++) {
    char *allocated_string = repeat_string("<this is allocated>", 3);
    printf("Allocated: %s\n", allocated_string);

    // This is the important part of what's going on
    free(allocated_string);
  }

  // If we don't call free, the memory will not go back
  // to the system until the program ends
}
