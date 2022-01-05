#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/*
 * This is the data that's used to test this program.  It forms a tree that
 * looks like this:
 *
 *               64
 *              /  \
 *             /    \
 *            /      \
 *           /        \
 *          32        96
 *         /  \      /  \
 *        /    \    /    \
 *       16    48  80    112
 *      /  \     \   \   /  \
 *     8   24    56  88 104 120
 */
#define NUM_TEST_DATA 13
const int TEST_DATA[NUM_TEST_DATA] =
  {64, 32, 96, 16, 48, 80, 112, 8, 24, 56, 88, 104, 120};

int cmp_ints(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int main(int argc, char** argv) {

  printf("== Creating BST...\n");
  struct bst* bst = bst_create();
  printf("\n== Inserting %d values into BST...\n", NUM_TEST_DATA);
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    bst_insert(bst, TEST_DATA[i], (void*)&TEST_DATA[i]);
  }

  int* sorted = malloc(NUM_TEST_DATA * sizeof(int));
  memcpy(sorted, TEST_DATA, NUM_TEST_DATA * sizeof(int));
  qsort(sorted, NUM_TEST_DATA, sizeof(int), cmp_ints);

  printf("\n== Creating iterator over BST...\n");
  struct bst_iterator* iter = bst_iterator_create(bst);
  int* value;
  int key, k = 0;
  printf("\n== Using iterator to enumerate BST: key / value (expected)\n");
  while (k < NUM_TEST_DATA && bst_iterator_has_next(iter)) {
    key = bst_iterator_next(iter, (void**)&value);
    if (value) {
      printf("  - %3d / %3d (%3d)\n", key, *value, sorted[k]);
    } else {
      printf("  - value unexpectedly NULL for key %3d (expected %3d)\n", key,
        sorted[k]);
    }
    k++;
  }

  printf("\n== Making sure all nodes were visited (expect 1): %d\n",
    k == NUM_TEST_DATA);
  printf("== Making sure no nodes left to visit in iterator (expect 0): %d\n",
    bst_iterator_has_next(iter));

  free(sorted);
  bst_iterator_free(iter);
  bst_free(bst);

  return 0;
}
