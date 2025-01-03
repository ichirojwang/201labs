#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  printf("Please enter some text\n");

  // char inputs[100];
  char *saveptr;
  // scanf("%[^\n]%*c", inputs);

  char *inputs = NULL;
  size_t n = 0;
  size_t len = getline(&inputs, &n, stdin);
  if (len == -1) {
    perror("Error with getline\n");
    exit(EXIT_FAILURE);
  } else if (len > 0) {
    inputs[len - 1] = '\0';
  }

  char *token = strtok_r(inputs, " ", &saveptr);
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok_r(NULL, " ", &saveptr);
  }
  return 0;
}
