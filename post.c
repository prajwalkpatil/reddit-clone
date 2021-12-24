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

void add_post()
{
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
    printf("Enter post title: \n");
    scanf("%[\n]s", p->title);
    printf("Enter post content: \n");
    scanf("%[\n]s", p->content);
    p->user_id = main_user_holder->user_content->id;
    strcpy(p->username, main_user_holder->user_content->username);
}
