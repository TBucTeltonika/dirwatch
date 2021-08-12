#include "config.h"
//TO DO: ADD BETTER ERROR CODES
//Return: 0-no errors. | 1 - Error
//Reads the config file.
int ReadConfig()
{
    FILE *cfg = fopen(cfgfile, "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (!cfg)
    {
        printf("can not open config file for reading.\n");
        printf("Attempting to create a default cfg.\n");

        LogToFile("Config file not found or not accessible attempt to create a default CFG", "CFG");
        if (CreateDefaultConfig() != 0)
        {
            LogToFile("Creating default CFG file failed. Exiting..", "CFG");
            return 1;
        }
        LogToFile("Successfully created a default CFG file", "CFG");    

        return ReadConfig();
    }

    char activeblock = ' ';
    while ((read = getline(&line, &len, cfg)) != -1)
    {
        //Check if line isnt null
        if (line == NULL)
            continue;
        
        //Newline operator at the end is annoying lets just remove it if it exists.
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        //Get first character
        char firstchar = line[0];

        //If the first character is # that means the line is a comment
        if (firstchar == '#')
            continue;

        char lastchar = ' ';

        if (strlen(line) - 1 > 0)
            lastchar = line[strlen(line) - 1];
        
        //checking if the line is of category type ex. [GENERAL]
        if (firstchar == '[' && lastchar == ']')
        {
            printf("%s\n", line);

            if (STARTS_WITH("[GENERAL]", line))
                activeblock = 'G';
            else if (STARTS_WITH("[TYPES]", line))
                activeblock = 'T';
        }
        
        else if (activeblock == 'G')
        {
            printf("%s\n",line);
            if (STARTS_WITH("WATCH_DIRS=", line))
            {
                char *linewithoutpre = line + strlen("WATCH_DIRS=");

                //char *processedline = linewithoutpre;
                char *processedline = ReplaceTokens(linewithoutpre);
                free(line);
                if (processedline == NULL)
                    {
                        //free(line);
                        return 3;
                    }
                
                watch_dir = processedline;
            }
        }
        //TYPES PART
        else if (activeblock == 'T')
        {
            printf("%s\n",line);
            char *cutloc = strrchr(line, ';');

            if (cutloc == 0)
            {
                LogToFile("Line doesn't contain a ; symbol", "CFG");
                return 1;
            }

            //This is everything past ; symbol.
            char *destdir = cutloc + 1;
            destdir = ReplaceTokens(destdir);
            
            if (FolderExists(destdir) > 0)
            {
                //free(destdir);
                free(line);
                fclose(cfg);
                printf("%s\n", "folder doesnt exist");
                
                return 2;
            }
                //return 2;
            //free(destdir);
            //Probably a bit too dirty but its fast?
            cutloc[0] = '\0';
            printf("%s\n", line);  
            const char *delim = ",";
            char *p = strtok(line, delim);
               
            while (p != NULL)
            {
                printf("%s\n", p);               
                if (InsertIntoFileType(p, destdir) > 0)
                {
                    free(line);
                    return 5;
                }
                //free(p);
                p = strtok(NULL, delim);
                
            }
            
            free(destdir);
        }
    }
    free(line);
    printf("config read closing file\n");
    fclose(cfg);
}

//Return: 0 success, anything else error code.
int CreateDefaultConfig()
{
    FILE* fd = fopen(cfgfile, "a+");
    //Failed to create the file
    if (fd < 0) 
        return 1;

    int result = flock(fileno(fd), 1);
    //fprintf(log,"[%s]%s\n",type, text);
        

    fprintf(fd,"[GENERAL]\n");
    fprintf(fd,"WATCH_DIRS=/home/$USR/Desktop/dmn/watch/\n");
    fprintf(fd,"#$USR will be replaced with current active user.\n");
    fprintf(fd,"#Comments(Lines starting with #) will be ignored.\n");

    fprintf(fd,"[TYPES]\n");
    fprintf(fd,"mp3,flac,wav;/home/$USR/Music/\n");
    fprintf(fd,"mkv,avi,mp4;/home/$USR/Videos/\n");
    fprintf(fd,"svg,jpeg,png;/home/$USR/Pictures/\n");
    fprintf(fd,"docx,txt,pdf;/home/$USR/Documents/\n");

    int release = flock(fileno(fd), 8);
    fclose(fd);
    return 0;
}

//Check if folder exists
//RETURN  0- folder exists. >0 - errno value
int FolderExists(char* path)
{
    DIR* dir = opendir(path);
    if (dir) {
    /* Directory exists. */
    
    closedir(dir);
    return 0;
    }
    else
    {
        closedir(dir);
        printf("Path: %s | %s\n",path, strerror(errno));
    /* Return error number */
    return errno;
    } 
}