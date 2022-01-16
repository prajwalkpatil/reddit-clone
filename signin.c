#include "reddit.h"
/**
Function Name: login_user
Input Params:NIL
Return Type: void
Description: username ,pass word is taken from the user and checks if the username already exists ,if exists return failure
else accepted,password is encrypted ,all the information is written in the file
**/
int login_user()
{
    main_user_holder = (USER_HOLDER *)malloc(sizeof(USER_HOLDER));
    main_user_holder->user_content = (USER *)malloc(sizeof(USER));
    printf("\n\xB2\xB2\xB2\xB2");
    blue();
    printf("  Login  ");
    reset();
    printf("\xB2\xB2\xB2\xB2\n");
    char entered_username[31];
    char temp_char;
    char pwd[31];
    int i = 0;
    int status = 0;
    printf("Username : ");
    scanf("%s", entered_username);
    printf("Password : ");
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
    status = auth_user(entered_username, pwd);
    if (status == SUCCESS)
    {
        strcpy(main_user_holder->user_content->username, entered_username);
        // print_success("Login Successful! You will be redirected");
        timeout(2);
        screen_reset();
        is_loggedin = 1;
        return SUCCESS;
    }
    else
        return FAILURE;
}
/**
Function Name: add_username_file
Input Params:char username_r[18]
Return Type: void
Description: a file to store the information of the user is created
**/
void add_username_file(char username_r[18])
{
    FILE *fp = fopen("files/auth/loggedin.rdt", "w+");
    if (fp == NULL)
    {
        printf("Error opening file!");
        return;
    }
    fprintf(fp, "%s", username_r);
    fclose(fp);
}