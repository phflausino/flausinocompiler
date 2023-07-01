#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
  void* value;
  struct node* next;
};

struct list {
  size_t node_value_size;
  struct node* head;
  struct node* tail;
};

typedef struct list list;
typedef struct list* list_ptr;

list_ptr create_list(size_t node_value_size);

struct node* list_add_node(const list_ptr list, void* value);

void list_for_each(const list_ptr list, void (*callback)(void* value));

#endif
