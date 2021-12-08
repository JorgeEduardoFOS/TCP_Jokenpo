#include "wraper.h"
#include <strings.h>

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp){
  int listenfd, n;
  const int on = 1;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("tcp_listen error");
  ressave = res;

  do {
    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0)
      continue; //error, try next one
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
      break; //success

    Close(listenfd);
  } while ( (res = res->ai_next) != NULL);

  if (res == NULL)
    err_quit("tec_listen error");

  Listen(listenfd, LISTENQ);

  if (addrlenp)
    *addrlenp = res->ai_addrlen;//return size of protocol IPaddress

  freeaddrinfo(ressave);

  return (listenfd);
}
