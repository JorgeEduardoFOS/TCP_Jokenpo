#include "wraper_others.h"
#include <string.h>
#include <stdlib.h>

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	if (Readline(sockfd, recvline, MAXLINE) == 0)
		err_quit("str_cli: server terminated prematurely");
	//////////teste
	//printf("%ld\n", strlen(recvline));

	/////////
	Fputs(recvline, stdout);

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
		if (!strcmp(recvline,"clear\n")){
			system("clear");
			while (strcmp(recvline,"next\n")) {
				if (Readline(sockfd, recvline, MAXLINE) == 0)
					err_quit("str_cli: server terminated prematurely");
				if (strcmp(recvline,"next\n"))
					Fputs(recvline, stdout);
				else if (!strcmp(recvline,"quit\n")){
					shutdown(sockfd, SHUT_RDWR);
					Close (sockfd);
					exit(0);
					return;
				}
			}
		}
		else
			Fputs(recvline, stdout);
	}
}
