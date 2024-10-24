#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: fill this part

  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (size <= current->size) {
      return current->id;
    }
    current = current->next;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: fill this part

  struct header *current = free_list_ptr;
  int diff = -1;
  int id = -1;

  while (current != NULL) {
    if (size <= current->size) {
      int newDiff = current->size - size;
      if (diff == -1 || newDiff < diff) {
        diff = newDiff;
        id = current->id;
      }
    }
    current = current->next;
  }

  return id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: fill this part

  struct header *current = free_list_ptr;
  int diff = -1;
  int id = -1;

  while (current != NULL) {
    if (size <= current->size) {
      int newDiff = current->size - size;
      if (diff == -1 || newDiff > diff) {
        diff = newDiff;
        id = current->id;
      }
    }
    current = current->next;
  }

  return id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 24, NULL, 1);
  initialize_block(free_block2, 6, free_block1, 2);
  initialize_block(free_block3, 10, free_block2, 3);
  initialize_block(free_block4, 18, free_block3, 4);
  initialize_block(free_block5, 4, free_block4, 5);

  struct header *free_list_ptr = free_block5;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  return 0;
}
