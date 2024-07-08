#include <stddef.h>

#include "object.h"

// When we work with objects, we're really
// working with pointers to objects.
//
// This keeps everything the same size and
// has some nice properties later that we will see :)
typedef struct VirtualMachine virtual_machine_t;

void gc_start();
void gc_stop();
void gc_allocate();
void gc_free();

// ==============================
// TODO: This is what you write in the course
void gc_collect();
// ==============================
