#include "fileop.h"

//On success, zero is returned. On error, -1 is returned, and errno is set appropriately.
int MoveFile(char *filepath,char* filename, char *destdir)
{

    int result = 444;
    char* src = (char *)calloc(256,sizeof(char));
    char* dest = (char *)calloc(256,sizeof(char));

    strcat(src,filepath);
    strcat(src,filename);

    strcat(dest,destdir);
    strcat(dest,filename);

    printf("s: %s\n",src);
    printf("dest: %s\n",dest);

    int exists = FileExists(dest);
    if(exists == 0)
        result = rename(src, dest);

    free(src);
    free(dest);

    return result;
}

int FileExists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

char* SuggestAName(char* filename, char *destdir)
{

}
