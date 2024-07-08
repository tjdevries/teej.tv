#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "garbage.h"
#include "stack.h"

typedef struct object_t {
  object_kind_t obj_kind;
  object_data_t obj_data;

  bool is_marked;
  object *next;
} object_t;

typedef struct frame {
  size_t size;
  object **referenced;
} frame;

typedef struct VirtualMachine {
  // TODO: Globals?

  // Stack frames
  size_t frame_size;
  frame *frames;

  // These are the rest of the objects.
  object *objects;
} virtual_machine_t;

void mark(virtual_machine_t *vm) {
  // Mark all the objects in the stack frames
  for (size_t i = 0; i < vm->frame_size; i++) {
    frame frame = vm->frames[i];
    for (size_t j = 0; j < frame.size; j++) {
      object obj = *frame.referenced[j];
      obj->is_marked = true;
    }
  }

  // Mark all the globals
  // TODO: Decide if we want to do that.
}

void mark_object(stack_t *gray_objects, object *ref) {
  if (ref == NULL) {
    return;
  }

  object obj = *ref;
  if (obj->is_marked) {
    return;
  }

  push(gray_objects, ref);
  obj->is_marked = true;
}

void blacken_object(stack_t *gray_objects, object *ref) {
  object obj = *ref;

  switch (obj->obj_kind) {
  case INTEGER:
  case FLOAT:
  case STRING:
    break;
  case VEC_3: {
    obj_vector_3 vec = obj->obj_data.v_vec_3;
    mark_object(gray_objects, vec.x);
    mark_object(gray_objects, vec.y);
    mark_object(gray_objects, vec.z);
    break;
  }
  case TUPLE: {
    // TODO
    assert(false);
    break;
  }
  }
}

void trace(virtual_machine_t *vm) {
  stack_t gray_objects = {0};

  // Get previously marked objects (which are the roots)
  for (object obj = *vm->objects; obj != NULL; obj = *obj->next) {
    if (obj->is_marked) {
      push(&gray_objects, &obj);
    }
  }

  // Trace through the objects
  while (gray_objects.count > 0) {
    blacken_object(&gray_objects, pop(&gray_objects));
  }

  // Clean up after ourselves :)
  stack_free(gray_objects);
}

void free_object(object obj);

void sweep(virtual_machine_t *vm) {
  object previous = NULL;
  object obj = *vm->objects;
  while (obj != NULL) {
    if (obj->is_marked) {
      previous = obj;
      // TODO: Could do it this way, or could just cycle all of them at the
      // end and set them to false. That way is a lot simpler conceptually

      // Set not marked so when we do next cycle
      obj->is_marked = false;
      obj = *obj->next;
    } else {
      // x -> y -> z
      // x -> z
      object unreachable = obj;
      obj = *obj->next;

      if (previous == NULL) {
        // Hey, we freed the first object!
        // So we need to move where we think the first object is to the actual
        // new first object.
        vm->objects = &obj;
      } else {
        // x->z
        previous->next = &obj;
      }

      free_object(obj);
    }
  }
}

void gc_collect(virtual_machine_t *vm) {
  mark(vm);
  trace(vm);
  sweep(vm);
}
