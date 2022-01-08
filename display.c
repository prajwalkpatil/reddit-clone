#include "reddit.h"

void d_red_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[41;30m %s \033[m", a);
}

void d_yellow_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[43;30m %s \033[m", a);
}

void d_green_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[42;30m %s \033[m", a);
}

void d_blue_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[44;30m %s \033[m", a);
}

void d_purple_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[45;30m %s \033[m", a);
}

void d_lblue_black(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[46;30m %s \033[m", a);
}

void d_blue(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[34m %s \033[m", a);
}

void d_red(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[31m %s \033[m", a);
}

void d_yellow(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[33m %s \033[m", a);
}

void d_lblue(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[36m %s \033[m", a);
}

void d_purple(char a[MAX_DISPLAY_SIZE])
{
    printf("\033[35m %s \033[m", a);
}

void red_black()
{
    printf("\033[41;30m");
}

void yellow_black()
{
    printf("\033[43;30m");
}

void green_black()
{
    printf("\033[42;30m");
}

void blue_black()
{
    printf("\033[44;30m");
}

void purple_black()
{
    printf("\033[45;30m");
}

void lblue_black()
{
    printf("\033[46;30m");
}

void blue()
{
    printf("\033[34m");
}

void red()
{
    printf("\033[31m");
}

void yellow()
{
    printf("\033[33m");
}

void lblue()
{
    printf("\033[36m");
}

void purple()
{
    printf("\033[35m");
}

void reset()
{
    printf("\033[m");
}
