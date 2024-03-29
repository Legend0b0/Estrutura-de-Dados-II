#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Exercicio
// Fazer com os 3 metodos de hash, deslocamento

#define SIZE 16
#define L 4
#define W 32
#define PRIME_CONST 31
#define A ((sqrt(5)/2) - 1)

struct Data
{
  char* name;
  unsigned long long int key;
  struct Data* next;
  struct Data* prev;
};

char* read_name(char* name)
{
  fgets(name, 128, stdin);
  name[strlen(name)-1] = 0;
  
  return(name);
}

struct Data** createTable()
{
  struct Data** hashtable = (struct Data**)calloc(SIZE, sizeof(struct Data*));

  return(hashtable);
}

int division_func(unsigned long long int key)
{
  return(key % SIZE);
}

int multiply_func(unsigned long long int key)
{
  return(SIZE * ((key * A) - (unsigned long long int)(key * A)));
}

int multiply_shift_func(unsigned long long int key)
{
  return(((unsigned long long int)(key * (pow(2, W) * A)) % (unsigned int)(pow(2, W))) >> (W - L));
}

unsigned long long int calc_key(char* name)
{
  unsigned long long int key = 0;
  
  for(int i = 0; name[i] != '\0'; i++)
  {
    key += ((name[i]) * (pow(PRIME_CONST, (i+1))));
  }

  return(key);
}

void insert(struct Data** hashtable, char* name)
{
  struct Data* aux = (struct Data*)malloc(sizeof(struct Data));
  aux->key = calc_key(name);
  aux->name = (char*)malloc(strlen(name)*sizeof(char));

  strcpy(aux->name, name);

  printf("\n\n%d\n\n", multiply_shift_func(aux->key));

  if(hashtable[multiply_shift_func(aux->key)] != NULL)
  {
    aux->next = hashtable[multiply_shift_func(aux->key)];
    hashtable[multiply_shift_func(aux->key)]->prev = aux;
  }
  else
  {
    aux->next = NULL;
  }
  
  hashtable[multiply_shift_func(aux->key)] = aux;
  hashtable[multiply_shift_func(aux->key)]->prev = NULL;
}

struct Data* search(struct Data** hashtable, char* name)
{
  struct Data* aux = hashtable[multiply_shift_func(calc_key(name))];

  while(aux != NULL)
  {
    if(aux->key == calc_key(name))
    {
      return(aux);
    }
    aux = aux->next;
  }

  return(NULL);
}

void delete_data(struct Data* aux)
{
    free(aux->name);
    memset(aux, 0, sizeof(struct Data));
    free(aux);

    return;
}

void delete(struct Data** hashtable, struct Data* aux)
{
  if(aux == NULL)
  {
    printf("\nNao existe\n");

    return;
  }

  if((aux->prev == NULL) && (aux->next == NULL))
  {
    hashtable[multiply_shift_func(aux->key)] = NULL;
   
    delete_data(aux);

    return;
  }

  if((aux->prev != NULL) && (aux->next == NULL))
  {
    aux->prev->next = NULL;

    delete_data(aux);

    return;
  }

  if((aux->prev == NULL) && (aux->next != NULL))
  {
    aux->next->prev = NULL;

    hashtable[multiply_shift_func(aux->key)] = aux->next;

    delete_data(aux);

    return;
  }

  if((aux->prev != NULL) && (aux->next != NULL))
  {
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    delete_data(aux);

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
      printf("\t<->\t%s", aux->name);
      aux = aux->next;
    } 
  
  printf("\t ->\tNULL\n");
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
    setbuf(stdin, NULL);

    switch(option)
    {
      case 1:
      {
        char name[128];
        
        printf("\nDigite o nome a ser inserido na tabela\n\n");
        read_name(name);

        insert(hashtable, name);

        break;
      }

      case 2:
      {
        char name[128];
        struct Data* aux;

        printf("\nDigite o nome a ser procurado na tabela\n\n");
        read_name(name);

        aux = search(hashtable, name);

        if(aux != NULL)
        {
          printf("\nIndex - %d\n", multiply_shift_func(aux->key));
        }
        else
        {
          printf("\nNao existe\n");
        }

        break;
      }

      case 3:
      {
        char name[128];

        printf("\nDigite o nome a ser deletado na tabela\n\n");
        read_name(name);
       
        delete(hashtable, search(hashtable, name));

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
