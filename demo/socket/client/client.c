#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "felix_base.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main(void){
    // create a TCP socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        // handle error
        return -1;
    }

    // connect to a server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT); // port number
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS); // bind to any address
    int connect_result = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_result < 0) {
        // handle error
        return -1;
    }

    while (1)
    {
        printf("Enter message to send: ");
        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);
        // send data to the server
        send(socket_fd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer)); // clear the buffer
    }

    close(socket_fd); // close the socket
    return 0;
}