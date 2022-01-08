#include "reddit.h"
/*
The Ansi escape codes let you set the color of the text-background the same way it lets you set the color of the foregrond. For example, the 8 background colors correspond to the codes:

Background Black: \u001b[40m
Background Red: \u001b[41m
Background Green: \u001b[42m
Background Yellow: \u001b[43m
Background Blue: \u001b[44m
Background Magenta: \u001b[45m
Background Cyan: \u001b[46m
Background White: \u001b[47m
With the bright versions being:

Background Bright Black: \u001b[40;1m
Background Bright Red: \u001b[41;1m
Background Bright Green: \u001b[42;1m
Background Bright Yellow: \u001b[43;1m
Background Bright Blue: \u001b[44;1m
Background Bright Magenta: \u001b[45;1m
Background Bright Cyan: \u001b[46;1m
Background Bright White: \u001b[47;1m
And reset is the same:

Reset: \u001b[0m
We can print them out and see them work
*/

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
