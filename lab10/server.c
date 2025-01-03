#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 64
#define PORT 8000
#define LISTEN_BACKLOG 32

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int total_message_count = 0; // Shared counter for total messages
int client_id_counter = 1;   // Counter to assign unique IDs to clients
pthread_mutex_t count_mutex =
    PTHREAD_MUTEX_INITIALIZER; // Mutex for thread safety
pthread_mutex_t client_id_mutex =
    PTHREAD_MUTEX_INITIALIZER; // Mutex for client ID assignment

struct client_info {
  int cfd;
  int client_id;
};

void *handle_client(void *arg) {
  struct client_info *client = (struct client_info *)arg;
  int id = client->client_id;
  int cfd = client->cfd;
  free(client);
  ssize_t num_read;
  char buf[BUF_SIZE];

  // TODO: print the message received from client
  // TODO: increase total_message_count per message

  while ((num_read = read(cfd, buf, BUF_SIZE)) > 0) {

    buf[num_read] = '\0';
    printf("Client ID: %d: %s", id, buf);

    pthread_mutex_lock(&count_mutex);
    printf("Total message count: %d\n", ++total_message_count);
    pthread_mutex_unlock(&count_mutex);
  }

  if (num_read == -1) {
    handle_error("read");
  }

  if (close(cfd) == -1) {
    handle_error("close");
  }

  return NULL;
}

int main() {
  struct sockaddr_in addr;
  int sfd;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1)
    handle_error("socket");

  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
    handle_error("bind");

  if (listen(sfd, LISTEN_BACKLOG) == -1)
    handle_error("listen");

  for (;;) {
    // TODO: create a new thread when a new connection is encountered
    // TODO: call handle_client() when launching a new thread, and provide

    struct client_info *client =
        (struct client_info *)malloc(sizeof(struct client_info));
    if (client == NULL) {
      handle_error("malloc");
    }

    client->cfd = accept(sfd, NULL, NULL);
    if (client->cfd == -1) {
      free(client);
      handle_error("accept");
    }

    pthread_mutex_lock(&client_id_mutex);
    client->client_id = client_id_counter++;
    pthread_mutex_unlock(&client_id_mutex);

    pthread_t tid;
    if (pthread_create(&tid, NULL, handle_client, client) != 0) {
      free(client);
      handle_error("pthread_create");
    }

    pthread_detach(tid);
  }

  if (close(sfd) == -1)
    handle_error("close");

  return 0;
}
