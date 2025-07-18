#ifndef GET_PATH_H
#define GET_PATH_H

#include "felix_base.h"

bool SetFilePath(const char *path);
// if the path need to hold for long term, please use strdup to copy the path.
const char *GetFilePath(void);

#endif