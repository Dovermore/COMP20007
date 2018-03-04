/*****************************************************************************
 *Author   : Calvin Huang
 *Licence  : None
 *File Name: 10004 bicolouring.c
 
 *This program is created for the purpose of:
    question 10004 bicolouring problem in UVa website
 *It's not supposed to be shared without permission of author.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_graph.h"



#define DEBUG1 1

#if DEBUG1
#define DUMPINT1(x) printf("line %3d: %s = %d\n", __LINE__, #x, x)
#else
#define DUMPINT1(x)
#endif



#define TRUE 1
#define FALSE 0
#define COLOUR1 1
#define COLOUR2 -1

void check_graph(graph_t *g);
int assign_check_node(graph_t *g, int x, int c);


int
main(int argc, char *argv[]) {
    graph_t *g = NULL;
    while (TRUE){
        g = read_graph(FALSE);
        if (!g->nvertices){
            break;
        }
        // printf("print graph\n");
        // print_graph(g);
        // printf("Check\n");
        check_graph(g);
        free_graph(g);
    }
    free_graph(g);
    return 0;
}

void check_graph(graph_t *g) {
    if (assign_check_node(g, 0, COLOUR1)) {
        printf("BICOLORABLE.\n");
    } else {
        printf("NOT BICOLORABLE.\n");
    }
    return;
}

int assign_check_node(graph_t *g, int x, int c) {
    nodedata_t *node = &(g->nodes[x]);
    edgenode_t *edge = g->edges[x];
    if(node->data == 0) {
        node->data = -c;
        while (edge != NULL) {
            // printf("x:%d, y=%d, c:%d\n", x, edge->y, c);
            if (assign_check_node(g, edge->y, -c) == 0) {
                return 0;
            }
            edge = edge->next;
        }
        return 1;
    } else if (node->data + c != 0) {
        return 0;
    } else {
        return 1;
    }
}