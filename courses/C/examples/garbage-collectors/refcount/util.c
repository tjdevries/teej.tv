#include <assert.h>
#include <string.h>

#include "util.h"

object_t *make_int(int i) {
  object_t *obj = malloc(sizeof(object_t));
  assert(obj != NULL);

  obj->ref_count = 1;
  obj->obj_kind = INTEGER;
  obj->obj_data = (object_data_t){.v_int = i};

  return obj;
}

object_t *make_string(char *str) {
  object_t *obj = malloc(sizeof(object_t));
  assert(obj != NULL);

  obj->ref_count = 1;
  obj->obj_kind = STRING;
  obj->obj_data = (object_data_t){
      .v_string = {.size = strlen(str), .characters = strdup(str)}};

  return obj;
}

object_t *make_tuple_2(object_t *a, object_t *b) {
  obj_tuple tuple = {0};

  gc_object_inc(a);
  gc_object_inc(b);

  tuple.size = 2;
  tuple.elements = malloc(sizeof(object_t) * 2);
  tuple.elements[0] = a;
  tuple.elements[1] = b;

  object_t *obj = malloc(sizeof(object_t));
  obj->ref_count = 1;
  obj->obj_kind = TUPLE;
  obj->obj_data = (object_data_t){.v_tuple = tuple};

  return obj;
}
