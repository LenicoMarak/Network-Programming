#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int getSum(int *buffer) {
    int sum = 0;
    for (int i = 1; i <= buffer[0]; i++) {
        sum += buffer[i];
    }
    return sum;
}

void printBuffer(int *buffer) {
    int len = buffer[0];
    for (int i = 1; i <= len; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int main() {
    int buffer[1024];
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    bzero(buffer, 1024);
    addr_size = sizeof(client_addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);
    printf("Data received from Client: ");
    printBuffer(buffer);
    char result[100];
    int sum = getSum(buffer);
    sprintf(result, "Sum = %d", sum);
    sendto(sockfd, result, 100, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    printf("Data send: %s\n", result);
    return 0;
}
