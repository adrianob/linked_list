#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct produto{
  int codigo;
  float preco;
};

struct user{
  int codigo;
  char *name;
};

bool cmp_produto(void *data){
  return ((struct produto *)data)->codigo == 7;
}
bool produto_iterator(void *data){
  printf("codigo: %d preco:%.2f\n", ((struct produto*)data)->codigo, ((struct produto *)data)->preco);
  return TRUE;
}

bool user_iterator(void *data){
  printf("codigo: %d nome:%s\n", ((struct user*)data)->codigo, ((struct user *)data)->name);
  return TRUE;
}

int main(int argc, const char *argv[])
{
  struct produto prod, prod2, prod3;
  struct user user;
  iterator iterator;

  prod2.codigo = 2;
  prod3.codigo = 3;
  prod.codigo = 4;
  prod.preco = 5.4;
  user.codigo = 2;
  user.name = "teste";

  LIST_NODE *produtos = initialize();
  LIST_NODE *users = initialize();

  append(&produtos, &prod);
  push(&produtos, &prod2);
  push(&produtos, &prod3);
  remove_all(&produtos, cmp_produto);
  iterator = produto_iterator;
  for_each(produtos, iterator);
  printf("%d\n", list_size(produtos));
  for_each_reverse(produtos, iterator);


  push(&users, &user);
  push(&users, &user);
  iterator = user_iterator;
  for_each(users, iterator);
}
