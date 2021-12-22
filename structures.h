#ifndef _STRUCTURES_INCULDED_
#define _STRUCTURES_INCULDED_

#define MAX_SIZE_TITLE 100
#define MAX_SIZE_CONTENT 1000
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

struct comment
{
    int id;
    int score;
    char username[18];
    char content[MAX_SIZE_CONTENT];
    struct comment *next;
    struct comment *child;
};

struct post
{
    int id;
    int score;
    char username[18];
    char title[MAX_SIZE_TITLE];
    char content[MAX_SIZE_CONTENT];
    struct post *next;
    struct comment *child;
};

typedef struct post POST;
typedef struct comment COMMENT;
#endif