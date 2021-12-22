#include "reddit.h"
#include "utility.c"
#include "signup.c"
#include "signin.c"

int main()
{
    init_users();
    print_all_users();
    sign_up();
    print_all_users();
    return 0;
}