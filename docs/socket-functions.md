## Socket Functions in C

The following is a description of the functions used here.

**int socket(int domain, int type, int protocol)**
Creates an endpoint for communication, parameters specify the following:
- domain: protocol family, `AF_INET` for IPv4 and `AF_INET6` for IPv6.
- type: type of socket within the chosen family, `SOCK_STREAM` for TCP/IP and `SOCK_DGRAM` for UDP/IP.
- protocol: is normally set to `0` to use the default protocol, which is TCP for a streaming protocol, and UDP for a datagram protocol.

#### int connect(int fd, struct sockaddr *remote_host, socklen_t addr_length)

#### int bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
