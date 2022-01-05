#include "reddit.h"

void create_comment_file(char user_name[25])
{
    char file_name[70];
    user_community_file_name(user_name, file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        return;
    }
    fclose(fp1);
}

void comment_file_name(char comment_name[25], char file_name[70])
{
    int i = 0;
    int k = 0;
    strcpy(file_name, "files/comments/");
    i = 15;
    while (comment_name[k] != '\0')
    {
        file_name[i] = comment_name[k];
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

void add_comment(int post_id)
{
    read_post_count();
    COMMENT *p = (COMMENT *)malloc(sizeof(COMMENT));
    if (p == NULL)
    {
        print_error("Heap is full!");
        return;
    }
    getchar();
    printf("Enter your comment: \n");
    scanf("%[^\n]s", p->content);
    strcpy(p->username, main_user_holder->user_content->username);
    p->id = ++post_count_start;
    p->dt = date_time();
    char file_name[50];
    char post_name[50];
    itoa(p->id, post_name, 10);
    comment_file_name(post_name, file_name);
    FILE *fp = fopen(file_name, "a+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp, "%d %d %d %llu %s\n%s\n", p->id, p->upvotes, p->downvotes, p->dt, p->username, p->content);
    fclose(fp);

    itoa(post_id, post_name, 10);
    post_file_name(post_name, file_name);
    FILE *fp1 = fopen(file_name, "a+");
    if (fp1 == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp1, "%d\n", p->id);
    fclose(fp1);

    update_post_count();
}

void add_reply(int comment_id)
{
    read_post_count();
    COMMENT *p = (COMMENT *)malloc(sizeof(COMMENT));
    if (p == NULL)
    {
        print_error("Heap is full!");
        return;
    }
    getchar();
    printf("Enter your reply: \n");
    scanf("%[^\n]s", p->content);
    strcpy(p->username, main_user_holder->user_content->username);
    p->id = ++post_count_start;
    p->dt = date_time();
    char file_name[50];
    char comment_name[50];
    itoa(p->id, comment_name, 10);
    comment_file_name(comment_name, file_name);
    FILE *fp = fopen(file_name, "a+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp, "%d %d %d %llu %s\n%s\n", p->id, p->upvotes, p->downvotes, p->dt, p->username, p->content);
    fclose(fp);

    itoa(comment_id, comment_name, 10);
    comment_file_name(comment_name, file_name);
    FILE *fp1 = fopen(file_name, "a+");
    if (fp1 == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp1, "%d\n", p->id);
    fclose(fp1);
    update_post_count();
}