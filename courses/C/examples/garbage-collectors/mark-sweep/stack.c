#include "stack.h"

void push(stack_t *stack, object *obj) {
  // TODO: idk... maybe we should make them fail
  // with the segfault the first time? :)
  if (stack->data == NULL) {
    stack->capacity = 8;
    stack->data = realloc(stack->data, stack->capacity);
    if (stack->data == NULL) {
      // Unable to realloc, just exit :) get gud
      exit(1);
    }
  }

  if (stack->count == stack->capacity) {
    // Double stack capacity to avoid reallocing often
    stack->capacity *= 2;
    stack->data = realloc(stack->data, stack->capacity);
    if (stack->data == NULL) {
      // Unable to realloc, just exit :) get gud
      exit(1);
    }
  }

  stack->data[stack->count] = obj;
  stack->count++;

  return;
}

object *pop(stack_t *stack) {
  if (stack->count == 0) {
    return NULL;
  }

  stack->count--;
  void *value = stack->data[stack->count];
  return value;
}

void stack_free(stack_t stack) { free(stack.data); }
