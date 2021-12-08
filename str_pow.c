#include "wraper_others.h"
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define PEDRA 0
#define PAPEL 1
#define TESOURA 2
#define DIVISOR 3

void str_echo(int sockfd) {
	ssize_t		n;
	char	sendline[MAXLINE], recvline[MAXLINE];
	char menu1[] = "Digite \"1\" para pedra, \"2\" para papel, \"3\" para tesoura, \"q\" para sair e outras teclas para exibir mais opções.\n";
	char menu2[] = "Digite:\n\"1\" para pedra\n\"2\" para papel\n\"3\" para tesoura\n\"q\" para sair\noutras teclas para exibir este menu\n\"p\" para o placar.\n";
	int adversaryChoice, yourPoints = 0, adversaryPoints = 0;
  char adversaryChoiceString[15];

	srandom(time(NULL));

	//strcpy(sendline,menu1);
	Write(sockfd, menu1, strlen(menu1));
again:
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0){

		adversaryChoice = random() % DIVISOR;
		if (adversaryChoice == PEDRA) {
			strcpy(adversaryChoiceString, "PEDRA. ");
		} else if (adversaryChoice == PAPEL) {
			strcpy(adversaryChoiceString, "PAPEL. ");
		} else {
			strcpy(adversaryChoiceString, "TESOURA. ");
		}

		if (!strcmp(recvline,"1\n")) {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			Write(sockfd, menu1, strlen(menu1));
			strcpy(sendline, "Você escolheu PEDRA e seu adversário escolheu ");
			strcat(sendline, adversaryChoiceString);
			if (adversaryChoice == PEDRA) {
				strcat(sendline, "Houve EMPATE!\n");
				Write(sockfd, sendline, strlen(sendline));
			} else if (adversaryChoice == PAPEL) {
				strcat(sendline, "Você PERDEU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++adversaryPoints;
			} else {
				strcat(sendline, "Você GANHOU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++yourPoints;
			}
			strcpy(sendline, "next\n");
			Write(sockfd, sendline, strlen(sendline));

		} else if (!strcmp(recvline,"2\n")) {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			Write(sockfd, menu1, strlen(menu1));
			strcpy(sendline, "Você escolheu PAPEL e seu adversário escolheu ");
			strcat(sendline, adversaryChoiceString);
			if (adversaryChoice == PEDRA) {
				strcat(sendline, "Você GANHOU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++yourPoints;
			} else if (adversaryChoice == PAPEL) {
				strcat(sendline, "Houve EMPATE!\n");
				Write(sockfd, sendline, strlen(sendline));
			} else {
				strcat(sendline, "Você PERDEU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++adversaryPoints;
			}
			strcpy(sendline, "next\n");
			Write(sockfd, sendline, strlen(sendline));
		} else if (!strcmp(recvline,"3\n")) {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			Write(sockfd, menu1, strlen(menu1));
			strcpy(sendline, "Você escolheu TESOURA e seu adversário escolheu ");
			strcat(sendline, adversaryChoiceString);
			if (adversaryChoice == PEDRA) {
				strcat(sendline, "Você PERDEU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++adversaryPoints;
			} else if (adversaryChoice == PAPEL) {
				strcat(sendline, "Você GANHOU!\n");
				Write(sockfd, sendline, strlen(sendline));
				++yourPoints;
			} else {
				strcat(sendline, "Houve EMPATE!\n");
				Write(sockfd, sendline, strlen(sendline));
			}
			strcpy(sendline, "next\n");
			Write(sockfd, sendline, strlen(sendline));
		} else if (!strcmp(recvline,"q\n")) {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			//strcpy(sendline, "Fim de jogo.\n");
			//Write(sockfd, sendline, strlen(sendline));
			strcpy(sendline, "quit\n");
			Write(sockfd, sendline, strlen(sendline));
			return;
		} else if (!strcmp(recvline,"p\n")) {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			Write(sockfd, menu1, strlen(menu1));
			snprintf(sendline, 50, "O placar está: Você %d x %d adversário\n", yourPoints, adversaryPoints);
			Write(sockfd, sendline, strlen(sendline));
			strcpy(sendline, "next\n");
			Write(sockfd, sendline, strlen(sendline));
		} else {
			strcpy(sendline, "clear\n");
			Write(sockfd, sendline, strlen(sendline));
			Write(sockfd, menu2, strlen(menu2));
			strcpy(sendline, "next\n");
			Write(sockfd, sendline, strlen(sendline));
		}
	}

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_quit("str_echo: read error");
}
