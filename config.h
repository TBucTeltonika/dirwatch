#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <errno.h>

#include "stringop.h"
#include "logger.h"
#include "filetype.h"

#define cfgfile "/etc/watchdaemon.conf"
extern char* watch_dir;

int ReadConfig();
int CreateDefaultConfig();
int FolderExists(char* paath);
#endif