/*
 * CSE 6010 Assignment 5
 * Created by Amirtha Ganesh Pugazhendhi
 * Last edited on 17 October 2020
 */
// ignore some useless warnings
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h> 
#include <errno.h>
#include "generate.h"
   
     
// Representation of stack 
// A structure to represent an stack of nodes selected 
struct Stack {
	int top;
	unsigned capacity;
	int* array;
};
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}
// Stack is full when top is equal to the last index
// Function reduce the stack if it already reached its max capcity
int isFull(struct Stack* stack)
{
	return stack->top == stack->capacity - 1;
}
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
	return stack->top == -1;
}
// Function to add an item to stack. It increases top by 1
void push(struct Stack* stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
	// printf("%d pushed to stack\n", item);
}
// Function to remove an item from stack. It decreases top by 1
int pop(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}
// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}

// representation of graphs 
// A structure to represent an adjacency list node 
struct AdjListNode 
{ 
	int dest; 
	struct AdjListNode* next; 
}; 
// A structure to represent an adjacency list 
struct AdjList 
{ 
	struct AdjListNode *head; 
}; 
// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices 
// in graph) 
struct Graph 
{ 
	int V; 
	struct AdjList* array; 
}; 
// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest) 
{ 
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->next = NULL; 
	return newNode; 
} 
// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = V; 
	// Create an array of adjacency lists. Size of 
	// array will be V 
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
	// Initialize each adjacency list as empty by 
	// making head as NULL 
	int i; 
	for (i = 0; i < V; ++i) 
		graph->array[i].head = NULL; 
	return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) 
{ 
	// Add an edge from src to dest. A new node is 
	// added to the adjacency list of src. The node 
	// is added at the beginning 
	struct AdjListNode* newNode = newAdjListNode(dest); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 
	// Since graph is undirected, add an edge from 
	// dest to src also 
	newNode = newAdjListNode(src); 
	newNode->next = graph->array[dest].head; 
	graph->array[dest].head = newNode; 
} 
// A utility function to print the adjacency list 
// representation of graph 
void printGraph(struct Graph* graph,FILE *file) 
{ 
	int v; 
	for (v = 0; v < graph->V; ++v) 
	{ 
		struct AdjListNode* pCrawl = graph->array[v].head; 
		// printf("\n Adjacency list of vertex %d\n  ", v); 
		while (pCrawl) 
		{ 
			fprintf(file,"%d ", pCrawl->dest); 
			pCrawl = pCrawl->next; 
		} 
		fprintf(file,"\n"); 
	} 
} 


// Function to extract the row number from given node number
int node_to_row(int N){
  int r =0;
  r = floor(N/colmax);
  return  r;
}
// Function to extract the column number from given node number
int node_to_col(int N){
   int c =0;
   c= N%(col);  
   return  c;
}
  // Function to extract Node number from the given row number and column number 
int row_col_to_node( int r ,int c){
   int node =0;
   node = colmax*r+c;
   return node;
}

 // Funtion to check whether exist free node to the right of the selected node
 int check_right(int N){
   int r;
   int c;
    r=node_to_row(N);
    r++;
   //  printf("\n row: %d",row);
    c=node_to_col(N);
    c++;
   //  printf("\n col: %d",col);
    if(maze_visted_array[r][c+1]==0){
      //  printf(" right: %d\n",maze_visted_array[row-1+1][col+1]);
       return 0;
    }
    return 1; 
 }
 // Funtion to check whether exist free node to the left of the selected node
    int check_left(int N){
    int r;
    int c;
    r=node_to_row(N);
    r++;
   //  printf("\n row: %d",row);
    c=node_to_col(N);
    c++;;
   //  printf("\n col: %d",col);
    if(maze_visted_array[r][c-1]==0){
      //  printf("\n left: %d\n",maze_visted_array[row-1+1][col+1]);
       return 0;
    }
    return 1; 
 }
// Funtion to check whether exist free node to the top of the selected node
   int check_up(int N){
    int r;
    int c;
    r=node_to_row(N);
    r++;
   //  printf("\n row: %d",row);
    c=node_to_col(N);
    c++;
   //  printf("\n col: %d",col);
    if(maze_visted_array[r-1][c]==0){
      //  printf("\n up: %d\n",maze_visted_array[row-1+1][col+1]);
       return 0;
    }
    return 1; 
 }
