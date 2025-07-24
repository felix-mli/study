#include "client.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#define CLI_UDS_PATH "/var/run"
#define CLI_UDS_NAME "cli_uds"
#define PATH_MAX 256

static int g_uds_socket_fd = -1;
static pthread_mutex_t g_uds_mutex = PTHREAD_MUTEX_INITIALIZER;

// 读取CLI_UDS_PATH目录下的所有socket文件，并打印它们的名称
static void ListProcesses() {
    // 检测CLI_UDS_PATH目录下的所有socket文件
    DIR *dir = opendir(CLI_UDS_PATH);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    char path[PATH_MAX];
    struct stat st;
    // readdir会逐个读取目录的条目，返回struct dirent这个结构体指针
    while ((entry = readdir(dir)) != NULL)
    {
        // 检查文件是否是socket文件
        snprintf(path, sizeof(path), "%s/%s", CLI_UDS_PATH, entry->d_name);
        if (stat(path, &st) == 0)
        {
            if(S_ISSOCK(st.st_mode)) {
                // 打印socket文件的名称
                printf("Socket: %s\n", entry->d_name);
            }
        }
    }
}

static bool OpenUDSSocket(const char *uds_path) {
    pthread_mutex_lock(&g_uds_mutex);
    int g_uds_socket_fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (g_uds_socket_fd < 0) {
        perror("socket");
        return -1;
    }
    pthread_mutex_unlock(&g_uds_mutex);
}

static bool ConnectUDSSocket(const char *uds_path) {
    // 如果要使用UDS的话，需要使用sockaddr_un
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, uds_path, sizeof(addr.sun_path) - 1);
    // 连接到UNIX域套接字
    pthread_mutex_lock(&g_uds_mutex);
    if(connect(g_uds_socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        close(g_uds_socket_fd);
        return -1;
    }
    pthread_mutex_unlock(&g_uds_mutex);
    printf("Connected to UNIX domain socket: %s\n", addr.sun_path);
    return true;
}