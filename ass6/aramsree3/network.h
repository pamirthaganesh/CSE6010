/*
 * CSE 6010 Assignment 6
 * Created by Athulya Ram
 * Last edited on 29 October 2020
 */

#ifndef NETWORK_H
#define NETWORK_H
#define	POP 500
#define nneighbor 500

// Data structure to create ringgrpah property for each villagers of village
typedef struct ringgraph ringgraph;
 
// Data structure to create a village with 500 villagers.
// (ie) each villager is a node in form ringraph structure within an array of 500 villagers
typedef struct village village;

int euclidean_mod(int number, int divisor);
double randprob();
int select_random_node();
int check_array(int select_random_node, int larray[],int rarray[], int j);
void make_network(village *pv, int neib, double p);
void print_person(village *pv,int neib);

#endif