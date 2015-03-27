#include <stdlib.h>
#include "linked_list.h"

LIST_NODE * initialize(void){
  return NULL;
}

void push(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = malloc(sizeof(LIST_NODE));
  node->data = element;
  node->prev = NULL;
  node->next = *head_ref;

  if (*head_ref) {
    node->next->prev = node;
  }
  *head_ref = node;
}

void append(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = malloc(sizeof(LIST_NODE));
  LIST_NODE *aux = *head_ref;
  node->data = element;

  node->next = NULL;
  if (!aux) {//empty list
    node->prev = NULL;
    *head_ref = node;
  }
  else{
    aux = last_node(*head_ref);
    aux->next = node;
    node->prev = aux;
  }
}

void for_each(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  while(node){
    iterator(node->data);
    node = node->next;
  }
}

LIST_NODE * last_node(LIST_NODE *head){
  LIST_NODE *node = head;
  if (node) {
    while(node->next){
      node = node->next;
    }
  }
  return node;
}

void for_each_reverse(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  node = last_node(head);
  while(node){
    iterator(node->data);
    node = node->prev;
  }
}

void destroy(LIST_NODE **head_ref){
  LIST_NODE *aux = *head_ref;

  while(*head_ref){
    aux = *head_ref;
    *head_ref = aux->next;
    free(aux);
  }
  free(*head_ref);
  *head_ref = NULL;
}

void remove_all(LIST_NODE **head_ref, filter filter ){
  LIST_NODE *aux = *head_ref;
  if (!aux) {
    return;
  }
  while(aux){
    if (filter(aux->data)) {//remove
      if (!aux->prev) {//first element
        *head_ref = aux->next;
      }
      else {
        aux->prev->next = aux->next;
      }
      if (aux->next) {
        aux->next->prev = aux->prev;
      }
      free(aux);
    }

    aux = aux->next;
  }

}

int list_size(LIST_NODE *head){
  unsigned int i = 0;
  LIST_NODE *node = head;
  while(node){
    i++;
    node = node->next;
  }
  return i;
}
