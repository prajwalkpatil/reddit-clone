#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"
#include "post.c"
#include "comment.c"

int main()
{
    int status = 0;
    init_users();
    // print_all_users();
    init_communities();
    // print_all_communities();
    // print_all_users();
    // sign_up();
    // while (status == 0)
    //     status = login_user();
    // create_community();
    // print_all_communities();
    // login_user();
    // add_post();
    // add_comment(2);
    // print_all_users();
    // add_reply(12);
    initialize_posts();
    print_all_posts();
    // printf("\n**************************************\n");
    return 0;
}