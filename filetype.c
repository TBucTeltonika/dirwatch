#include "filetype.h"

extern filetype_t* filetypes;
//attempts to create a new node and insert it into the global pointers filetypes;
//RETURN: 0 - everything went OK. 1 - Error creating the node.
int InsertIntoFileType(char *filetype, char *destination)
{

    filetype_t* new = newnode(filetype,destination);

    //Check if new node was created successfully.
    if (new == NULL)
        return 1;

    //filetypes not initialiazed yet we need to do it.
    if (filetypes == NULL)
    {
        printf("inserting new %s\n",filetype);
        filetypes = new;
        return 0;
    }

    //Search for the last node in the linked list.
    filetype_t *curr = filetypes;
    filetype_t *next = curr->next;

    while (next != NULL)
    {
        curr = next;
        next = curr->next;
    }
    printf("inserting into existing. %s\n",filetype);
    printf("after %s\n",curr->filetype);
    //insert into the last node.
    curr->next = new;

    return 0;
}

//Returns node if everything went ok, returns NULL if there was an error.
filetype_t *newnode(char *filetype, char *destination)
{
    filetype_t *node = (filetype_t *)malloc(sizeof(filetype_t));

    //set up the data in the node.
    if (strlen(filetype) > sizeof(node->filetype))
    {
        LogToFile("filetype too large.", "CFG");
        free(node);
        return NULL;
    }
    
    strcpy(node->filetype, filetype);

    if (strlen(destination) > sizeof(node->destination))
    {
        LogToFile("destination too large.", "CFG");
        free(node);
        return NULL;
    }
    strcpy(node->destination, destination);
    node->next = NULL;

    return node;
}

//returns pointer to the filetype_t if we found the extension. returns NULL if not matched.
filetype_t *MatchExtension(char *str)
{
    filetype_t *ret = NULL;

    filetype_t *curr = filetypes;

    if (curr == NULL)
    {
        printf("filetypes not initialized?\n");
        return NULL;
    }
    filetype_t *next = curr->next;

    while (next != NULL)
    {
        if (EndsWith(str,curr->filetype))
            return curr;

        curr = next;
        next = curr->next;
    }

    return ret;
}