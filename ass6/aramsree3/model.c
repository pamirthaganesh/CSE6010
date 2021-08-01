/*
 * CSE 6010 Assignment 6
 * Created by Athulya Ram
 * Last edited on 30 October 2020
 * model.c
 */

#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h> 
#include <errno.h>
#include <string.h>
#define	POP 500
#define nneighbor 500

/**********************************************************************************************/
/* Data structures needed for the graph - developed by Amirtha Ganesh */

// Data structure to create ringgrpah property for each villagers of village
typedef struct ringgraph{
    int node;//  name of the current node starts from 0 and goes up to 500
    int left_array[nneighbor/2+1];//right side neighbor j-1 to j-5
    int right_array[nneighbor/2+1];//right side neighbor j+1 to j+5
    int status;//susceptible
}ringgraph;
 
// Data structure to create a village with 500 villagers.
// (ie) each villager is a node in form ringraph structure within an array of 500 villagers
typedef struct village{   
   ringgraph villager[POP];//array of villager  with ringgraph structure;
}village;

/**********************************************************************************************/
/* Functions used to model the epidemic - developed by Athulya Ram  */

/**********************************************************************************************/
// Function to print a particular row of a matrix, for testing purposes
void print_matrix(int target, int row, int col, int matrix[row][col]) {
    for(int j=0;j<col;j++) {
            printf("%d    ", matrix[target][j]);
    }
    printf("\n\n");
}

/**********************************************************************************************/
// Function to get a random number in [0,1]
double get_random_01() { 
    return ((double)rand() / (double)RAND_MAX); 
}

/**********************************************************************************************/
// Function to find the number of times a value appear in a row of a matrix
int frequency(int row, int col, int target_row, int matrix[row][col], int x) { 
    int result = 0; 
    for (int i=0; i<col; i++) 
        if (x == matrix[target_row][i]) 
          result++; 
    return result; 
} 

/**********************************************************************************************/
// Function to find the index of a given value in an array.
// Input - an array, size of the array, and a value.
// Returns the index position where the array is found.
int FindIndex(const int a[], int size, int value) {
    int index = 0;
    while (index<size && a[index] != value ) 
        ++index;
    return (index == size ? -1 : index );
}

/**********************************************************************************************/
// Function to find the maximum value in an array
// Input - an array, length of the array
int maximum(int array[], int size) {
    int max = 0;
    for (int i=0; i<size; i++) {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

/**********************************************************************************************/
// Function to disconnect an edge
// Inputs: probability of disconnection, node1, node2, graph
// Disconnects the edge between node1 and node2 (both ways) by replacing the name of the node in
// left and right arrays with -1.
// In the epidemic model, only positive nodes are considered, so the nodes are effectively
// disconnected.
void disconnect(double pDisconnect, int j, int neighbor, village* pv) {
    // Person j is infected. Each of its edges should be disconnected with a probability pDisconnect.
    // Neighbour node set to -1 to denote disconnection.
    for (int k=0; k<neighbor/2; k++) {
        if (get_random_01() < pDisconnect) {// Loop through left array first
            int target_nbr = (pv->villager)[j].left_array[k]; // Number of neighbouring node we're at.
            (pv->villager)[j].left_array[k] = -1; // Edge between infected node and neighbour disconnected.
            // Now to disconnect the edge between neigbour and infected node.
            // First find if infected node is in the right or left array of target neighbour
            for (int m=0; m<neighbor/2; m++) {
                if (j == (pv->villager)[target_nbr].left_array[m]) { // If the infected node is in left array of this neighbour
                    int inf_index = FindIndex((pv->villager)[target_nbr].left_array, neighbor/2, j);
                    (pv->villager)[target_nbr].left_array[inf_index] = -1; // Edge between target neighbour and infected node disconnected
                }
                if (j == (pv->villager)[target_nbr].right_array[m]) { // If the infected node is in right array
                    int inf_index = FindIndex((pv->villager)[target_nbr].right_array, neighbor/2, j);
                    (pv->villager)[target_nbr].right_array[inf_index] = -1; // Edge between target neighbour and infected node disconnected
                }
            }
        }
        if (get_random_01() < pDisconnect) {// Loop through right array next
            int target_nbr = (pv->villager)[j].right_array[k]; // Number of neighbouring node we're at.
            (pv->villager)[j].right_array[k] = -1; // Edge between infected node and neighbour disconnected.
            // Now to disconnect the edge between neigbour and infected node.
            // First find if infected node is in the right or left array of target neighbour
            for (int m=0; m<neighbor/2; m++) {
                if (j == (pv->villager)[target_nbr].left_array[m]) { // If the infected node is in left array
                    int inf_index = FindIndex((pv->villager)[target_nbr].left_array, neighbor/2, j);
                    (pv->villager)[target_nbr].left_array[inf_index] = -1; // Edge between target neighbour and infected node disconnected
                }
                if (j == (pv->villager)[target_nbr].right_array[m]) { // If the infected node is in right array
                    int inf_index = FindIndex((pv->villager)[target_nbr].right_array, neighbor/2, j);
                    (pv->villager)[target_nbr].right_array[inf_index] = -1; // Edge between target neighbour and infected node disconnected
                }
            }
        }
    }
}
