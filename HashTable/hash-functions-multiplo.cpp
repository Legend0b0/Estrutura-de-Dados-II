#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <chrono>

#define SIZE 1024
#define L 10
#define W 32
#define PRIME_CONST 31
#define A ((sqrt(5)/2) - 1)

struct Data
{
  int key;
};

struct Data** createTable()
{
  struct Data** hashtable = (struct Data**)calloc(SIZE, sizeof(struct Data*));

  return(hashtable);
}

int division_func(int key)
{
  return(key % SIZE);
}

int multiply_func(int key)
{
  return(SIZE * ((key * A) - (int)(key * A)));
}

int multiply_shift_func(int key)
{
  long long int doisW = pow(2, W);    //2 elevado a w bits
  long long int a = A * doisW;    
  long long int resto = (key * a) % doisW;
  
  return(resto >> (W - L));
}

void insert(struct Data** hashtable, int value, int (*ptr)(int), int* count)
{
  struct Data* aux = (struct Data*)malloc(sizeof(struct Data));
  aux->key = value;

  if(hashtable[(*ptr)(aux->key)] != NULL)
  {
    (*count)++;
    free(hashtable[(*ptr)(aux->key)]);
  }
 
  hashtable[(*ptr)(aux->key)] = aux;

  return;
}

void print_table(struct Data** hashtable)
{
  struct Data* aux;

  printf("\n");

  for(int i = 0; i < SIZE; i++)
  {
    printf("%d", i);
    printf("\t%d\n", aux->key);
  }

  printf("\n");

  return;
}

void destroy_table(struct Data **hashtable)
{
  for(int i = 0; i < SIZE; i++)
  {
    if(hashtable[i] != NULL)
    {
      memset(hashtable[i], 0, sizeof(struct Data));
      free(hashtable[i]);
    }
  }

  free(hashtable);
}

int main()
{
  int count;

  int (*fp)(int);

  struct Data** hashtable = createTable();
  
  std::chrono::time_point<std::chrono::system_clock> start, end;


//  Division func
  hashtable = createTable();

  count = 0;

  fp = division_func;

  start = std::chrono::system_clock::now();

  for(int i = 0; i < SIZE; i++)
  {
    insert(hashtable, i * PRIME_CONST, fp, &count);
  }

  end = std::chrono::system_clock::now();
  
  std::chrono::duration<double> elapsed_seconds = end - start;

  printf("Division function - %d colisoes\n", count);
  printf("%3.5lf us\n\n", ((elapsed_seconds.count())*1000000));

  destroy_table(hashtable);


//  Multiply func
  hashtable = createTable();

  count = 0;

  fp = multiply_func;

  start = std::chrono::system_clock::now();

  for(int i = 0; i < SIZE; i++)
  {
    insert(hashtable, i * PRIME_CONST, fp, &count);
  }

  end = std::chrono::system_clock::now();
  
  elapsed_seconds = end - start;

  printf("Multiply function - %d colisoes\n", count);
  printf("%3.5lf us\n\n", ((elapsed_seconds.count())*1000000));

  destroy_table(hashtable);


//  Multiply-Shift func
  hashtable = createTable();

  count = 0;

  fp = multiply_shift_func;

  start = std::chrono::system_clock::now();

  for(int i = 0; i < SIZE; i++)
  {
    insert(hashtable, i * PRIME_CONST, fp, &count);
  }

  end = std::chrono::system_clock::now();
  
  elapsed_seconds = end - start;

  printf("Multiply-Shift function - %d colisoes\n", count);
  printf("%3.5lf us\n", ((elapsed_seconds.count())*1000000));

  destroy_table(hashtable);

  return 0;
}
