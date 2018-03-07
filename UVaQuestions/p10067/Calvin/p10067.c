#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXV 10000 /* maximum number of vertices */
#define MSET 100

typedef struct nodedata nodedata_t;
typedef struct info_one info_one_t;
typedef struct info_all info_all_t;


struct nodedata {
    int forbid;
    int visited;
    int step;
};


struct info_one {
    int sour;
    int dest;
    nodedata_t nodes[MAXV];
};

struct info_all {
    int n;
    info_one_t *info_ones;
};

void initialize_point(info_one_t *io);
void get_number(int ind, int* n1, int* n2, int* n3, int* n4);
int get_ind(int n1, int n2, int n3, int n4);
void read_point(info_one_t *io, int sour_dest_forbid);
void read_data(info_all_t *ia);
int click_button(int ind, int pos, int up_down);
int validation(info_one_t *cur_io, int ind, int s);
int bit_check(info_one_t *cur_io, int ind, int* queue, int *tail);
void check_data(info_one_t *cur_io);



int
main(int argc, char *argv[]) {
    int i = 0;
    info_all_t *ia = (info_all_t*)malloc(sizeof(info_all_t));
    read_data(ia);
    for (i=0;i<ia->n;i++) {
        check_data(&(ia->info_ones[i]));
    }
    free(ia);
    return 0;
}



void initialize_point(info_one_t *io) {
    int i = 0;
    for (i = 0; i < MAXV; i++) {
        io->nodes[i].forbid = 0;
        io->nodes[i].visited = 0;
        io->nodes[i].step = 0;
    }
}

void get_number(int ind, int* n1, int* n2, int* n3, int* n4) {
    *n1 = ind / 1000;
    *n2 = (ind - *n1 * 1000) / 100;
    *n3 = (ind - *n1 * 1000 - *n2 * 100) / 10;
    *n4 = (ind - *n1 * 1000 - *n2 * 100 - *n3 * 10);
}

int get_ind(int n1, int n2, int n3, int n4) {
    return 1000 * n1 + 100 * n2 + 10 * n3 + n4;
}

void read_point(info_one_t *io, int sour_dest_forbid) {
    int n1, n2, n3, n4, p;
    scanf("%d %d %d %d\n", &n1, &n2, &n3, &n4);
    p = 1000 * n1 + 100 * n2 + 10 * n3 + n4;
    if (!sour_dest_forbid) {
        io->sour = p;
        io->nodes[p].visited = 1;
    } else if (sour_dest_forbid==1) {
        io->dest = p;
    } else {
        io->nodes[p].forbid = 1;
    }
}


void read_data(info_all_t *ia) {
    int i = 0,
        j = 0,
        nforbid = 0;
    scanf("%d", &(ia->n));
    ia->info_ones = (info_one_t*)malloc(ia->n*sizeof(info_one_t));
    info_one_t *cur_info = NULL;
    for (i=0; i<ia->n; i++) {
        cur_info = &(ia->info_ones[i]);
        initialize_point(cur_info);
        read_point(cur_info, 0);
        read_point(cur_info, 1);
        scanf("%d\n", &nforbid);
        for (j=0; j<nforbid; j++) {
            read_point(cur_info, 2);
        }
    }
}

int click_button(int ind, int pos, int up_down) {
    int n1, n2, n3, n4;
    get_number(ind, &n1, &n2, &n3, &n4);
    if (pos == 0) {
        n1 = (n1 + up_down + 10) % 10;
    } else if (pos == 1) {
        n2 = (n2 + up_down + 10) % 10;
    } else if (pos == 2) {
        n3 = (n3 + up_down + 10) % 10;
    } else if (pos == 3) {
        n4 = (n4 + up_down + 10) % 10;
    }
    return get_ind(n1, n2, n3, n4);
}

int validation(info_one_t *cur_io, int ind, int s) {
    if (cur_io->nodes[ind].forbid) {
        return -2;
    }
    if (cur_io->dest == ind) {
        return s+1;
    }
    if (cur_io->nodes[ind].visited == 1) {
        return -1;
    } else {
        cur_io->nodes[ind].visited = 1;
        cur_io->nodes[ind].step = s + 1;
    }
    return 0;
}

int bit_check(info_one_t *cur_io, int ind, int* queue, int *tail) {
    int pos = 0, 
        next_ind = 0,
        res = 0,
        dir = 0,
        s   = 0;
    for (pos = 0; pos < 4; pos++) {
        for (dir = -1; dir < 2; dir+=2){
            s = cur_io->nodes[ind].step;
            next_ind = click_button(ind, pos, dir);
            if ((res = validation(cur_io, next_ind, s)) == 0) {
                queue[*tail] = next_ind;
                *tail = (*tail - 1 + MAXV) % MAXV;
            } else if (res > 0) {
                return res;
            }
        }
    }
    return -1;
}

void check_data(info_one_t *cur_io) {
    int win = -1,
        ind = 0,
        queue[MAXV],
        head= 0,
        tail=MAXV-1;
    queue[0] = cur_io->sour;
    if (cur_io->sour == cur_io->dest) {
        printf("0\n");
        return;
    }
    while (head != tail) {
        ind = queue[head];
        head = (head - 1 + MAXV) % MAXV;
        win = bit_check(cur_io, ind, queue, &tail);
        if (win != -1) {
            break;
        }
    }
    printf("%d\n", win);
}