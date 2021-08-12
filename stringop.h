#ifndef STRINGOP_H
#define STRINGOP_H
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/file.h>
#include <dirent.h>

#if (__STDC_VERSION__ >= 199901L)
#include <stdint.h>
#endif

#define STARTS_WITH(pre,str) strncmp(pre, str, strlen(pre)-1) == 0
#define USR_TOKEN "$USR"

char* str_replace(char* string, const char* substr, const char* replacement);
char* replaceWord(const char* s, const char* oldW, const char* newW);
char *ReplaceTokens(char *str);
char* getusernamedirty();
int EndsWith(const char *str, const char *suffix);

#endif