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
    while(aux->next){
      aux = aux->next;
    }
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

void for_each_reverse(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  if (node) {
    while(node->next){
      node = node->next;
    }//node receives last element
    while(node){
      iterator(node->data);
      node = node->prev;
    }
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
