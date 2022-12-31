// Implementation of Dijkstra's Algorithm for finding single pair shortest path in C Language

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Priority queue node
typedef struct node
{
    int vertex;
    int distance;
} Node;

// Heap implementation
typedef struct heap
{
    Node *data;
    int size;
    int capacity;
} Heap;

// Create a new heap with a given capacity
Heap *createHeap(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (Node *)malloc(capacity * sizeof(Node));
    return heap;
}

// Swap two nodes in the heap
void swap(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Check if the heap is empty
int isEmpty(Heap *heap)
{
    return heap->size == 0;
}

// Get the parent index of a given index
int parent(int i)
{
    return (i - 1) / 2;
}

// Get the left child index of a given index
int left(int i)
{
    return 2 * i + 1;
}

// Get the right child index of a given index
int right(int i)
{
    return 2 * i + 2;
}

// Extract the minimum element from the heap
Node extractMin(Heap *heap)
{
    Node min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    int i = 0;
    while (i < heap->size)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap->size && heap->data[l].distance < heap->data[i].distance)
        {
            smallest = l;
        }
        if (r < heap->size && heap->data[r].distance < heap->data[smallest].distance)
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else
        {
            break;
        }
    }
    return min;
}

// Insert a new element into the heap
void insert(Heap *heap, Node element)
{
    heap->data[heap->size] = element;
    heap->size++;
    int i = heap->size - 1;
    while (i > 0)
    {
        int p = parent(i);
        if (heap->data[p].distance > heap->data[i].distance)
        {
            swap(&heap->data[p], &heap->data[i]);
            i = p;
        }
        else
        {
            break;
        }
    }
}

// Decrease the distance of a given vertex
void decreaseDistance(Heap *heap, int vertex, int distance)
{
    int i;
    for (i = 0; i < heap->size; i++)
    {
        if (heap->data[i].vertex == vertex)
        {
            heap->data[i].distance = distance;
            break;
        }
    }
    while (i > 0)
    {
        int p = parent(i);
        if (heap->data[p].distance > heap->data[i].distance)
        {
            swap(&heap->data[p], &heap->data[i]);
            i = p;
        }
        else
        {
            break;
        }
    }
}

// Check if a given vertex is present in the heap
int isInHeap(Heap *heap, int vertex)
{
    int i;
    for (i = 0; i < heap->size; i++)
    {
        if (heap->data[i].vertex == vertex)
        {
            return 1;
        }
    }
    return 0;
}

// Dijkstra's Algorithm

void dijkstra(int graph[][MAX], int vertices, int source)
{
    int distance[vertices];
    int i;
    for (i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
    Heap *heap = createHeap(vertices);
    for (i = 0; i < vertices; i++)
    {
        Node node;
        node.vertex = i;
        node.distance = distance[i];
        insert(heap, node);
    }
    while (!isEmpty(heap))
    {
        Node min = extractMin(heap);
        int u = min.vertex;
        for (i = 0; i < vertices; i++)
        {
            if (graph[u][i] != 0)
            {
                int v = i;
                if (isInHeap(heap, v) && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    decreaseDistance(heap, v, distance[v]);
                }
            }
        }
    }
    printf("Vertex\tDistance from source %d vertex to other vertices in the graph are: ", source);
    for (i = 0; i < vertices; i++)
    {
        printf("%d\t", distance[i]);
    }
    printf("");
}

int main()
{
    int graph[MAX][MAX];
    int vertices, edges;
    printf("********** Dijastra's Algorithm for Finding Single Pair Shortest Path **********\n");
    printf("Enter the number of vertices: \n");
    scanf("%d", &vertices);
    printf("Enter the number of edges: \n");
    scanf("%d", &edges);
    int i;
    for (i = 0; i < vertices; i++)
    {
        int j;
        for (j = 0; j < vertices; j++)
        {
            graph[i][j] = 0;
        }
    }
    printf("Enter the edges in the graph: \n");
    for (i = 0; i < edges; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }
    int source;
    printf("Enter the source vertex: \n");
    scanf("%d", &source);
    dijkstra(graph, vertices, source);
    return 0;
}
