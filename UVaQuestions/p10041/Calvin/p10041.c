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


/*
This function computes a random integer between [lo, hi)
 */
int random_selection(int lo, int hi) {
    if (hi == lo) {
        return lo;
    }
    int r = lo + rand() % (hi - lo);
    return r;
}


/*
Swap the value of two integers a and b
*/
void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*
The partition
ary: The array to be partitioned
val: The value selected as the axis (Not index)
left: The left most elements of array to be partitioned
right: The left most elements of array to be partitioned
btm: returning the the index to the first value equal to val after partition
top: returning the the index to the first value larger to val after partition
So [oth..., lo1, lo2, lo3...., loi, eq1, eq2, ... eqj, hi1, hi2,.... hik, oth..]
             ^                       ^                  ^             ^
             |                       |                  |             |
            left                    btm                top          right
 */
void partition(int *ary, int val, int left, int right, int* btm, int* top) {
    int lo = left,   /* Index of the first value equal to val
                        in the sorted part */
                     /* ###There is a potential bug here, since at first the
                        first element is assumed to be equal to val ###*/
        hi = right,  /* Index - 1 of the first larger value 
                        in the sorted array(i.e.this is not sorted yet)  */
        cur = left;  /* The current unsearched 
                        index(i.e. This is not sorted) */

    /* While the unsorted index is still less than the sorted part */
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



/*
Return the top_k value of an array
ary: pointer to the array
n:   length of the array (1 based)
k:   The k-th value needed (1 baesd)
 */
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