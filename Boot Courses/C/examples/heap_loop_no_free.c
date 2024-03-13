#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *repeat_string(char *str, int count) {}

int main() {
  // But what if we wanted to have more than these? Does this work
  char *repeated = repeat_string("STR", 5);

  // This turns out to be really bad...
  //    Good video opportunity
  //    We can show the memory getting bigger and bigger...
  //    and never going down
  for (int i = 0; i < 1000000; i++) {
    repeat_string("STR", 3);
  }
}
