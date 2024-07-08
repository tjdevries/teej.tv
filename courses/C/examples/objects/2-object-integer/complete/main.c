#include <stdio.h>
#include <stdlib.h>

// Forward declare the object
typedef struct Object object_t;

typedef enum ObjectKind {
  INTEGER,
} object_kind_t;

typedef union ObjectData {
  int v_int;
} object_data_t;

typedef struct Object {
  object_kind_t obj_kind;
  object_data_t obj_data;
} object_t;
