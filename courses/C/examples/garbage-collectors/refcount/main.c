#include <assert.h>
#include <stdio.h>

#include "garbage.h"
#include "memory.h"
#include "util.h"

void test_free_int_first() {
  object_t *i1 = make_int(1);
  object_t *i2 = make_int(2);

  object_t *obj = make_tuple_2(i1, i2);

  gc_object_inc(obj);
  gc_object_dec(obj);

  // Free i1 before freeing list
  gc_object_dec(i1);
  assert(!gc_is_freed(i1));

  // Now there are no references to i1, so it should be freed.
  gc_object_dec(obj);
  assert(gc_is_freed(obj));

  // i1 also magically gets updated!
  assert(gc_is_freed(i1));

  // Clean up last memory
  gc_object_dec(i2);
  assert(gc_is_freed(i2));
}

void test_free_tuple_first() {
  object_t *i1 = make_int(1);
  object_t *i2 = make_int(2);

  object_t *obj = make_tuple_2(i1, i2);

  gc_object_inc(obj);
  gc_object_dec(obj);

  assert(!gc_is_freed(obj));
  gc_object_dec(obj);
  assert(gc_is_freed(obj));

  // Free i1 after freeing list
  assert(!gc_is_freed(i1));
  gc_object_dec(i1);
  assert(gc_is_freed(i1));

  // Clean up last memory
  gc_object_dec(i2);
  assert(gc_is_freed(i2));
}

void test_free_string() {
  object_t *str1 = make_string("hello, world!");

  assert(!gc_is_freed(str1));
  gc_object_dec(str1);
  assert(gc_is_freed(str1));
}

void refcount_test() {
  test_free_int_first();
  test_free_tuple_first();
  test_free_string();
}

int main() {
  printf("-- Starting refcount gc\n");
  refcount_test();
  printf("-- Finished refcount gc\n");

  return 0;
}
