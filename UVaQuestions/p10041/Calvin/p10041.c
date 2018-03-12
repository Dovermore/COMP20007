/*****************************************************************************
 *Author   : Calvin Huang
 *Licence  : None
 *File Name: p10041.c
 
 *This program is created for the purpose of:
    UVa Online question p10041
 *It's not supposed to be shared without permission of author.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



#define TRUE 1
#define FALSE 0

typedef struct loc {
    int nloc;
    int *pts;
} loc_t;

typedef struct data {
    int ncase;
    loc_t *locs;
} data_t;


void read_data(data_t* d) {
    int i = 0,
        j = 0;
    scanf("%d", &(d->ncase));
    d->locs = (loc_t*)malloc(sizeof(loc_t) * d->ncase);
    for (i = 0; i < d->ncase; i++) {
        scanf("%d", &((d->locs+i)->nloc));
        (d->locs+i)->pts = (int*)malloc(sizeof(int) * (d->locs+i)->nloc);
        for (j = 0; j < (d->locs+i)->nloc; j++) {
            scanf("%d", (d->locs+i)->pts+j);
        }
    }
}

void print_data(data_t *d) {
    int i = 0,
        j = 0;
    for (i = 0; i < d->ncase; i++) {
        for (j = 0; j < (d->locs+i)->nloc; j++) {
            printf("%d\n", *((d->locs+i)->pts+j));
        }
    }
}

/*
    It's most efficient to use find median value and compute using 
    median value. (If even number of values, use any point in between the two
    mid most value suffice)
 */

int random_selection(int lo, int hi) {
    if (hi == lo) {
        return lo;
    }
    int r = lo + rand() % (hi - lo);
    return r;
}

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition(int *ary, int val, int left, int right, int* btm, int* top) {
    int lo = left,
        hi = right,
        cur = left;
    while (cur <= hi) {
        if (ary[cur] > val) {
            swap_int(ary+cur, ary+hi);
            hi--;
        } else if (ary[cur] == val) {
            cur++;
        } else {
            swap_int(ary+lo, ary+cur);
            cur++;
            lo++;
        }
    }
    *btm = lo;
    *top = cur;
}

int top_k_selection(int *ary, int n, int k) {
    int k_lo = 0,
        k_hi = 0,
        left = 0,
        right = n - 1,
        ind = 0,
        val = 0;
    /* k is 1 based index and k_hi is 0 based index, for example,
       if k == 5, then the element with ary[k - 1] (4) must be in the range,
       since k_hi does not include the k_hi value in it, so the relation must
       be k_lo <= k - 1 <= k_hi - 1. E.g. 4 <= 5 - 1 <= 5 - 1 */
    while (!(k_lo <= k - 1 && k <= k_hi)) {
        if (k < k_lo + 1) {
            right = k_lo - 1;
        } else {
            left = k_hi;
        }
        ind = random_selection(left, right);
        val = ary[ind];
        partition(ary, val, left, right, &k_lo, &k_hi);
    }
    return ary[k - 1];
}

int find_min(loc_t *loc) {
    int i = 0,
        dist = 0,
        val = 0,
        n = loc->nloc,
        k = (loc->nloc + 1) / 2;
    val = top_k_selection(loc->pts, n, k);
    for (i = 0; i < loc->nloc; i++) {
        dist += abs(loc->pts[i] - val);
    }
    return dist;
}


int
main(int argc, char *argv[]) {
    data_t d;
    int i = 0;
    srand(time(NULL));   /* Setting the random seed for selection process */
    read_data(&d);
    for (i = 0; i < d.ncase; i++) {
        printf("%d\n", find_min(d.locs+i));
    }
    return 0;
}