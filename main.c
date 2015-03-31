#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

void random_list(LIST_NODE **head_ref, int size);
bool produto_equal(void *data, void *n);
bool produto_greater(void *data, void *n);
bool produto_less(void *data, void *n);
bool produto_iterator(void *data);
void menu(void);
void menu_destroy(void);
void le_produto(LIST_NODE **head);

struct produto{
  int codigo;
  float preco;
};

void random_list(LIST_NODE **head_ref, int size){
  int i;
  struct produto *prod;
  for (i = 0; i < size; i++) {
    prod = (struct produto *) malloc(sizeof(struct produto));
    prod->codigo = i;
    prod->preco = rand();
    push(head_ref, prod);
  }

}

bool asc(void *data1, void *data2){
  return ((struct produto *)data1)->preco < ((struct produto *)data2)->preco;
}

bool produto_equal(void *data, void *n){
  return ((struct produto *)data)->codigo == *((int *)n);
}

bool produto_greater(void *data, void *n){
  return ((struct produto *)data)->codigo > *((int *)n);
}

bool produto_less(void *data, void *n){
  return ((struct produto *)data)->codigo < *((int *)n);
}

bool produto_iterator(void *data){
  printf("codigo: %d preco: %.2f\n", ((struct produto*)data)->codigo, ((struct produto *)data)->preco);
  return TRUE;
}

void menu(void){
  printf("1. insere novo produto\n");
  printf("2. lista todos produtos\n");
  printf("3. lista todos produtos em ordem reversa\n");
  printf("4. destroi a lista\n");
  printf("5. imprimir tamanho da lista\n");
  printf("6. remover elementos\n");
  printf("7. criar lista aleatoria\n");
  printf("8. ordenar por preco\n");
  printf("9. sair\n");
}

void menu_destroy(void){
  printf("1. remove com valor igual\n");
  printf("2. remove com valor maior\n");
  printf("3. remove com valor menor\n");
}

void le_produto(LIST_NODE **head){
  struct produto *prod;
  prod = (struct produto *)malloc(sizeof(struct produto));
  printf("Informe o codigo:\n");
  scanf("%d", &prod->codigo);
  printf("Informe o preco:\n");
  scanf("%f", &prod->preco);
  push(head, prod);
}

int main(void)
{
  srand(time(NULL));
  int option, cod, cod_destroy;
  iterator iterator;
  filter filter;

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
        menu_destroy();
        scanf("%d", &cod_destroy);
        printf("valor:\n");
        scanf("%d", &cod);
        switch (cod_destroy) {
          case 1:
            filter = produto_equal;
            break;
          case 2:
            filter = produto_greater;
            break;
          case 3:
            filter = produto_less;
            break;
          default:
            exit(1);
        }
        remove_all(&produtos, filter, (void *) &cod);
        break;
      case 7:
        printf("quantidade de elementos:\n");
        scanf("%d", &cod);
        random_list(&produtos, cod);
        break;
      case 8:
        sort(&produtos, asc);
        break;
      case 9:
        exit(1);
      default:
        printf("opcao invalida\n");
    }
    printf("\n");
    menu();
  }

}
