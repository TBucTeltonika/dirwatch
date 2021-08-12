#include "stringop.h"

char* str_replace(char* string, const char* substr, const char* replacement) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	int   oldstr_len = 0;
	int   substr_len = 0;
	int   replacement_len = 0;

	newstr = strdup(string);
	substr_len = strlen(substr);
	replacement_len = strlen(replacement);

	if (substr == NULL || replacement == NULL) {
		return newstr;
	}

	while ((tok = strstr(newstr, substr))) {
		oldstr = newstr;
		oldstr_len = strlen(oldstr);
		newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}

		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
		memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

		free(oldstr);
	}

	//free(string);

	return newstr;
}

char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
    return result;
}


//return - string with tokens replaced(this was malloced so it will need to be freed later;
//Returns NULL if something went wrong.
char *ReplaceTokens(char *str)
{
    //check if &USR exists
    if (strstr(str, USR_TOKEN))
    {
        char* login;
    
        //uid_t uid = geteuid();
        //struct passwd *pw = getpwuid(uid);
        //login = pw->pw_name;
        //Dont need to call this every time.
        //static char *login = NULL;
        //if (login == NULL)
        //    login = getenv("USER");

       
        login = getusernamedirty();
        printf("%s | %s\n",str, login);

        //we got the login successfully.
        if (login != NULL)
        {
            char *newstr = str_replace(str, USR_TOKEN, login);
            printf("newstr: %s\n", newstr);
            //free(str);
            return newstr;
        }
        else
        {
            printf("failed to get the user\n");
            return NULL;
        }
            
    }
    //Set up without tokens.
    else
    {
        char *str_array;
        str_array = (char*)malloc(strlen(str)*sizeof(char));
        strcpy(str_array,str);
        //free(str);
        return str_array;

    }
}

char* getusernamedirty()
{
    DIR *dir;
    struct dirent *ent;
    char dirstr[] = "/home/";
    if ((dir = opendir(dirstr)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            //Patikrinam ar tai yra direktorija
            if (ent->d_type == DT_DIR)
            {
                printf ("d_name: %s\n", ent->d_name);
                closedir(dir);
                return ent->d_name;
            }
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        closedir(dir);
        return NULL;
    }

}

int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}