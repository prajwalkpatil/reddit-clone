#include "reddit.h"
/**
Function Name: get_date
Input Params:int n, int *year, int *month, int *day
Return Type:void
Description: calculates year,day,month
**/
void get_date(int n, int *year, int *month, int *day)
{
    *year = n / 10000;
    *day = n % 100;
    *month = n / 100;
    *month = *month % 100;
}
/**
Function Name:get_date_time
Input Params:long long n, int *year, int *month, int *day, int *hr, int *min
Return Type:void
Description: calculates date along with minutes and hour
**/
void get_date_time(long long n, int *year, int *month, int *day, int *hr, int *min)
{
    get_date(n / 10000, year, month, day);
    *min = n % 100;
    *hr = n / 100;
    *hr = *hr % 100;
}
/**
Function Name:print_date
Input Params: int n
Return Type:void
Description: prints day,month,year
**/
void print_date(int n)
{
    int year;
    int month;
    int day;
    year = n / 10000;
    day = n % 100;
    month = n / 100;
    month = month % 100;
    printf(" %d/%d/%d ", day, month, year);
}
/**
Function Name:print_date_time
Input Params: unsigned long long n
Return Type:void
Description:prints day,month,year,hours,minutes and seconds
**/
void print_date_time(unsigned long long n)
{
    // 20220105155722
    int year;
    int month;
    int day;
    int hr;
    int min;
    int sec;
    get_date(n / 1000000, &year, &month, &day);
    n = n % 1000000;
    hr = n / 10000;
    n = n % 10000;
    min = n / 100;
    n = n % 100;
    sec = n;
    printf(" %d/%d/%d %d:%d:%d ", day, month, year, hr, min, sec);
}
/**
Function Name:print_error
Input Params: char str[1000]
Return Type:void
Description: printing error messeges using colors
**/
void print_error(char str[1000])
{
    printf("\033[1;31m");
    printf("\n%s\n", str);
    printf("\033[0m");
}
/**
Function Name:print_success
Input Params: char str[1000]
Return Type:void
Description: printing success messeges using colors
**/
void print_success(char str[1000])
{
    printf("\033[1;32m");
    printf("\n%s\n", str);
    printf("\033[0m");
}
/**
Function Name:screen_reset
Input Params: NIL
Return Type:void
Description: resets screen
**/
void screen_reset()
{
    printf("\e[1;1H\e[2J");
}
/**
Function Name:read_ucs
Input Params: NIL
Return Type:void
Description: reads usercount form the file
**/
void read_ucs()
{
    FILE *fp = fopen("files/auth/ucs.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fscanf(fp, "%d", &user_count_start);
    fclose(fp);
}
/**
Function Name:update_ucs
Input Params: NIL
Return Type:void
Description: updates usercount and written in the file
**/
void update_ucs()
{
    FILE *fp = fopen("files/auth/ucs.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return;
    }
    fprintf(fp, "%d", user_count_start);
    fclose(fp);
}
/**
Function Name:timeout
Input Params: int seconds
Return Type:int
Description: returns 1 after specific time
**/
int timeout(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }
    return 1;
}
/**
Function Name:init_users
Input Params: NIL
Return Type:void
Description: reads user data from file and inserts to the Linked list
**/
void init_users()
{
    FILE *fp = fopen("files/auth/users.rdt", "r");
    if (fp == NULL)
    {
        print_error("File empty!");
        return;
    }
    while (!feof(fp))
    {
        USER *u = (USER *)malloc(sizeof(USER));
        if (u == NULL)
        {
            print_error("Heap is full");
            return;
        }
        fscanf(fp, "%d\t", &u->id);
        fscanf(fp, "%s\t", u->username);
        fscanf(fp, "%s\t", u->name);
        fscanf(fp, "%d\t", &u->karma);
        fscanf(fp, "%d\t", &u->followers);
        fscanf(fp, "%d\t", &u->date_of_joining);
        fscanf(fp, "%s\t", u->email);
        all_users = insert_user_at_end(all_users, u);
    }
    fclose(fp);
}
/**
Function Name:insert_user_at_end
Input Params: USER_HOLDER *hdr, USER *u
Return Type:USER_HOLDER *
Description: function to insert the user data to a linked list
**/
USER_HOLDER *insert_user_at_end(USER_HOLDER *hdr, USER *u)
{
    USER_HOLDER *n = (USER_HOLDER *)malloc(sizeof(USER_HOLDER));
    if (n == NULL)
    {
        print_error("The Heap is full!");
        return hdr;
    }
    n->next = NULL;
    n->user_content = u;
    if (hdr == NULL)
    {
        hdr = n;
        return hdr;
    }
    USER_HOLDER *temp = hdr;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = n;
    return hdr;
}
/**
Function Name:print_all_users
Input Params: NIL
Return Type:void
Description:prints all the data of users loaded to the Linked list from the file
**/
void print_all_users()
{
    if (all_users == NULL)
    {
        print_error("No users!");
        return;
    }
    USER_HOLDER *temp = all_users;
    printf("\n>> REGISTERED USERS: \n");
    int i = 0;
    while (temp != NULL)
    {
        printf("%s\n", temp->user_content->username);
        temp = temp->next;
        i++;
    }
    printf("\n%d\n", i);
}
/**
Function Name:update_users_file
Input Params: NIL
Return Type:void
Description:adds user data to the appropriate file
**/
void update_users_file()
{
    if (all_users == NULL)
    {
        print_error("No users!");
        return;
    }
    FILE *fp = fopen("files/auth/users.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    USER_HOLDER *temp = all_users;
    USER *u;
    while (temp != NULL)
    {
        u = temp->user_content;
        fprintf(fp, "%d\t", u->id);
        fprintf(fp, "%s\t", u->username);
        fprintf(fp, "%s\t", u->name);
        fprintf(fp, "%d\t", u->karma);
        fprintf(fp, "%d\t", u->followers);
        fprintf(fp, "%d\t", u->date_of_joining);
        fprintf(fp, "%s\t", u->email);
        fprintf(fp, "\n");
        temp = temp->next;
    }
    fclose(fp);
}
//! Don't use this function unless you want to reset all the users and communities
/**
Function Name:update_users_file
Input Params: NIL
Return Type:void
Description: creates all files erases all data ,gives a fresh start
**/
void create_initial_files()
{
    FILE *fp = fopen("files/auth/users.rdt", "w+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fclose(fp);

    FILE *fp1 = fopen("files/auth/ucs.rdt", "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening file.");
        return;
    }

    fclose(fp1);

    FILE *fp2 = fopen("files/auth/users.rdt", "w+");
    if (fp2 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fclose(fp2);

    FILE *fp3 = fopen("files/auth/loggedin.rdt", "w+");
    if (fp3 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fclose(fp3);

    FILE *fp4 = fopen("files/community/communities_all.rdt", "w+");
    if (fp4 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fclose(fp4);

    FILE *fp5 = fopen("files/community/community_count.rdt", "w+");
    if (fp5 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fprintf(fp5, "0");
    fclose(fp5);

    FILE *fp6 = fopen("files/posts/post_count.rdt", "w+");
    if (fp6 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fprintf(fp6, "0");
    fclose(fp6);

    FILE *fp7 = fopen("files/posts/posts_all.rdt", "w+");
    if (fp7 == NULL)
    {
        print_error("Error opening file.");
        return;
    }
    fclose(fp7);
}
/**
Function Name: file_empty_check
Input Params:char *filename
Return Type:int
Description: if file is empty return 1 else return 0
**/
int file_empty_check(char *filename)
{

    struct stat filestat;
    stat(filename, &filestat);
    if (filestat.st_size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
Function Name:  date
Input Params:char *filename
Return Type:long
Description: calculates and return date
**/
long int date()
{
    int year, month, day;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    long int date;
    date = (year * 10000) + (month * 100) + day;
    return date;
}
/**
Function Name:  date_time
Input Params:NIL
Return Type:unsigned long long int
Description: calculates and return date and time
**/
unsigned long long int date_time()
{
    int year, month, day, hour, min, sec;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    hour = tm.tm_hour;
    min = tm.tm_min;
    sec = tm.tm_sec;
    unsigned long long int date_time;
    date_time = (year * 10000000000) + (month * 100000000) + (day * 1000000) + (hour * 10000) + (min * 100) + sec;
    return date_time;
}
/**
Function Name: fgets_newline_kill
Input Params:char a[]
Return Type: void
Description:  deletes all the new lines obtained from fgets
**/
void fgets_newline_kill(char a[])
{
    size_t sl = strlen(a);

    if (sl > 0 && a[sl - 1] == '\n')
    {
        a[sl - 1] = '\0';
    }
}
/**
Function Name: init
Input Params:NIL
Return Type: void
Description: data of users ,communities,posts,comments are read from the file and inserted into tree
**/
void init()
{
    init_users();
    init_communities();
    initialize_posts();
    post_sorted = (POST **)malloc(sizeof(POST *) * MAX_NUMBER_OF_POSTS);
    if (post_sorted == NULL)
    {
        print_error("Heap is full");
        return;
    }
    comment_sorted = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    if (comment_sorted == NULL)
    {
        print_error("Heap is full");
        return;
    }
    user_search_result = (USER_RESULT **)malloc(sizeof(USER_RESULT *) * MAX_NUMBER_OF_USERS);
    if (user_search_result == NULL)
    {
        print_error("Heap is full");
        return;
    }
    post_search_result = (POST_RESULT **)malloc(sizeof(POST_RESULT *) * MAX_NUMBER_OF_POSTS);
    if (post_search_result == NULL)
    {
        print_error("Heap is full");
        return;
    }
    community_search_result = (COMMUNITY_HOLDER **)malloc(sizeof(COMMUNITY_HOLDER *) * 1000);
    if (community_search_result == NULL)
    {
        print_error("Heap is full");
        return;
    }
}
