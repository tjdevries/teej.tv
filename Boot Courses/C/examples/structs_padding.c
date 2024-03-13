#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  char a;
  double b;
  char c;
  char d;
  long e;
  char f;
} poorly_aligned_t;

typedef struct {
  double b;
  long e;
  char c;
  char d;
  char a;
  char f;
  char g;
  char h;
  char i;
  char j;
} better_t;

int main() {
  printf("Padding and alignment\n");

  printf("sizeof(poorly_aligned_t) = %lu\n", sizeof(poorly_aligned_t));
  printf("sizeof(better_t) = %lu\n", sizeof(better_t));

  return 0;
}
