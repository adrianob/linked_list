#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct produto{
  int codigo;
  float preco;
};

bool cmp_produto(void *data, void *n){
  return ((struct produto *)data)->codigo == *((int *)n);
}

bool produto_iterator(void *data){
  printf("codigo: %d preco: %.2f\n", ((struct produto*)data)->codigo, ((struct produto *)data)->preco);
  return TRUE;
}

void menu(){
  printf("1. insere novo produto\n");
  printf("2. lista todos produtos\n");
  printf("3. lista todos produtos em ordem reversa\n");
  printf("4. destroi a lista\n");
  printf("5. imprimir tamanho da lista\n");
  printf("6. remover elementos\n");
  printf("7. sair\n");
}

void le_produto(LIST_NODE **head){
  struct produto *prod;
  prod = malloc(sizeof(struct produto));
  printf("Informe o codigo:\n");
  scanf("%d", &prod->codigo);
  printf("Informe o preco:\n");
  scanf("%f", &prod->preco);
  push(head, prod);
}

int main(int argc, const char *argv[])
{
  int option, cod;
  iterator iterator;

  LIST_NODE *produtos = initialize();
  iterator = produto_iterator;
  menu();

  while(TRUE){
    scanf("%d", &option);
    switch (option) {
      case 1:
        le_produto(&produtos);
        break;
      case 2:
        for_each(produtos, iterator);
        break;
      case 3:
        for_each_reverse(produtos, iterator);
        break;
      case 4:
        destroy(&produtos);
        break;
      case 5:
        printf("%d elementos\n", list_size(produtos));
        break;
      case 6:
        printf("codigo a remover:\n");
        scanf("%d", &cod);
        remove_all(&produtos, cmp_produto, (void *) &cod);
        break;
      case 7:
        exit(1);
      default:
        printf("opcao invalida\n");
    }
    printf("\n");
    menu();
  }

}
