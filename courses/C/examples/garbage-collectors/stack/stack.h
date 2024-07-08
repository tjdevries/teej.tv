#include <stddef.h>
#include <stdlib.h>

typedef struct stack_t {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

void push(stack_t *stack, void *value);
void *pop(stack_t *stack);
