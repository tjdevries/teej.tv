#pragma once

#include <stdbool.h>
#include <stdlib.h>

void gc_free(void *ptr);
bool gc_is_freed(void *ptr);

void *gc_malloc(size_t size);
