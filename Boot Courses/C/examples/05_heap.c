#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *repeat_string(char *str, int count) {
  // GOTCHA MOMENT!!!!!!!! This isn't big enough
  //    This would be a good multiple choice question here
  //    TODO: Decide if we should do something like sizeof(char) here too
  char *repeated_str = malloc(strlen(str) * count + 1);

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
  // But what if we wanted to have more than these? Does this work
  char *repeated = repeat_string("STR", 5);
}
