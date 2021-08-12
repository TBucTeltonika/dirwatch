#include "logger.h"

int LogToFile(char* text, char* type)
{
    FILE *log = fopen(logfile, "ab+");
    //if (!log) log = fopen(logfile, "wt");
    if (!log) {
        printf("can not open log file for writing.\n");
        return 1;   
    }

    //int lock = flock(log->, 1);  // Lock the file . . .
    int result = flock(fileno(log), 1);
    fprintf(log,"[%s]%s\n",type, text);
    int release = flock(fileno(log), 8);  // Unlock the file . . .

    fclose(log);

    return 0;
}

int LogMoveToFile(char* from, char* file, char* to)
{
    char* temp = (char *)calloc(256,sizeof(char));

    sprintf(temp,"%s | %s -> %s",file,from,to);
    int result = LogToFile(temp,"MOVE");
    free(temp);

    return result;
}

int LogMoveToFileError(char* from, char* file, char* to)
{
    char* temp = (char *)calloc(256,sizeof(char));

    sprintf(temp,"ERROR: %s | %s | %s -> %s",strerror(errno),file,from,to);
    int result = LogToFile(temp,"MOVE");
    free(temp);

    return result;
}
