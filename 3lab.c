#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {

  char *buffer = NULL;
  size_t bufsize = 0;

  while (1) {

    printf("Enter full command path: ");
    size_t len = getline(&buffer, &bufsize, stdin);

    if (len == -1) {
      perror("Failed to read line!\n");
      break;
    } else if (len > 0) {
      buffer[len - 1] = '\0';
    }

    pid_t pid = fork();

    if (pid == 0) {

      printf("%s\n", buffer);

      if (execl(buffer, buffer, (char *)NULL) == -1) {
        perror("execl failed\n");
        exit(EXIT_FAILURE);
      }
    } else {
      int wstatus = 0;
      if (waitpid(pid, &wstatus, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(wstatus)) {
        printf("Child exited.\n");
      }
      free(buffer);
      buffer = NULL;
    }
  }
}
