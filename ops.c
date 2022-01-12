#include "reddit.h"

int score(int upvotes, int downvotes)
{
    return (upvotes - downvotes);
}

double controversy(int upvotes, int downvotes)
{
    if (upvotes <= 0 || downvotes <= 0)
    {
        return 0;
    }
    double magnitude = 0;
    double balance = 0;
    magnitude = upvotes + downvotes;
    if (upvotes > downvotes)
    {
        balance = (float)downvotes / upvotes;
    }
    else
    {
        balance = (float)upvotes / downvotes;
    }
    return pow(magnitude, balance);
}

double confidence(int upvotes, int downvotes)
{
    /*
    The confidence sort.
    http://www.evanmiller.org/how-not-to-sort-by-average-rating.html
    */
    float n = upvotes + downvotes;
    if (n == 0)
    {
        return 0;
    }
    double z = 1.281551565545; // 80% confidence;
    double p = (double)upvotes / n;
    double left, right, under;

    left = p + 1 / (2 * n) * z * z;
    right = z * sqrt(p * (1 - p) / n + z * z / (4 * n * n));
    under = 1 + 1 / n * z * z;

    return (double)(left - right) / under;
}

double hot(int upvotes, int downvotes, unsigned long long t)
{
    int n = upvotes - downvotes;
    return (double)(n) / t;
}

void post_sort_top(POST *p)
{
    if (p == NULL)
    {
        print_error("Heap us full!");
        return;
    }
    POST *temp = p;
    ps_start = 0;
    ps_end = -1;
    while (temp != NULL)
    {
        post_sorted[++ps_end] = temp;
        temp = temp->next;
    }
    if (!(ps_start > ps_end))
        post_quickSort(ps_start, ps_end, 1);
}

void post_sort_best(POST *p)
{
    if (p == NULL)
    {
        print_error("Heap us full!");
        return;
    }
    POST *temp = p;
    ps_start = 0;
    ps_end = -1;
    while (temp != NULL)
    {
        post_sorted[++ps_end] = temp;
        temp = temp->next;
    }
    if (!(ps_start > ps_end))
        post_quickSort(ps_start, ps_end, 2);
}

void post_sort_controversial(POST *p)
{
    if (p == NULL)
    {
        print_error("Heap us full!");
        return;
    }
    POST *temp = p;
    ps_start = 0;
    ps_end = -1;
    while (temp != NULL)
    {
        post_sorted[++ps_end] = temp;
        temp = temp->next;
    }
    if (!(ps_start > ps_end))
        post_quickSort(ps_start, ps_end, 3);
}

void post_sort_old(POST *p)
{
    if (p == NULL)
    {
        print_error("Heap us full!");
        return;
    }
    POST *temp = p;
    ps_start = 0;
    ps_end = -1;
    while (temp != NULL)
    {
        post_sorted[++ps_end] = temp;
        temp = temp->next;
    }
    if (!(ps_start > ps_end))
        post_quickSort(ps_start, ps_end, 4);
}
void post_sort_new(POST *p)
{
    if (p == NULL)
    {
        print_error("Heap us full!");
        return;
    }
    POST *temp = p;
    ps_start = 0;
    ps_end = -1;
    while (temp != NULL)
    {
        post_sorted[++ps_end] = temp;
        temp = temp->next;
    }
    if (!(ps_start > ps_end))
        post_quickSort(ps_start, ps_end, 5);
}
/*
    Post sorting -
    1 : top
    2 : Best
    3 : Controversial
    4 : Old
    5 : New
*/
int post_partition(int low, int high, int type)
{
    POST *temp_post;
    POST *pivot = post_sorted[high];
    int i = (low - 1);
    switch (type)
    {
    case 1:
        for (int j = low; j < high; j++)
        {
            if (score(post_sorted[j]->upvotes, post_sorted[j]->downvotes) <= score(pivot->upvotes, pivot->downvotes))
            {
                temp_post = post_sorted[i];
                post_sorted[i] = post_sorted[j];
                post_sorted[j] = temp_post;
                i++;
            }
        }
        break;
    case 2:
        for (int j = low; j < high; j++)
        {
            if (confidence(post_sorted[j]->upvotes, post_sorted[j]->downvotes) <= confidence(pivot->upvotes, pivot->downvotes))
            {
                temp_post = post_sorted[i];
                post_sorted[i] = post_sorted[j];
                post_sorted[j] = temp_post;
                i++;
            }
        }
        break;
    case 3:
        for (int j = low; j < high; j++)
        {
            if (controversy(post_sorted[j]->upvotes, post_sorted[j]->downvotes) <= controversy(pivot->upvotes, pivot->downvotes))
            {
                temp_post = post_sorted[i];
                post_sorted[i] = post_sorted[j];
                post_sorted[j] = temp_post;
                i++;
            }
        }
        break;
    case 4:
        for (int j = low; j < high; j++)
        {
            if (post_sorted[j]->dt <= pivot->dt)
            {
                temp_post = post_sorted[i];
                post_sorted[i] = post_sorted[j];
                post_sorted[j] = temp_post;
                i++;
            }
        }
        break;
    case 5:
        for (int j = low; j < high; j++)
        {
            if ((-1 * post_sorted[j]->dt) <= (-1 * pivot->dt))
            {
                temp_post = post_sorted[i];
                post_sorted[i] = post_sorted[j];
                post_sorted[j] = temp_post;
                i++;
            }
        }
        break;
    }
    temp_post = post_sorted[i + 1];
    post_sorted[i + 1] = post_sorted[high];
    post_sorted[high] = temp_post;
    return (i + 1);
}

void post_quickSort(int low, int high, int type)
{
    if (low < high)
    {
        int pi = post_partition(low, high, type);
        post_quickSort(low, pi - 1, type);
        post_quickSort(pi + 1, high, type);
    }
}
