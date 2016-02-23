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

	//FILE* fdopen ( int fd , const char "w+" );
	while(1)
	{
		int end = 1;
		socket_client = accept(socket_serveur, NULL, NULL);

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
			write(socket_client,message_bienvenue, strlen(message_bienvenue));

			while(end == 1)
			{
				char * buffer = malloc(256);
				if(read(socket_client,buffer,sizeof(buffer)) == -1)
				{
					perror("read client");
					return -1;
				}
				if(strncmp("/close",buffer,5) == 0)
				{
					end = 0;
					if(close(socket_client) ==-1)
					{
						perror("close");
						return -1;
					}
				}
				else
				{
					write(socket_client,buffer, sizeof(buffer));
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
