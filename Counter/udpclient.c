#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(buffer, 1024);
    printf("Enter a sentence: ");
    fgets(buffer,sizeof(buffer),stdin);
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
    printf("[+]Sending data...... %s\n",buffer);
    bzero(buffer, 1024);
    addr_size = sizeof(addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
    printf("Data received from server: %s\n", buffer);
    return 0;
}
