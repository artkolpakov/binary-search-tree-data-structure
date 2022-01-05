#include <stdlib.h>
#include <assert.h>

#include "list.h"

/*
 * This structure is used to represent a single link in a singly-linked list.
 * It is not defined in list.h, so it is not visible to the user.
 */
struct link {
  void* val;
  struct link* next;
};

struct list {
  struct link* head;
};

struct list* list_create() {
  struct list* list = malloc(sizeof(struct list));
  list->head = NULL;
  return list;
}

void list_free(struct list* list) {
  assert(list);

  struct link* next, * curr = list->head;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  free(list);
}

void list_insert(struct list* list, void* val) {
  assert(list);

  struct link* link = malloc(sizeof(struct link));
  link->val = val;
  link->next = list->head;
  list->head = link;
}

int list_isempty(struct list* list) {
  assert(list);
  if (list->head) {
    return 0;
  } else {
    return 1;
  }
}

void* list_head(struct list* list) {
  assert(list);

  if (list->head) {
    return list->head->val;
  } else {
    return NULL;
  }
}

void list_remove_head(struct list* list) {
  assert(list);

  if (list->head) {
    struct link* old_head = list->head;
    list->head = old_head->next;
    free(old_head);
  }
}
