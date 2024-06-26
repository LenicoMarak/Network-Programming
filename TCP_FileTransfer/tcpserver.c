#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define SIZE 1024

void write_file(int sockfd) {
    int n;
    FILE *fp;
    char *filename = "recv.txt";
    char buffer[SIZE];
    fp = fopen(filename, "w");
    while (1) {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
            break;
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
}

int main() {
    int e;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
    write_file(new_sock);
    printf("[+]Data written in the file successfully \n");
    return 0;
}
