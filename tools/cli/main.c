#include "client.h"

// 写一个cli程序，cli other_program command arg1 arg2...
int main(int argc, char *argv[]) {
    // 这里的代码就是去开一个socket，应该没有什么区别
    // 但是需要实现比如cli list显示所有的可以交互的进程
    if (argc > 1) {
        if (strcmp(argv[1], "list") == 0) {
            ListProcesses();
            return 0;
        }
    }
    
    char uds_path[PATH_MAX];
    snprintf(uds_path, sizeof(uds_path), "%s/cli_uds_%s", CLI_UDS_PATH, argv[1]);
    int sockfd = OpenSocket(uds_path);
    if (sockfd < 0) {
        fprintf(stderr, "Failed to open socket\n");
        return 1;
    }

    // buffer要怎么写？？
    char buffer[256] = {0};
    for (size_t i = 2; i < argc; i++)
    {
        if (i > 2) {
            strncat(buffer, " ", sizeof(buffer) - strlen(buffer) - 1);
        }
        strncat(buffer, argv[i], sizeof(buffer) - strlen(buffer) - 1);
    }
    send(sockfd, buffer, strlen(buffer), 0);
    printf("Sent command: %s\n", buffer);
    close(sockfd);
    return 0;
}