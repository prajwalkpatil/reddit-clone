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
    delete_lines(6);
    switch (choice)
    {
    case 1:
        sign_up();
        display_lr();
        break;
    case 2:
        while (status == 0)
            status = login_user();
        display_loggedin();
        return;
        break;
    case 3:
        printf("\n\n");
        print_all_posts();
        display_logo();
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
    printf("\n\n");
    purple_black();
    printf("  Logged in as  ");
    reset();
    lblue_black();
    printf(" u/%s  ", main_user_holder->user_content->username);
    reset();
    display_user_posts();
    display_options();
    printf("\n");
}

void display_user_posts()
{
    printf("\n\n\n");
    lblue_black();
    printf(" =================== ");
    reset();
    green_black();
    printf(" FEED ");
    reset();
    lblue_black();
    printf(" =================== ");
    reset();
    printf("\n");
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

void display_community_posts_obo()
{
    int choice = 0;
    int start_c = 0;
    int end_c = -1;
    USER_HOLDER *logged_user = main_user_holder;
    POST *post_temp;
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
        if (c[i]->user_content->posts != NULL)
        {
            post_temp = c[i]->user_content->posts;
            while (post_temp != NULL)
            {
                display_post_obo(post_temp);
                printf("\n1) Next Post");
                printf("\n2) Exit display");
                printf("\nEnter your choice: ");
                scanf("%d", &choice);
                delete_lines(4);
                if (choice != 1)
                {
                    return;
                }
                post_temp = post_temp->next;
            }
        }
    }
}

void display_options()
{
    int choice;
    int temp;
    d_red("\nProceed to display post individually to upvote/downvote or add comments/replies to it.");
    printf("\n0) Display posts individually");
    printf("\n1) Post to a community");
    printf("\n2) Comment to a post by id");
    printf("\n3) Reply to a comment by id");
    printf("\n4) Join Community");
    printf("\n5) Create Community");
    printf("\n6) Back to main menu");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    delete_lines(10);
    switch (choice)
    {
    case 0:
        display_community_posts_obo();
        display_options();

        break;
    case 1:
        add_post();
        display_options();

        break;
    case 2:
        printf("Enter id of the post: ");
        scanf("%d", &temp);
        add_comment(temp);
        display_options();

        break;
    case 3:
        printf("Enter id of the comment: ");
        scanf("%d", &temp);
        add_reply(temp);
        display_options();

        break;
    case 4:
        join_community();
        display_options();
        break;
    case 5:
        create_community();
        display_options();
        break;
    default:
        display_lr();
        break;
    }
}

int flag = 0;

void display_post_obo(POST *p)
{
    int choice;
    char ch;
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
    printf(" (#%3d)", temp_post->id);
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
    while (1 && !flag)
    {
        printf("Score(#%3d):%6d\nUpvotes:%10d\nDownvotes:%8d", temp_post->id, (temp_post->upvotes - temp_post->downvotes), temp_post->upvotes, temp_post->downvotes);
        printf("\n\n");
        printf("Actions for %d: \n", temp_post->id);
        printf("1) ");
        printf("Upvote post ");
        UPVOTE_ARROW;
        printf("\n");
        printf("2) ");
        printf("Downvote post ");
        DOWNVOTE_ARROW;
        printf("\n");
        printf("3) Remove Upvote/Downvote\n");
        printf("4) Add comment to this post\n");
        printf("5) View comments/replies\n");
        printf("6) Exit this post to proceed next\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        delete_lines(12);
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
            temp_post = add_comment_to_post(temp_post);
            break;
        case 5:
            if (temp_post->child == NULL)
            {
                print_error("No comment exists proceeding to parent comment/post");
                getchar();
                printf("Do you want to proceed to previous post? (y/n): ");
                scanf("%c", &ch);
                delete_lines(4);
                printf("\nScore(#%3d):%6d\n", temp_post->id, (temp_post->upvotes - temp_post->downvotes));
                if (ch == 'N' || ch == 'n')
                {
                    flag = 1;
                }
                else
                {
                    return;
                }
            }
            display_comments_obo(temp_post->child, 1);
            break;
        default:
            return;
            break;
        }
    }
}

