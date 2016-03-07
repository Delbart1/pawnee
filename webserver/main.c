#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include "socket.h"


int isWhiteSpace( char c )
{
    if( c == ' ' || c == '\t' || c == '\n' || c == '\r' )
        return 1;
    return -1;
}

int wordCount( char *string )
{
    char *s = string;
    int inWord = -1;
    int i = 0;

    while(*s)
    {
        if(isWhiteSpace(*s) == 1)
        {
            inWord = -1;
            while(isWhiteSpace(*s) == 1)
                s++;
        }
        else
        {
            if(inWord == -1)
            {
                inWord = 1;
                i++;
            }
            s++;
        }
    }

    return i;
}

int message_HTTP(char* get){
int i;

char* buffer = malloc(4* sizeof(char));
	for(i = 0; i<4 ;i++){
		buffer[i] = get[i];
	}

	if(strcmp(buffer, "GET ") != 0) 
	{
		return -1;
	}

	if(wordCount(get) != 3){
		return -1;
	}

char * http = strstr(get, "HTTP/");
	int position = http - get;

	buffer = realloc(buffer, 8 * sizeof(char));
	for(i = 0; i < 8; i++) 
	{
		buffer[i] = get[i + position];
	}

	if(strcmp(buffer, "HTTP/1.0") != 0 && strcmp(buffer, "HTTP/1.1") != 0)
	{
		return -1;
	}

	return 0;
 
}


int main(/*int argc, char **argv*/void)
{

	printf("Bienvenue sur pawnee\n");
	int socket_client;
	int socket_serveur = creer_serveur(8080);
	FILE* stream;

	while(1)
	{
		
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
					
				int taille = 256 * sizeof(char);
				char * buffer = malloc(taille);
				fgets(buffer,taille,stream);
				
				while(strcmp(buffer, "\n") == 0)
				{
				write(socket_client, "Entrez une chaine valide\n", strlen("Entrez une chaine valide\n"));
				fgets(buffer, taille, stream);
				}

				if(message_HTTP(buffer) == -1){
					perror("HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n400 Bad request\r\n");
					return -1;
				}
				write(socket_client, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"));

				const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur \n 1\n 2\n 3\n 4\n 5\n 6\n 7\n 8\n 9\n 10\n";
				sleep(1);
				fprintf(stream,"%s",message_bienvenue);
				
				while(fgets(buffer, taille, stream) != '\0')
				{
			
					printf("%s %s","<Pawnee>",buffer);
				
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
	
	fclose(stream);
	return 0;
}
