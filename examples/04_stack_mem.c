#include <stdio.h>

int main() {
  // This is bad, because it doesn't have a \0 at the end
  char bad[5] = "hello";
  char bad_next[] = ", world";

  // What do you think this will print?
  // Is there any way to guarantee we get the bad print here?
  //    I want to show them the pitfall of not having a \0 terminated string
  printf("bad : %s\n", bad);

  // char good[6] = "hello";
  // char good_next[] = ", world";
  // printf("good: %s\n", good);
}
