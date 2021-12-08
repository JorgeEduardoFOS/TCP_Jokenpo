#include <stdio.h>//perror
#include <errno.h>
#include <string.h>//strcpy, strcat, bzero
#include <stdlib.h>//exit
#include <unistd.h>//read
#include "wraper_others.h"

int main(int argc, char **argv) {
   int    sockfd;
   char   error[MAXLINE + 1];
   struct sockaddr_in servaddr;

   if (argc != 2) {
      strcpy(error,"uso: ");
      strcat(error,argv[0]);
      strcat(error," <IPaddress>");
      err_quit(error);
   }

   sockfd = socket (AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port   = htons(13);

   Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

   Connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

   str_cli(stdin, sockfd);


   exit(0);


}
