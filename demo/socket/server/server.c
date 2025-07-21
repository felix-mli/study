#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "felix_base.h"


#define IP_ADDRESS "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

// TCP socket
int main(void){
    // create a socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        // handle error
        return -1;
    }

    // bind the socket to an address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT); // port number
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS); // bind to any address
    int bind_result = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (bind_result < 0) {
        // handle error
        return -1;
    }

    // listen for incoming connections
    int listen_result = listen(socket_fd, 5); // 5 is the backlog
    if (listen_result < 0) {
        // handle error
        return -1;
    }

    // accept a connection
    int new_socket_fd = accept(socket_fd, NULL, NULL);
    if (new_socket_fd < 0) {
        // handle error
        return -1;
    }

    while(1) {
        // receive data from the client
        char buffer[BUFFER_SIZE];
        int valread = read(new_socket_fd, buffer, BUFFER_SIZE);
        if (valread < 1) {
            // handle error or connection closed
            break;
        }
        printf("Received: %s", buffer);
        send(new_socket_fd, buffer, valread, 0); // echo back the data
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer
    }

    close(new_socket_fd); // close the new socket
    close(socket_fd); // close the listening socket
    return 0;
}
