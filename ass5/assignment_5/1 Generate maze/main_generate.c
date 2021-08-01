/*
 * CSE 6010 Assignment 5
 * Created by Amirtha Ganesh Pugazhendhi
 * Last edited on 17 October 2020
 */

#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h> 
#include <errno.h>
#include "generate.h"

#define USAGE_STRING "USAGE:./executableName nRows nCols filename"
 

int row = 0 ;
int col = 0;
int colmax =  0;
int STACK_MAX = 0; 
int count=0;
int maze_visted_array[152][152] = {0};

 int main(int argc, char** argv){

    if(argc != 4) {
        fprintf(stderr, "%s\nYou must pass your data file as an argument to this program.\n", USAGE_STRING);
        return 1;
    }

// Declare command line input variables
// All command line inputs are read as chars (strings)
// Use atoi to convert chars to ints
row = atoi(argv[1]); // number of rows of maze graph (arg[1])
//printf("%s %d\n", "nRows:", nRows);
col = atoi(argv[2]); // number of columns of maze graph (arg[2])
colmax =col;
//printf("%s %d\n", "nCols:", nCols);
char* filename = argv[3]; // name of the textfile to which the maze information should be outputted (arg[3])
STACK_MAX= row*col; // total number of nodes in the maze graph
count=0; // global variable to store the count of the free nodes in the maze array.
 // Array to to store the node visited and set boundry for the Maze
 // Here "1" represents the node already visited and "0" represents the node which still free and unvisitied
 // boundry covering the Array is the boundry, which is also marked as "1"
//    int maze_visted_array[row+2][col+2];
  for( int i = 0; i<row+2 ; i++){
     for(int j=0; j<col+2 ; j++){
        if(i==0||i==row+1||j==0||j==col+1){
           maze_visted_array[i][j]=1;
        }
        else{
           maze_visted_array[i][j]=0;
        }
     }
  }
  // Priniting the intial Maze array.
  for( int i = 0; i<row+2 ; i++){
     for(int j =0; j<col+2 ; j++){       
         //   printf("%d\t",maze_visted_array[i][j]);
      }
   //   printf("\n");
  }
//   // Counting the unvisited or free nodes 
// int count_free_nodes(int maze_visted_array[15][col+2],int count){
//    for(int i=0; i<row+2; i++){
//       for(int j=0; j<col+2;j++){
//          if(maze_visted_array[i][j]==0){
//             count= count+1;
//          }
//       }
//    }
//    return count;
// }
 // Storing the count of the unvisited/free node in the global count variable
 count= row*col;
 
// Creating and instantiating the stack data structure
struct Stack* stack = createStack(STACK_MAX);
// Declaring the # of graph nodes
int V = row*col; 
// Creating and instantiating the Graph data structure
struct Graph* graph = createGraph(V); 
// selecting the first node of the maze randomly   
srand(time(0)); 
int selected_node = select_random_node();
int first_node = selected_node;
// pushing the currenly selected node as stack member
push(stack,selected_node);
//declaration of the index variable for accessing the visited maze array elements
int a=0,b=0; 
int poped=0;
// finding the row value for the given node 
a=node_to_row(selected_node);
// finding the row value for the given node 
b=node_to_col(selected_node);
count--;// reducing the count of unvisited array
maze_visted_array[a+1][b+1]=1;
// printf("count :%d row: %d  col %d",count, a, b);
  for( int i = 0; i<row+2 ; i++){
     for(int j=0; j<col+2 ; j++){       
         //   printf("%d\t",maze_visted_array[i][j]);       
     }
   //   printf("\n");
  }
// declaration of a variable to store the newly selected node
int new_selection_node=0;
while(count>0){
   selected_node= peek(stack);
   // printf("\nThe top  of stack :%d \n",selected_node);
   // Back-Tracking 
   if(check_possible_free_node(selected_node)==0){
      // printf("\nSelected node: %d is already visited hence removing it from stack \n",selected_node);
      poped=pop(stack);// back-tracking if new node is already visited
      // printf("\nThe poped element :%d \n",poped);      
   }else
   {// new node visiting
      new_selection_node= select_nearest_random_node(selected_node);
      // printf("new selection node : %d\n",new_selection_node);
      addEdge(graph,selected_node,new_selection_node);
      push(stack,new_selection_node);
      //   for( int i =0; i<row+2 ; i++){
      //    for(int j=0; j<col+2 ; j++){       
      //      printf("%d\t",maze_visted_array[i][j]);       
      //    }
      //    printf("\n");
      //   }
   }
 }
//   printf("\n");
 // printing and checking whether all nodes are visited in maze.
  for( int i = 0; i<row+2 ; i++){
     for(int j=0; j<col+2 ; j++){
                //   printf("%d\t",maze_visted_array[i][j]);       
     }
   //   printf("\n");
  }
  //peeking the last node from stack
   int last_node=peek(stack);
	// print the adjacency list representation of the above graph 
      // printf("%d %d\n",row,col);
      // printf("%d %d\n",first_node,last_node);
   	// printGraph(graph);  


    // ********** Print adjacency list to textfile **********
    FILE *file;
    file = fopen(filename, "w"); // write to a textfile with the name as specified in the command line input
    fprintf(file, "%d %d \n", row, col); // print number of rows and columns
    fprintf(file, "%d %d \n", first_node, last_node); // print starting node and finishing node
    printGraph(graph,file);
    fclose(file); // close file once we are done writing

 
 free(graph);
 free(stack);
 return 0;

 }