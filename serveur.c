#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "fonction_serveur.c"

int main()
{
	/* Déclaration des variables */
	int sockserveur, lg;
	struct sockaddr_in coord_client;
	struct sockaddr_in mes_coord;
	struct tm *m;
	char* pc;
	char msg[100];
	
	/* Création d'un socket */
	sockserveur = socket(AF_INET, SOCK_STREAM, 0);
	
	/* Serveur : appel BIND */
	bzero(&mes_coord, sizeof(mes_coord));
	mes_coord.sin_family = AF_INET;
	mes_coord.sin_port = htons(2000);
	mes_coord.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockserveur, (struct sockaddr*) &mes_coord, sizeof(mes_coord)) < 0)
	{
		printf("Erreur BIND\n");
		exit(0);
	}
	
	/* Serveur : appel LISTEN */
	if (listen(sockserveur,5) < 0)
	{
		printf("Erreur LISTEN\n");
		exit(0);
	}
	
	/* Serveur : appel ACCEPT */
	while(1)
	{
		int i;
		int nb_player = 1;
		printf("Saisir le nombre de joueur\n");
		scanf("%d", &nb_player);
		int pid[nb_player];
		
		
		Player* player_list = malloc(sizeof(Player) * nb_player);
		for(i=0 ; i<nb_player ; i++)
		{
			lg = sizeof(coord_client);
			player_list[i].budget = 100;
			player_list[i].socket = accept(sockserveur, (struct sockaddr*) &coord_client, &lg);			
			if(player_list[i].socket == (-1))
			{
				printf("Erreur ACCEPT\n");
				exit(0);
			}
		}
		
		DeckCard* deck = initDeck();
		Card* croupier_hand = malloc(sizeof(Card) * 3);
		dealCards(player_list, croupier_hand, nb_player, deck);


		for(i=0 ; i<nb_player ; i++)
		{
			forkSon();
		}




		read(newsockfd, msg, sizeof(msg));
		printf(" message recut %s \n",msg);
		char msg2[100];
		scanf("%s", msg2);
		write(newsockfd, msg2, sizeof(msg2));
		printf(" message envoye \n");
		


		for(i=0 ; i<nb_player ; i++)
		{
			close(player_list[i].socket);
		}
		free(player_list);
		free(croupier_hand);
		free();
	}
	close(sockserveur);
}