// tcp_client.c
// A simple TCP client that connects to a server, sends a message, and receives a response.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // for close()
#include <arpa/inet.h>   // for inet_pton, htons, etc.

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char *message = "Hello from TCP client!";

    // 1. Create the socket (IPv4, TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // 2. Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT); // convert to network byte order
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 3. Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock);
        return EXIT_FAILURE;
    }

    // 4. Send message to server
    send(sock, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

    // 5. Receive response from server
    int bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; // null-terminate received string
        printf("Server response: %s\n", buffer);
    }

    // 6. Close the socket
    close(sock);
    return 0;
}
