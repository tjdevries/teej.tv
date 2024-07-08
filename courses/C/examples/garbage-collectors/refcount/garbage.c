// TODOs offstream:
// - differences between typedeft shenanigans

// Jokes:
// - mark-and-sweep you off your feet

// For eductional purposes, should we implement
// both a mark-and-sweep, as well as a ref-count?

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "garbage.h"
#include "memory.h"

void gc_object_inc(object_t *obj) {
  // Should only increment live objects
  assert(obj->ref_count >= 1);

  obj->ref_count++;
  return;
}

void gc_object_dec(object_t *obj) {
  obj->ref_count--;

  // Should never get a negative ref count
  assert(obj->ref_count >= 0);

  if (obj->ref_count == 0) {
    return gc_object_free(obj);
  }

  return;
}

void gc_object_free(object_t *obj) {
  assert(obj->ref_count == 0);

  // decrement all the things this is holding
  switch (obj->obj_kind) {
  case INTEGER:
    // Integers are allocated within the object, so nothing to free
    break;
  case FLOAT:
    // Floats are allocated within the object, so nothing to free
    break;
  case STRING: {
    // Free the allocated characters for the string.
    obj_string *str = &obj->obj_data.v_string;
    free(str->characters);
    break;
  }
  case VEC_3: {
    // We don't have to *free* the objects,
    // we simply decrement their reference counts.
    //
    // If they go to 0, decrement will handle freeing them.
    obj_vector_3 vec = obj->obj_data.v_vec_3;
    gc_object_dec(vec.x);
    gc_object_dec(vec.y);
    gc_object_dec(vec.z);
    break;
  }
  case TUPLE: {
    obj_tuple *tuple = &obj->obj_data.v_tuple;

    // decrement all the references in our tuple
    for (size_t i = 0; i < tuple->size; i++) {
      gc_object_dec(tuple->elements[i]);
    }

    // (tricky to remember) Free the element list
    gc_free(tuple->elements);

    break;
  }
  default:
    assert(false);
  }

  // Free the memory that we allocated for an object.
  gc_free(obj);

  return;
}
