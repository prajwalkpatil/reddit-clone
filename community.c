#include "reddit.h"

char *community_file_name(char community_name[25])
{
    char file_name[70];
    int i = 0;
    int k = 0;
    strcpy(file_name, "files/community/");
    i = 16;
    while (community_name[k] != '\0')
    {
        file_name[i] = community_name[k];
        i++;
        k++;
    }
    k = 0;
    while (k != 4)
    {
        file_name[i] = ".rdt"[k];
        i++;
        k++;
    }
}

int search_communtity(char community_name[25])
{
    FILE *fp = fopen("files/community/communities_all.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    char temp[25];
    while (!feof(fp))
    {
        fscanf(fp, "%s", temp);
        if (!strcmp(community_name, temp))
        {
            fclose(fp);
            return SUCCESS;
        }
    }
    fclose(fp);
    return FAILURE;
}
