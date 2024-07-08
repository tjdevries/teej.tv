#include <stddef.h>
#include <stdlib.h>

#include "object.h"

typedef struct stack_t {
  size_t count;
  size_t capacity;
  object **data;
} stack_t;

void push(stack_t *stack, object *obj);
object *pop(stack_t *stack);
void stack_free(stack_t stack);
