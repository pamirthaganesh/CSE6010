/*
 * CSE 6010 Assignment 6
 * Created by Amirtha Ganesh Pugazhendhi
 * Last edited on 29 October 2020
 * network.c
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

// Function to  find the Euclidean modulus and return positive mod(re) value
 int euclidean_mod(int number, int divisor){
    int mod  = number%divisor;
    if(mod<0){
     mod = mod+divisor;
     return mod;
    }
    return mod;
 }
// Function to roll a die and generate a random probability between 0 and 1;
double randprob(){
        return (double)rand() / (double)RAND_MAX ;
 }   

// Function to select random node and return the randomly nodes selected
 int select_random_node(){
 int lower = 0; int upper = POP-1; 
 int num = (rand() % (upper - lower + 1)) + lower;
	// printf("\n random selected node: %d \n ", num);
 return num;
 }


// Function to check whether the selected random node  is already a neighor 
   int check_array(int select_random_node, int larray[],int rarray[], int j){
       for(int k=0; k<j;k++){
           int flag =0;
           if(larray[k]==select_random_node ||rarray[k]==select_random_node){               
               return 1;
           }
       }
       return 0;
   }

 // Function to Generate ringnetwork for the each villager in the  village 'v' 
    void make_network(village *pv, int neib, double p){
        // Selection of neighbor nodes when pReplaceRandom =0;
         if (p==0){
         for(int i=0; i<POP;i++){
                pv->villager[i].node=i;// node name
                pv->villager[i].status=0; // assigning it as a susceptible node
                // printf("\n 1) node status %d \n", (pv->villager)[0].status); 
             for (int j=0; j<neib/2;j++){
                pv->villager[i].left_array[j]=euclidean_mod((i-j-1),POP);// left side neighbors           
                pv->villager[i].right_array[j]=euclidean_mod((i+j+1),POP); // right side neighbors 
                    //  printf("\n 2) node status %d \n", (pv->villager)[0].status);              
                }
            }
            //  printf("\n  node status %d \n", (pv->villager)[0].status); 
        }
        // Selection of neighbor nodes when pReplaceRandom > 0;
        else{
            double selection_probability=0;        
            for(int i=0; i<POP;i++){
               pv->villager[i].node=i;// node name;
               pv->villager[i].status=0; // assigning it as a susceptible node
                // printf("\n 1) node status %d \n", (pv->villager)[0].status); 
                int larray[neib/2];// a temporary array to store left neighbors for node
                int rarray[neib/2];// a temporary array to store right neighbors for node
             for (int j=0; j<neib/2;j++){
                    selection_probability=randprob(); // generate random proability                   
                    if(selection_probability<1-p){ // check its less than pReplaceRandom
                     pv->villager[i].left_array[j]=euclidean_mod((i-j-1),POP); // normal neighbor allocation for left array
                     larray[j] =pv->villager[i].left_array[j];// storing them temporarily
                     }else{
                        resample_left:{
                        }
                        int random_nodeleft = select_random_node();// random left node selection                      
                        int lcheck=check_array(random_nodeleft,larray,rarray,j);// check whether the random node selected is already allocatd in left array
                       if(lcheck==1){
                           goto resample_left;
                       }
                        pv->villager[i].left_array[j]=select_random_node();// random left node aasignment  to the villager
                        larray[j] =pv->villager[i].left_array[j];
                    } 
                    selection_probability=randprob();
                    int larray[neib/2];
                    if(selection_probability<1-p){// check its less than pReplaceRandom
                    pv->villager[i].right_array[j]=euclidean_mod((i+j+1),POP); // normal neighbor allocation for left array
                    rarray[j] =pv->villager[i].right_array[j];//storing them temporarily
                    }else{
                        resample_right:{
                        }
                        int random_noderight = select_random_node();// random left node selection                          
                        int rcheck=check_array(random_noderight,larray,rarray,j);// check whether the random node selected is already allocatd in right array
                       if(rcheck==1){
                           goto resample_right;
                       }
                     pv->villager[i].right_array[j] =select_random_node();// random right node aasignment  to the villager
                     rarray[j] =pv->villager[i].right_array[j]; 
                    } 
             
                }
           
                
            }
            
        }

    }

// Function to print each villager details in the village
void print_person(village *pv,int neib){
for(int i=0; i<POP;i++){
printf("\n Node %d ",(pv->villager)[i].node);
printf("\n status %d ",(pv->villager)[i].status);
for (int j=0; j<neib/2;j++){
    printf("\n Node %d Left array %d: %d ",(pv->villager)[i].node,j,(pv->villager)[i].left_array[j]);
    printf("\n Node %d Right array %d: %d ",(pv->villager)[i].node,j,(pv->villager)[i].right_array[j]); 
}
printf("\n");
}
}