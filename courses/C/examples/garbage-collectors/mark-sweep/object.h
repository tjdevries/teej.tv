#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>
typedef struct object_t *object;

// Object Definitions
typedef enum ObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VEC_3,
  TUPLE,
  // TABLE, a key-value pair?
} object_kind_t;

typedef struct {
  size_t size;
  char *characters;
} obj_string;

typedef struct {
  object *x;
  object *y;
  object *z;
} obj_vector_3;

typedef struct {
  size_t size;
  object **elements;
} obj_tuple;

typedef union ObjectData {
  int v_int;
  float v_float;
  obj_vector_3 v_vec_3;
  obj_string v_string;
  obj_tuple v_tuple;
} object_data_t;
#endif