// Funtion to check whether exist free node to the bottom of the selected node
   int check_down(int N){
 int r;
    int c;
    r=node_to_row(N);
    r++;
   //  printf("\n row: %d",row);
    c=node_to_col(N);
    c++;
   //  printf("\n col: %d",col);
    if(maze_visted_array[r+1][c]==0){
      //  printf("\n down: %d\n",maze_visted_array[row-1+1][col+1]);
       return 0;
    }
    return 1; 
 }
// Funtion to select the  free node to the right of the selected node as the next visiting node
 int select_node_right(int N){
   int r=0,c=0; 
   r=node_to_row(N);
   c=node_to_col(N);
   N=row_col_to_node(r, c+1);
   count--;
   r++ ; // fset
   c++ ;
   maze_visted_array[r][c+1]=1;
   return N;
 }
// Funtion to select the  free node to the left of the selected node as the next visiting node
  int select_node_left(int N){
   int r=0,c=0; 
   r=node_to_row(N);
   c=node_to_col(N);
   N=row_col_to_node(r, c-1);
   count--;
   r++ ; // fset
   c++ ;
   maze_visted_array[r][c-1]=1;
    return N;
 }
// Funtion to select the  free node to the top of the selected node as the next visiting node
 
  int select_node_up(int N){
   int r=0,c=0; 
   r=node_to_row(N);
   c=node_to_col(N);
   N=row_col_to_node(r-1, c);
   count--;
   r++ ; // fset
   c++ ;
   maze_visted_array[r-1][c]=1;   
   return N;
 }
 // Funtion to select the  free node to the bottom of the selected node as the next visiting node
  int select_node_down(int N){
   int r=0,c=0; 
   r=node_to_row(N);
   c=node_to_col(N);
   N=row_col_to_node(r+1, c);
   count--;
   r++ ; // fset
   c++ ;
   maze_visted_array[r+1][c]=1;   
   return N;
 }
// Function to select the initial first node randomly
 int select_random_node(){
 int lower = 0; int upper = row*col-1; int no_rand = 1;
 int num = (rand() % (upper - lower + 1)) + lower;
	// printf("\n random selected node: %d \n ", num);
 return num;
}
// Use current time as  
// seed for random generator 
 
// Function to randomly select the next direction to move
int select_random_direction()
{
   int lower=1;
   int upper =4;
   int count=1;
	int num = (rand() %	(upper - lower + 1)) + lower;
		// printf("\n random selected direction: %d \n ", num);
	   return num;
}
//Function to check for adjacent free node availality of selected node
int check_possible_free_node(int selected_node){
   if (check_down(selected_node)==0||check_up(selected_node)==0||check_left(selected_node)==0||check_right(selected_node)==0){
      return 1;
   }else
   {
      return 0;
   }
}
//function to randomly select an available adajcent node as next node, refered from the currenly selected node 
int select_nearest_random_node(int selected_node){
select_direction:
{
  int direction = select_random_direction();
      // printf("\n selected direction %d",direction);
      // printf("\n selected selected node %d \n",selected_node);      
   switch (direction)
   {
   case 1:
      {
         // check left
        if( check_left(selected_node)==0){
         //   printf("\n For the selected node %d , selected direction is left \n",selected_node);
           int node =select_node_left(selected_node);
         //   printf("\n New Node selected: %d\n",node);
           return  node;
        }else
        {
           goto select_direction;
        }               
      }           
   case 2:
      {
         // check right
        if( check_right(selected_node)==0){
         //   printf("\n For the selected node %d , selected direction is right \n",selected_node);
           int node =select_node_right(selected_node);
         //   printf("\n New Node selected: %d\n",node);
           return  node;
        }else
        {
           goto select_direction;
        }        
      }
   
   case 3:
      {
         // check up
        if( check_up(selected_node)==0){
         //   printf("\n For the selected node %d , selected direction is up \n",selected_node);
           int node =select_node_up(selected_node);
         //   printf("\n New Node selected: %d\n",node);
           return  node;
        }else
        {
           goto select_direction;
        }        
      }

   case 4:
      {
         // check down
        if(check_down(selected_node)==0){
         //   printf("\n For the selected node %d , selected direction is down \n",selected_node);
           int node =select_node_down(selected_node);
         //   printf("\n New Node selected: %d\n",node);
           return  node;
        }else
        {
           goto select_direction;
        }      
      }
      break;   
   }
 }
}


