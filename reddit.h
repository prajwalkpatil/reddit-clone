#ifndef _REDDIT_H_INCLUDED_
#define _REDDIT_H_INCLUDED_

// Including all the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <limits.h>
#include <sys/stat.h>
#include "structures.h"

// Status Codes
#define SUCCESS 1
#define FAILURE_EMAIL -1
#define FAILURE_USERNAME -2
#define FAILURE 0

// Debugging
#define err(v) printf(v);
#define NEWLINE printf("\n");

// Static variables
int user_count_start = 0;
int post_count_start = 0;
int community_count_start = 0;

// Global declarions
USER_HOLDER *main_user_holder = NULL;
USER_HOLDER *all_users = NULL;
COMMUNITY_HOLDER *all_communities = NULL;

// TODO: Insert function definitions
char *hash448(char *str);
int add_user(USER *u);
int write_pwd(char username[8], char pwd_hash[31]);
int pwd_input(char username[8], char pwd[31]);
int email_input(char email[64]);
int check_duplicates(char username_req[18], char email_req[64]);
void add_username_file(char username_r[18]);
int auth_user(char username_r[18], char password_r[31]);
void sign_up();
int login_user();
USER_HOLDER *insert_user_at_end(USER_HOLDER *hdr, USER *u);
void init_users();
void print_all_users();
void update_users_file();
void community_file_name(char community_name[25], char file_name[70]);
int search_communtity(char community_name[25]);
void add_post();
void read_post_count();
void update_post_count();
int create_community();
void update_community_count();
void read_community_count();
void init_communities();
COMMUNITY_HOLDER *insert_community_at_end(COMMUNITY_HOLDER *hdr, COMMUNITY *u);
void print_all_communities();
void update_communities_file();

// TODO: sort as - top, new, best
#endif