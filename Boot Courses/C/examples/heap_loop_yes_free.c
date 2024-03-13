#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *repeat_string(char *str, int count) {}

int main() {
  // But what if we wanted to have more than these? Does this work
  char *repeated = repeat_string("STR", 5);

  // Now, since we're freeing on every iteration, we don't explode the memory!
  for (int i = 0; i < 1000000; i++) {
    char *repeated = repeat_string("STR", 3);

    // Do some useful work with the repeated string...
    printf("Repeated: %s\n", repeated);
    // ... and free it when we're done with it

    free(repeated);
  }
}
