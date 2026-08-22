#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    WSADATA wsa;
    SOCKET server_socket = INVALID_SOCKET;
    SOCKET client_socket = INVALID_SOCKET;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_size = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int bytes_received;
    FILE *output_file;

    printf("Initialising Winsock...\n");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 1) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server is running.\n");
    printf("Listening on port %d...\n", PORT);
    printf("Waiting for file...\n");

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_size);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Client connected.\n");

    output_file = fopen("received_file.txt", "wb");
    if (!output_file) {
        printf("Could not create received_file.txt.\n");
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, (size_t)bytes_received, output_file);
    }

    fclose(output_file);

    if (bytes_received == 0) {
        printf("File received successfully.\n");
        printf("Saved as received_file.txt\n");
    } else {
        printf("Receive failed: %d\n", WSAGetLastError());
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
