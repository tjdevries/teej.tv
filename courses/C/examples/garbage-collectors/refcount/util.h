#pragma once

#include "garbage.h"
#include "memory.h"

object_t *make_int(int i);
object_t *make_string(char *);
object_t *make_tuple_2(object_t *a, object_t *b);
