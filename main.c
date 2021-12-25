#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"

int main()
{
    init_users();
    print_all_users();
    init_communities();
    print_all_communities();
    create_community();
    print_all_communities();
    return 0;
}