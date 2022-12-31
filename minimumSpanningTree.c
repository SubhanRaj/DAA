// Implementation of Minimum Spanning Tree Algorithm in C Language
// This program uses Prim's algorithm to find the minimum spanning tree of a graph

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NUM_VERTICES 100

// Structure to represent an edge in the graph
typedef struct
{
    int source;
    int destination;
    int weight;
} Edge;

// Structure to represent a graph
typedef struct
{
    int numVertices;
    int numEdges;
    Edge *edges;
} Graph;

// Structure to represent a subset for union-find
typedef struct
{
    int parent;
    int rank;
} Subset;

// Function to create a graph with V vertices and E edges
Graph *createGraph(int numVertices, int numEdges)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    graph->edges = (Edge *)malloc(numEdges * sizeof(Edge));
    return graph;
} // end of createGraph()

// Function to find the root of the set in which element k belongs
int find(Subset *subsets, int k)
{
    // If k is not the root
    if (subsets[k].parent != k)
        // Path compression
        subsets[k].parent = find(subsets, subsets[k].parent);
    return subsets[k].parent;
} // end of find()

// Function to perform union of two subsets
void Union(Subset *subsets, int x, int y)
{
    int xRoot = find(subsets, x);
    int yRoot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xRoot].rank < subsets[yRoot].rank)
        subsets[xRoot].parent = yRoot;
    else if (subsets[xRoot].rank > subsets[yRoot].rank)
        subsets[yRoot].parent = xRoot;

    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
} // end of Union()

// Comparison function used by qsort() to sort an array of edges in ascending order of weight
int compareEdges(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight > b1->weight;
} // end of compareEdges()

// Function to find the minimum spanning tree of a graph using Prim's algorithm
void minimumSpanningTree(Graph *graph)
{
    int numVertices = graph->numVertices;
    Edge result[numVertices]; // This will store the resultant MST
    int e = 0;                // An index variable, used for result[]
    int i = 0;                // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of the graph
    qsort(graph->edges, graph->numEdges, sizeof(graph->edges[0]), compareEdges);

    // Allocate memory for creating V subsets
    Subset *subsets = (Subset *)malloc(numVertices * sizeof(Subset));

    // Create V subsets with single elements
    for (int v = 0; v < numVertices; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < numVertices - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        Edge nextEdge = graph->edges[i++];

        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.destination);

        // If including this edge does't cause cycle, include it in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
        // Else discard the nextEdge
    } // end of while

    // print the contents of result[] to display the built MST
    printf("Minimum Spanning Tree: ");
    for (i = 0; i < e; ++i)
        printf("(%d, %d) ", result[i].source, result[i].destination);
    printf("");
} // end of minimumSpanningTree()

int main()
{
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numVertices, numEdges);

    printf("Enter the edges in the format: source destination weight: \n");
    for (int i = 0; i < numEdges; i++)
    {
        scanf("%d %d %d", &graph->edges[i].source, &graph->edges[i].destination, &graph->edges[i].weight);
    }

    minimumSpanningTree(graph);

    return 0;
} // end of main()


