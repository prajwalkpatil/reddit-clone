#include "reddit.h"

void add_post()
{
    char community_name[25];
    printf("Enter a community name: ");
    scanf("%s", community_name);
    if (!search_communtity(community_name))
    {
        print_error("Community not found!");
        return;
    }
}
