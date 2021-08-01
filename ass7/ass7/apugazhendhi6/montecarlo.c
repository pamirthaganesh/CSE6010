/*
 * CSE 6010 Assignment 7
 * Created by Amirtha Ganesh Pugazhendhi
 * Last edited on 16 November 2020
 * montecarlo.c
 */
// Libraries for program
#include <stdio.h> //standard input and output
#include <stdlib.h> // standard c library
#include <time.h> // c time based library
#include <omp.h>// OpenMP C parallelization library
#include <limits.h>// C limits library
#include <math.h>// C mathematical functions library
// Main function for executing the full program
int main(int argc, char const *argv[])
{
  // serial_montecarlo() is function to implement montecarlo integration with serial implementation
  // parameter 1: n_points (long integer) - total number of points (iterations) in the montecarlo integration
    double serial_montecarlo(long int n_points) 
    {
     unsigned int _tid = omp_get_thread_num();// setting the number of threads  by instantiating them
     unsigned int tid = _tid;// getting the thread id
     unsigned int _time = (unsigned int)time(0);
     unsigned int seed = rand_r(&tid);// seed based on thread id
     seed ^= _time;
     srand(time(NULL));    
    //Defining necessary variables
      double timer_start, timer_stop;// Clock start and stop time
      double yscale, area_under_curve, time_taken;   
      yscale = 5.5; // setting the yscale
      long int points;
      int count,n_threads;
    //Number of  points for iteration N0
      long int N0 = n_points;
      count=0;      
        for (int i = 0; i < 3; i++){  // for loop to scaleup by factor of 10              
            timer_start = omp_get_wtime();// starting the timer
        //for loop to calculate area_under_curve
          for(points = 0; points <N0; points++){
              double x,y, y_curve;
              x = (double)rand_r(&seed)/(double)RAND_MAX;// generating values of x using random numbers 
              y = ((double)rand_r(&seed)/(double)RAND_MAX)*yscale;// generating values of y using random numbers 
              y_curve = 2*x*exp(x*x); // ploting y values 
              if(y < y_curve){
                  count = count + 1;//counting the points under the y curve
              }               
        }  
        n_threads=omp_get_thread_num(); // getting the # of threads while implementation 
        double area_under_curve = ((double)count/(double)(N0))*yscale;// estimating the LHS based on points under the curve
        timer_stop = omp_get_wtime();//stopping the timer
        time_taken = ((double)(timer_stop - timer_start));// calculating the execution time
        //Serial Execution printing
        printf("\033[1;31m");
        printf("\n Serial implemention summary");
        printf("\033[0m");
        printf("\033[1;35m");
        printf("\n T= %f seconds, Number of threads =%d, Number points for iterations N = %ld, Orginal 'e' = %0.3f, Estimated 'e' = %0.3f\n",time_taken, n_threads, N0, exp(1), area_under_curve +1 );
        printf("\033[0m");
        count =0;// resetting the counts 
        N0 = N0*10;// Scaling up the number of points for the iteration by 10 times
        } 
     return 0;
    }
  // parallel_montecarlo() is function to implement montecarlo integration with parallelization
  // parameter 1: n_points (long integer) - total number of points (iterations) in the montecarlo integration
  // prarmeter 2: n_threads (integer) - The number thread to useds in the montecarlo integration
    double parallel_montecarlo(long int n_points, int threads) 
    {
     long int count=0;// intializing the count   
     long int N0 = n_points;// intializing number of points for iterations
     int n_threads;// declaration for number of threads variable
     double yscale =5.5;// setting the yscale
     for (int i = 0; i < 3; i++){  // for loop to scaleup by factor of 10           
            double timer_start = omp_get_wtime();// starting the timer
            omp_set_num_threads(threads);// setting the number of threads based on the parameter 'n_threads'
            // initiating the parallel section with shared and private variables
            #pragma omp parallel shared(n_threads, count) firstprivate(yscale, N0) default(none)
            {
                unsigned int _tid = omp_get_thread_num();// setting the number of threads  by instantiating them
                unsigned int tid = _tid;// getting the thread id
                unsigned int _time = (unsigned int)time(0);
                unsigned int seed = rand_r(&tid);// seed based on thread id
                seed ^= _time;
                #pragma omp single nowait // to prevent unnecessary race condition
                n_threads = omp_get_num_threads();// getting the number of thread in the parallel block            
                #pragma omp for reduction (+:count) // reduction on parallel counting
                for(long int points = 1; points <= N0; points++){// for loop to perform montecarlo integration                                
                double x,y, y_curve;               
                x = (double)rand_r(&seed)/(double)RAND_MAX; // generating values of x using random numbers
                y = ((double)rand_r(&seed)/(double)RAND_MAX)*yscale;// generating values of y using random numbers
                y_curve = 2*x*exp(x*x); // ploting y values             
                if(y < y_curve){
                    count = count + 1; //counting the points under the y curve
                }           
              }
            }
        double area_under_curve = ((double)count/(double)(N0))*yscale;// estimating the LHS based on points under the curve
        double timer_stop = omp_get_wtime();// stoping the timer
        double time_taken = timer_stop - timer_start;//calculating the parallel execution time
        printf("\033[1;32m");
        printf("\n Parallel implemention summary");
        printf("\033[0m");
        printf("\033[1;36m");
        printf("\n T= %f seconds, Number of threads =%d, Number points for iterations N = %ld, Orginal 'e' = %0.3f, Estimated 'e' = %0.3f\n",time_taken, n_threads, N0, exp(1), area_under_curve +1 );
        printf("\033[0m");
        N0 = N0 * 10;
        count =0;        
      }
     return 0;
    }

//-----------------------------------------------------------------------------------------
printf("\033[1;32m");
printf("\n\n###############################################################################################");
printf("\nWelcome to CSE 6010 : Computational Problem Solving\n");
printf("\nFall 2020 - Date 16th November 2020\n");
printf("\nAssignment 7 :");
printf("\nAmirtha Ganesh Pugazhendhi");
printf("\nGT ID: 903515950");
printf("###############################################################################################\n");
printf("\033[0m");
printf("\033[1;33m");
printf("\n\n###############################################################################################");
printf("\nMonte Carlo Integration Using OpenMP \n");
printf("###############################################################################################");
printf("\033[0m");
//----------------------------------------------------------------------------------------------------
    // serial implementation for estimating the value of 'e'
    serial_montecarlo(2000000);
    // parallel implementation for estimating the value of 'e'
    parallel_montecarlo(2000000,28);// 28 parallel threads
}