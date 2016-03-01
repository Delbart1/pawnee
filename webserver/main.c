#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include "socket.h"

int main(/*int argc, char **argv*/void)
{

	printf("pawnee");
	int socket_client;
	int socket_serveur = creer_serveur(8080);
	FILE* stream;
	while(1)
	{
		int end = 1;
		socket_client = accept(socket_serveur, NULL, NULL);
		stream = fdopen (socket_client ,"w+");
		if(socket_client == -1)
		{
			perror("accept");
			return -1;	
		}

		pid_t pid = fork();

		if(pid == 0)
		{
			
			const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur \n 1\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n 10\n";
			sleep(1);
			fprintf(stream,"%s",message_bienvenue);
			
			while(end == 1)
			{

				int taille = 256 * sizeof(char);
				char * buffer = malloc(taille);
				
				while(fgets(buffer, taille, stream) != '\0')
				{
			
					fprintf(stream,"%s %s","<Pawnee>",buffer);
					end = 0;
				}	
			}	
		}
		else
		{
			if(close(socket_client) ==-1)
			{
				perror("close");
				return -1;
			}
			
		}
	}

	if(close(socket_client) ==-1)
	{
		perror("close");
		return -1;
	}
	
	return 0;
}
