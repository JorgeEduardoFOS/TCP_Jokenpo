#include <stdio.h>//FILE
#include <netdb.h>//sockaddr, socklen_t

#define LISTENQ 10
#define MAXDATASIZE 200
#define MAXLINE 4096

ssize_t writen(int fd, const void *vptr, size_t n);
void err_quit(const char *s);
void Close(int fd);
void Write(int fd, const void *buf, size_t count);
int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);
int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *restrict src, void *restrict dst);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
void Fputs(const char *restrict s, FILE *restrict fluxo);
void Fputs(const char *restrict s, FILE *restrict fluxo);
int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
void str_cli(FILE *fp, int sockfd);
ssize_t Writen(int fd, const void *vptr, size_t n);
