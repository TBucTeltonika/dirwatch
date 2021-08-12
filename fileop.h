#ifndef FILEOP_H
#define FILEOP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int MoveFile(char *filepath,char* filename, char *destdir);
int FileExists(const char *fname);
#endif
