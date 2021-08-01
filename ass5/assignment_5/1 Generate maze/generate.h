/*
 * CSE 6010 Assignment 5
 * Created by Amirtha Ganesh Pugazhendhi
 * Last edited on 17 October 2020
 */


#ifndef ASSIGNMENT5_GENERATE_H
#define ASSIGNMENT5_GENERATE_H
// Utility functions to implement Stack Data Structures
struct Stack* createStack(unsigned capacity); // to create stact
int isFull(struct Stack* stack);// to check its full 
int isEmpty(struct Stack* stack);// to check its empty
void push(struct Stack* stack, int item);// to push a node into the stack
int pop(struct Stack* stack);//to pop the node out of the stack
int peek(struct Stack* stack);// to peek the top node from stack
// Utility functions to implement Graph Data Structures
struct AdjListNode* newAdjListNode(int dest);// to create adjaceny node
struct Graph* createGraph(int V);// to create Graph nodes
void addEdge(struct Graph* graph, int src, int dest) ;// to create Graph edges between graph nodes
void printGraph(struct Graph* graph,FILE *file) ;// to print the graph 
// Utility function for Randomized Depth first search;
int node_to_row(int N);// to convert node number to row number
int node_to_col(int N);// to convert node number to column number
int row_col_to_node( int r ,int c);// to convert  row number, column number to node number 
int check_right(int N);// to check for free node to the Right of selected node
int check_left(int N);// to check for free node to the Left of selected node
int check_up(int N);// to check for free node to the Top of selected node
int check_down(int N);// to check for free node to the Bottom of selected node
int select_node_right(int N);// to check for free node to the Right of selected node
int select_node_left(int N);// to check for free node to the Left of selected node
int select_node_up(int N);// to check for free node to the Top of selected node
int select_node_down(int N);// to check for free node to the Bottom of selected node
int select_random_node();// to randomly select the first random node
int select_random_direction();//  to randomly select the next random direction of selection
int check_possible_free_node(int selected_node);// to check whether a free node exist to proceed further
int select_nearest_random_node(int selected_node);// to select the nearest random node

// These are global extern variable with multiple file scope
extern int row;
extern int col;
extern int colmax ;
extern int STACK_MAX ; 
extern int count;
extern int maze_visted_array[152][152]; //max maze size it can generate ;

#endif //ASSIGNMENT5_GENERATE_H
