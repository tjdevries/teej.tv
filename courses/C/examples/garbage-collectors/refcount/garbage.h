#pragma once

/// Our simple "object" model for our garbage collector.
/// Shared between refcount and mark-sweep collector

#include <stddef.h>

typedef struct Object object_t;

// ==============================
// TODO: This is what you implement in the course!
void gc_object_inc(object_t *ref);
void gc_object_dec(object_t *ref);
void gc_object_free(object_t *ref);
// ==============================

// Object Definitions
typedef enum ObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VEC_3,
  TUPLE,
} object_kind_t;

typedef struct {
  size_t size;
  char *characters;
} obj_string;

typedef struct {
  object_t *x;
  object_t *y;
  object_t *z;
} obj_vector_3;

typedef struct {
  size_t size;
  object_t **elements;
} obj_tuple;

typedef union ObjectData {
  int v_int;
  float v_float;
  obj_vector_3 v_vec_3;
  obj_string v_string;
  obj_tuple v_tuple;
} object_data_t;

typedef struct Object {
  int ref_count;
  object_kind_t obj_kind;
  object_data_t obj_data;
} object_t;
