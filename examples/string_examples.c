#include <stdio.h>
#include <string.h>

int main() {
  char nulled[] = "hello\0world";
  printf("nulled: %s\n", nulled);
  printf("strlen(nulled): %d\n", strlen(nulled));
}
