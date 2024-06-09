#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

void printBuffer(int *buffer) {
    int len = buffer[0];
    for (int i = 1; i <= len; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int main() {
    int sockfd;
    struct sockaddr_in addr;
    int buffer[1024];
    socklen_t addr_size;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(buffer, 1024);
    printf("How many digit ? ");
    scanf("%d", &buffer[0]);
    printf("Enter a number: ");
    for (int i = 1; i <= buffer[0]; i++) {
        scanf("%d", &buffer[i]);
    }
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
    printf("[+]Sending data...... ");
    printBuffer(buffer);
    // bzero(buffer, 1024);
    char result[100];
    addr_size = sizeof(addr);
    recvfrom(sockfd, result, 100, 0, (struct sockaddr *)&addr, &addr_size);
    printf("Data received from server: %s\n", result);
    return 0;
}