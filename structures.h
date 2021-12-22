#ifndef _STRUCTURES_INCULDED_
#define _STRUCTURES_INCULDED_

// Structure for user
struct user
{
    int id;
    char username[18];
    char name[25];
    int karma;
    int followers;
    int date_of_joining;
    char email[64];
};
typedef struct user USER;

// Structure for holding users
struct user_holder
{
    struct user *user_content;
    struct user_holder *next;
};
typedef struct user_holder USER_HOLDER;

#endif