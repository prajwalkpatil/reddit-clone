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
        print_error("Heap is full!");
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
    printf("*****");
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

void post_sort_hot(POST *p)
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
        post_quickSort(ps_start, ps_end, 6);
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
    6:  Hot
*/

//* Quick sort ---START

void swap_posts(int i, int j)
{
    POST *temp;
    temp = post_sorted[i];
    post_sorted[i] = post_sorted[j];
    post_sorted[j] = temp;
}

int post_partition(int lower, int upper, int type)
{
    int i = (lower - 1);
    POST *pivot = post_sorted[upper];
    int j;
    switch (type)
    {
    case 1:
        for (j = lower; j < upper; j++)
        {
            if (score(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= score(pivot->upvotes, pivot->downvotes))
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    case 2:
        for (j = lower; j < upper; j++)
        {
            if (controversy(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= controversy(pivot->upvotes, pivot->downvotes))
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    case 3:
        for (j = lower; j < upper; j++)
        {
            if (controversy(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= controversy(pivot->upvotes, pivot->downvotes))
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    case 4:
        for (j = lower; j < upper; j++)
        {
            if (post_sorted[j]->dt <= pivot->dt)
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    case 5:
        for (j = lower; j < upper; j++)
        {
            if (post_sorted[j]->dt >= pivot->dt)
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    case 6:
        for (j = lower; j < upper; j++)
        {
            if (hot(post_sorted[j]->upvotes, post_sorted[j]->downvotes, post_sorted[j]->dt) >= hot(pivot->upvotes, pivot->downvotes, pivot->dt))
            {
                i++;
                swap_posts(i, j);
            }
        }
        swap_posts(i + 1, upper);
        return (i + 1);
        break;
    }
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
//* Quick sort ---END

/*
    Comment sorting -
    1 : top
    2 : Best
    3 : Controversial
    4 : Old
    5 : New
*/

//* Merge sort ---START

int number_of_comments(COMMENT *p)
{
    if (p == NULL)
    {
        return 0;
    }
    int i = 0;
    while (p != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}

void comment_mergeSort_top(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_top(cs_start, cs_end);
}
void comment_mergeSort_best(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_best(cs_start, cs_end);
}
void comment_mergeSort_controversial(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_controversial(cs_start, cs_end);
}
void comment_mergeSort_old(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_old(cs_start, cs_end);
}

void comment_mergeSort_new(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_new(cs_start, cs_end);
}
void comment_mergeSort_hot(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    cs_start = 0;
    cs_end = -1;
    COMMENT *temp = p;
    while (temp != NULL)
    {
        comment_sorted[++cs_end] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_hot(cs_start, cs_end);
}

void _comment_mergeSort_top(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_top(l, m);
        _comment_mergeSort_top(m + 1, r);
        comment_merge(l, m, r, 1);
    }
}
void _comment_mergeSort_best(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_best(l, m);
        _comment_mergeSort_best(m + 1, r);
        comment_merge(l, m, r, 2);
    }
}
void _comment_mergeSort_controversial(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_controversial(l, m);
        _comment_mergeSort_controversial(m + 1, r);
        comment_merge(l, m, r, 3);
    }
}
void _comment_mergeSort_old(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_old(l, m);
        _comment_mergeSort_old(m + 1, r);
        comment_merge(l, m, r, 4);
    }
}
void _comment_mergeSort_new(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_new(l, m);
        _comment_mergeSort_new(m + 1, r);
        comment_merge(l, m, r, 5);
    }
}
void _comment_mergeSort_hot(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        _comment_mergeSort_hot(l, m);
        _comment_mergeSort_hot(m + 1, r);
        comment_merge(l, m, r, 5);
    }
}

void comment_merge(int l, int m, int r, int type)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    COMMENT **L = (COMMENT **)malloc(sizeof(COMMENT *) * n1);
    COMMENT **R = (COMMENT **)malloc(sizeof(COMMENT *) * n2);

    for (i = 0; i < n1; i++)
        L[i] = comment_sorted[l + i];
    for (j = 0; j < n2; j++)
        R[j] = comment_sorted[m + 1 + j];

    /*
        Comment sorting -
        1 : top
        2 : Best
        3 : Controversial
        4 : Old
        5 : New
        6:  Hot
    */
    switch (type)
    {
    case 1:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (score(L[i]->upvotes, L[i]->downvotes) >= score(R[j]->upvotes, R[j]->downvotes))
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    case 2:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (confidence(L[i]->upvotes, L[i]->downvotes) >= confidence(R[j]->upvotes, R[j]->downvotes))
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    case 3:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (controversy(L[i]->upvotes, L[i]->downvotes) >= controversy(R[j]->upvotes, R[j]->downvotes))
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    case 4:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i]->dt <= R[j]->dt)
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    case 5:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i]->dt >= R[j]->dt)
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    case 6:
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (hot(L[i]->upvotes, L[i]->downvotes, L[i]->dt) >= hot(R[j]->upvotes, R[j]->downvotes, R[j]->dt))
            {
                comment_sorted[k] = L[i];
                i++;
            }
            else
            {
                comment_sorted[k] = R[j];
                j++;
            }
            k++;
        }
        break;
    }
    while (i < n1)
    {
        comment_sorted[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        comment_sorted[k] = R[j];
        j++;
        k++;
    }
}

