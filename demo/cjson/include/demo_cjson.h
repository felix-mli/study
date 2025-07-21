#ifndef DEMO_CJSON_H
#define DEMO_CJSON_H

#include "cJSON.h"
#include "felix_base.h"
#include "felix_path.h"

typedef struct {
    const char *name;
    void (*func)(int argc, char *argv[]);
} TestEntry;

void CJSONParse(const char *filename);
void CJSONType(const char *filename);
void CJSONGetObjectItem(const char *filename);
void CJSONGetArrayItem(const char *filename);

void TestCJSONParse(int argc, char *argv[]);
void TestCJSONType(int argc, char *argv[]);
void TestCJSONGetObjectItem(int argc, char *argv[]);
void TestCJSONGetArrayItem(int argc, char *argv[]);

void GetTestTable(TestEntry **table, size_t *size);

#endif