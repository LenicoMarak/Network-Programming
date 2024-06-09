
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define SIZE 1050

void sendMessage(char *message, int sockfd){

  if (send(sockfd, message, strlen(message), 0) == -1){
		perror("[-]Error in sending message.!");
		exit(1);
	}
	printf("you: %s\n", message);
}

int main(){
	int error;
	int sockfd;
	char message[SIZE];
	struct sockaddr_in server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8080;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	error = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (error == -1){
		printf("Couldn't connect to server !");
		exit(1);
	}

	while (1){
		//Sendind part
		bzero(message, SIZE);
		printf("Type a message: ");
        fgets(message, SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';
        if (strlen(message) == 0) {
            printf("Can't send empty message !\n");
			continue;
        }
        sendMessage(message, sockfd);
	 	if (strcmp(message, "bye") == 0 || strcmp(message, "exit") == 0){
			break;
		}

		//Receiving part
		bzero(message, SIZE);
        int bytes_received = recv(sockfd, message, SIZE, 0);
         if (bytes_received > 0) {
            printf("server: %s\n", message);
        } else {
            printf("Error can't recive message !\n");
        }
         if (strcmp(message, "bye") == 0 || strcmp(message, "exit") == 0){
			break;
		}
	}

	printf("Connection Closed....\n");
	close(sockfd);
	return 0;
}
