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
    file_name[i] = '\0';
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
    COMMUNITY *c = (COMMUNITY *)malloc(sizeof(COMMUNITY));
    while (!feof(fp))
    {
        fscanf(fp, "%d\t%d\t%d\t%s\n%[^\n]s\n ", &c->id, &c->members, &c->dt_created, c->name, c->desc);
        if (!strcmp(community_name, c->name))
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
    FILE *fp = fopen("files/community/communities_all.rdt", "a+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return FAILURE;
    }
    getchar();
    char file_name[70];
    community_file_name(community_name, file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        fclose(fp);
        return FAILURE;
    }
    fclose(fp1);
    printf("Enter a description: ");
    scanf("%[^\n]s", c->desc);
    c->members = 0;
    c->dt_created = 0;
    fprintf(fp, "%d\t%d\t%d\t%s\n%s\n", c->id, c->members, c->dt_created, c->name, c->desc);
    fclose(fp);
    update_community_count();
    print_success("Community sucessfully created!");
    all_communities = insert_community_at_end(all_communities, c);
    return SUCCESS;
}

void init_communities()
{
    read_community_count();
    FILE *fp = fopen("files/community/communities_all.rdt", "r");
    if (fp == NULL)
    {
        print_error("File empty!");
        return;
    }
    while (!feof(fp))
    {
        COMMUNITY *c = (COMMUNITY *)malloc(sizeof(COMMUNITY));
        if (c == NULL)
        {
            print_error("Heap is full");
            return;
        }
        fscanf(fp, "%d\t%d\t%d\t%s\n%[^\n]s\n", &c->id, &c->members, &c->dt_created, c->name, c->desc);
        if (c->id > community_count_start)
        {
            break;
        }
        all_communities = insert_community_at_end(all_communities, c);
    }
    fclose(fp);
}

COMMUNITY_HOLDER *insert_community_at_end(COMMUNITY_HOLDER *hdr, COMMUNITY *u)
{
    COMMUNITY_HOLDER *n = (COMMUNITY_HOLDER *)malloc(sizeof(COMMUNITY_HOLDER));
    if (n == NULL)
    {
        print_error("The Heap is full!");
        return hdr;
    }
    n->next = NULL;
    n->user_content = u;
    if (hdr == NULL)
    {
        hdr = n;
        return hdr;
    }
    COMMUNITY_HOLDER *temp = hdr;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = n;
    return hdr;
}

void print_all_communities()
{
    if (all_communities == NULL)
    {
        print_error("No communities!");
        return;
    }
    COMMUNITY_HOLDER *temp = all_communities;
    printf("\n>> COMMUNITIES: \n");
    while (temp != NULL)
    {
        printf("%d) %s - %s\n", temp->user_content->id, temp->user_content->name, temp->user_content->desc);
        temp = temp->next;
    }
}

void update_communities_file()
{
    if (all_users == NULL)
    {
        print_error("No communities!");
        return;
    }
    FILE *fp = fopen("files/community/communities_all.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    COMMUNITY_HOLDER *temp = all_communities;
    COMMUNITY *c;
    while (temp != NULL)
    {
        c = temp->user_content;
        fprintf(fp, "%d\t%d\t%d\t%s\n%s\n", c->id, c->members, c->dt_created, c->name, c->desc);
        temp = temp->next;
    }
    fclose(fp);
}

void join_community()
{
    char community_name[25];
    printf("Enter a community name: ");
    scanf("%s", community_name);
    if (!search_communtity(community_name))
    {
        print_error("Community not found!");
        return;
    }

    char file_name[70];
    char temp_community_name[70];
    user_community_file_name(main_user_holder->user_content->username, file_name);

    //*Check if the user has already joined the community
    FILE *fp_c = fopen(file_name, "r");
    if (fp_c == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    while (!feof(fp_c))
    {
        fscanf(fp_c, "%s\n", temp_community_name);
        if (!strcmp(community_name, temp_community_name))
        {
            print_error("You've already joined the community!");
            return;
        }
    }
    fclose(fp_c);

    //*Write the community name in the user file
    FILE *fp_usr = fopen(file_name, "a+");
    if (fp_usr == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    //*Write the community name in the user file
    fprintf(fp_usr, "%s\n", community_name);
    fclose(fp_usr);
    print_success("You have sucessfully joined the community!");

    //*Increase the number of members in the community
    COMMUNITY_HOLDER *temp = all_communities;
    while (temp != NULL)
    {
        if (!strcmp(community_name, temp->user_content->name))
        {
            ++(temp->user_content->members);
            break;
        }
        temp = temp->next;
    }
}