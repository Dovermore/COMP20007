#include <stdio.h>
#include <assert.h>

#define MAXV 1000 /* maximum number of vertices */

typedef struct edgenode edgenode_t;
typedef struct graph graph_t;
typedef struct nodedata nodedata_t;

struct edgenode {
    int y; /* adjacency info */
    int weight; /* edge weight */
    edgenode_t *next; /* next edge in list */
};

struct nodedata {
    int data;
};

struct graph {

    edgenode_t *edges[MAXV]; /* adjacency info */
    nodedata_t nodes[MAXV];
    int degree[MAXV]; /* outdegree of each vertex */
    int nvertices; /* number of vertices in graph */
    int nedges; /* number of edges in graph */
    int directed; /* is the graph directed? */
};


#define DEBUG 0

#if DEBUG
#define DUMPINT(x) printf("line %3d: %s = %d\n", __LINE__, #x, x)
#else
#define DUMPINT(x)
#endif


graph_t *initialize_graph(int directed);
graph_t *read_graph(int directed);
void insert_edge(graph_t *g, int x, int y, int directed);
static edgenode_t *find_edge(edgenode_t *edge, int y);
edgenode_t *find_connection(graph_t *g, int x, int y);
int check_connection(graph_t *g, int x, int y);
void change_weight(graph_t *g, int x, int y, int w);
void print_graph(graph_t *g);
void free_graph(graph_t *g);



graph_t *initialize_graph(int directed) {
    int i; /* counter */

    graph_t *g=(graph_t*)malloc(sizeof(graph_t));
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (i = 0; i < MAXV; i++) {
        g->degree[i] = 0;
        g->edges[i] = NULL;
        g->nodes[i].data = 0;
    }

    return g;
}

graph_t *read_graph(int directed) {
    int i; /* counter */
    int m; /* number of edges */
    int x, y; /* vertices in edge (x, y) */
    
    graph_t *g = initialize_graph(directed);

    scanf("%d %d", &(g->nvertices), &m);

    DUMPINT(g->nvertices);
    DUMPINT(m);

    for (i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        DUMPINT(x);
        DUMPINT(y);
        insert_edge(g, x, y, directed);
    }

    return g;
}

void insert_edge(graph_t *g, int x, int y, int directed) {
    edgenode_t *tmp; /* temp pointer */

    tmp = (edgenode_t*)malloc(sizeof(edgenode_t)); /* allocate edgenode storage */
    assert(tmp != NULL);

    tmp->weight = NULL;
    tmp->next = g->edges[x];
    tmp->y = y;
    
    g->edges[x] = tmp; /* insert at head of list */

    g->degree[x] ++;

    if (!directed) {
        insert_edge(g, y, x, 1);
    } else {
        g->nedges ++;
    }

    return;
}

void print_graph(graph_t *g) {
    int i; /* counter */
    edgenode_t *tmp; /* temp pointer */

    for (i = 0; i < g->nvertices; i++) {
        printf("%d: ", i);
        tmp = g->edges[i];

        while(tmp != NULL) {
            // printf("\n%p\n", tmp);
            printf(" %d", tmp->y);
            tmp = tmp->next;
        }

        printf("\n");
    }

    return;
}

static edgenode_t *find_edge(edgenode_t *edge, int y) {
    assert(edge != NULL);
    while (edge != NULL && edge->y != y) {
        edge = edge->next;
    }
    return edge;
}

edgenode_t *find_connection(graph_t *g, int x, int y) {
    assert(g != NULL);
    return find_edge(g->edges[x], y);
}

int check_connection(graph_t *g, int x, int y) {
    return (find_connection(g, x, y) == NULL) ? 0 : 1;
}

void change_weight(graph_t *g, int x, int y, int w) {
    int directed = g->directed;
    assert(check_connection(g, x, y));
    edgenode_t *edge = find_connection(g, x, y);
    edge->weight = w;
    if (!directed) {
        edge = find_connection(g, y, x);
        edge->weight = w;
    }
}


void free_graph(graph_t *g){
    int i = 0;
    edgenode_t *edgenode = NULL,
               *tmp = NULL;
    for (i = 0; i < g->nvertices; i++){
        edgenode = g->edges[i];
        while (edgenode != NULL) {
            edgenode->y = 0;
            edgenode->weight = 0;
            tmp = edgenode;
            edgenode = edgenode->next;
            tmp->next = NULL;
            free(tmp);
        }
    }
    for (i = 0; i < g->nvertices; i ++){
        g->degree[i] = 0;
    }
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = 0;
    free(g);
}