//* Merge sort ---END

int rabinKarp(char pattern[], char text[], int q)
{
    int m = strlen(pattern);
    int n = strlen(text);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    int z = 0;

    for (i = 0; i < m - 1; i++)
        h = (h * D) % q;

    // Calculate hash value for pattern and text
    for (i = 0; i < m; i++)
    {
        p = (D * p + pattern[i]) % q;
        t = (D * t + text[i]) % q;
    }

    // Find the match
    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                z++;
            // printf("Pattern is found at position:  %d \n", i + 1);
        }

        if (i < n - m)
        {
            t = (D * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return z;
}

void print_sorted_posts()
{
    POST *temp = (POST *)malloc(sizeof(POST));
    if (temp == NULL)
    {
        print_error("Heap is full");
        return;
    }
    if (ps_start == 0 && ps_end == -1)
    {
        print_error("Sort the posts first!");
        return;
    }
    for (int i = ps_start; i <= ps_end; i++)
    {
        temp = post_sorted[i];
        printf("\n\n");
        // printf("%d)", temp_post->id);
        yellow_black();
        printf("  r/%s  ", temp->community_name);
        reset();
        ARROW;
        blue_black();
        printf(" u/%s", temp->username);
        reset();
        printf(" posted at ");
        blue_black();
        print_date_time(temp->dt);
        reset();
        printf(" : ");
        lblue();
        printf("\n%s\n", temp->title);
        reset();
        printf("%s\n\n", temp->content);
        printf("Score: #(%4d)\n", temp->upvotes - temp->downvotes);
        print_comments(temp->child, 1);
        printf("\n");
    }
}

void print_sorted_comments()
{
    COMMENT *temp_comment = (COMMENT *)malloc(sizeof(COMMENT));
    if (temp_comment == NULL)
    {
        print_error("Heap is full");
        return;
    }
    if (cs_start == 0 && cs_end == -1)
    {
        print_error("Sort the comments first!");
        return;
    }
    for (int i = cs_start; i <= cs_end; i++)
    {
        temp_comment = comment_sorted[i];
        printf("\n(#%3d) ", temp_comment->id);
        purple_black();
        printf(" u/%s ", temp_comment->username);
        reset();
        printf(" commented at ");
        purple_black();
        print_date_time(temp_comment->dt);
        reset();
        printf(" : ");
        purple();
        printf("%s\n", temp_comment->content);
        printf(" Score(#%3d): %d\n", temp_comment->id, score(temp_comment->upvotes, temp_comment->downvotes));
        reset();
        print_comments(temp_comment->child, 2);
    }
}
