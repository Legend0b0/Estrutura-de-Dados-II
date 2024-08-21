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

struct TreeNode*
minimum(struct TreeNode* node)
{
  while((node != NULL) && (node->left != NULL))
  {
    node = node->left;
  }
  return(node);
}

struct TreeNode*
maximum(struct TreeNode* node)
{
  while(node != NULL)
  {
    node = node->right;
  }
  return(node);
}

struct TreeNode*
successor(struct TreeNode* node)
{
  if(node->right != NULL)
  {
    return(minimum(node->right));
  }

  struct TreeNode *parent = node->parent;

  while((parent != NULL) && (node == parent->right))
  {
    node = parent;
    parent = parent->parent;
  }
  return(parent);
}

struct TreeNode*
predeccessor(struct TreeNode* node)
{
  if(node->left != NULL)
  {
    return(maximum(node->left));
  }
  struct TreeNode* parent = node->parent;

  while((parent != NULL) && (node == parent->left))
  {
    node = parent;
    parent = parent->parent;
  }
  return(parent);
}

void
insert_node(struct TreeNode* node, int key)
{
  if(key == node->key)
  {
    return;
  }
  if(key < node->key)
  {
    if(node->left == NULL)
    {
      node->left = create_node(key);
      node->left->parent = node;
      return;
    }
    return insert_node(node->left, key);
  }
  if(key > node->key)
  {
    if(node->right == NULL)
    {
      node->right = create_node(key);
      node->right->parent = node;
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
}

struct TreeNode*
search_node(struct TreeNode* node, int key)
{
  if((node == NULL) || (node->key == key))
  {
    return(node);
  }

  if(key < node->key)
  {
    return(search_node(node->left, key));
  }

  if(key > node->key)
  {
    return(search_node(node->right, key));
  }

  return(NULL);
}

struct TreeNode*
search(struct Tree* tree, int key)
{
  if((tree != NULL) && (tree->root != NULL))
  {
    return(search_node(tree->root, key));
  }
  else
  {
    return(NULL);
  }
}

void
transplant(struct Tree* tree, struct TreeNode* u, struct TreeNode* v)
{
  if(u->parent == NULL)
  {
    tree->root = v;
  }
  else
  {
    if((u->parent->left != NULL) && (u == u->parent->left))
    {
      u->parent->left = v;
    }
    if((u->parent->right != NULL) && (u == u->parent->right))
    {
      u->parent->right = v;
    }
    if(v != NULL)
    {
      v->parent = u->parent;
    }
  }
}

void
delete(struct Tree* tree, int key)
{
  struct TreeNode* aux = search(tree, key);

  if(aux != NULL)
  {
    if((aux->left == NULL) && (aux->right == NULL))
    {
      transplant(tree, aux, NULL);
      free(aux);

      return;
    }
    if((aux->left != NULL) && (aux->right == NULL))
    {
      transplant(tree, aux, aux->left);
      free(aux);

      return;
    }
    if((aux->left == NULL) && (aux->right != NULL))
    {
      transplant(tree, aux, aux->right);
      free(aux);

      return;
    }
    if((aux->left != NULL) && (aux->right != NULL))
    {
      struct TreeNode* aux1 = minimum(aux->right);
        
      if(aux1 != aux->right)
      {
        transplant(tree, aux1, aux->right);
        aux1->right = aux->right;
        aux1->right->parent = aux1;
      }
      
      transplant(tree, aux, aux1);
      aux1->left = aux->left;
      aux1->left->parent = aux1;

      free(aux);
    }
  }
}

void
print_inorder(struct TreeNode* node)
{
  if(node != NULL)
  {
    print_inorder(node->left);
    printf("%d\n", node->key);
    print_inorder(node->right);
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

  print_tree(aux->right, b+1);
  print_node(aux->key, b);
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

  insert(tree, 5);
  insert(tree, 1);
  insert(tree, 2);
  insert(tree, 7);
  
  delete(tree, 5);

  printf("\n");

  free_tree(tree);

  return(0);
}

/*
    pre == +*+36-415
    in == 3+6*4-1+5
    pos == 36+41-*5+
*/
