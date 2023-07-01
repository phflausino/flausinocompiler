#include <stdlib.h>
#include <memory.h>
#include "list.h"

list_ptr create_list(size_t node_value_size) {
  list_ptr new_list = malloc(sizeof(list));
  new_list->node_value_size = node_value_size;
  new_list->head = NULL;
  new_list->tail = NULL;
  return new_list;
}

struct node* _create_node (const list_ptr list, void* value) {
  struct node* new_node = malloc(sizeof(struct node));
  void* temp = malloc(sizeof(value));
  memcpy(temp, value, list->node_value_size);
  new_node->value = temp;
  new_node->next = NULL;
  return new_node;
};

struct node* list_add_node(const list_ptr list, void* value) {
  struct node* new_node = _create_node(list, value);
  if(!list->head) {
    list->head = new_node;
  } else if (!list->tail) {
    list->tail = new_node;
    list->head->next = list->tail;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  } 
  return new_node;
}

void list_for_each(const list_ptr list, void (*callback)(void* value)) {
  struct node* temp = list->head;
  while(temp) {
    (*callback)(temp->value);
    temp = temp->next;
  }
}
