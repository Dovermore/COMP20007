/* Xulin Yang, 904904, time: 2018-2-28 12:31:44, description: UVA p10004
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_VERTICES 200 /* maximum number of vertices */
#define BICOLORABLE "BICOLORABLE."
#define NOT_BICOLORABLE "NOT BICOLORABLE." 
#define DIRECTED 0

#define data_t int
#define ERROR -999  /* wrong queue operation */
#define NO_ELEMENT_POSITION -1
#define NO_ELEMENT 0

#define UNCOLOURED -1
#define WHITE 0
#define BLACK 1

typedef struct queue queue_t;
typedef struct node node_t;

struct node {
    data_t data;
    node_t *next;
};

struct queue {
    node_t *front; /* queue head */
    node_t *rear; /* queue rear */
};

typedef struct edgenode edgenode_t;
typedef struct graph graph_t;

struct edgenode {
    int y; /* adjacency info */
    int weight; /* edge weight */
    edgenode_t *next; /* next edge in list */
};

struct graph {
    edgenode_t *edges[MAX_VERTICES + 1]; /* adjacency info */
    int degree[MAX_VERTICES + 1]; /* outdegree of each vertex */
    int nvertices; /* number of vertices in graph */
    int nedges; /* number of edges in graph */
    int directed; /* is the graph directed? */
};

typedef struct vertices vertices_t;

struct vertices {
    int processed[MAX_VERTICES];
    int discovered[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int colour[MAX_VERTICES];
};

void initialize_graph(graph_t *g, int directed);
void read_graph(graph_t *g, int directed);
void insert_edge(graph_t *g, int x, int y, int directed);
void free_graph(graph_t *g);

queue_t* create_queue();
void enqueue(queue_t *q, data_t item);
int is_empty(queue_t *q);
data_t dequeue(queue_t *q);

void initialize_search(graph_t *g, vertices_t *v);
int bfs(graph_t *g, vertices_t *v, int start);
void process_vertex_early(int v);
void process_vertex_late(int v);
int process_edge(int x, int y, vertices_t *v);

int complement(int colour);
int two_colour(graph_t *g);

int main(int argc, char **argv) {
    int i, nvertices = 1, nedges;
    graph_t *g = (graph_t*)malloc(sizeof(graph_t));

    read_graph(g, DIRECTED);

    return 0;
}

int two_colour(graph_t *g) {
    int i; /* counter */
    int bipartite;
    vertices_t *v = (vertices_t*)malloc(sizeof(vertices_t));

    for (i = 0; i < g->nvertices; i++) {
        v->colour[i] = UNCOLOURED;
    }

    bipartite = 1;

    
    initialize_search(g, v);

    for (i = 0; i < g->nvertices; i++) {
        if (!v->discovered[i]) {
            v->colour[i] = WHITE;
            if (!bfs(g, v, i)) {
                return 0;
            }
        }
    }

    free(v);
    v =NULL;

    return 1;
}

int complement(int colour) {
    if (colour == WHITE) {
        return BLACK;
    } else if (colour == BLACK) {
        return WHITE;
    }

    return UNCOLOURED;
}

/* my_queue */

queue_t* create_queue() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    assert(q != NULL);

    q->front = NULL;
    q->rear = NULL;

    return q;
}

void enqueue(queue_t *q, data_t item) {
    node_t *tmp = (node_t*)malloc(sizeof(node_t));
    assert(tmp != NULL);

    
    tmp->data = item;
    tmp->next = NULL;

    
    if (q->front == NULL) {
        q->front = tmp;
    }
    if (q->rear == NULL) {
        q->rear = tmp;
    } else {
        q->rear->next = tmp;
        q->rear = tmp;
    }

    return;
}

int is_empty(queue_t *q) {
    return (q->front == NULL);
}

data_t dequeue(queue_t *q) {
    if (is_empty(q)) {
        return ERROR;
    }

    node_t *tmp = q->front;
    data_t item;
    
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
    }

    item = tmp->data;
    free(tmp);
    tmp = NULL;

    return item;
}

/* my_bfs */

void initialize_search(graph_t *g, vertices_t *v) {
    int i; /* counter */

    for (i = 0; i < g->nvertices; i++) {
        v->processed[i] = v->discovered[i] = 0;
        v->parent[i] = -1;
    }

    return;
}

int bfs(graph_t *g, vertices_t *v, int start) {
    queue_t *q = create_queue(); /* queue of vertices to visit */
    int cur_v; /* current vertex */
    int y; /* successor vertex */
    edgenode_t *p;

    enqueue(q, start);
    v->discovered[start] = 1;

    
    while (!is_empty(q)) {
        cur_v = dequeue(q);

        process_vertex_early(cur_v);

        v->processed[cur_v] = 1;
        p = g->edges[cur_v];

        while (p != NULL) {
            y = p->y;
            if ((!v->processed[y]) || (g->directed)) {
                if (!process_edge(cur_v, y, v)) {
                    return 0;
                }
            }

            if (!v->discovered[y]) {
                enqueue(q, y);
                v->discovered[y] = 1;
                v->parent[y] = cur_v;
            }

            p = p->next;
        }

        process_vertex_late(cur_v);
    }

    free(q);
    q = NULL;

    return 1;
}

void process_vertex_early(int v) {
    return;
}

void process_vertex_late(int v) {
    return;
}

int process_edge(int x, int y, vertices_t *v) {
    if (v->colour[x] == v->colour[y]) {
        printf("%s\n", NOT_BICOLORABLE);
        return 0;
    }

    v->colour[y] = complement(v->colour[x]);
    return 1;
}

/* my_adjacency_list */
void initialize_graph(graph_t *g, int directed) {
    int i; /* counter */

    g->nedges = 0;
    g->directed = directed;

    for (i = 0; i < MAX_VERTICES; i++) {
        g->degree[i] = 0;
        g->edges[i] = NULL;
    }

    return;
}

void read_graph(graph_t *g, int directed) {
    int i; /* counter */
    int m; /* number of edges */
    int x, y; /* vertices in edge (x, y) */
    
    while (scanf("%d", &(g->nvertices)) && g->nvertices) {
        initialize_graph(g, directed);

        scanf("%d", &m);

        for (i = 1; i <= m; i++) {
            scanf("%d %d", &x, &y);

            insert_edge(g, x, y, directed);
        }
        

        if (two_colour(g)) {
            printf("%s\n", BICOLORABLE);
        }
        
        free_graph(g);

    }

    return;
}

void insert_edge(graph_t *g, int x, int y, int directed) {
    edgenode_t *tmp; /* temp pointer */

    tmp = (edgenode_t*)malloc(sizeof(edgenode_t)); /* allocate edgenode storage */
    assert(tmp != NULL);

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



void free_graph(graph_t *g) {
    int i; /* counter */
    edgenode_t *tmp, *pre; /* temp pointer */

    for (i = 0; i < g->nvertices; i++) {
        tmp = g->edges[i];
        while(tmp != NULL) {
            pre = tmp;
            tmp = tmp->next;
            free(pre);
            pre = NULL;
        }

        g->edges[i] = NULL;
    }

    return;
}
