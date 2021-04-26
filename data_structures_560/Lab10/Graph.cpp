#include "Graph.h"

Graph::Graph() : adjacency_matrix(nullptr), graph_size(0)
{

}

Graph::~Graph()
{
    for (int i = 0; i < graph_size; i++)
        delete [] adjacency_matrix[i];

    delete [] adjacency_matrix;
}

void Graph::buildGraph(int** graph, int size)
{
    graph_size = size;
    /* Allocate space for adjacency matrix */ 
    adjacency_matrix = new int*[size];
    for (int i = 0; i < size; i++)
        adjacency_matrix[i] = new int[size];

    /* copy input array into adjacency matrix */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adjacency_matrix[i][j] = graph[i][j];
        }
    }
}

/* Breadth First Search traversal
 * Should return two arrays:
 *      - Array 1: Tree edges of the graph
 *      - Array 2: Cross edges of the graph
*/
int*** Graph::breadthFirstSearch()
{
    int** ret[2];

}

/* Depth First Search traversal
 * Should return two arrays:
 *      - Array 1: Tree edges of the graph
 *      - Array 2: Back edges of the graph
*/
int*** Graph::depthFirstSearch()
{
    int** ret[2];
}

/* Kruskal's MST algorithm
 * Should return:
 *      - Array of edges (and the costs) denoting the MST 
*/
int** Graph::kruskal()
{

}

/* Prim's MST algorithm
 * Should return:
 *      - Array of edges (and the costs) denoting the MST 
*/
int** Graph::prim()
{

}
