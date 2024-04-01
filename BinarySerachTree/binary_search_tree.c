#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
  int key;
  struct TreeNode *parent, *left, *right;
};

struct Tree
{
  struct TreeNode *root;
};

struct TreeNode*
create_node(int key)
{
  struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));

  node->key = key;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

struct Tree*
create_tree()
{
  struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));
 
  tree->root = NULL;

  return(tree);
}

void
insert_node(struct TreeNode* node, int key)
{
  if(key <= node->key)
  {
    if(node->left == NULL)
    {
      node->left = create_node(key);
      return;
    }
    return insert_node(node->left, key);
  }
  if(key > node->key)
  {
    if(node->right == NULL)
    {
      node->right = create_node(key);
      return;
    }
    return insert_node(node->right, key);
  }
}

void
insert(struct Tree* tree, int key)
{
  if(tree != NULL)
  {
    if(tree->root != NULL)
    {
      insert_node(tree->root, key);
    }
    else
    {
      tree->root = create_node(key);
    }
  }
  else
  {
    tree = create_tree();
    tree->root = create_node(key);
  }
}

void
print_node(int key, int b)
{
  for(int i = 0; i < b; i++)
  {
    printf("\t");
  }
  printf("%d\n", key);
}

void
print_tree(struct TreeNode* aux, int b)
{
  if (aux == NULL)
  {
    return;
  }

  print_node(aux->key, b);
  print_tree(aux->right, b+1);
  print_tree(aux->left, b+1);
}

void
free_node(struct TreeNode* aux)
{
  if(aux == NULL)
  {
    return;
  }

  free_node(aux->left);
  free_node(aux->right);

  free(aux);
}

void
free_tree(struct Tree* tree)
{
  free_node(tree->root);

  free(tree);
}

int
main()
{
  struct Tree* tree = create_tree();

  insert(tree,2);
  insert(tree,1);
  insert(tree,0);
  insert(tree,3);

  print_tree(tree->root, 0);

  return(0);
}
