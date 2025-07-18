#include "felix_path.h"
#include "felix_base.h"

static char g_path[256]; // Global variable to store the JSON path
static pthread_mutex_t g_pathMutex = PTHREAD_MUTEX_INITIALIZER;

bool SetFilePath(const char *path)
{
    if (path == NULL || path[0] == '\0')
    {
        printf("Invalid path\n");
        return false;
    }

    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s", path);

    pthread_mutex_lock(&g_pathMutex);
    strncpy(g_path, filePath, sizeof(g_path) - 1);
    g_path[sizeof(g_path) - 1] = '\0'; // Ensure null termination
    pthread_mutex_unlock(&g_pathMutex);

    return true;
}

const char *GetFilePath(void)
{
    pthread_mutex_lock(&g_pathMutex);
    if (g_path == NULL || g_path[0] == '\0')
    {
        printf("File path is not set\n");
        return NULL;
    }
    const char *ret = g_path;
    pthread_mutex_unlock(&g_pathMutex);
    return ret;
}