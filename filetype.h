#ifndef FILETYPE_H
#define FILETYPE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"
#include "stringop.h"
typedef struct filetype {
    char filetype[32];
    char destination[128];
    struct filetype * next;
} filetype_t;


int InsertIntoFileType(char *filetype, char *destination);
filetype_t *MatchExtension(char *str);
filetype_t *newnode(char *filetype, char *destination);
#endif