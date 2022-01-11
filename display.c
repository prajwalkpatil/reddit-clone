#include "reddit.h"

void d_red_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[41;30m %s \033[m", a);
}

void d_yellow_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[43;30m %s \033[m", a);
}

void d_green_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[42;30m %s \033[m", a);
}

void d_blue_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[44;30m %s \033[m", a);
}

void d_purple_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[45;30m %s \033[m", a);
}

void d_lblue_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[46;30m %s \033[m", a);
}

void d_blue(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[34m %s \033[m", a);
}

void d_red(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[31m %s \033[m", a);
}

void d_yellow(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[33m %s \033[m", a);
}

void d_lblue(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[36m %s \033[m", a);
}

void d_purple(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[35m %s \033[m", a);
}

void red_black()
{
    printf("\033[41;30m");
}

void yellow_black()
{
    printf("\033[43;30m");
}

void green_black()
{
    printf("\033[42;30m");
}

void blue_black()
{
    printf("\033[44;30m");
}

void purple_black()
{
    printf("\033[45;30m");
}

void lblue_black()
{
    printf("\033[46;30m");
}

void blue()
{
    printf("\033[34m");
}

void red()
{
    printf("\033[31m");
}

void green()
{
    printf("\033[32m");
}

void yellow()
{
    printf("\033[33m");
}

void lblue()
{
    printf("\033[36m");
}

void purple()
{
    printf("\033[35m");
}

void reset()
{
    printf("\033[0m");
}

void delete_lines(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\33[2K");
        printf("\033[A");
    }
}

void display_lr()
{
    int status = 0;
    int choice = 0;
    printf("\n1) Register");
    printf("\n2) Login");
    printf("\n3) Browse");
    printf("\n4) Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        sign_up();
        display_lr();
        break;
    case 2:
        while (status == 0)
            status = login_user();
        return;
        break;
    case 3:
        printf("\n\n");
        print_all_posts();
        display_lr();
        break;
    default:
        exit(0);
        break;
    }
}

void display_logo()
{
    red();
    printf("    ____           __    ___ __\n"
           "   / __ \\___  ____/ /___/ (_) /_\n"
           "  / /_/ / _ \\/ __  / __  / / __/\n"
           " / _, _/  __/ /_/ / /_/ / / /_\n"
           "/_/ |_|\\___/\\__,_/\\__,_/_/\\__/\n");
    printf("\nThe front page of the internet.\n");
    reset();
}
void display_loggedin()
{
    // screen_reset();
    purple_black();
    printf("  Logged in as  ");
    reset();
    lblue_black();
    printf(" u/%s  ", main_user_holder->user_content->username);
    reset();
    printf("\n");
}

void display_user_posts()
{
    int start_c = 0;
    int end_c = -1;
    USER_HOLDER *logged_user = main_user_holder;
    COMMUNITY_HOLDER *c[MAX_NOC];
    char file_name[300];
    char comm_name[300];
    user_community_file_name(logged_user->user_content->username, file_name);
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        return;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", comm_name);
        c[++end_c] = get_community(comm_name);
    }
    fclose(fp);
    for (int i = start_c; i <= end_c; i++)
    {
        print_community_posts(c[i]);
    }
}

void display_options()
{
    int choice;
    int temp;
    printf("\n1) Post");
    printf("\n2) Comment");
    printf("\n3) Reply");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        add_post();
        break;
    case 2:
        printf("Enter id of the post: ");
        scanf("%d", &temp);
        add_comment(temp);
        break;
    case 3:
        printf("Enter id of the comment: ");
        scanf("%d", &temp);
        add_reply(temp);
        break;
    }
}

void display_post_obo(POST *p)
{
    int choice;
    int u_s = 0;
    int d_s = 0;
    if (p == NULL)
    {
        return;
    }
    POST *temp_post = p;
    printf("\n\n");
    // printf("%d)", temp_post->id);
    yellow_black();
    printf("  r/%s  ", temp_post->community_name);
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
    printf("%s\n\n", temp_post->content);
    while (1)
    {
        printf("Score:%6d\nUpvotes:%6d\nDownvotes:%6d", (temp_post->upvotes - temp_post->downvotes), temp_post->upvotes, temp_post->downvotes);
        printf("\n\n");
        printf("Actions: \n");
        printf("1) ");
        printf("Upvote post ");
        UPVOTE_ARROW;
        printf("\n");
        printf("2) ");
        printf("Downvote post ");
        DOWNVOTE_ARROW;
        printf("\n");
        printf("3) Remove Upvote/Downvote\n");
        printf("4) View comments/replies\n");
        printf("5) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        delete_lines(11);
        switch (choice)
        {
        case 1:
            if (u_s == 0 && d_s == 0)
            {
                u_s = 1;
                upvote_post(temp_post);
            }
            else if (u_s == 0)
            {
                u_s = 1;
                d_s = 0;
                temp_post->downvotes--;
                update_post_file(temp_post);
                upvote_post(temp_post);
            }
            break;
        case 2:
            if (u_s == 0 && d_s == 0)
            {
                d_s = 1;
                downvote_post(temp_post);
            }
            else if (d_s == 0)
            {
                d_s = 1;
                u_s = 0;
                temp_post->upvotes--;
                update_post_file(temp_post);
                downvote_post(temp_post);
            }
            break;
        case 3:
            if (u_s == 1 && d_s == 0)
            {
                u_s = 0;
                temp_post->upvotes--;
            }
            else if (d_s == 1 && u_s == 0)
            {
                d_s = 0;
                temp_post->downvotes--;
            }
            update_post_file(temp_post);
            break;
        case 4:
            print_comments(temp_post->child, 1);
            break;
        default:
            return;
            break;
        }
    }
}