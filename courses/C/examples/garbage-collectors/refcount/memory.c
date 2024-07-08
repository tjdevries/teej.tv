#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Think about this as a nice way to write some
// additional asserts for tests running for students.
//
// Would be nice to tell them they've forgotten X frees
// in the browser
static int malloc_count = 0;
static int free_count = 0;

void *freed[100] = {0};

void gc_free(void *ptr) {
  if (free_count > 90) {
    printf("Freed too many pointers");
  }

  freed[free_count] = ptr;
  free_count++;

  printf("gc_free => %p\n", ptr);
  free(ptr);
}

bool gc_is_freed(void *ptr) {
  for (int i = 0; i < free_count; i++) {
    if (freed[i] == ptr) {
      return true;
    }
  }

  return false;
}

void *gc_malloc(size_t size) {
  malloc_count++;

  printf("MALLOCING SOMETHING!\n");
  return malloc(size);
}
