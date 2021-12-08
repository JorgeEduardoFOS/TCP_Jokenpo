#include <stdio.h>//perror
#include <stdlib.h>//exit
#include <errno.h>
#include <arpa/inet.h>//inet_peton
#include <unistd.h>
#include "wraper_others.h"

void err_quit(const char *s){
  perror(s);
  exit(1);
}

void Close(int fd) {
  if (close(fd) == -1)
    err_quit("Close error");
}

void Write(int fd, const void *buf, size_t count){
  if (write(fd, buf, count) == -1)
    err_quit("write error");
}

int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen){
  int temp;
  if ((temp = setsockopt(sockfd, level, optname, optval, optlen)) == -1){
    perror("setsockopt error");
    exit(1);
  }
  else
    return temp;
}

int Socket(int domain, int type, int protocol){
  int listenfd;
  if ((listenfd = socket(domain, type, protocol)) == -1){
    perror("socket error");
    exit(1);
  }
  else
    return listenfd;
}

void Inet_pton(int af, const char *restrict src, void *restrict dst){
  if (inet_pton(af, src, dst) <= 0)
    err_quit("inet_pton error");
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  if (bind(sockfd, addr, addrlen) == -1)
    err_quit("bind");
}

void Fputs(const char *restrict s, FILE *restrict fluxo){
  if (fputs(s, fluxo) == EOF)
    err_quit("fputs error");
}
/*char *Fgets(char *restrict s, int size, FILE *restrict stream){
  char *temp;
  if ( ( temp = fgets(s, size, stream)) == NULL) {
    perror("fgets error");
    exit(1);
  } else
    return temp;
}*/
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  if (connect(sockfd, addr, addrlen) < 0)
    err_quit("connect error");
}

void Listen(int sockfd, int backlog){
  if (listen(sockfd, backlog) == -1)
    err_quit("listen error");
}

int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen){
  int connfd;
  if ((connfd = accept(sockfd, addr, addrlen)) == -1 ){
    perror("accept error");
    exit(1);
  }
  else
    return connfd;
}

ssize_t Writen(int fd, const void *vptr, size_t n){
  ssize_t temp;
  if( (temp = writen(fd, vptr, n)) == -1){
    perror("writen error");
    exit(1);
  }
  else
    return temp;
}
