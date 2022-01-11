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
        fscanf(fp, "%d\t%d\t%d\t%s\n", &c->id, &c->members, &c->dt_created, c->name);
        fgets(c->desc, MAX_SIZE_DESCRIPTION, fp);
        fgets_newline_kill(c->desc);
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

    char file_name[270];
    char temp_community_name[270];
    user_community_file_name(main_user_holder->user_content->username, file_name);

    //*Check if the user has already joined the community
    FILE *fp_c = fopen(file_name, "r");
    if (fp_c != NULL)
    {
        while (!feof(fp_c))
        {
            fscanf(fp_c, "%s\n", temp_community_name);
            if (!strcmp(community_name, temp_community_name))
            {
                print_error("You've already joined the community!");
                return;
            }
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
    update_communities_file();
}

POST *insert_post_at_end(POST *head, int post_id)
{
    POST *p = (POST *)malloc(sizeof(POST));
    p->next = NULL;
    p->child = NULL;
    if (head == NULL)
    {
        head = get_post_by_id(head, p, post_id);
        // printf("\n%d\n%s\n%s", head->id, head->title, head->content);
        return head;
    }
    POST *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = get_post_by_id(temp->next, p, post_id);
    // printf("\n%d\n%s\n%s\n", temp->next->id, temp->next->title, temp->next->content);
    return head;
}

POST *get_post_by_id(POST *t, POST *p, int id)
{
    if (p == NULL)
    {
        print_error("Heap is full!");
        return NULL;
    }
    char file_name[25];
    int temp_comm_id;
    char post_name[25];
    itoa(id, post_name, 10);
    post_file_name(post_name, file_name);
    // printf("%s\n", file_name);
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        print_error("Unable to open the file");
        return NULL;
    }
    fscanf(fp, "%d %llu %d %d %s %s\n", &p->id, &p->dt, &p->upvotes, &p->downvotes, p->username, p->community_name);
    fgets(p->title, MAX_SIZE_TITLE, fp);
    fgets_newline_kill(p->title);
    fgets(p->content, MAX_SIZE_CONTENT, fp);
    fgets_newline_kill(p->content);
    p->child = NULL;
    while (!feof(fp))
    {
        fscanf(fp, "%d\n", &temp_comm_id);
        p->child = insert_comment_at_end(p->child, temp_comm_id);
    }
    fclose(fp);
    t = p;
    return t;
}

POST **post_by_id(int req_id)
{
    COMMUNITY_HOLDER *temp = all_communities;
    POST **p_ptr = (POST **)malloc(sizeof(POST *));
    if (temp == NULL)
    {
        return p_ptr;
    }
    while (temp != NULL)
    {
        if (temp->user_content->posts->id == req_id)
        {
            *p_ptr = temp->user_content->posts;
            break;
        }
        temp = temp->next;
    }
    return p_ptr;
}

void initialize_posts()
{
    if (all_communities == NULL)
    {
        print_error("No communities!");
        return;
    }
    COMMUNITY_HOLDER *temp = all_communities;
    char t_c[25];
    char file_name[40];
    FILE *fp;
    int temp_post_id;
    while (temp->next->next != NULL)
    {
        strcpy(t_c, temp->user_content->name);
        community_file_name(t_c, file_name);
        if (!file_empty_check(file_name))
        {
            fp = fopen(file_name, "r");
            while (!feof(fp))
            {
                fscanf(fp, "%d\n", &temp_post_id);
                temp->user_content->posts = insert_post_at_end(temp->user_content->posts, temp_post_id);
            }
        }
        fclose(fp);
        temp = temp->next;
    }
}

void print_all_posts()
{
    COMMUNITY_HOLDER *temp = all_communities;
    if (temp == NULL)
    {
        print_error("No communitites!");
        return;
    }
    POST *temp_post = (POST *)malloc(sizeof(POST));
    COMMENT *temp_comment = (COMMENT *)malloc(sizeof(COMMENT));
    COMMENT *temp_comment_child = (COMMENT *)malloc(sizeof(COMMENT));
    if (temp_post == NULL)
    {
        print_error("Heap is full!");
        return;
    }
    int i = 0;
    while (temp->next != NULL)
    {
        i = 0;
        yellow_black();
        temp_post = temp->user_content->posts;
        if (temp_post != NULL)
            printf("  r/%s  ", temp->user_content->name);
        reset();
        while (temp_post != NULL)
        {
            printf("\n\n");
            printf("%d)", temp_post->id);
            blue_black();
            printf(" u/%s", temp_post->username);
            reset();
            printf(" posted at ");
            blue_black();
            print_date_time(temp_post->dt);
            reset();
            printf(" : ");
            lblue();
            printf("%s\n", temp_post->title);
            reset();
            printf("%s\n", temp_post->content);
            print_comments(temp_post->child, 1);
            printf("\n");
            temp_post = temp_post->next;
            i++;
            printf("\n\n");
        }
        temp = temp->next;
    }
}

void print_community_posts(COMMUNITY_HOLDER *c)
{
    COMMUNITY_HOLDER *temp = c;
    if (temp == NULL)
    {
        print_error("No communitites!");
        return;
    }
    POST *temp_post = (POST *)malloc(sizeof(POST));
    COMMENT *temp_comment = (COMMENT *)malloc(sizeof(COMMENT));
    COMMENT *temp_comment_child = (COMMENT *)malloc(sizeof(COMMENT));
    if (temp_post == NULL)
    {
        print_error("Heap is full!");
        return;
    }
    int i = 0;
    temp_post = temp->user_content->posts;
    while (temp_post != NULL)
    {
        printf("\n\n");
        // printf("%d)", temp_post->id);
        yellow_black();
        printf("  r/%s  ", temp->user_content->name);
        reset();
        ARROW;
        blue_black();
        printf(" u/%s", temp_post->username);
        reset();
        printf(" posted at ");
        blue_black();
        print_date_time(temp_post->dt);
        reset();
        printf(" : ");
        lblue();
        printf("\n%s\n", temp_post->title);
        reset();
        printf("%s\n", temp_post->content);
        print_comments(temp_post->child, 1);
        printf("\n");
        temp_post = temp_post->next;
        i++;
        printf("\n\n");
    }
}

COMMUNITY_HOLDER *get_community(char community_name[50])
{
    COMMUNITY_HOLDER *temp = all_communities;
    COMMUNITY_HOLDER *temp_c = NULL;
    if (temp == NULL)
    {
        return NULL;
    }
    while (temp != NULL)
    {
        if (!strcmp(temp->user_content->name, community_name))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}