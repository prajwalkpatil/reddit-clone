#ifndef _REDDIT_H_INCLUDED_
#define _REDDIT_H_INCLUDED_

// Including all the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <math.h>
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
int is_loggedin = 0;
// Global declarations
USER_HOLDER *main_user_holder = NULL;
USER_HOLDER *all_users = NULL;
COMMUNITY_HOLDER *all_communities = NULL;
POST **post_sorted = NULL;
COMMENT **comment_sorted = NULL;
USER_RESULT **user_search_result = NULL;
COMMUNITY_HOLDER **community_search_result = NULL;
POST_RESULT **post_search_result = NULL;
COMMUNITY_HOLDER *community_members_sort_arr[MAX_NUMBER_OF_COMMENTS];
USER_HOLDER *users_followers_sort_arr[MAX_NUMBER_OF_USERS];
USER_HOLDER *users_karma_sort_arr[1000];
int ps_start = 0;
int ps_end = -1;
int cs_start = 0;
int cs_end = -1;
int ur_start = 0;
int ur_end = -1;
int pr_start = 0;
int pr_end = -1;
int cr_start = 0;
int cr_end = -1;

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
void display_user_posts();
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
void init();
void community_sort_mem();
void display_community_posts_obo();
POST *add_comment_to_post(POST *post_ptr);
COMMENT *add_reply_to_comment(COMMENT *comment_ptr);
void print_community_result();
void search_commmunity_by_name(char req_community[]);
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
void delete_lines(int n);
void display_comments_obo(COMMENT *c, int level);
void display_options();
void display_post_obo(POST *p);
//! Don't use this function unless you want to reset all the users and communities
void create_initial_files();
//!______________________________________________________________________________//

// TODO: sort as - top, new, best

//***** Operations *****
int score(int upvotes, int downvotes);
double controversy(int upvotes, int downvotes);
double confidence(int upvotes, int downvotes);
double hot(int upvotes, int downvotes, unsigned long long t);

//* Quick Sort - Functions
void swap_posts(int i, int j);
void post_sort_top(POST *p);
void post_sort_best(POST *p);
void post_sort_hot(POST *p);
void post_sort_controversial(POST *p);
void post_sort_old(POST *p);
void post_sort_new(POST *p);
int post_partition(int low, int high, int type);
void post_quickSort(int low, int high, int type);

//* Merge Sort - Functions
void display_post_by_id();
int number_of_comments(COMMENT *p);
void _comment_mergeSort_top(int l, int r);
void _comment_mergeSort_best(int l, int r);
void _comment_mergeSort_controversial(int l, int r);
void _comment_mergeSort_old(int l, int r);
void _comment_mergeSort_new(int l, int r);
void _comment_mergeSort_hot(int l, int r);
void comment_merge(int l, int m, int r, int type);
void comment_mergeSort_top(COMMENT *p);
void comment_mergeSort_best(COMMENT *p);
void comment_mergeSort_controversial(COMMENT *p);
void comment_mergeSort_old(COMMENT *p);
void comment_mergeSort_new(COMMENT *p);
void comment_mergeSort_hot(COMMENT *p);

int rabinKarp(char pattern[MAX_SIZE_CONTENT], char text[MAX_SIZE_CONTENT], int q);
void print_sorted_posts();
void print_sorted_comments();
int bruteforce_substring_search(char text[], char pattern[]);
void search_users(char req_username[]);
void print_user_result();
void print_post_result();
void search_posts(char req_pattern[]);
void insertion_sort_posts();
void print_all_communities_precise();
void user_sort_karma();
void user_sort_followers();
void display_search_menu();
void print_community_post_result();
void display_post_options(POST *temp_post);
COMMUNITY_HOLDER *community_return(char req_community[MAX_SIZE_CONTENT]);
void display_community_options(COMMUNITY_HOLDER *temp_comm);
//**********************
#endif