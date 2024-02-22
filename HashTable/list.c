#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
  int data;
  struct Node *next; 
};

struct List
{
  struct Node *head;
};

struct List* create_list()
{
  struct List *list = (struct List*)malloc(sizeof(struct List));
  if(list != NULL)
  {
    list->head = NULL;
    return(list);
  }
  else
  {
    printf("\nError Create List\n");
    free(list);
    return(NULL);
  }
}

struct Node* create_node()
{
  struct Node *node = (struct Node*)malloc(sizeof(struct Node));

  if(node != NULL)
  {
    node->next = NULL;
    return(node);
  }
  else
  {
    printf("\nError Create Node\n");
    free(node);
    return(NULL);
  }
}

int is_empty(struct List *list)
{
  return(list->head == NULL);
}

void insert_begin(struct List *list, int value)
{
  struct Node *aux = create_node();

  aux->data = value;

  aux->next = list->head;
  list->head = aux;
}

void print_list(struct List *list)
{
  if(!is_empty(list))
  {
    struct Node *aux = list->head;

    printf("\n");
    do
    {
      printf("%d -> ", aux->data);
      aux = aux->next;
    } while(aux != NULL);
    
    printf("\n");
  }
  else
  {
    printf("\nLista Vazia\n");
  }
}

void delete_begin(struct List *list)
{
  if(!is_empty(list))
  {
    struct Node *aux = list->head;
    list->head = aux->next;
    memset(aux, 0, sizeof(struct Node));
    free(aux);
  }
  else
  {
    printf("\nLista Vazia\n");
  }
}

void delete_end(struct List *list)
{
  if(!is_empty(list))
  {
    struct Node *aux = list->head;
    
    if(aux->next != NULL)
    {
      while(aux->next->next != NULL)
      {
        aux = aux->next;
      }
      memset(aux->next, 0, sizeof(struct Node));
      free(aux->next);
      aux->next = NULL;
    }
    else
    {
      memset(aux, 0, sizeof(struct Node));
      free(aux);
      list->head = NULL;
    }
  }
  else
  {
    printf("\nLista Vazia\n");
    return;
  }

}

void search(struct List *list)
{
  if(!is_empty(list))
  {
    int value = 0, count = 0;
    int i = 0;

    struct Node *aux = list->head;
    
    printf("\nEntre com o valor a ser buscado\n");
    scanf("%d", &value);

    printf("\n");
   
    do
    { 
      if(aux->data == value)
      {
        printf("%d ", i);
        count++;
      }

      aux = aux->next;
      i++;
    } while(aux != NULL);

    if(count == 0)
    {
      printf("-1");
    }
    printf("\n");
  }
  else
  {
    printf("\n-1\n");
  }
}

void delete_search(struct List *list)
{
  if(!is_empty(list))
  {
    int value = 0;

    struct Node *aux = list->head;
    
    printf("Entre com o valor a ser deletado\n");
    scanf("%d", &value);
    
    while(aux->data == value)
    {
      delete_begin(list);
      aux = list->head;
    }

    while(aux->next != NULL)
    {
      if(aux->next->data == value)
      {
        struct Node *aux2 = aux->next->next;
        memset(aux->next, 0, sizeof(struct Node));
        free(aux->next);
        aux->next = aux2;
      }
      else
      {
        aux = aux->next;
      }
    }
  }
  else
  {
    printf("\nLista Vazia\n");
  }
}


void destroy_node(struct Node *head)
{
  if(head->next != NULL)
  {
    destroy_node(head->next);
  }
  else
  {
    return;
  }
  
  memset(head->next, 0, sizeof(struct Node));
  free(head->next);

  return;
}

void destroy_list(struct List *list)
{
  if(!is_empty(list))
  {
    destroy_node(list->head);
    
    memset(list->head, 0, sizeof(struct Node));
    free(list->head);

    memset(list, 0, sizeof(struct Node));
    free(list);
  }
}















int
main()
{
  struct List *list = create_list();

  int option = 0;

  do
  {
    scanf("%d", &option);

    switch(option)
    {
      case 1:
      {
        break;
      }
      case 2:
      {
        break;
      }
      case 3:
      {
        break;
      }
      case 4:
      {
        break;
      }
      case 5:
      {
        break;
      }
      case 6:
      {
        break;
      }
      case 7:
      {
        break;
      }
      case 8:
      {
        break;
      }
      default:
      {
        printf("\nOpcao Invalida!\n");
        break;
      }
    }
  } while(option != 8);  

  destroy_list(list);
  
  return(0);
}
