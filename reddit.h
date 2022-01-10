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

// Global declarations
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
void user_file_name(char user_name[25], char file_name[270]);
void create_user_file(char user_name[25]);
void post_file_name(char post_name[25], char file_name[270]);
void create_post_file(int id);
void create_user_community_file(char user_name[25]);
void user_community_file_name(char user_name[25], char file_name[270]);
void join_community();
void create_comment_file(char user_name[25]);
void comment_file_name(char comment_name[25], char file_name[70]);
void add_comment(int post_id);
void add_reply(int comment_id);
POST *get_post_by_id(POST *t, POST *p, int id);
POST *insert_post_at_end(POST *head, int post_id);
void initialize_posts();
void print_all_posts();
int file_empty_check(char *filename);
long int date();
unsigned long long int date_time();
void fgets_newline_kill(char a[]);
COMMENT *insert_comment_at_end(COMMENT *head, int comment_id);
COMMENT *get_comment_by_id(COMMENT *t, COMMENT *p, int id);
void print_comments(COMMENT *p, int level);
void update_post_file(POST *p);
void update_comment_file(COMMENT *c);
void upvote_post(POST *p);
void downvote_post(POST *p);
void upvote_comment(COMMENT *p);
void downvote_comment(COMMENT *p);
void print_community_posts(COMMUNITY_HOLDER *c);
COMMUNITY_HOLDER *get_community(char community_name[50]);
POST **post_by_id(int req_id);
//********** Display functions ***************

void d_red_black(char a[MAX_DISPLAY_SIZE]);
void d_yellow_black(char a[MAX_DISPLAY_SIZE]);
void d_green_black(char a[MAX_DISPLAY_SIZE]);
void d_blue_black(char a[MAX_DISPLAY_SIZE]);
void d_purple_black(char a[MAX_DISPLAY_SIZE]);
void d_lblue_black(char a[MAX_DISPLAY_SIZE]);
void d_blue(char a[MAX_DISPLAY_SIZE]);
void d_red(char a[MAX_DISPLAY_SIZE]);
void d_yellow(char a[MAX_DISPLAY_SIZE]);
void d_lblue(char a[MAX_DISPLAY_SIZE]);
void d_purple(char a[MAX_DISPLAY_SIZE]);
void red_black();
void yellow_black();
void green_black();
void blue_black();
void purple_black();
void lblue_black();
void blue();
void red();
void yellow();
void lblue();
void purple();
void green();
void reset();

//********************************************
void print_date_time(unsigned long long n);
void print_date(int n);
void display_lr();
void display_logo();
void display_loggedin();
//! Don't use this function unless you want to reset all the users and communities
void create_initial_files();
//!______________________________________________________________________________//
// TODO: sort as - top, new, best
#endif