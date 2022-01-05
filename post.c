#include "reddit.h"

void read_post_count()
{
    FILE *fp = fopen("files/posts/post_count.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fscanf(fp, "%d", &post_count_start);
    fclose(fp);
}

void update_post_count()
{
    FILE *fp = fopen("files/posts/post_count.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fprintf(fp, "%d", post_count_start);
    fclose(fp);
}
void create_post_file(int id)
{
    char post_name[25];
    itoa(id, post_name, 10);
    // printf("%s\n", post_name);
    char file_name[270];
    post_file_name(post_name, file_name);
    // printf("%s\n", file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        return;
    }
    fclose(fp1);
}
void add_post()
{
    read_post_count();
    char community_name[25];
    printf("Enter a community name: ");
    scanf("%s", community_name);
    if (!search_communtity(community_name))
    {
        print_error("Community not found!");
        return;
    }

    POST *p = (POST *)malloc(sizeof(POST));
    if (p == NULL)
    {
        print_error("Heap is full!");
        return;
    }
    getchar();
    p->id = ++post_count_start;
    printf("Enter post title: \n");
    scanf("%[^\n]s", p->title);
    getchar();
    printf("Enter post content: \n");
    scanf("%[^\n]s", p->content);
    p->user_id = main_user_holder->user_content->id;
    strcpy(p->username, main_user_holder->user_content->username);
    strcpy(p->community_name, community_name);
    //*Create the file with name of post id
    create_post_file(p->id);
    //***********************************************
    //*Write the id of post in the file of community
    char file_name[70];
    community_file_name(p->community_name, file_name);
    FILE *fp_com = fopen(file_name, "a+");
    if (fp_com == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    //*Write the id of post in the community file
    fprintf(fp_com, "%d\n", p->id);
    fclose(fp_com);
    //*******************************************

    //***********************************************
    //*Write the id of post in the file of user
    strcpy(p->username, main_user_holder->user_content->username);
    user_file_name(p->username, file_name);
    FILE *fp_usr = fopen(file_name, "a+");
    if (fp_usr == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    //*Write the id of post in the user file
    fprintf(fp_usr, "%d\n", p->id);
    fclose(fp_usr);
    //*******************************************

    //********************************************
    //*Write the post content in the post file
    char post_name[25];
    itoa(p->id, post_name, 10);
    post_file_name(post_name, file_name);
    FILE *fp_post = fopen(file_name, "a+");
    if (fp_post == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    //*Write the id of post in the user file
    fprintf(fp_post, "%d %llu %d %d %s %s\n", p->id, p->dt, p->upvotes, p->downvotes, p->username, p->community_name);
    fprintf(fp_post, "%s\n%s\n", p->title, p->content);
    fclose(fp_post);
    //********************************************
    update_post_count();
    print_success("This post was sucessfully posted!");
}

void post_file_name(char post_name[25], char file_name[270])
{
    int i = 0;
    int k = 0;
    strcpy(file_name, "files/posts/");
    i = 12;
    while (post_name[k] != '\0')
    {
        file_name[i] = post_name[k];
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