#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
  int socket_fd, port_no, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];

  if (argc < 2)
  {
    fprintf(stderr,"Error: No port provided\n");
    exit(1);
  }

  port_no = atoi(argv[2]);
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    fprintf(stderr,"Error: Could not create socket\n", argv[0]);
    exit(1);
  }

  server = gethostbyname(argv[1]);

  if (server == NULL)
  {
    fprintf(stderr,"Error: no such host\n");
    exit(1);
  }

  memset((char *) &serv_addr, 0, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;

  bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr, server->h_length);

  serv_addr.sin_port = htons(port_no);

  if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("Error connecting");

  while (1)
  {
    printf("Say something: ");

    memset(buffer, 0, 256);

    fgets(buffer, 256, stdin);

    n = write(socket_fd, buffer, strlen(buffer));
    if (n < 0)
      error("Error writing to socket");

    memset(buffer, 0, 256);

    n = read(socket_fd, buffer, 256);
    if (n < 0)
      error("Error reading from socket");
    printf("%s\n", buffer);
  }

  close(socket_fd);
  return 0;
}
