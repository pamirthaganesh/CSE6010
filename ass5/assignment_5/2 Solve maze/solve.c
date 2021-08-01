/*
 * CSE 6010 Assignment 5
 * Created by Athulya Ram
 * Last edited on 17 October 2020
 * solve.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define USAGE_STRING "./<exe name> Generated_Maze_File.txt"
#define LINEBUF_SIZE 2048
#define SIZE 23104 //152*152 maximum possible size of the graph.
static char line_buffer[LINEBUF_SIZE];

struct LLNode {
  int vertex;
  struct LLNode* next;
};

struct LLQueue {
  int LLNode[SIZE];
  int head;
  int tail;
};

struct LLGraph {
  int numVertices;
  struct LLNode** adjLists;
  int* visited;
};

/* Functions used to solve the maze */

/*******************************************************************************************************************/
// Function used to create a Node. This dynamically allocates memory for the structure.
// Node contains a vertex and a pointer to the next node.
struct LLNode* createNode(int v) {
  struct LLNode* newNode = malloc(sizeof(struct LLNode));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

/*******************************************************************************************************************/
// Function to create a graph.
// The graph structure contains the number of vertices of the graph, its list of connected nodes as a linked list,
// and a component to store the visited nodes in the BFS algorithm.
struct LLGraph* createGraph(int vertices) {
  struct LLGraph* graph = malloc(sizeof(struct LLGraph));
  graph->numVertices = vertices;
  graph->adjLists = malloc(vertices * sizeof(struct LLNode*));
  graph->visited = malloc(vertices * sizeof(int));
  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

/*******************************************************************************************************************/
// Function to add an edge to our graph.
// Input - graph, source node, destination node.
// Creates an edge: (source, destination).
void addEdge(struct LLGraph* graph, int src, int dest) {
  struct LLNode* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;
}

/*******************************************************************************************************************/
// Function to create a queue.
// Creates a queue, return NULL if the operation fails, e.g., due to a lack of memory.
struct LLQueue* createQueue() {
  struct LLQueue* q = malloc(sizeof(struct LLQueue));
  if (q == NULL) {
        return NULL;
    }
  q->head = -1;
  q->tail = -1;
  return q;
}

/*******************************************************************************************************************/
// Function to check if the queue is empty. Returns -1 if it is empty, 0 otherwise.
int isEmpty(struct LLQueue* q) {
  if (q->tail == -1)
    return 1;
  else
    return 0;
}

/*******************************************************************************************************************/
// Function to insert elements into the queue.
// If the queue has elements than the total number of vertices due to some error, it prints an error.
void enqueue(struct LLQueue* q, int value, int size) {
  if (q->tail == size - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->head == -1)
      q->head = 0;
    q->tail++;
    q->LLNode[q->tail] = value;
  }
}

/*******************************************************************************************************************/
// Function to remove elements from queue.
// If queue is already empty, it prints an error. The function returns the deleted item.
int LLQ_delete(struct LLQueue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } else {
    item = q->LLNode[q->head];
    q->head++;
    if (q->head > q->tail) {
      //printf("Resetting queue ");
      q->head = q->tail = -1;
    }
  }
  return item;
}

/*******************************************************************************************************************/
// Function to find if a vlaue is in an array.
//Input - an array and a value.
// If the value is present in the array, returns 1. Otherwise returns 0.
int is_present(int a[], int value, int size) {
   int i;
   for (i=0; i<size; i++) {
	 if (a[i] == value) {
	    return(1);  // Value is found
	 }
   }
   return(0);  // Value is not found
}

/*******************************************************************************************************************/
// Function to find the index of a given value in an array.
// Input - an array, size of the array, and a value.
// Returns the index position where the array is found.
int FindIndex(const int a[], int size, int value ) {
    int index = 0;
    while (index<size && a[index] != value ) 
        ++index;
    return (index == size ? -1 : index );
}

/*******************************************************************************************************************/
// Function to print the path properly from the array generated from the algorithm.
void print_loop(int path[], int startVertex, int size) {
  int start_index = FindIndex(path, size, startVertex);
  for (int i=0; i<=start_index; i++) {
      printf("%d ", path[start_index-i]);
  }
  printf("\n");
}

/*******************************************************************************************************************/
// The actual function that generates the path using BFS algorithm.
// Inputs - graph, vertex at starting point, vertex at finish point, total number of vertices in the graph.
void bfs(struct LLGraph* graph, int startVertex, int endVertex, int size) {
    // First, create a queue to hold the elements
    struct LLQueue* q = createQueue();
    // Declare an array 'vertex' to store the vertices of the graph, in the order they are visited.
    int vertex[size];
    // Declare an array 'predecessor' to store the predecessors of the vertices, as produced by BFS algorithm.
    // Predecessor of vertex 'i' is stored at index 'i' of the array.
    int predecessor[size];
    // Predecessor of the starting point is defined as -1.
    predecessor[startVertex]=-1; 
    int k = 0;
    // To initialize, the starting vertex is marked as visited.
    graph->visited[startVertex] = 1;

    // Add starting vertex to the queue.
    enqueue(q, startVertex, size);

    // Implement the BFS algorithm until queue is empty.
    while (!isEmpty(q)) {
        // The current vertex is deleted from the queue.
        int currentVertex = LLQ_delete(q);
        // The recently removed vertex is stored in the array 'vertex'.
        vertex[k] = currentVertex;
        // Increment the index k, which is used to store elements in the array.
        k++;
        // This line can be uncommented to test if the BFS algorithm is working properly.
        //printf("Visited %d\n", currentVertex);

        // Get the neighbours of the current vertex.
        struct LLNode* temp = graph->adjLists[currentVertex];

        // Looping through all the neighbours
        while (temp) {
            int adjVertex = temp->vertex;
            // If the neighbour is not visited, mark it as visited and add it to the queue.
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex, size);
                // Predecessor of the neighbour is set as the current vertex (whose neighbours we're looking at).
                predecessor[adjVertex] = currentVertex;
            }
            //Proceed to the next neighbour.
            temp = temp->next;
        }
    }
    // Uncomment the following lines to print the arrays 'vertex' and 'predecessor' - for testing purposes.
    /*
    for(int loop = 0; loop < size; loop++)
        printf("%d ", vertex[loop]);
    printf("\n");
    for(int loop = 0; loop < size; loop++)
        printf("%d ", predecessor[loop]);
    printf("\n");
    */

    // Now we can construct the path from the arrays 'vertex' and 'predecessor'.
    // Define an array of size = total number of vertices
    int path[size];
    // Here, first we are looking at a path from finish point to the start point.
    // This way, we can uniquely retrace the path.
    // First element of path is the finish vertex.
    path[0] = endVertex;
    int m=1;
    // Loop until we get to the start vertex.
    while(is_present(path, startVertex, size) == 0) {
        // Predecessor of each element is added to the path backwards.
        path[m] = predecessor[path[m-1]];
        m++;
    }
    // Uncomment these lines to print the backwards path - 
    // this path will contain elements from end-vertex to start-vertex,
    // and then all the predecessors of the rest of the vertices, which we can ignore.
    /*
    for(int loop = 0; loop < size; loop++)
        printf("%d ", path[loop]);
    printf("\n");
    */

    // Use the function print_path to print the path properly.
    // This will ignore all the elements after start-vertex, and flip the path to show start -> end.
    print_loop(path, startVertex, size);
}
