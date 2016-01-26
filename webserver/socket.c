#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>

int creer_serveur(int port){
	port = 8080;
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if (socket_serveur == -1)
	{
		perror("socket_serveur");
		return -1;
	}

	if(close(socket_serveur) == -1){
		perror("close socket");
		return -1;
	}
	/* Utilisation de la socket serveur */
	port ++;
	return 0;
}
