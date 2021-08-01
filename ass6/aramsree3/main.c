// Preprocesser and Macros
#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h> 
#include <errno.h>
#include <string.h>
#include "network.h"
#include "model.h"

#define	POP 500
#define nneighbor 500

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

int main(){
    /************************* Code by Amirtha Ganesh ***********************/
    int neighbor;// defining a global variable neigbhor to change the number of neartest neighor required for each villager

    check:
    // Scanning input for choose the number of nieghbors each villagers
    printf("\n Please enter the number of nieghbors for the each villager (less than %d) \n",POP);
    scanf("%d",&neighbor);
    // Condition to check whether the number of  neigbors is even or not and make it even by adding 1 incase of odd.
    if(neighbor%2!=0){
        neighbor =neighbor+1;
    printf(" \n The number of can not be odd. Hence incremented the number of neighor by 1 and actually number of neighbor consider = %d  \n", neighbor);
    }
    // Condition to check whether the number of  neigbors is less than the total number of villagers and asking to enter a new value, till is appropriate.
    if(neighbor >500){
    printf("\n Please enter the number of nieghbors can be greater than %d, please enter the number of nieghbors for the each villager less than %d  \n",POP, POP);  
    goto check;
    }

    // Declaring the pReplaceRandom parameter.
    double pReplaceRandom= 0;
    // Scanning input for choosing the  Probability of substituting a nearest-neighbor edge with a different edgeeach villagers
    printf("\n Please enter the probability of substituting a nearest-neighbor edge with a different edge.\n");
    scanf("%lf",&pReplaceRandom);

    //  Checking if pReplaceRandom is greater than 0 and less than 1
    if(pReplaceRandom<0){
        pReplaceRandom =0;// if pReplaceRandom entered is lesser than 0 replace it as 0
        printf(" \n Probability cannot be lesser than 0, hence its considered as 0.\n");
    }else if(pReplaceRandom>1){
        pReplaceRandom =1;// if pReplaceRandom entered is greater  than 0 replace it as 1
        printf(" \n Probability cannot be greater than 1, hence its considered as 1.\n");
    }

    // Creating random seed using time function
    srand(time(0));
    // instantiating the village v
    village v;
    village* pv = &v ;// pointer to the village 'v'


    // srand(time(0));
    make_network(pv,neighbor,pReplaceRandom);
    //  make_network(pv,neighbor,0);
    //print_person(pv, neighbor);
    // printf("\n  node status %d \n", v.villager[100].left_array[1]);    


    /**************************************** Modeling *************************************/
    /*********************************** Code by Athulya Ram *******************************/
    
    int numIterations = 100; // Total number of iteration (days)
    int numAgents = POP; // Total population
    double pInfection = 0.05; // Probability of infection per contact
    double pRecovery = 0.1; // Probability of recovery

    // Enter the value for pDisconnect, the probability of disconnecting an edge once the person becomes infected.
    double pDisconnect = 0;
    // Scan the input for pDisconnect
    printf("\n Please enter the probability of disconnecting an edge once a person becomes infected.\n");
    scanf("%lf",&pDisconnect);

    //  Checking if pDisconnect is greater than 0 and less than 1
    if (pDisconnect<0) {
        pDisconnect = 0; // if pDisconnect entered is < 0 set it to 0.
        printf("\n Probability cannot be lesser than 0, pDisconnect set to 0.\n");
    }
    else if (pDisconnect>1) {
        pDisconnect = 1; // if pDisconnect entered is > 0 set it to 1.
        printf("\n Probability cannot be greater than 1, pDisconnect set to 1.\n");
    }

    // 10 iterations for every set of parameters
    for (int realizations=0; realizations<10; realizations++) {
        // Define a matrix A(t, N) (t=numIterations, N = numAgents).
        int Agents[numIterations+1][numAgents];
        // Initially set all elemets to 0. Susceptible individuals are flagged as 0.
        memset(Agents, 0, sizeof(Agents));
        // Tester to make sure the matrix is updated properly
        //print_matrix(0, numIterations, numAgents, Agents);

        // Initialize counter arrays to store the total number of susceptible, infected, and recovered people in each iteration
        int S_counter[numIterations+1]; // Susceptible
        int I_counter[numIterations+1]; // Infected
        int R_counter[numIterations+1]; // Recovered

        // Initially, a random person is infected.
        int random_inf = rand() % 500; // Function gives a random number between 0 and 499.
        Agents[0][random_inf] = 1; // Infected individuals are flagged as 1.
        //print_matrix(0, numIterations, numAgents, Agents); // Uncomment to test proper working.
        // Spread of disease per individual across time
        for (int i=0; i<numIterations; i++) {
            // Copy the left and right neighbour arrays for one iteration, as this should not be changed.
            // Now changing the state of each individual
            for (int j=0; j<POP; j++) {
                // Disconnect neighbours according to the probability pDisconnect, if the node has become
                // infected in the previous iteration
                
                if (pDisconnect != 0) { // If pDisconnect=0, we don't have to go through this process.
                    if (i==1) { // For the 1st iteration, this applies to the initial infected individual
                        if (Agents[i-1][j] == 1) // If the person was initially infected
                            disconnect(pDisconnect, j, neighbor, pv); // Disconnect w.r.t probability
                    }
                    else if (i>1) { // For later iterations, we need to know if the status switched from S to I in the previous iteration.
                        if (Agents[i-1][j] == 1 && Agents[i-2][j] == 0)
                            disconnect(pDisconnect, j, neighbor, pv); // Disconnect w.r.t probability
                    }
                }

                // To find the current number of infected neighbours of j
                // If a neighbour is disconnected, then the neighbour will appear as '-1' in left/right array.
                // So disconnected neighbours are not counted here.
                int i_curr = 0;
                for (int k=0; k<neighbor/2; k++) {
                    if ((pv->villager)[j].left_array[k]>0) { // making sure disconnected neighbours are not counted
                        if (Agents[i][(pv->villager)[j].left_array[k]] == 1)
                            i_curr += 1; // increment the value of i_curr if an infected neighbour is found.
                    }
                    if ((pv->villager)[j].right_array[k]>0) { // making sure disconnected neighbours are not counted
                        if (Agents[i][(pv->villager)[j].right_array[k]] == 1)
                            i_curr += 1; // increment the value of i_curr if an infected neighbour is found.
                    }
                }
                // pInfection is per contact.
                // So the total infection rate = pInfection * total number of infected contacts
                double inf_rate = i_curr*pInfection;
                // When an individual is susceptible
                if (Agents[i][j] == 0) {
                    // There is a probability of inf_rate that the person gets infected.
                    // If the person has no infected neighbours, inf_rate is just zero.
                    // So this essentially affects only people who have infected neighbours.
                    if (get_random_01() <= inf_rate)
                        Agents[i+1][j] = 1; // flag the person as infected
                    else
                        Agents[i+1][j] = 0; // flag the person as susceptible for the next iteration
                }
                // When an individual is infected
                else if (Agents[i][j] == 1) {
                    // There is a probability of pRecovery that the person recovers.
                    if (get_random_01() <= pRecovery)
                        Agents[i+1][j] = 2; // flag the person as recovered
                    else
                        Agents[i+1][j] = 1; // flag the person as infected for the next iteration
                }
                // If not S or I, the person is already recovered
                else    
                    Agents[i+1][j] = 2; // flag the person as recovered for the next iteration
            }
            // Once we are done with all the individuals in an iteration, count the numbers
            S_counter[i] = frequency(numIterations, numAgents, i, Agents, 0);
            I_counter[i] = frequency(numIterations, numAgents, i, Agents, 1);
            R_counter[i] = frequency(numIterations, numAgents, i, Agents, 2);
            // Uncomment to print values in each iteration, for testing purposes
            //printf("S = %d, I = %d, R = %d ///", S_counter[i], I_counter[i], R_counter[i]);
            //printf(" Iteration %d done\n", i);
        }
    // Uncomment to see the network for testing purposes.
    //print_person(pv,neighbor);
    printf("...............Realization %d...............\n", realizations+1);
    printf("Maximum number of infected individuals in a single iteration is %d. \n", maximum(I_counter, numIterations+1));
    printf("This happens at iteration number %d.\n", FindIndex(I_counter, numIterations+1, maximum(I_counter, numIterations+1)));
    printf("The sum of the number of currently infected and recovered individuals after the last iteration = %d.\n", I_counter[numIterations-1]+R_counter[numIterations-1]);
    }

    return 0;
}