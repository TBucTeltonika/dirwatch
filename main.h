#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <syslog.h>
#include <sys/file.h>
#include <errno.h>
#include <pwd.h>

#include "daemon.h"
#include "stringop.h"
#include "logger.h"
#include "config.h"
#include "fileop.h"
//#include "filetype.h"

//Logai turi buti //var/log//watchdaemon
//cfg turi buti etc//
//          //var//log//watchdaemon
//          etc//



char* watch_dir;

int ParseDirectory();
int FreeMemory();
static void exit_handler1(void);




