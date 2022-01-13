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
            if (score(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= score(pivot->upvotes, pivot->downvotes))
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
            if (confidence(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= confidence(pivot->upvotes, pivot->downvotes))
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
            if (controversy(post_sorted[j]->upvotes, post_sorted[j]->downvotes) >= controversy(pivot->upvotes, pivot->downvotes))
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
            if (post_sorted[j]->dt >= pivot->dt)
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
            if ((-1 * post_sorted[j]->dt) >= (-1 * pivot->dt))
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

/*
    Comment sorting -
    1 : top
    2 : Best
    3 : Controversial
    4 : Old
    5 : New
*/

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
    COMMENT *temp = p;
    while (p != NULL)
    {
        comment_sorted[i] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_top(comment_sorted, n);
}

void comment_mergeSort_best(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    COMMENT *temp = p;
    while (p != NULL)
    {
        comment_sorted[i] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_best(comment_sorted, n);
}

void comment_mergeSort_controversial(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    COMMENT *temp = p;
    while (p != NULL)
    {
        comment_sorted[i] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_controversial(comment_sorted, n);
}

void comment_mergeSort_old(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    COMMENT *temp = p;
    while (p != NULL)
    {
        comment_sorted[i] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_old(comment_sorted, n);
}

void comment_mergeSort_new(COMMENT *p)
{
    int n = number_of_comments(p);
    int i = 0;
    COMMENT *temp = p;
    while (p != NULL)
    {
        comment_sorted[i] = temp;
        temp = temp->next;
        i++;
    }
    _comment_mergeSort_new(comment_sorted, n);
}

void _comment_mergeSort_top(COMMENT **a, int n)
{
    COMMENT **b = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    COMMENT **c = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    int i, j = 0;
    if (n > 1)
    {
        for (i = 0; i < ((n / 2)); i++)
            b[i] = a[i];
        for (i = n / 2; i < n; i++)
            c[j++] = a[i];
        _comment_mergeSort_top(b, n / 2);
        _comment_mergeSort_top(c, (n - (n / 2)));
        comment_merge(b, c, a, n / 2, n - (n / 2), 1);
    }
}
void _comment_mergeSort_best(COMMENT **a, int n)
{
    COMMENT **b = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    COMMENT **c = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    int i, j = 0;
    if (n > 1)
    {
        for (i = 0; i < ((n / 2)); i++)
            b[i] = a[i];
        for (i = n / 2; i < n; i++)
            c[j++] = a[i];
        _comment_mergeSort_best(b, n / 2);
        _comment_mergeSort_best(c, (n - (n / 2)));
        comment_merge(b, c, a, n / 2, n - (n / 2), 2);
    }
}
void _comment_mergeSort_controversial(COMMENT **a, int n)
{
    COMMENT **b = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    COMMENT **c = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    int i, j = 0;
    if (n > 1)
    {
        for (i = 0; i < ((n / 2)); i++)
            b[i] = a[i];
        for (i = n / 2; i < n; i++)
            c[j++] = a[i];
        _comment_mergeSort_controversial(b, n / 2);
        _comment_mergeSort_controversial(c, (n - (n / 2)));
        comment_merge(b, c, a, n / 2, n - (n / 2), 3);
    }
}
void _comment_mergeSort_old(COMMENT **a, int n)
{
    COMMENT **b = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    COMMENT **c = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    int i, j = 0;
    if (n > 1)
    {
        for (i = 0; i < ((n / 2)); i++)
            b[i] = a[i];
        for (i = n / 2; i < n; i++)
            c[j++] = a[i];
        _comment_mergeSort_old(b, n / 2);
        _comment_mergeSort_old(c, (n - (n / 2)));
        comment_merge(b, c, a, n / 2, n - (n / 2), 4);
    }
}
void _comment_mergeSort_new(COMMENT **a, int n)
{
    COMMENT **b = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    COMMENT **c = (COMMENT **)malloc(sizeof(COMMENT *) * MAX_NUMBER_OF_COMMENTS);
    int i, j = 0;
    if (n > 1)
    {
        for (i = 0; i < ((n / 2)); i++)
            b[i] = a[i];
        for (i = n / 2; i < n; i++)
            c[j++] = a[i];
        _comment_mergeSort_new(b, n / 2);
        _comment_mergeSort_new(c, (n - (n / 2)));
        comment_merge(b, c, a, n / 2, n - (n / 2), 5);
    }
}

void comment_merge(COMMENT **b, COMMENT **c, COMMENT **a, int p, int q, int type)
{
    int i = 0, j = 0;
    int k = 0;

    switch (type)
    {
    case 1:
        while (i < p && j < q)
        {
            if (score((b[i])->upvotes, (b[i])->downvotes) >= score((c[i])->upvotes, (c[i])->downvotes))
                a[k] = b[i++];
            else
                a[k] = c[j++];
            k++;
        }
        break;
    case 2:
        while (i < p && j < q)
        {
            if ((confidence((b[i])->upvotes, (b[i])->downvotes) >= confidence((c[i])->upvotes, (c[i])->downvotes)))
                a[k] = b[i++];
            else
                a[k] = c[j++];
            k++;
        }
        break;
    case 3:
        while (i < p && j < q)
        {
            if ((controversy((b[i])->upvotes, (b[i])->downvotes) >= controversy((c[i])->upvotes, (c[i])->downvotes)))
                a[k] = b[i++];
            else
                a[k] = c[j++];
            k++;
        }
        break;
    case 4:
        while (i < p && j < q)
        {
            if ((b[i])->dt >= (c[i])->dt)
                a[k] = b[i++];
            else
                a[k] = c[j++];
            k++;
        }
        break;
    case 5:
        while (i < p && j < q)
        {
            if ((-1 * (b[i])->dt) >= (-1 * (c[i])->dt))
                a[k] = b[i++];
            else
                a[k] = c[j++];
            k++;
        }
        break;
    }
    if (i == p)
    {
        for (j; j < q; j++)
            a[k++] = c[j];
    }
    else
    {
        for (i; i < p; i++)
            a[k++] = b[i];
    }
}

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
