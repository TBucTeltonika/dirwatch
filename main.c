#include "main.h"

//Pointer to the head
filetype_t *filetypes = NULL;

int main(int argc, char *argv[])
{
    atexit(exit_handler1);
    //LogToFile("Reading config", "CFG");
    if (ReadConfig() != 0)
    {
        LogToFile("Error with reading config file", "CFG");
        return 0;
    }

    filetype_t *curr = filetypes;
    filetype_t *next = curr->next;
    printf("%s |||||||||||||||||| %s\n", curr->filetype, curr->destination);

    while (next != NULL)
    {

        curr = next;
        next = curr->next;
        printf("%s |||||||||||||||||| %s\n", curr->filetype, curr->destination);
    }


    LogToFile("Attempting to daemonize", "STARTUP");
    skeleton_daemon();

    while (1)
    {
        ParseDirectory();

        sleep(5);
        //return 0;
    }
    //FreeMemory();
    return 0;
}

static void exit_handler1(void)
{
    FreeMemory();
}

int ParseDirectory()
{
    DIR *dir;
    struct dirent *ent;
    //char dirstr[] = "/home/tomas/";
    printf("Parsing directory: %s\n", watch_dir);
    if ((dir = opendir(watch_dir)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            //Patikrinam ar tai yra file'as
            if (ent->d_type == DT_REG)
                printf("%s\n", ent->d_name);

            filetype_t *type = MatchExtension(ent->d_name);
            if (type == NULL)
                continue;

            printf("%s \n", type->filetype);
            printf("%s \n", type->destination);
            int result = MoveFile(watch_dir, ent->d_name, type->destination);
            if (result == 0)
                LogMoveToFile(watch_dir, ent->d_name, type->destination);
            else
                LogMoveToFileError(watch_dir, ent->d_name, type->destination);
            if (result == 444)
            {
                LogToFile("FILE ALREADY EXISTS IN THE DESINATION!","MOVE");
            }
            //printf("result %d \n",result);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }

    //TO DO ADD PROCESSING
}

int FreeMemory()
{
    free(watch_dir);

    //Free the linked list:
    filetype_t *curr = filetypes;
    filetype_t *next = curr->next;
    printf("%s |||||||||||||||||| %s\n", curr->filetype, curr->destination);
    free(curr);
    while (next != NULL)
    {
        curr = next;
        next = curr->next;
        printf("%s |||||||||||||||||| %s\n", curr->filetype, curr->destination);
        free(curr);
    }

    return 0;
}
