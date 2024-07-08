#include <assert.h>
#include <stdlib.h>
#include <string.h>

// This struct is a fixed size...
//  This is because it doesn't CONTAIN a list.
//  It holds a POINTER to an array
typedef struct this_is_optional {
  int num_needed;
  char **needed;

  int spent;
  // int budget; ?
} grocery_list;

// void append_to_list(string_list_t *list, char *str) { list->size++; }

int grocery_find_needed(grocery_list *g, char *item) {
  for (int i = 0; i < g->num_needed; i++) {
    char *needed_item = g->needed[i];
    if (0 == strcmp(needed_item, item)) {
      return i;
    }
  }

  return -1;
}

void purchase_item(grocery_list *g, char *item, int price) {
  // Find the item in needed
  int index = grocery_find_needed(g, item);
  if (index == -1) {
    // TODO: Think about error handling :)
    return;
  }

  // Remove the item from needed
  int new_size = g->num_needed - 1;
  char **new_items = malloc(new_size * sizeof(char *));

  // Up to index
  for (int i = 0; i < index; i++) {
    new_items[i] = g->needed[i];
  }

  // After index, to the end
  for (int i = index + 1; i < g->num_needed; i++) {
    new_items[i - 1] = g->needed[i];
  }

  // Clean up!
  char **old_items = g->needed;
  free(old_items);

  g->num_needed--;
  g->needed = new_items;
  g->spent += price;
}

int main() {
  char **items = {0};

  // We can put a grocery list ON THE STACK
  assert(sizeof(grocery_list) == 16);

  // we don't have to free our string_list...
  // BUT we do need to free items
}
