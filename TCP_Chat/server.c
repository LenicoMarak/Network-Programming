#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define SIZE 1050

void sendMessage(char *message, int server_sockfd) {

	if (send(server_sockfd, message, strlen(message), 0) == -1) {
		perror("[-]Error in sending message.\n");
		exit(1);
	}
	printf("You: %s\n", message);
}

int main(){

	int error;
	char message[SIZE];
	int server_sockfd, client_sockfd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8080;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	error = bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(error == -1){
        printf("Couln't bind server address !");
        exit(1);
    }

    if (listen(server_sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}
	else{
		perror("[-]Error in listening\n");
		exit(1);
	}

	addr_size = sizeof(client_addr);
	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &addr_size);

	while (1){
		//Receiving part
		bzero(message, SIZE);
        int bytes_received = recv(client_sockfd, message, SIZE, 0);
        if (bytes_received > 0) {
            printf("client: %s\n", message);
        } else {
            printf("Error can't recive message !\n");
        }
        if (strcmp(message, "bye") == 0 || strcmp(message, "exit") == 0){
			break;
		}
		// Sending part
		bzero(message, SIZE);
		printf("Type a message: ");
        fgets(message, SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';
        if (strlen(message) == 0){
			printf("Can't send empty message !\n");
			continue;
		}
		sendMessage(message, client_sockfd);
		if (strcmp(message, "bye") == 0 || strcmp(message, "exit") == 0){
			break;
		}

	}

	printf("Connection Closed....\n");
	close(server_sockfd);
	close(client_sockfd);
	return 0;
