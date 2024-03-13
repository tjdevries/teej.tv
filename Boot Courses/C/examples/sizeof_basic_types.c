#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

int main() {
  printf("sizeof(char) = %lu\n", sizeof(char));
  printf("sizeof(bool) = %lu\n", sizeof(bool));
  printf("sizeof(short) = %lu\n", sizeof(short));
  printf("sizeof(int) = %lu\n", sizeof(int));
  printf("sizeof(float) = %lu\n", sizeof(float));
  printf("sizeof(double) = %lu\n", sizeof(double));
  printf("sizeof(long double) = %lu\n", sizeof(long double));
  printf("sizeof(long long) = %lu\n", sizeof(long long));

  // unsigned vs signed
  printf("sizeof(uint64_t) = %lu\n", sizeof(uint64_t));
  printf("sizeof(int64_t) = %lu\n", sizeof(int64_t));

  // BIG REVELATION HERE
  //    Something fun here: when you run this on boot, you'll get 4
  //    But if you ran this locally, you'll likely get 8
  printf("sizeof(size_t) = %lu\n", sizeof(size_t));
  printf("sizeof(char*) = %lu\n", sizeof(char *));
  printf("sizeof(int*) = %lu\n", sizeof(int *));
  printf("sizeof(float*) = %lu\n", sizeof(float *));
  printf("sizeof(long double*) = %lu\n", sizeof(long double *));

  printf("sizeof(void) = %lu\n", sizeof(void));
  printf("sizeof(void*) = %lu\n", sizeof(void *));

  // Structs
  printf("sizeof(coordinate_t) = %lu\n", sizeof(coordinate_t));
  printf("sizeof(coordinate_t*) = %lu\n", sizeof(coordinate_t *));

  printf("sizeof(int[3]) = %lu\n", sizeof(int[3]));
  printf("sizeof(char[5]) = %lu\n", sizeof(int[5]));

  // Why do we get 6 here? :) We'll come back to this in the strings section!
  //                             chars: 12345
  printf("sizeof(\"hello\") = %lu\n", sizeof("hello"));
  // {'h', 'e', 'l', 'l', 'o', '\0'}
}
