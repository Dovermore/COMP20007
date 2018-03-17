/*
WARNING::::::

    THIS IS A REALLY BAD PROGRAM THROUGH OUT.
    WITH BAD STALYING BAD COMMENT AND BAD THOUGHT BEFORE IMPLEMENTING
    PLEASE DO NOT EVER WRITE ANY TYPE OF PROGRAM STRUCTURED LIKE THIS AND
    SWEAR TO WHOMEVER WROTE THOSE TYPE OF PROGRAMS!

 */





/*****************************************************************************
 *Author   : Calvin Huang
 *Licence  : None
 *File Name: p10037.c
 
 *This program is created for the purpose of:
    problem p10037 in UVa question (Bridge)
 *It's not supposed to be shared without permission of author.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#define DEBUG 0

#if DEBUG
#define DUMPINT(x) printf("line %3d: %s = %d\n", __LINE__, #x, x)
#else
#define DUMPINT(x)
#endif

#define TRUE 1
#define FALSE 0

typedef struct data {
    int nfrom;
    int from[1001];
    int process[6006];
    int nprocess;
} DATA;


int comfunc(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}


void read_one_case(DATA *d) {
    int i = 0;
    scanf("%d", &(d->nfrom));
    for (i=0; i < d->nfrom; i++) {
        scanf("%d", d->from+i);
    }
    d->nprocess = 0;
    qsort(d->from, d->nfrom, sizeof(int), comfunc);
    for (i = 0; i < d->nfrom; i++) {
        DUMPINT(d->from[i]);
    }
}

/*
int move(DATA* d, int forward, int ind) {
    if (forward) {
        d->to[d->nto] = d->from[ind];
        d->nto++;
        d->from[ind] = d->from[d->nfrom-1];
    } else {
        d->from[d->nto] = d->to[ind];
        d->nfrom++;
        d->to[ind] = d->to[d->nto-1];
    }
    return forward ? d->to[d->nto-1] : d->from[d->nfrom-1];
}
*/

int make_moveNupdate(DATA* d, int *t) {
    int t1,
        t2,
        tmax = d->from[d->nfrom-1],
        tmax2= d->from[d->nfrom-2],
        tmin = d->from[0],
        tmin2 = d->from[1];
    DUMPINT(d->nfrom);
    if (d->nfrom > 3/* 4 */) {
        t1 = tmax + tmax2 + 2 * tmin;
        t2 = tmax + 2 * tmin2 + tmin;
        DUMPINT(t1);
        DUMPINT(t2);
        if (t1 < t2) {
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-1];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-2];
            d->process[d->nprocess++] = d->from[0];
            *t += t1;
        } else {
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[1];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-1];
            d->process[d->nprocess++] = d->from[d->nfrom-2];
            d->process[d->nprocess++] = d->from[1];
            *t += t2;
        }
        d->nfrom -= 2;
        return 1;
    } else if (d->nfrom == 2) {
        d->process[d->nprocess++] = d->from[0];
        d->process[d->nprocess++] = d->from[1];
        *t += tmin2;
        return 0;
    } else if (d->nfrom == 3) {
        d->process[d->nprocess++] = d->from[0];
        d->process[d->nprocess++] = d->from[2];
        d->process[d->nprocess++] = d->from[0];
        d->process[d->nprocess++] = d->from[0];
        d->process[d->nprocess++] = d->from[1];
        *t += (tmin + tmin2 + tmax);
        return 0;
    }/* else if (d->nfrom == 4) {
        DUMPINT(tmin);
        DUMPINT(tmin2);
        DUMPINT(tmax);
        DUMPINT(tmax2);
        t1 = 2 * tmin + tmin2 + tmax + tmax2;
        t2 = tmin + 3 * tmin2 + tmax;
        DUMPINT(t1);
        DUMPINT(t2);
        if (t1 < t2) {
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-1];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-2];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[1]; 
            *t += t1;
        } else {
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[1];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[d->nfrom-1];
            d->process[d->nprocess++] = d->from[d->nfrom-2];
            d->process[d->nprocess++] = d->from[1];
            d->process[d->nprocess++] = d->from[0];
            d->process[d->nprocess++] = d->from[1];
            *t += t2;
        }
        return 0;
    } */else {
        d->process[d->nprocess++] = d->from[0];
        *t += tmin;
        return 0;
    }
}

void calc_and_print(DATA *d) {
    int res = 0,
        t   = 0,
        i   = 0;
    while ((res = make_moveNupdate(d, &t)) != 0) {
        /* pass */
    }
    printf("%d\n", t);
    for (i = 0; i < d->nprocess; i++) {
        if (i%3 == 0 && i != d->nprocess - 1) {
            printf("%d ", d->process[i]);
        } else if (i%3 == 1) {
            printf("%d\n", d->process[i]);
        } else {
            printf("%d\n", d->process[i]);
        }
    }
}





int
main(int argc, char *argv[]) {
    int i = 0,
        n;
    scanf("%d", &n);
    DATA* d = (DATA*)malloc(sizeof(DATA));
    for (i=0; i<n; i++) {
        read_one_case(d);
        calc_and_print(d);
        if (i!=n-1) {
            printf("\n");
        }
    }
    return 0;
}