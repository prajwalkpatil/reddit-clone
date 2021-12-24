#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"
#include "community.c"

int main()
{
    init_users();
    print_all_users();
    create_community();
    return 0;
}