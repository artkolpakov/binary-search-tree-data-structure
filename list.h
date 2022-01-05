#ifndef __LIST_H
#define __LIST_H

/*
 * Structure used to represent a singly-linked list.
 */
struct list;

struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
int list_isempty(struct list* list);
void* list_head(struct list* list);
void list_remove_head(struct list* list);

#endif
