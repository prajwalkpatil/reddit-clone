#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"
#include "post.c"
#include "comment.c"
#include "display.c"
#include "ops.c"

int main()
{
    // screen_reset();
    init();
    post_sort_new(all_communities->user_content->posts);
    print_sorted_posts();
    // display_post_by_id();
    // // display_post_obo(all_communities->user_content->posts);
    // display_logo();
    // display_lr();
    // display_loggedin();
    // upvote_post(*post_by_id(15));
    // downvote_post(*post_by_id(15));
    // display_options();
    // display_user_posts();
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
    // printf("\n**************************************\n");
    return 0;
}