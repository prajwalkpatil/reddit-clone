#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"
#include "post.c"
#include "comment.c"
#include "display.c"
int main()
{
    screen_reset();
    init_users();
    init_communities();
    initialize_posts();
    display_logo();
    display_lr();
    display_loggedin();
    // print_all_users();
    // print_all_communities();
    // print_all_users();
    // sign_up();
    // create_community();
    // print_all_communities();
    // while (status == 0)
    //     status = login_user();
    // add_post();
    // add_comment(15);
    // while (status == 0)
    //     status = login_user();
    // add_reply(22);
    // print_all_users();
    // print_all_posts();
    // printf("\n**************************************\n");
    return 0;
}