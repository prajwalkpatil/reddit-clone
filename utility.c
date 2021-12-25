#include "reddit.h"

void get_date(int n, int *year, int *month, int *day)
{
    *year = n / 10000;
    *day = n % 100;
    *month = n / 100;
    *month = *month % 100;
}

void get_date_time(long long n, int *year, int *month, int *day, int *hr, int *min)
{
    get_date(n / 10000, year, month, day);
    *min = n % 100;
    *hr = n / 100;
    *hr = *hr % 100;
}

void print_error(char str[1000])
{
    printf("\033[1;31m");
    printf("\n%s\n", str);
    printf("\033[0m");
}
void print_success(char str[1000])
{
    printf("\033[1;32m");
    printf("\n%s\n", str);
    printf("\033[0m");
}

void screen_reset()
{
    printf("\e[1;1H\e[2J");
}

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

int timeout(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
    {
    }
    return 1;
}

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
