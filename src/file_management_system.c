#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <io.h>
#include <winsock2.h> // For network operations

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

#define BUFFER_SIZE 8192

// Function prototypes
void create_file(const char *filename);
void delete_file(const char *filename);
void change_permissions(const char *filename, int permissions);
void merge_files(const char *file1, const char *file2, const char *output_file);
void encrypt_file(const char *filename, const char *password);
void decrypt_file(const char *filename, const char *password);
void monitor_directory(const char *directory);
int validate_file_exists(const char *filename);
int authenticate_user(const char *username, const char *password);
void send_file(const char *filename, const char *server_ip, int server_port);
void display_menu();

int main() {
    int choice;
    char filename[256], filename2[256], output_file[256], password[50], directory[256];
    char username[50], entered_password[50];

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the file name to create: ");
                scanf("%s", filename);
                create_file(filename);
                break;

            case 2:
                printf("Enter the file name to delete: ");
                scanf("%s", filename);
                if (validate_file_exists(filename)) {
                    delete_file(filename);
                }
                break;

            case 3:
                printf("Enter the file name to change permissions: ");
                scanf("%s", filename);
                int permissions;
                printf("Enter new permissions (e.g., 644): ");
                if (scanf("%o", &permissions) != 1) {
                    printf("Error: Invalid permissions format. Try again.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (validate_file_exists(filename)) {
                    change_permissions(filename, permissions);
                }
                break;

            case 4:
                printf("Enter the first file name: ");
                scanf("%s", filename);
                printf("Enter the second file name: ");
                scanf("%s", filename2);
                printf("Enter the output file name: ");
                scanf("%s", output_file);
                if (validate_file_exists(filename) && validate_file_exists(filename2)) {
                    merge_files(filename, filename2, output_file);
                }
                break;

            case 5:
                printf("Enter the file name to encrypt: ");
                scanf("%s", filename);
                printf("Enter the encryption password: ");
                scanf("%s", password);
                if (validate_file_exists(filename)) {
                    encrypt_file(filename, password);
                }
                break;

            case 6:
                printf("Enter the file name to decrypt: ");
                scanf("%s", filename);
                printf("Enter the decryption password: ");
                scanf("%s", password);
                if (validate_file_exists(filename)) {
                    decrypt_file(filename, password);
                }
                break;

            case 7:
                printf("Enter the directory to monitor: ");
                scanf("%s", directory);
                monitor_directory(directory);
                break;

            case 8:
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", entered_password);

                if (!authenticate_user(username, entered_password)) {
                    printf("Authentication failed. You do not have permission to send files.\n");
                    break;
                }

                printf("Enter the file name to send: ");
                scanf("%s", filename);
                printf("Enter the server IP address: ");
                char server_ip[50];
                scanf("%s", server_ip);
                int server_port;
                printf("Enter the server port: ");
                scanf("%d", &server_port);

                if (validate_file_exists(filename)) {
                    send_file(filename, server_ip, server_port);
                }
                break;

            case 9:
                printf("Exiting the program. Goodbye!\n");
                return 0;

            case 10: // Test file existence
                printf("Enter the file name to test existence: ");
                scanf("%s", filename);
                if (validate_file_exists(filename)) {
                    printf("File '%s' exists and is accessible.\n", filename);
                } else {
                    printf("File '%s' does not exist or cannot be accessed.\n", filename);
                }
                break;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
    return 0;
}

void display_menu() {
    printf("\nFile Management System - Menu\n");
    printf("1. Create a file\n");
    printf("2. Delete a file\n");
    printf("3. Change file permissions\n");
    printf("4. Merge two files\n");
    printf("5. Encrypt a file\n");
    printf("6. Decrypt a file\n");
    printf("7. Monitor directory changes\n");
    printf("8. Send a file over the network\n");
    printf("9. Exit\n");
    printf("10. Test if a file exists\n"); // Updated menu
}

void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        printf("File '%s' created successfully.\n", filename);
        fclose(file);
    } else {
        perror("Error: Unable to create file");
    }
}

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error: Unable to delete file");
    }
}

void change_permissions(const char *filename, int permissions) {
    if (_chmod(filename, permissions) == 0) {
        printf("Permissions for '%s' changed to %o successfully.\n", filename, permissions);
    } else {
        perror("Error: Unable to change file permissions");
    }
}

void merge_files(const char *file1, const char *file2, const char *output_file) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(output_file, "w");

    if (!f1 || !f2 || !out) {
        perror("Error: Unable to open files for merging");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (out) fclose(out);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;

    while ((bytes = fread(buffer, 1, BUFFER_SIZE, f1)) > 0) {
        fwrite(buffer, 1, bytes, out);
    }
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, f2)) > 0) {
        fwrite(buffer, 1, bytes, out);
    }

    printf("Files '%s' and '%s' successfully merged into '%s'.\n", file1, file2, output_file);

    fclose(f1);
    fclose(f2);
    fclose(out);
}

void encrypt_file(const char *filename, const char *password) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error: Unable to open file for encryption");
        return;
    }

    int pass_len = strlen(password);
    char ch;

    while (fread(&ch, 1, 1, file) > 0) {
        ch ^= password[(ftell(file) - 1) % pass_len];
        fseek(file, -1, SEEK_CUR);
        fwrite(&ch, 1, 1, file);
    }

    printf("File '%s' encrypted successfully.\n", filename);
    fclose(file);
}

void decrypt_file(const char *filename, const char *password) {
    encrypt_file(filename, password); // XOR decryption is identical to encryption
}

void monitor_directory(const char *directory) {
    printf("Monitoring directory '%s'... (Stub implementation)\n", directory);
}

int validate_file_exists(const char *filename) {
    if (_access(filename, 0) != 0) {
        fprintf(stderr, "Error: File '%s' does not exist.\n", filename);
        return 0;
    }
    return 1;
}

int authenticate_user(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "securepass") == 0) {
        return 1;
    }
    return 0;
}

void send_file(const char *filename, const char *server_ip, int server_port) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    FILE *file;
    char buffer[1024];
    size_t bytes_read;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Could not create socket. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return;
    }
    printf("Connected to server.\n");

    file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Unable to open file '%s'.\n", filename);
        closesocket(sock);
        WSACleanup();
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(sock, buffer, bytes_read, 0) < 0) {
            printf("Failed to send file data.\n");
            fclose(file);
            closesocket(sock);
            WSACleanup();
            return;
        }
    }

    printf("File '%s' sent successfully.\n", filename);

    fclose(file);
    closesocket(sock);
    WSACleanup();
}
