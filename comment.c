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

COMMENT *insert_comment_at_end(COMMENT *head, int comment_id)
{
    COMMENT *p = (COMMENT *)malloc(sizeof(COMMENT));
    p->next = NULL;
    p->child = NULL;
    if (head == NULL)
    {
        head = get_comment_by_id(head, p, comment_id);
        // printf("\n%d\n%s\n%s", head->id, head->title, head->content);
        return head;
    }
    COMMENT *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = get_comment_by_id(temp->next, p, comment_id);
    // printf("\n%d\n%s\n%s\n", temp->next->id, temp->next->content);
    return head;
}

COMMENT *get_comment_by_id(COMMENT *t, COMMENT *p, int id)
{
    if (p == NULL)
    {
        print_error("Heap is full!");
        return NULL;
    }
    char file_name[55];
    int temp_comment_id;
    char comment_name[25];
    itoa(id, comment_name, 10);
    comment_file_name(comment_name, file_name);
    FILE *fp = fopen(file_name, "r");
    // printf("\n%s\n", file_name);
    if (fp == NULL)
    {
        return NULL;
    }
    fscanf(fp, "%d %d %d %llu %s\n", &p->id, &p->upvotes, &p->downvotes, &p->dt, p->username);
    fgets(p->content, MAX_SIZE_CONTENT, fp);
    fgets_newline_kill(p->content);
    while (!feof(fp))
    {
        fscanf(fp, "%d\n", &temp_comment_id);
        p->child = insert_comment_at_end(p->child, temp_comment_id);
    }
    fclose(fp);
    p->next = NULL;
    t = p;
    return t;
}

void print_comments(COMMENT *p, int level)
{
    if (p == NULL)
    {
        return;
    }
    COMMENT *temp_comment = p;
    while (temp_comment != NULL)
    {
        for (int l = 0; l < level; l++)
        {
            printf("\xB2\xB2");
        }
        printf("%d)", temp_comment->id);
        purple_black();
        printf(" u/%s ", temp_comment->username);
        reset();
        if (level == 1)
            printf(" commented at ");
        else
            printf(" replied at ");
        purple_black();
        print_date_time(temp_comment->dt);
        reset();
        printf(" : ");
        purple();
        printf("%s\n", temp_comment->content);
        reset();
        print_comments(temp_comment->child, level + 1);
        temp_comment = temp_comment->next;
    }
}

void update_comment_file(COMMENT *c)
{
    if (c == NULL)
    {
        return;
    }
    COMMENT *temp;
    char file_name[100];
    char comment_name[15];
    itoa(c->id, comment_name, 10);
    comment_file_name(comment_name, file_name);
    FILE *fp = fopen(file_name, "w+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp, "%d %d %d %llu %s\n%s\n", c->id, c->upvotes, c->downvotes, c->dt, c->username, c->content);
    temp = c->child;
    while (temp != NULL)
    {
        fprintf(fp, "%d\n", temp->next);
        temp = temp->next;
    }
    fclose(fp);
}

void upvote_comment(COMMENT *p)
{
    p->upvotes++;
    USER_HOLDER *temp = all_users;
    while (temp != NULL)
    {
        if (!strcmp(p->username, temp->user_content->username))
        {
            temp->user_content->karma++;
            update_users_file();
            break;
        }
        temp = temp->next;
    }
    update_comment_file(p);
}

void downvote_comment(COMMENT *p)
{
    p->downvotes++;
    USER_HOLDER *temp = all_users;
    while (temp != NULL)
    {
        if (!strcmp(p->username, temp->user_content->username))
        {
            temp->user_content->karma--;
            update_users_file();
            break;
        }
        temp = temp->next;
    }
    update_comment_file(p);
}
