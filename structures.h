#ifndef _STRUCTURES_INCULDED_
#define _STRUCTURES_INCULDED_

// Size of title and comment
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_CONTENT 1000
#define MAX_SIZE_DESCRIPTION 1000

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
    int user_id;
    int upvotes;
    int downvotes;
    unsigned long long dt;
    char username[18];
    char content[MAX_SIZE_CONTENT];
    struct comment *next;
    struct comment *child;
};
typedef struct comment COMMENT;

struct post
{
    int id;
    int user_id;
    int upvotes;
    int downvotes;
    unsigned long long dt;
    char username[18];
    char title[MAX_SIZE_TITLE];
    char content[MAX_SIZE_CONTENT];
    struct post *next;
    struct comment *child;
};
typedef struct post POST;

struct community
{
    int id;
    int dt_created;
    int members;
    char desc[MAX_SIZE_DESCRIPTION];
};
typedef struct community COMMUNITY;
#endif