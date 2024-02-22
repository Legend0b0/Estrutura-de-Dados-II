#include <stdio.h>
#include <stdlib.h>

#define SIZE 11

struct Data
{
  char* name;
  int key;
  struct Data* next;
};

int Hash(int key)
{
  return(key % SIZE);
}

int Key(char* name)
{
  int key = 0;
  
  for(int i = 0; name[i] != '\0'; i++)
  {
    key = name[i] * (i+1);
  }

  return(key);
}

struct Data* createTable()
{
 struct Data* hashtable = (struct Data*) malloc(SIZE * sizeof(struct Data));
  for(int i = 0; i < SIZE; i++)
  {
    hashtable[i] = NULL;
  }

  return(hashtable);
}

void Insert(struct Data* hashtable, char* name)
{
  struct Data* data = (struct Data*) malloc(sizeof(struct Data));
  data->key = Key(name);
  data->name = name;

  if(hashtable[Hash(data->key)] == NULL)
    {
      data->next = NULL;
      hashtable[Hash(data->key)] = &data;
    }
  else
  { 
      data->next = hashtable[Hash(data->key)];
      hashtable[Hash(data->key)] = data;
  }
}

int Search(struct Data* hashtable, char* name)
{
  return(Hash(Key(name)));
}

void Delete(struct Data* hashtable, char* name)
{
  int key = Key(name);
  int index = Hash(key);
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
          
        }



      while((hashtable[index]->next != NULL) && (hashtable[index]->key != Key))
        {
        }

      return;
    }
  if(aux->key == key)
  {
    free(aux);
    aux = NULL;

    return;
  }
}





int
main()
{
  struct Data* hashtable = createTable();

  


  return(0);
}
