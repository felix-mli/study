#include "demo_cjson.h"

#define FILE_PATH 

char *TestCJSONParse(const char *file){
    if (file == NULL || file[0] == '\0') {
        printf("Invalid file name\n");
        return NULL;
    }

    bool ret = SetFilePath(file);
    char *filepath = GetFilePath();
}

