#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <errno.h>

#define logfile "/var/log/watchdaemon.log"
int LogToFile(char* text, char* type);
int LogMoveToFile(char* from, char* file, char* to);
int LogMoveToFileError(char* from, char* file, char* to);
#endif
