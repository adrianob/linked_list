#include <stdlib.h>
#include <stdio.h>
#include "circular_linked_list.h"

LIST_NODE * initialize(void){
  return NULL;
}

void push(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = malloc(sizeof(LIST_NODE));
  node->data = element;

  if (!*head_ref) {//empty
    node->next = node;
    node->prev = node;
  }
  else{
    node->next = *head_ref;
    node->prev = node->next->prev;//previous points to last element
    node->next->prev->next = node;//last element points to new head
    node->next->prev = node;//next element points to new head
  }
  *head_ref = node;
}

void append(LIST_NODE **head_ref, void *element){
  LIST_NODE *node = malloc(sizeof(LIST_NODE));
  LIST_NODE *aux = *head_ref;
  node->data = element;

  if (!aux) {//empty list
    node->prev = node;
    node->next = node;
    *head_ref = node;
  }
  else{
    aux = last_node(*head_ref);
    aux->next = node;
    (*head_ref)->prev = node;
    node->next = *head_ref;
    node->prev = aux;
  }
}

void for_each(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  while(node){
    iterator(node->data);
    node = (node->next != head) ? node->next : NULL;
  }
}

void for_each_reverse(LIST_NODE *head, iterator iterator){
  LIST_NODE *node = head;
  node = last_node(head);
  while(node){
    iterator(node->data);
    node = (node == head) ? NULL : node->prev;
  }
}

void destroy(LIST_NODE **head_ref){
  LIST_NODE *aux = *head_ref;
  LIST_NODE *head = *head_ref;

  while(*head_ref){
    aux = *head_ref;
    *head_ref = (aux->next == head) ? NULL : aux->next;
    free(aux->data);
    free(aux);
    aux = NULL;
  }
  free(*head_ref);
  *head_ref = NULL;
}

void remove_all(LIST_NODE **head_ref, filter filter, void * filter_arg ){
  LIST_NODE *aux = *head_ref;
  LIST_NODE *next;
  LIST_NODE *current;
  LIST_NODE *tail = last_node(*head_ref);
  while(aux){
    current = aux;
    next = aux->next;
    if (filter(aux->data, filter_arg)) {//remove
      if (aux == *head_ref) {//first element
        *head_ref = (aux->next == aux) ? NULL : aux->next;
        if (*head_ref) {
          tail->next = *head_ref;
        }
      }
      else {
        aux->prev->next = aux->next;
      }
      aux->next->prev = aux->prev;

      free(aux->data);
      free(aux);
      aux = NULL;
    }

    tail = last_node(*head_ref);
    aux = (*head_ref && current != tail) ? next : NULL;
  }

}

int list_size(LIST_NODE *head){
  unsigned int i = 0;
  LIST_NODE *node = head;
  while(node){
    i++;
    node = (node->next == head) ? NULL : node->next;
  }
  return i;
}

LIST_NODE * last_node(LIST_NODE *head){
  LIST_NODE *node = head;
  if (node) {
    node = node->prev;
  }
  return node;
}
