#ifndef LINKED_LIST
#define LINKED_LIST

typedef enum {FALSE, TRUE} bool;
typedef bool (*iterator)(void *);
typedef bool (*filter)(void *);

typedef struct _list_node {
  void *data;
  struct _list_node *next;
  struct _list_node *prev;
} LIST_NODE;

LIST_NODE * initialize(void);
LIST_NODE * last_node(LIST_NODE *head);
void push(LIST_NODE **head_ref, void *element);
void append(LIST_NODE **head_ref, void *element);
void for_each(LIST_NODE *head, iterator iterator);
void for_each_reverse(LIST_NODE *head, iterator iterator);
void destroy(LIST_NODE **head_ref);
void remove_all(LIST_NODE **head_ref, filter filter );
int list_size(LIST_NODE *head);

#endif
