#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "stack.h"

struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst {
  struct bst_node* root;
};

struct bst* bst_create() {

  struct bst* tree = malloc(sizeof(struct bst)); 
  tree->root = NULL;

  return tree;
}

void bst_free_helper(struct bst_node* curr) {
    if (curr != NULL){
      bst_free_helper(curr->left);
      bst_free_helper(curr->right);
      free(curr);
    }
}

void bst_free(struct bst* bst) {
  /*
   struct bst_node* temp;

    struct stack *stack = stack_create();
    stack_push(stack, bst->root);

    while(stack_isempty(stack) != 1){
      temp = stack_pop(stack);
      if(temp->left != NULL){
        stack_push(stack, temp->left);
      }
      if(temp->right != NULL){
        stack_push(stack, temp->right);
      }
    free(temp);
    }
    stack_free(stack);
    free(bst);
  */

  /*
  or the recursive way:
  */

  struct bst_node* curr = bst->root;
  bst_free_helper(curr);
  free(bst);
  return;
}

int bst_size(struct bst* bst) {
  int size = 0;
  struct bst_node* temp;
  struct stack *stack = stack_create();
  stack_push(stack, bst->root);

  while(stack_isempty(stack) != 1){
      temp = stack_pop(stack);
      size++;

      if(temp->left != NULL){
        stack_push(stack, temp->left);
      }
      if(temp->right != NULL){
        stack_push(stack, temp->right);
      }
    }
  stack_free(stack);
  return size;
}

void bst_insert(struct bst* bst, int key, void* value) {
  struct bst_node* prev;
  struct bst_node* curr;

  prev = NULL;
  curr = bst->root;
  while (curr != NULL){
  prev = curr;
    if(key < curr->key){
        curr = curr->left;
      }
    else{
        curr = curr->right;
      }
  }
  
  struct bst_node* new_node = malloc(sizeof(struct bst_node));
  new_node->key = key;
  new_node->value = value; 
  new_node->left = NULL;
  new_node->right = NULL;

  if(prev == NULL){
    bst->root = new_node;
    return;
  }

  if (new_node->key < prev->key){
  prev->left = new_node;
  }
  else{
    prev->right = new_node;
  }
  return;
  }

void bst_remove(struct bst* bst, int key) {
  if (bst->root == NULL){   
      return;
  }

  struct bst_node* prev;
  struct bst_node* curr;

  prev = NULL;
  curr = bst->root;

  while (curr != NULL){
    if(key == curr->key){
        break;
      }
    else if (key < curr->key){
        prev = curr;
        curr = curr->left; 
      }
    else{
      prev = curr;
      curr = curr->right;
    }
  } // this way curr - the node to be removed, prev - its parent

  //if N has no children: update PN to point to NULL instead of N
  if (curr->left == NULL && curr->right == NULL){
    if (prev->left == curr){
      prev->left = NULL;
    }
    if (prev->right == curr){
      prev->right = NULL;
    }    
  }
  //else if N has one child: update PN to point to N’s child instead of N
  else if( (curr->left == NULL && curr->right != NULL) || (curr->left != NULL && curr->right == NULL) ){
    if ( (prev->left == curr) || curr->left != NULL){
      prev->left = curr->left;
    }

    if ( (prev->right == curr) || curr->right != NULL){
      prev->right = curr->right;
    }
  }
  else{
    struct bst_node* leftomost;
    struct bst_node* leftomost_parent;
    
    leftomost = curr->right;
    leftomost_parent = NULL;

    while (leftomost->left != NULL){
      leftomost_parent = leftomost;
      leftomost = leftomost->left; 
    }
    leftomost->left = curr->left;

    if (leftomost != curr->right){
      leftomost_parent->left = leftomost->right;
      leftomost->right = curr->right;
    }
    if(prev == NULL){
      bst->root= leftomost;
    }
    else if(prev->left == curr){
      prev->left = leftomost;
    }
    else if(prev->right == curr){
      prev->right = leftomost;
    }
    
  } 
  free(curr);
  return;
}

