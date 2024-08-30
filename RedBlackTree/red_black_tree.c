#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

struct TreeNode
{
  int color;
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
  node->color = RED;

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
left_rotate(struct Tree* tree, struct TreeNode* node)
{
  struct TreeNode* right = node->right;
  
  node->right = right->left;
  
  if(node->right != NULL)
  {
    node->right->parent = node;
  }
  
  right->parent = node->parent;
  
  if(node->parent != NULL)
  {
    if(node == node->parent->left)
    {
      node->parent->left = right;
    }
    else
    {
      node->parent->right = right;
    }
  }
  else
  {
    tree->root = right;
  }
  
  right->left = node;
  node->parent = right;
}

void
right_rotate(struct Tree* tree, struct TreeNode* node)
{
  struct TreeNode* left = node->left;
  
  node->left = left->right;
  
  if(node->left != NULL)
  {
    node->left->parent = node;
  }
  
  left->parent = node->parent;
  
  if(node->parent != NULL)
  {
    if(node == node->parent->right)
    {
      node->parent->right = left;
    }
    else
    {
      node->parent->left = left;
    }
  }
  else
  {
    tree->root = left;
  }
  
  left->right = node;
  node->parent = left;
}

int
black_height(struct TreeNode* node)
{
  int height = 1;
  if(node == NULL)
  {
    return height;
  }

  node = node->left;
  while(node != NULL)
  {
    if(node->color == BLACK)
    {
      height++;
    }
    node = node->left;
  }

  return height;
}

void
insert_fix_up(struct Tree* tree, struct TreeNode* node)
{
  while((node != tree->root) && (node->parent->color == RED) && (node->color == RED))
  {
    if(node->parent == node->parent->parent->left)
    {
      struct TreeNode* uncle = node->parent->parent->right;

      if((uncle != NULL) && (uncle->color == RED))
      {
        uncle->color = BLACK;
        node->parent->color = BLACK;
        node->parent->parent->color = RED;

        node = node->parent->parent;
      }
      else
      {
        if(node == node->parent->right)
        {
          node = node->parent;
          left_rotate(tree, node);
        }
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        right_rotate(tree, node->parent->parent);
      }
    }
    else
    {
      struct TreeNode* uncle = node->parent->parent->left;
      
      if((uncle != NULL) && (uncle->color == RED))
      {
        uncle->color = BLACK;
        node->parent->color = BLACK;
        node->parent->parent->color = RED;

        node = node->parent->parent;
      }
      else
      {
        if(node == node->parent->left)
        {
          node = node->parent;
          right_rotate(tree, node);
        }
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        left_rotate(tree, node->parent->parent);
      }
    }
  }
  tree->root->color = BLACK;
}

void
insert_node(struct Tree* tree, struct TreeNode* node, int key)
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
      insert_fix_up(tree, node->left);
      return;
    }
    return insert_node(tree, node->left, key);
  }
  if(key > node->key)
  {
    if(node->right == NULL)
    {
      node->right = create_node(key);
      node->right->parent = node;
      insert_fix_up(tree, node->right);
      return;
    }
    return insert_node(tree, node->right, key);
  }
}

void
insert(struct Tree* tree, int key)
{
  if(tree != NULL)
  {
    if(tree->root != NULL)
    {
      insert_node(tree, tree->root, key);
    }
    else
    {
      tree->root = create_node(key);
      insert_fix_up(tree, tree->root);
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
delete_fix_up(struct Tree* tree, struct TreeNode* node)
{
  while((node != tree->root) && (node->color == BLACK))
  {
    struct TreeNode* sibling = NULL;
   
    if((node->parent->left != NULL) && (node == node->parent->left))
    {
      sibling = node->parent->right;

      if((sibling != NULL) && (sibling->color == RED))
      {
        sibling->color = BLACK;
        node->parent->color = RED;
        left_rotate(tree, node->parent);
        sibling = node->parent->right;
      }
      if((sibling != NULL) && (sibling->left != NULL) && (sibling->right != NULL) && (sibling->left->color == BLACK) && (sibling->right->color == BLACK))
      {
        sibling->color = RED;
        node = node->parent;
      }
      else
      {
        if((sibling != NULL) && (sibling->right->color == BLACK)) 
        {
          sibling->left->color = BLACK;
          sibling->color = RED;
          right_rotate(tree, sibling);
          sibling = node->parent->right;
        }
        if(sibling != NULL)
        {
          sibling->color = node->parent->color;
          node->parent->color = BLACK;
          sibling->right->color = BLACK;
          left_rotate(tree, node->parent);
          node = tree->root;
        }
      }
    }
    else
    {
      sibling = node->parent->left;

      if((sibling != NULL) && (sibling->color == RED))
      {
        sibling->color = BLACK;
        node->parent->color = RED;
        right_rotate(tree, node->parent);
        sibling = node->parent->left;
      }
      if((sibling != NULL) && (sibling->left != NULL) && (sibling->right != NULL) && (sibling->left->color == BLACK) && (sibling->right->color == BLACK))
      {
        sibling->color = RED;
        node = node->parent;
      }
      else
      {
        if((sibling != NULL) && (sibling->left->color == BLACK))
        {
          sibling->right->color = BLACK;
          sibling->color = RED;
          left_rotate(tree, sibling);
          sibling = node->parent->left;
        }
        if(sibling != NULL)
        {
          sibling->color = node->parent->color;
          node->parent->color = BLACK;
          sibling->left->color = BLACK;
          right_rotate(tree, node->parent);
          node = tree->root;
        }
      }
    }
  }
  node->color = BLACK;
}

void
delete(struct Tree* tree, int key)
{
  struct TreeNode* node = search(tree, key);
  struct TreeNode* aux = node;
  struct TreeNode* aux2 = NULL;

  int aux_color = aux->color;

  if(node->left == NULL)
  {
    aux2 = node->right;
    transplant(tree, node, node->right);
  }
  else
  {
    if(node->right == NULL)
    {
      aux2 = node->left;
      transplant(tree, node, node->left);
    }
    else
    {
      aux = minimum(node->right);
      aux_color = aux->color;
      aux2 = aux->right;

      if(aux != node->right)
      {
        transplant(tree, aux, aux->right);
        aux->right = node->right;
        aux->right->parent = aux;
      }
      else
      {
        aux2->parent = aux;
      }
      transplant(tree, node, aux);
      aux->left = node->left;
      aux->left->parent = aux;
      aux->color = node->color;
    }
  }
  if(aux_color == BLACK)
  {
    if(aux2 != NULL)
    {
      delete_fix_up(tree, aux2);
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
  insert(tree, 3);
  insert(tree, 9);
  insert(tree, 10);
  insert(tree, 7);
  insert(tree, 18);
  insert(tree, 4);
  insert(tree, -10);
  insert(tree, 24);
  insert(tree, 100);

  struct TreeNode* aux = tree->root;

  while(aux != NULL)
  {
    printf("Altura preta: %d\n", black_height(aux));
    aux = aux->left;
  }
  
  free_tree(tree);

  return(0);
}

