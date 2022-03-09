#include <stdlib.h>
#include <stdio.h>

#include "list.h"

node* node_new(int val, node* p) {
  node* q = (node*)malloc(sizeof(node));
  q->val = val;
  q->next = p;
  return q;
}

list* list_new() {
  list* l = (list*)malloc(sizeof(list));
  l->size = 0;
  l->first = NULL;
  return l;
}

list* list_new_random(int size, int range) {
  list* l = list_new();
  int i;
  for (i = 0; i < size; i++)
    list_add_first(rand() % range, l);
  return l;
}

void list_add_first(int val, list* l) {
  node* p = node_new(val, l->first);
  l->first = p;
  l->size++;
}

void list_add_last(int val, list* l) {
  node* p = node_new(val, NULL);
  if (l->size == 0)
    l->first = p;
  else {
    node* q = l->first;
    while (q->next != NULL)
      q = q->next;
    q->next = p;
  }
  l->size++;
}

int list_get_first(list* l) {
  return l->first->val;
}

int list_get_last(list* l) {
  while (1) {
    node* p = l->first;
    if (p->next == NULL) return p->val;
  }
}

void list_remove_first(list *l) {
  node* p = l->first;
  l->first = l->first->next;
  l->size--;
  free(p);
}

void list_remove_last(list* l) {
  //to complete;
}

int list_size(list* l) {
  //to complete
}

void list_print(list* l) {

}