void display_comments_obo(COMMENT *c, int level)
{
    char ch;
    int u_s = 0;
    int d_s = 0;
    int choice;
    if (c == NULL)
    {
        return;
    }
    COMMENT *temp_comment = c;
    printf("\n");
    for (int l = 0; l < level; l++)
    {
        printf("\xB2\xB2");
    }
    printf(" (#%3d) ", temp_comment->id);
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
    while (1 && !flag)
    {
        printf("Score(#%3d):%6d\nUpvotes:%10d\nDownvotes:%8d", temp_comment->id, (temp_comment->upvotes - temp_comment->downvotes), temp_comment->upvotes, temp_comment->downvotes);
        printf("\n\n");
        printf("Actions for #%d: \n", temp_comment->id);
        printf("1) ");
        printf("Upvote post ");
        UPVOTE_ARROW;
        printf("\n");
        printf("2) ");
        printf("Downvote post ");
        DOWNVOTE_ARROW;
        printf("\n");
        printf("3) Remove Upvote/Downvote\n");
        printf("4) Add reply to this comment/reply\n");
        printf("5) View next replies/comments\n");
        printf("6) View replies to this comment/reply\n");
        printf("7) Proceed to previous post/comment/reply\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6)
            delete_lines(12);
        else
            delete_lines(13);
        switch (choice)
        {
        case 1:
            if (u_s == 0 && d_s == 0)
            {
                u_s = 1;
                upvote_comment(temp_comment);
            }
            else if (u_s == 0)
            {
                u_s = 1;
                d_s = 0;
                temp_comment->downvotes--;
                update_comment_file(temp_comment);
                upvote_comment(temp_comment);
            }
            break;
        case 2:
            if (u_s == 0 && d_s == 0)
            {
                d_s = 1;
                downvote_comment(temp_comment);
            }
            else if (d_s == 0)
            {
                d_s = 1;
                u_s = 0;
                temp_comment->upvotes--;
                update_comment_file(temp_comment);
                downvote_comment(temp_comment);
            }
            break;
        case 3:
            if (u_s == 1 && d_s == 0)
            {
                u_s = 0;
                temp_comment->upvotes--;
            }
            else if (d_s == 1 && u_s == 0)
            {
                d_s = 0;
                temp_comment->downvotes--;
            }
            update_comment_file(temp_comment);
            break;
        case 4:
            temp_comment = add_reply_to_comment(temp_comment);
            break;
        case 5:
            if (temp_comment->next == NULL)
            {
                print_error("No comment exists.");
                getchar();
                printf("Do you want to proceed to previous post? (y/n): ");
                scanf("%c", &ch);
                delete_lines(4);
                printf("\nScore(#%3d):%6d\n", temp_comment->id, (temp_comment->upvotes - temp_comment->downvotes));
                if (ch == 'N' || ch == 'n')
                {
                    flag = 1;
                }
                else
                {
                    return;
                }
            }
            display_comments_obo(temp_comment->next, level);
            // return;
            break;
        case 6:
            if (temp_comment->child == NULL)
            {
                print_error("No comment exists.");
                getchar();
                printf("Do you want to proceed to previous post/comment? (y/n): ");
                scanf("%c", &ch);
                delete_lines(4);
                printf("\nScore(#%3d):%6d\n", temp_comment->id, (temp_comment->upvotes - temp_comment->downvotes));
                if (ch == 'N' || ch == 'n')
                {
                    flag = 1;
                }
                else
                {
                    return;
                }
            }
            display_comments_obo(temp_comment->child, level + 1);
            break;
        default:
            return;
            break;
        }
    }
}

void display_post_by_id()
{
    int temp_id;
    printf("\nEnter the id of post: ");
    scanf("%d", &temp_id);
    display_post_obo(*(post_by_id(temp_id)));
}
