#ifndef _STRUCTURES_INCULDED_
#define _STRUCTURES_INCULDED_

// Size of title and comment
#define MAX_SIZE_TITLE 100
#define MAX_SIZE_CONTENT 1000
#define MAX_SIZE_DESCRIPTION 10000
#define MAX_NUMBER_OF_POSTS 10000
#define MAX_NUMBER_OF_COMMENTS 100000
#define MAX_DISPLAY_SIZE 1000000
#define MAX_NOC 200
#define ARROW printf(" \xAF ");
#define UPVOTE_ARROW printf(" \x1E ");
#define DOWNVOTE_ARROW printf(" \x1F ");

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
    char community_name[25];
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
    char name[25];
    char desc[MAX_SIZE_DESCRIPTION];
    struct post *posts;
};
typedef struct community COMMUNITY;

struct community_holder
{
    struct community *user_content;
    struct community_holder *next;
};
typedef struct community_holder COMMUNITY_HOLDER;

#endif