void* bst_get_helper(struct bst_node* curr, int key){
  if (curr == NULL){  
    return NULL;
  }

  if (curr->key == key){
    return curr->value;
  }

  void* left_val = bst_get_helper(curr->left, key);
  void* right_val = bst_get_helper(curr->right, key);
  if(left_val == NULL && right_val == NULL){
    return NULL;
  }
  if(right_val != NULL){
    return right_val;
  }
  if(left_val != NULL){
    return left_val;
  }
}

void* bst_get(struct bst* bst, int key) {
  if (bst->root == NULL) return NULL;

  struct bst_node* prev;
  struct bst_node* curr;

  prev = NULL;
  curr = bst->root;

  while (curr != NULL){
  prev = curr;
    if(key == curr->key){
        return curr->value;
      }
    else if (key < curr->key){
        curr = curr->left; 
      }
    else{
      curr = curr->right;
    }
  }
  return NULL;

/* RECURSIVE WAY: 
  struct bst_node* curr = bst->root;
  return bst_get_helper(curr, key);
*/
  }

int bst_height_helper(struct bst_node* curr){

    if (curr == NULL){   // base case
      return 0;
    }
    int counter1 = 0, counter2 = 0;
    counter1 = bst_height_helper(curr->left) + 1;   
    counter2 =  bst_height_helper(curr->right) + 1;
    if (counter1> counter2){
      return counter1;
    } 
    else{
      return counter2;
    }
}


/*
 * This function returns the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 */
  int bst_height(struct bst* bst) {

    int height;
    struct bst_node* curr = bst->root;
    height = bst_height_helper(curr);
    return height-1;
 }


int bst_path_sum_helper(struct bst_node* curr, int sum){

    if (curr == NULL){ 
      return 0;
    }
    int counter1 = 0, counter2 = 0;
    counter1 = bst_path_sum_helper(curr->left, sum - curr->key);   
    counter2 =  bst_path_sum_helper(curr->right, sum - curr->key);
    if (counter1 == 1 || counter2 == 1){
      return 1;
    } 
    else if (curr->left == NULL && curr->right == NULL) {
      return (sum == curr->key);
    }
    return 0;
}
/*
 * This function determines whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 */
int bst_path_sum(struct bst* bst, int sum) {
    int compare;
    struct bst_node* curr = bst->root;
    if (bst_path_sum_helper(curr, sum) == 1){
      return 1;
    }
    else{
      return 0;
    }
}

int bst_range_sum_helper(struct bst_node* curr, int lower, int upper){

    if (curr == NULL){ 
      return 0;
    }
    if (curr->key < lower){
      return bst_range_sum_helper(curr->right, lower, upper);
      //do not work with it (if == it's fine)
    }
    if (curr->key > upper){
      return bst_range_sum_helper(curr->left, lower, upper);
      //do not work with it (if == it's fine)
    }
    int sum;
    sum = bst_range_sum_helper(curr->left, lower, upper) + curr->key + bst_range_sum_helper(curr->right, lower, upper);
    return sum;
}

/*
 * This function should computes a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  struct bst_node* curr = bst->root;
    return bst_range_sum_helper(curr, lower, upper);
}

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

void bst_iterator_create_helper(struct bst_node* curr, struct stack * stack) {
    if (curr != NULL){
      bst_iterator_create_helper(curr->right, stack);
      stack_push(stack, curr);
      bst_iterator_create_helper(curr->left, stack);
    }
    return;
}

struct bst_iterator* bst_iterator_create(struct bst* bst) {
  struct bst_node* curr = bst->root;

  struct bst_iterator* iter = malloc(sizeof(struct bst_iterator));
  iter->stack = stack_create();
  bst_iterator_create_helper(curr, iter->stack);

  return iter;
}

void bst_iterator_free(struct bst_iterator* iter) {
  stack_free(iter->stack);
  free(iter);
  return;
}

int bst_iterator_has_next(struct bst_iterator* iter) {
    return !stack_isempty(iter->stack);
}

int bst_iterator_next(struct bst_iterator* iter, void** value) {
  struct bst_node* curr = stack_pop(iter->stack);

  if (value) {
    *value = curr->value;
  }
  else{
    *value = NULL;
  }
  return curr->key;
}
