/*****************************************************************************
 *Author   : Calvin Huang
 *Licence  : None
 *File Name: p120.c
 
 *This program is created for the purpose of:
    p120 of UVa Online questions
 *It's not supposed to be shared without permission of author.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TRUE 1
#define FALSE 0
#define MCAKE 1000
#define SHOW_FLIP TRUE


#define DEBUG 0

#if DEBUG
#define DUMPINT(x) printf("line %3d: %s = %d\n", __LINE__, #x, x)
#else
#define DUMPINT(x)
#endif


typedef struct my_queue {
    int hcake;
    int tcake;
    int cakes[MCAKE];
} my_queue_t;

typedef struct my_stack {
    int ncake;
    int cakes[MCAKE];
} my_stack_t;

int read_one_data(my_stack_t *s) {
    int a = 0,
        i = 0;
    char end;
    while ((a = scanf("%d%c", s->cakes+i, &end)) > 0) {
        i++;
        if (end == '\n') {
            break;
        }
    }
    s->ncake = i;
    return a;
}


void print_stack(my_stack_t *s) {
    int i = 0;
    for (i = 0; i < s->ncake; i++) {
        printf("%d ", s->cakes[i]);
    }
    printf("\n");
}

int find_max(int *ary, int lo, int hi) {
    int i = lo + 1,
        ind = lo;
    for (i = lo + 1; i < hi; i++) {
        if (ary[i] > ary[ind]) {
            ind = i;
        }
    }
    return ind;
}

void flip(int k, my_stack_t *s, my_queue_t *q, int show) {
    q->hcake = 0;
    q->tcake = 0;

    while (s->ncake >= k) {
        q->cakes[q->tcake] = s->cakes[s->ncake-1];
        q->tcake++;
        s->ncake--;
    }
    while (q->tcake > q->hcake) {
        s->cakes[s->ncake] = q->cakes[q->hcake];
        s->ncake++;
        q->hcake++;
    }
    if (show) {
        printf("%d ", k);
    }
}

void sort_stack(my_stack_t *s) {
    int ind = 0,
        k = 0;
    my_queue_t q;
    flip(1, s, &q, 0);
    while (ind <= s->ncake - 1) {
        k = find_max(s->cakes, ind, s->ncake) + 1;
        DUMPINT(k);
        DUMPINT(s->cakes[k-1]);
        if (k-1 != ind) {
            DUMPINT(k);
            DUMPINT(s->ncake);
            DUMPINT(ind);
            if (k != s->ncake) {
                flip(k, s, &q, SHOW_FLIP);
                flip(ind+1, s, &q, SHOW_FLIP);
            } else {
                flip(ind+1, s, &q, SHOW_FLIP);
            }
        }
        ind++;
    }
}


int
main(int argc, char *argv[]) {
    my_stack_t s;
    int res;
    while ((res =read_one_data(&s)) != -1) {
        print_stack(&s);
        sort_stack(&s);
        printf("0\n");
        /*print_stack(&s);*/
    }
    return 0;
}