#include "demo_cjson.h"
#include "felix_base.h"

int main(int argc, char *argv[])
{
    if(argc == 1) {
        printf("Usage: %s <test_name>\n", argv[0]);
        return 1;
    }
    char *testName = argv[1];
    TestEntry *testTable = NULL;
    size_t testSize = 0;
    GetTestTable(&testTable, &testSize);

    for (size_t i = 0; i < testSize; i++) {
        if (strcmp(testTable[i].name, testName) == 0) {
            testTable[i].func(argc - 1, argv + 1);
            break;
        }
    }

    return 0;
}