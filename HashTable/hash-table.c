#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

struct Data
{
  char* name;
  int key;
  struct Data* next;
};

int hash_code(int key)
{
  return(key % SIZE);
}

int hash(char* name)
{
  int key = 0;

  for(int i = 0; name[i] != '\0'; i++)
  {
    key = name[i] * (i+1);
  }

  return(key);
}

struct Data** createTable()
{
  struct Data** hashtable = (struct Data**) malloc(SIZE * sizeof(struct Data*));

  for(int i = 0; i < SIZE; i++)
  {
    hashtable[i] = NULL;
  }

  return(hashtable);
}

void insert(struct Data** hashtable, char* name)
{
  struct Data* aux = (struct Data*) malloc(sizeof(struct Data));
  aux->key = hash(name);
  aux->name = (char*)malloc(strlen(name)*sizeof(char));

  strcpy(aux->name, name);

  if(hashtable[hash_code(aux->key)] == NULL)
  {
    aux->next = NULL;
    hashtable[hash_code(aux->key)] = aux;
  }
  else
  {
    aux->next = hashtable[hash_code(aux->key)];
    hashtable[hash_code(aux->key)] = aux;
  }
}

int search(struct Data** hashtable, char* name)
{
  return(hash_code(hash(name)));
}

void delete(struct Data** hashtable, char* name)
{
  int key = hash(name);
  int index = hash_code(key);
  struct Data* aux = (struct Data*) malloc(sizeof(struct Data));

  aux = hashtable[index];

  if(aux == NULL)
  {
    printf("Nao existe");

    return;
  }
  
  if(aux->next != NULL)
  {
    if(aux->key == key)
    {
      hashtable[index] = aux->next;
      free(aux);

      return;
    }

    do
    {
      if(aux->next->key == key)
      {
        struct Data* aux2 = aux->next;
        aux->next = aux->next->next;
        free(aux2);

        return;
      }

      aux->next = aux->next->next;
    }
    while (aux->next != NULL);   

    printf("Nao existe");

    return;
  }

  if(aux->key == key)
  {
    free(aux);
    hashtable[index] = NULL; 

    return;
  }
}

void print_table(struct Data** hashtable)
{
  struct Data* aux;

  printf("\n");

  for(int i = 0; i < SIZE; i++)
  {
    aux = hashtable[i];

    printf("%d", i);

    while(aux != NULL)
    {
      printf(" -> %s", aux->name);
      aux = aux->next;
    } 
    
    printf(" -> NULL\n");
  }
  printf("\n");

  return;
}

void destroy_data(struct Data *data)
{
  if(data->next != NULL)
  {
    free(data->next->name);
    destroy_data(data->next);
  }
  else
  {
    return;
  }


  memset(data->next, 0, sizeof(struct Data));
  free(data->next);

  return;
}

void destroy_table(struct Data **hashtable)
{
  for(int i = 0; i < SIZE; i++)
  {
    if(hashtable[i] != NULL)
    {
      destroy_data(hashtable[i]);

      free(hashtable[i]->name);
      memset(hashtable[i], 0, sizeof(struct Data));
      free(hashtable[i]);
    }
  }

  free(hashtable);
}

int
main()
{
  struct Data** hashtable = createTable();

  int option;

  do
  {
    printf("\nSelecione uma opcao\n\n1- Inserir nome\n2- Procurar nome\n3- Deletar nome\n4- Printar tabela\n5- Sair\n\n");
    scanf("%d", &option);

    switch(option)
    {
      case 1:
      {
        char name[30];
        
        printf("\nDigite o nome a ser inserido na tabela\n\n");
        scanf("%s", name);

        insert(hashtable, name);

        break;
      }

      case 2:
      {
        char name[30];

        printf("\nDigite o nome a ser procurado na tabela\n\n");
        scanf("%s", name);

        int index = search(hashtable, name);

        if(hashtable[index] != NULL)
        {
          printf("\nIndex - %d\n", index);
        }
        else
        {
          printf("\nNao existe\n");
        }

        break;
      }

      case 3:
      {
        char name[30];

        printf("\nDigite o nome a ser procurado na tabela\n\n");
        scanf("%s", name);
       
        delete(hashtable, name);

        break;
      }

      case 4:
      {
        print_table(hashtable);

        break;
      }

      case 5:
      {
        destroy_table(hashtable);

        break;
      }

      default:
      {
        printf("\nOpcao invalida\n\n");
      }
    }
  }
  while(option != 5);

  return(0);
}
