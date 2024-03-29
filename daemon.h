#ifndef DAEMON_H
#define DAEMON_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void skeleton_daemon();
void signal_handler(int sig);
#endif