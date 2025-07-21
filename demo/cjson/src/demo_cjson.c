#include "demo_cjson.h"

#define FILE_PATH "/home/lmk/test/study/file/testfile/jsonfile"

void LoadFromCJSON(const char *filename, char **filebuffer){
    if (filename == NULL || filename[0] == '\0') {
        printf("Invalid file name\n");
        return;
    }

    bool ret = SetFilePath(FILE_PATH);
    const char *filepath = GetFilePath();

    char file[128];
    snprintf(file, sizeof(file), "%s/%s", filepath, filename);
    if (file == NULL || file[0] == '\0') {
        printf("File path is not set\n");
        return;
    }

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", file);
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return;
    }

    size_t readlen = fread(buffer, 1, fileSize, fp);
    buffer[readlen] = '\0'; // Null-terminate the string
    fclose(fp);
    if (readlen != fileSize) {
        printf("Failed to read the entire file: %s\n", file);
        free(buffer);
        return;
    }
    *filebuffer = buffer; // Assign the buffer to the output parameter
}

// test the cJSON parse function
void TestCJSONParse(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <json_file>\n", argv[0]);
        return;
    }
    CJSONParse(argv[1]);
}

void CJSONParse(const char *filename){
    if (filename == NULL || filename[0] == '\0') {
        printf("Invalid file name\n");
        return;
    }
    char *buffer;
    LoadFromCJSON(filename, &buffer);
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (json == NULL) {
        printf("Failed to parse JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }
    printf("JSON parsed successfully:\n");
    char *jsonString = cJSON_Print(json);
    if (jsonString != NULL) {
        printf("%s\n", jsonString);
        free(jsonString);
    } else {
        printf("Failed to print JSON\n");
    }
}

// investigate the type of the cJSON structure
/*
typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;

    int type;

    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;
} cJSON;

cJSON Types:
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)

*/
void TestCJSONType(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <json_file>\n", argv[0]);
        return;
    }
    CJSONType(argv[1]);
}

void CJSONType(const char *filename){
    if (filename == NULL || filename[0] == '\0') {
        printf("Invalid file name\n");
        return;
    }
    char *buffer;
    LoadFromCJSON(filename, &buffer);
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (json == NULL) {
        printf("Failed to parse JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }

    // test for false => 0
    printf("married: %d\n", cJSON_GetObjectItem(json, "married")->type);
    // test for true => 1
    printf("isEmployed: %d\n", cJSON_GetObjectItem(json, "isEmployed")->type);
    // test for null => 2
    printf("children: %d\n", cJSON_GetObjectItem(json, "children")->type);
    // test for number => 3
    printf("age: %d\n", cJSON_GetObjectItem(json, "age")->type);
    // test for string => 4
    printf("name: %d\n", cJSON_GetObjectItem(json, "name")->type);
    // test for array => 5
    printf("hobbies: %d\n", cJSON_GetObjectItem(json, "hobbies")->type);
    // test for object => 6
    printf("address: %d\n", cJSON_GetObjectItem(json, "address")->type);

    // for cJSON array type
    // test for string in array
    printf("hobbies[0]: %d\n", cJSON_GetArrayItem(cJSON_GetObjectItem(json, "hobbies"), 0)->type);
    // test for value in array
    printf("hobbies[3]: %d\n", cJSON_GetArrayItem(cJSON_GetObjectItem(json, "hobbies"), 3)->type);
    // for value in array, it can print with valueint or valuedouble, test for both of it
    printf("hobbies[3] valueint: %d\n", cJSON_GetArrayItem(cJSON_GetObjectItem(json, "hobbies"), 3)->valueint);
    printf("hobbies[3] valuedouble: %f\n", cJSON_GetArrayItem(cJSON_GetObjectItem(json, "hobbies"), 3)->valuedouble);

    cJSON_Delete(json);
}

// test cJSON_GetObjectItem function
void TestCJSONGetObjectItem(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <json_file>\n", argv[0]);
        return;
    }
    CJSONGetObjectItem(argv[1]);
}

void CJSONGetObjectItem(const char *filename)
{
    if (filename == NULL || filename[0] == '\0') {
        printf("Invalid file name\n");
        return;
    }
    char *buffer;
    LoadFromCJSON(filename, &buffer);
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (json == NULL) {
        printf("Failed to parse JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }

    // Get object item
    cJSON *item = cJSON_GetObjectItem(json, "name");
    if (item != NULL) {
        printf("%s: %s\n", item->string, item->valuestring);
    } else {
        printf("Item not found\n");
    }

    cJSON_Delete(json);
}

// test for cJSON_GetArrayItem & cJSON_GetArraySize
void TestCJSONGetArrayItem(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <json_file>\n", argv[0]);
        return;
    }
    CJSONGetArrayItem(argv[1]);
}

void CJSONGetArrayItem(const char* filename){
    if (filename == NULL || filename[0] == '\0') {
        printf("Invalid file name\n");
        return;
    }
    char *buffer;
    LoadFromCJSON(filename, &buffer);
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (json == NULL) {
        printf("Failed to parse JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }

    // Get array item
    cJSON *array = cJSON_GetObjectItem(json, "hobbies");
    if (array != NULL && cJSON_IsArray(array)) {
        for (int i = 0; i < cJSON_GetArraySize(array); i++) {
            cJSON *item = cJSON_GetArrayItem(array, i);
            if (item != NULL) {
                if (item->type == cJSON_String) {
                    printf("hobbies[%d]: %s\n", i, item->valuestring);
                } else if (item->type == cJSON_Number) {
                    if (item->valueint == item->valuedouble) {
                        printf("hobbies[%d]: %d\n", i, item->valueint);
                    } else {
                        printf("hobbies[%d]: %f\n", i, item->valuedouble);
                    }
                } else if (item->type == cJSON_False) {
                    printf("hobbies[%d]: false\n", i);
                } else if (item->type == cJSON_True) {
                    printf("hobbies[%d]: true\n", i);
                } else {
                    printf("hobbies[%d]: unknown type %d\n", i, item->type);
                }
            } else {
                printf("Item not found at index %d\n", i);
            }
        }
    } else {
        printf("Array not found or is not an array\n");
    }

    cJSON_Delete(json);
}

static TestEntry g_testTable[] = {
    {"CJSONParse", TestCJSONParse},
    {"CJSONType", TestCJSONType},
    {"CJSONGetObjectItem", TestCJSONGetObjectItem},
    {"CJSONGetArrayItem", TestCJSONGetArrayItem},
};

static const size_t g_testTableSize = sizeof(g_testTable) / sizeof(g_testTable[0]);

void GetTestTable(TestEntry **table, size_t *size)
{
    if (table == NULL || size == NULL) {
        return;
    }
    *table = g_testTable;
    *size = g_testTableSize;
}