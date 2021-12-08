#include <stdio.h>//snprintf
#include <stdlib.h>//exit
#include <string.h>//bzero, strlen
#include <unistd.h> //fork, close, write
#include <time.h> // Tirar se não for mais necessário.
#include <errno.h>
#include "wraper_others.h"

int main (int argc, char **argv) {
  socklen_t clilen;//, addrlen;
  int    listenfd, connfd;
  struct sockaddr_storage cliaddr;
  pid_t childpid;
  //char toCli[MAXDATASIZE];

  switch (argc) {
    case 1:
      listenfd = tcp_listen(NULL, "13", &clilen);
      break;
    case 2:
      listenfd = tcp_listen(NULL, argv[1], &clilen);
      break;
    case 3:
      listenfd = tcp_listen(argv[1], argv[2], &clilen);
      break;
    default:
      err_quit("usage: daytimetcpsrv2 [ <host>] <service or port>");
  }

  for ( ; ; ) {
    clilen = sizeof(cliaddr) ;
    connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

    if ((childpid = fork()) == 0) {
      Close(listenfd);

      ////////Jokenpo
      //strcpy(toCli,"Digite \"1\" para pedra, \"2\" para papel, \"3\" para tesoura, \"q\" para sair e outras teclas para exibir mais opções.\n");
      //Write(connfd, toCli, strlen(toCli));
      //strcpy(toCli,"pedra\n");
      //Write(connfd, toCli, strlen(toCli));


      ///////////Jokenpo end

      str_echo (connfd);
      shutdown(connfd, SHUT_RDWR);
      exit(0);
    }

  }
  return(0);
}
