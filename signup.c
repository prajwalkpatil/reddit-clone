#include "reddit.h"
/**
Function Name: hash448
Input Params:char *str
Return Type: char*
Description: a hash function used to generate a hash for passwords
**/
char *hash448(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    char *res = (char *)malloc(sizeof(char) * (i + 1));
    if (res == NULL)
    {
        print_error("Memory allocation error!");
        return res;
    }
    int j = 0;
    for (j = 0; j < i; j++)
    {
        res[j] = (char)(((int)str[j] + i) % 201);
    }
    res[j] = '\0';
    return res;
}
/**
Function Name: add_user
Input Params:char *u
Return Type: int
Description: details of the user is written in the appropriate files
**/
int add_user(USER *u)
{
    FILE *fp = fopen("files/auth/users.rdt", "a+");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return FAILURE;
    }
    fprintf(fp, "%d\t", u->id);
    fprintf(fp, "%s\t", u->username);
    fprintf(fp, "%s\t", u->name);
    fprintf(fp, "%d\t", u->karma);
    fprintf(fp, "%d\t", u->followers);
    fprintf(fp, "%d\t", u->date_of_joining);
    fprintf(fp, "%s\t", u->email);
    fprintf(fp, "\n");
    fclose(fp);
}
/**
Function Name:  write_pwd
Input Params:char username[8], char pwd_hash[31]
Return Type: int
Description: username and hashed password is written into the file
**/
int write_pwd(char username[8], char pwd_hash[31])
{
    FILE *fp = fopen("files/auth/pwds.rdt", "a+");
    if (fp == NULL)
    {
        print_error("Error opening file!");
        return FAILURE;
    }
    fprintf(fp, "%s %s\n", username, pwd_hash);
    fclose(fp);
    return SUCCESS;
}
/**
Function Name:  pwd_input
Input Params:char username[8], char pwd_hash[31]
Return Type: int
Description: checks if username and password already exists ,if exists return failure , else return success
**/
int pwd_input(char username[8], char pwd[31])
{
    printf("Password[1-30 chars]: ");
    char temp_char;
    char pwd_c[31];
    int i = 0;
    int status = 0;
    do
    {
        temp_char = getch();
        if (temp_char != '\b')
        {
            pwd[i] = temp_char;
            if (temp_char != '\r')
                printf("*");
            i++;
        }
        else
        {
            if (i != 0)
            {
                i--;
                printf("\b \b");
            }
            continue;
        }
    } while (pwd[i - 1] != '\r');
    pwd[i - 1] = '\0';
    i = 0;
    printf("\nConfirm Password: ");
    do
    {
        temp_char = getch();
        if (temp_char != '\b')
        {
            pwd_c[i] = temp_char;
            if (temp_char != '\r')
                printf("*");
            i++;
        }
        else
        {
            if (i != 0)
            {
                i--;
                printf("\b \b");
            }
            continue;
        }
    } while (pwd_c[i - 1] != '\r');
    pwd_c[i - 1] = '\0';
    if (!strcmp(pwd, pwd_c))
    {
        status = write_pwd(username, hash448(pwd));
        if (!status)
        {
            print_error("Failed to write!");
            return FAILURE;
        }
    }
    else
    {
        print_error("Passwords don't match!");
        return FAILURE;
    }
    return SUCCESS;
}
/**
Function Name:  email_input
Input Params:char email[64]
Return Type: int
Description: email is taken as input from the user , and written in the file
**/
int email_input(char email[64])
{
    printf("Email: ");
    scanf("%s", email);
    int i = 0;
    char temp;
    int at_count = 0;
    int period_count = 0;
    while (email[i] != '\0')
    {
        temp = email[i];
        if (temp == '@')
            at_count++;
        else if (temp == '.')
            period_count++;
        i++;
    }
    if (at_count > 0 && period_count > 0)
    {
        return SUCCESS;
    }
    else
    {
        print_error("Enter a valid email address.");
        return FAILURE;
    }
}
/**
Function Name:  check_duplicates
Input Params:char username_req[18], char email_req[64]
Return Type: int
Description: checks if username and email given as input already exists
**/
int check_duplicates(char username_req[18], char email_req[64])
{
    FILE *fp = fopen("files/auth/users.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return FAILURE;
    }
    int email_status;
    int username_status;
    int id;
    char username[18];
    char name[25];
    int karma;
    int followers;
    int date_of_joining;
    char email[64];
    while (!feof(fp))
    {
        fscanf(fp, "%d\t%s\t%s\t%d\t%d\t%d\t%s\n", &id, username, name, &karma, &followers, &date_of_joining, email);
        email_status = strcmp(email_req, email);
        username_status = strcmp(username_req, username);
        if (!username_status && !email_status)
        {
            print_error("Username and email already exists!");
            return FAILURE;
        }
        else if (!username_status)
        {
            print_error("Username already exists!");
            return FAILURE_USERNAME;
        }
        else if (!email_status)
        {
            print_error("Email already exists!");
            return FAILURE_EMAIL;
        }
    }
    fclose(fp);
    return SUCCESS;
}
/**
Function Name: user_file_name
Input Params:char user_name[25], char file_name[270]
Return Type: void
Description: creates a file for user_name of type .rdt
**/
void user_file_name(char user_name[25], char file_name[270])
{
    int i = 0;
    int k = 0;
    strcpy(file_name, "files/users/");
    i = 12;
    while (user_name[k] != '\0')
    {
        file_name[i] = user_name[k];
        i++;
        k++;
    }
    k = 0;
    while (k != 4)
    {
        file_name[i] = ".rdt"[k];
        i++;
        k++;
    }
    file_name[i] = '\0';
}
/**
Function Name: create_user_file
Input Params:char user_name[25]
Return Type: void
Description: creates a file for user_name of type .rdt and checks weather file is created
**/
void create_user_file(char user_name[25])
{
    char file_name[270];
    user_file_name(user_name, file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        return;
    }
    fclose(fp1);
}
/**
Function Name: user_community_file_name
Input Params:char user_name[25]
Return Type: void
Description: writes username in the community given the appropriate file_name
**/
void user_community_file_name(char user_name[25], char file_name[270])
{
    int i = 0;
    int k = 0;
    strcpy(file_name, "files/community/users/");
    i = 22;
    while (user_name[k] != '\0')
    {
        file_name[i] = user_name[k];
        i++;
        k++;
    }
    k = 0;
    while (k != 4)
    {
        file_name[i] = ".rdt"[k];
        i++;
        k++;
    }
    file_name[i] = '\0';
}
/**
Function Name: create_user_community_file
Input Params:char user_name[25]
Return Type: void
Description: creates file for a new community
**/
void create_user_community_file(char user_name[25])
{
    char file_name[70];
    user_community_file_name(user_name, file_name);
    FILE *fp1 = fopen(file_name, "w+");
    if (fp1 == NULL)
    {
        print_error("Error opening the file.");
        return;
    }
    fclose(fp1);
}
/**
Function Name: auth_user
Input Params:char username_r[18], char password_r[31]
Return Type: int
Description: checks if the username and password given is valid or not , if valid print the success messege else print failure messege
**/
int auth_user(char username_r[18], char password_r[31])
{
    FILE *fp = fopen("files/auth/pwds.rdt", "r");
    if (fp == NULL)
    {
        print_error("Error opening file.");
        return FAILURE;
    }
    char u_temp[18];
    char p[31];
    char p_temp[31];
    strcpy(p, hash448(password_r));
    while (!feof(fp))
    {
        fscanf(fp, "%s %s\n", u_temp, p_temp);
        if (!strcmp(u_temp, username_r))
        {
            if (!strcmp(p_temp, p))
            {
                print_success("You are logged in! soon will be redirected!");
                add_username_file(username_r);
                strcpy(main_user_holder->user_content->name, username_r);
                return SUCCESS;
            }
        }
    }
    print_error("Invalid username or password!");
    return FAILURE;
}
/**
Function Name:sign_up()
Input Params:NIL
Return Type: void
Description: takes input of username and password and email from the user and user is joined to appropriate community and all the data is written in the file
**/
void sign_up()
{
    read_ucs();
    green();
    printf("\nCreate an account on Reddit and become part of our community!\n");
    reset();
    char pwd[31];
    int status = 0;
    int status_t = 0;
    USER *u = (USER *)malloc(sizeof(USER));
    u->date_of_joining = date();
    u->id = ++user_count_start;
    if (u == NULL)
    {
        printf("Heap is full!");
        return;
    }
    printf("\n\xB2\xB2\xB2\xB2");
    green();
    printf("  Signup  ");
    reset();
    printf("\xB2\xB2\xB2\xB2\n");
    printf("Name: ");
    scanf("%s", u->name);
    getchar();
    status = 0;
    status = email_input(u->email);
    while (status == 0)
    {
        status = email_input(u->email);
    }
    getchar();
    printf("Username[3-8 chars]: ");
    scanf("%s", u->username);
    status_t = 0;
    status_t = check_duplicates(u->username, u->email);
    while (status_t == 0 || status_t == -1 || status_t == -2)
    {
        if (status_t == 0)
        {
            printf("Username[3-8 chars]: ");
            scanf("%s", u->username);
            status = 0;
            status = email_input(u->email);
            while (status == 0)
            {
                status = email_input(u->email);
            }
        }
        else if (status_t == -1)
        {
            status = 0;
            status = email_input(u->email);
            while (status == 0)
            {
                status = email_input(u->email);
            }
        }
        else if (status_t == -2)
        {
            printf("Username[3-8 chars]: ");
            scanf("%s", u->username);
        }
        status_t = check_duplicates(u->username, u->email);
    }
    getchar();

    status = 0;
    status = pwd_input(u->username, pwd);
    while (status == 0)
    {
        NEWLINE;
        status = pwd_input(u->username, pwd);
    }
    // printf("\nPass: %s", pwd);
    add_user(u);
    update_ucs();
    print_success("Account sucessfully created!..");
    print_success("You will be redirected to login page soon!");
    create_user_file(u->username);
    create_user_community_file(u->username);
    all_users = insert_user_at_end(all_users, u);
    timeout(3);
    screen_reset();
    // login_user();
}