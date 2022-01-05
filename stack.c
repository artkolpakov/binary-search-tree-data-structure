#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "list.h"

/*
 * This is the structure that represents a stack.  It contains a single field
 * representing a linked list that is used as the underlying data storage for
 * the stack.
 */
struct stack {
  struct list* list;
};

struct stack* stack_create() {
  struct stack* stack = malloc(sizeof(struct stack));
  stack->list = list_create();
  return stack;
}

void stack_free(struct stack* stack) {
  assert(stack);
  list_free(stack->list);
  free(stack);
}

int stack_isempty(struct stack* stack) {
  assert(stack);
  return list_isempty(stack->list);
}

void stack_push(struct stack* stack, void* val) {
  assert(stack);
  list_insert(stack->list, val);
}

void* stack_top(struct stack* stack) {
  assert(stack);
  return list_head(stack->list);
}

void* stack_pop(struct stack* stack) {
  assert(stack);
  void* head = list_head(stack->list);
  list_remove_head(stack->list);
  return head;
}
