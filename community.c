#include "reddit.h"

void read_community_count()
{
    FILE *fp = fopen("files/community/community_count.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fscanf(fp, "%d", &community_count_start);
    fclose(fp);
}

void update_community_count()
{
    FILE *fp = fopen("files/community/community_count.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp, "%d", community_count_start);
    fclose(fp);
}

void community_file_name(char community_name[25], char file_name[70])
{
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
        return FAILURE;
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

int create_community()
{
    read_community_count();
    COMMUNITY *c = (COMMUNITY *)malloc(sizeof(COMMUNITY));
    if (c == NULL)
    {
        print_error("Heap is full!");
        return FAILURE;
    }
    int status = 1;
    char community_name[25];
    printf("Enter a community name: ");
    scanf("%s", community_name);
    status = search_communtity(community_name);
    while (status == 1)
    {
        print_error("Community already exists!");
        printf("Enter a community name: ");
        scanf("%s", community_name);
        status = search_communtity(community_name);
    }
    strcpy(c->name, community_name);
    c->id = ++community_count_start;
    update_community_count();
    FILE *fp = fopen("files/community/communities_all.rdt", "a+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return FAILURE;
    }
    getchar();
    printf("Enter a description: ");
    scanf("%[^\n]s", c->desc);
    c->members = 0;
    c->dt_created = 0;
    fprintf(fp, "%d %d %d %s %s\n", c->id, c->members, c->dt_created, c->name, c->desc);
    fclose(fp);
    char file_name[70];
    community_file_name(community_name, file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        return FAILURE;
    }
    fclose(fp1);
    return SUCCESS;
}