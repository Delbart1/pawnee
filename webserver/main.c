#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

int main(/*int argc, char **argv*/void)
{

	printf("pawnee");
	int socket_client;
	int socket_serveur = creer_serveur(8080);

	
	while(1)
	{
	
		socket_client = accept(socket_serveur, NULL, NULL);

		if(socket_client == -1)
		{
			perror("accept");
			return -1;	
		}
		
		char * buffer = malloc(300);

		
		const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
		write(socket_client,message_bienvenue, strlen(message_bienvenue));

		while(1)
		{
			if(read(socket_client,buffer,sizeof(buffer)) == -1)
			{
				perror("read client");
				return -1;
			}
	
			write(socket_client,buffer, sizeof(buffer));
		}
	
	
 	}

	if(close(socket_client) ==-1)
	{
		perror("close");
		return -1;
	}
	return 0;
}
