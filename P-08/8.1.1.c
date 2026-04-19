#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct node {
    int vertex;
    struct node *next;
};
typedef struct node *GNODE;

GNODE graph[MAX] = {NULL};

int deleted[MAX] = {0};

void print(int *N);

void insertVertex(int *N) {
    int newV, numIn, numOut, src, dst, i;
    GNODE p, q;

    (*N)++;
    newV = *N;

    printf("Enter the number of edges from existing vertices to the new vertex : ");
    scanf("%d", &numIn);

    for (i = 0; i < numIn; i++) {
        printf("Enter the source vertex : ");
        scanf("%d", &src);

        if (src < 1 || src >= newV || deleted[src]) {
            printf("Invalid vertex.\n");
            continue;
        }

        q = (GNODE)malloc(sizeof(struct node));
        q->vertex = newV;
        q->next   = NULL;

        if (graph[src] == NULL) {
            graph[src] = q;
        } else {
            p = graph[src];
            while (p->next != NULL) p = p->next;
            p->next = q;
        }
    }

    printf("Enter the number of edges from the new vertex to existing vertices : ");
    scanf("%d", &numOut);

    for (i = 0; i < numOut; i++) {
        printf("Enter the destination vertex : ");
        scanf("%d", &dst);

        if (dst < 1 || dst > newV || deleted[dst]) {
            printf("Invalid vertex.\n");
            continue;
        }

        q = (GNODE)malloc(sizeof(struct node));
        q->vertex = dst;
        q->next   = NULL;

        if (graph[newV] == NULL) {
            graph[newV] = q;
        } else {
            p = graph[newV];
            while (p->next != NULL) p = p->next;
            p->next = q;
        }
    }

    printf("After inserting vertex the adjacency list is : \n");
    print(N);
}

void insertEdge(int *N) {
    int s, d;
    GNODE p, q;

    printf("Enter the source vertex of the edge : ");
    scanf("%d", &s);
    printf("Enter the destination vertex of the edge : ");
    scanf("%d", &d);

    if (s < 1 || s > *N || d < 1 || d > *N || deleted[s] || deleted[d]) {
        printf("Invalid vertex.\n");
        return;
    }

    q = (GNODE)malloc(sizeof(struct node));
    q->vertex = d;
    q->next   = NULL;

    if (graph[s] == NULL) {
        graph[s] = q;
    } else {
        p = graph[s];
        while (p->next != NULL) p = p->next;
        p->next = q;
    }

    printf("After inserting edge the adjacency list is : \n");
    print(N);
}

void deleteVertex(int *N) {
    int v, i;
    GNODE p, q, temp;

    if (*N == 0) {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter the vertex to be deleted : ");
    scanf("%d", &v);

    if (v < 1 || v > *N || deleted[v]) {
        printf("Invalid vertex.\n");
        return;
    }

    deleted[v] = 1;

    p = graph[v];
    while (p != NULL) {
        temp = p;
        p    = p->next;
        free(temp);
    }
    graph[v] = NULL;

    for (i = 1; i <= *N; i++) {
        if (i == v) continue;
        p = graph[i];
        q = NULL;
        while (p != NULL) {
            if (p->vertex == v) {
                if (q == NULL)
                    graph[i] = p->next;
                else
                    q->next = p->next;
                temp = p;
                p    = p->next;
                free(temp);
            } else {
                q = p;
                p = p->next;
            }
        }
    }

    while (*N > 0 && deleted[*N])
        (*N)--;

    printf("After deleting vertex the adjacency list is : \n");
    print(N);
}

void deleteEdge(int *N) {
    int s, d;
    GNODE p, q;

    printf("Enter the source vertex of the edge : ");
    scanf("%d", &s);
    printf("Enter the destination vertex of the edge : ");
    scanf("%d", &d);

    p = graph[s];
    q = NULL;

    while (p != NULL) {
        if (p->vertex == d) {
            if (q == NULL)
                graph[s] = p->next;
            else
                q->next = p->next;
            free(p);
            break;
        }
        q = p;
        p = p->next;
    }

    printf("After deleting edge the adjacency list is : \n");
    print(N);
}

void print(int *N) {
    GNODE p;
    int i;

    for (i = 1; i <= *N; i++) {
        if (!deleted[i] && graph[i] != NULL) {
            printf("%d=>", i);
            p = graph[i];
            while (p != NULL) {
                printf("%d\t", p->vertex);
                p = p->next;
            }
            printf("\n");
        }
    }
}
