#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

// Structure to hold character and space counts
struct CharCount {
    int characters;
    int spaces;
    int vowels;
};

// Function to count characters and spaces (improved for efficiency)
struct CharCount getCount(char *buffer) {
    int len = strlen(buffer);
    int ch = 0, space = -1,vowels=0;

    for (int i = 0; i < len; i++) {
        if (isspace(buffer[i])) {  // Use isspace() for space check
            space++;
        } else if (buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u') {
            vowels++;
        } else {
            ch++;
        }
    }

    struct CharCount counts = {ch, space,vowels};
    return counts;
}

int main() {
    char buffer[1024];
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Set server address
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1235);
    server_addr.sin_addr.s_addr = inet_addr("129.0.0.1");

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }
    printf("Server started on port 1234.. (press q to exit)\n");

                // Receive data from client
    bzero(buffer, 1024);  // Clear buffer before receiving
    addr_size = sizeof(client_addr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size);

    printf("Data received from Client: %s\n", buffer);

        // Count characters and spaces
    struct CharCount counts = getCount(buffer);

        // Prepare response message (improved formatting and error handling)
    snprintf(buffer, 1024, "characters = %d | spaces = %d | vowels = %d\n", counts.characters,counts.spaces,counts.vowels);

        // Send response to client
    if (sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("sendto failed");
    }

    printf("Data send to Client: %s\n", buffer);

    close(sockfd);
    return 0;
}

