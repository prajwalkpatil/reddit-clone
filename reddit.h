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

// Global declarions
USER_HOLDER *main_user_holder = NULL;
USER_HOLDER *all_users = NULL;

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

#endif