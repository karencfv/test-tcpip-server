## Socket Functions in C

The following is a description of the functions used here.

#### int socket(int domain, int type, int protocol)
Creates an endpoint for communication, parameters specify the following:
- domain: protocol family, `AF_INET` for IPv4 and `AF_INET6` for IPv6.
- type: type of socket within the chosen family, `SOCK_STREAM` for TCP/IP and `SOCK_DGRAM` for UDP/IP.
- protocol: is normally set to `0` to use the default protocol, which is TCP for a streaming protocol, and UDP for a datagram protocol.

#### int bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
Associates a socket to an address which is the host and port number specified.
- fd: Socket file descriptor, previously established socket.
- sockaddr *local_addr: Address tho which it's bound, pointer to (the address of) a structure containing the details of the address to bind to. Needs to be passed as a pointer as the structure that is used depends on the protocol.
- socklen_t addr_length: Size of the address to which it is bound.

#### int listen(int fd, int backlog_queue_size)
Only after the socket has been bound to an address can the server call listen() on the socket.
- fd: Socket file descriptor.
- backlog_queue_size: Maximum number of queued connection requests.

#### int accept(int fd, struct sockaddr *remote_host, socklen_t addr_length)
Causes the process to block until a client connects to the server. Returns a new file descriptor, and all communication on this connection should be done using the new file descriptor.
- fd: Socket file descriptor.
- sockaddr *remote_host: Reference pointer to the address of the client.
- socklen_t addr_length: Size of the address.

#### int connect(int fd, struct sockaddr *remote_host, socklen_t addr_length)
Function called by the client to connect a socket to a remote host (the server).
- fd: Socket file descriptor.
- struct sockaddr *remote_host: Address including port of the host to connect to (needs to know the port number of the server, but it does not need to know its own port number. This is by default assigned by the system when connect is called).
- socklen_t addr_length: Size of the address.

#### int send(int fd, void *buffer, size_t n, int flags)
Sends n bytes from *buffer to socket file descriptor.
Returns the number of bytes sent or -1 on error.

#### int receive(int fd, void *buffer, size_t n, int flags)
Reveives n bytes from socket file descriptor into *buffer.
Returns the number of bytes received or -1 on error.
This is a blocking call. When called to read from a stream, control isn't returned to our program until at least one byte of data is read from the remote site.
