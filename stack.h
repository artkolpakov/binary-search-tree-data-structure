#ifndef __STACK_H
#define __STACK_H

/*
 * Structure used to represent a stack.
 */
struct stack;

struct stack* stack_create();
void stack_free(struct stack* stack);
int stack_isempty(struct stack* stack);
void stack_push(struct stack* stack, void* val);
void* stack_top(struct stack* stack);
void* stack_pop(struct stack* stack);

#endif
