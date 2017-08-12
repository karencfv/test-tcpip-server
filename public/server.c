#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int socket_fd, client_socket_fd, port_no, n, pid;
  socklen_t client_len;
  struct sockaddr_in serv_addr, cli_addr;
  char buffer[256];

  if (argc < 2)
  {
    fprintf(stderr,"Error: No port provided\n");
    exit(1);
  }

  socket_fd =  socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    fprintf(stderr,"Error: Could not create socket\n", argv[0]);
    exit(1);
  }

  memset((char *) &serv_addr, 0, sizeof(serv_addr));

  port_no = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;

  serv_addr.sin_addr.s_addr = INADDR_ANY;

  serv_addr.sin_port = htons(port_no);

  if (bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    error("Error on binding");

  listen(socket_fd, 5);

  client_len = sizeof(cli_addr);

  while (1)
  {
    client_socket_fd = accept(socket_fd, (struct sockaddr *) &cli_addr, &client_len);

    if (client_socket_fd == -1)
    error("Error on accept");

    printf("I've connected from %s port %d!\n",
           inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    pid = fork();

    if (pid == -1)
      error("Error on fork");

    send(client_socket_fd, "I'm the server, ack!\n", 24, 0);

    memset(buffer, 0, 256);

    n = read(client_socket_fd, buffer, 256);
    if (n == -1)
      error("Error reading from socket");

    printf("Client says: %s\n", buffer);
  }

  close(client_socket_fd);
  close(socket_fd);
  return 0;
}
