#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"
#include "post.c"

int main()
{
    int status = 0;
    init_users();
    print_all_users();
    init_communities();
    print_all_communities();
    // create_community();
    // sign_up();
    while (status == 0)
        status = login_user();
    // add_post();
    print_all_communities();
    return 0;
}