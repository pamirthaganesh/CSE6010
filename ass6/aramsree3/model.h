/*
 * CSE 6010 Assignment 6
 * Created by Athulya Ram
 * Last edited on 29 October 2020
 */

#ifndef MODEL_H
#define MODEL_H
#define	POP 500
#define nneighbor 500

// Data structure to create ringgrpah property for each villagers of village
typedef struct ringgraph ringgraph;
 
// Data structure to create a village with 500 villagers.
// (ie) each villager is a node in form ringraph structure within an array of 500 villagers
typedef struct village village;

void print_matrix(int target, int row, int col, int matrix[row][col]);
double get_random_01();
int frequency(int row, int col, int target_row, int matrix[row][col], int x);
int FindIndex(const int a[], int size, int value);
int maximum(int array[], int size);
void disconnect(double pDisconnect, int j, int neighbor, village* pv);

#endif