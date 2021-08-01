#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"
#define USAGE_STRING "USAGE:./executableName input_file k_value"

//Function definition to allocate initial random centroid points for the initial k clusters
void rand_centroid_init(double *centroid_array, double *data_array, int nCols, int nRows, int start, int end, int *values, int k) { 
	//For loop to temporarily store the all observations data across all columns.
    int i = 0;
     for (int i = 0; i < nRows; i++) {     
         values[i] = i;
    }
    // For loop to randomize observation data positions
    for (int i; i < nRows; i++) {    
        int temp = values[i];
        int random = (rand() % (end - start + 1)) + start;
        values[i] = values[random];
        values[random] = temp;
    }
    // For loop  to randomily assign 'k' numbers of unique centeroid points from randomized array
	for (i = 0; i < k; i++) { 
		for(int j=0; j < nCols; j++){
            *(centroid_array + i*nCols + j) = *(data_array + values[i]*nCols + j) ;
        }		 
	} 
    
} //returns null

// Function definition to compute the Average across all the columns or a dimensions
void compute_average(double *data_array, int nRows, int nCols, double *avg){
	double sum;
    for(int j = 0 ; j < nCols; j++){
        sum = 0;
        for(int i = 0; i < nRows; i++){
            sum = sum + *(data_array + (i*nCols) + j);
        }
        *(avg + j) = sum/nRows;	
    }
    
}//returns null

// Function definition to compute the Standard Deviation accross all the columns or a dimensions
void compute_stdev(double *data_array, int nRows, int nCols, double *avg, double *std){
	double sum;
	for(int j = 0 ; j < nCols; j++){
			sum = 0;
			for(int i = 0; i < nRows; i++){
				sum = sum + pow(*(data_array + (i*nCols) + j) - *(avg + j), 2);
			}
			*(std + j) = sqrt(sum/nRows);
		}
    
}//returns null

// Function definition to perform normalization of data points in data_array
void compute_norm(double *data_array, int nRows, int nCols, double *avg, double *std ){
 //Calling function compute_average to compute the Average
 compute_average(data_array,nRows, nCols, avg);
 //Calling function compute_stdev to compute the Standard Deviation
 compute_stdev(data_array,nRows, nCols, avg, std);
// For loop to normalize the each and every observations in data_array
    for(int i = 0 ; i < nRows; i++){    
		for(int j = 0 ; j < nCols; j++){
			*(data_array + (nCols*i) + j) = (*(data_array + (nCols*i) + j) - *(avg + j))/ *(std + j);
			}
    }
}//returns null

// Function definition to  identify which cluster does the data points belong to.
void allocate_cluster(double *data_array, double *centroid_array, int nRows, int nCols, int k, int b, int *data_in_cluster, double *dist, double *min_dist, double *mean_sqr_dist, double *RMSE){
    double sumsqr;
// For loop to find compare to traverse through all observations (across all rows)
    for (int i = 0; i < nRows; i++){
        sumsqr = 0;
        //For loop  first compute RMS value between i = 0th point and 0th centroid.
        for(int x = 0; x < nCols; x++){
            sumsqr = sumsqr + pow(*(data_array + i*nCols + x) - *(centroid_array + 0*nCols + x), 2);
        }
		//Intially assuming this Root Mean Square (RMS) distance between i = 0th point and 0th centroid is minimum and assigning cluster 0 to i=0th point.
        *(min_dist + i) = sqrt(sumsqr);
		mean_sqr_dist[i] = sumsqr;        
        data_in_cluster[i] = 0;        
        // For loop to traverse through each cluster cenroid point
        for (int j = 0; j < k; j++){
            // compute RMS value between ith point and jth centroid.
            sumsqr = 0;
            // For loop to calculate the Squared distance between each Centroid and data obersvation
            for(int x = 0; x < nCols; x++){
            sumsqr = sumsqr + pow(*(data_array + i*nCols + x) - *(centroid_array + j*nCols + x),2);
            }            
            dist[i] = sqrt(sumsqr);
            // if RMS value between ith point and jth centroid < min_dist[i]
            // then assign that as the new min_dist[i] 
            if(dist[i] < min_dist[i])
            {
                min_dist[i] = dist[i];
				mean_sqr_dist[i] = sumsqr; 
                data_in_cluster[i] = j;
            }			

        }
		RMSE[b] = RMSE[b] + mean_sqr_dist[i];
        // computed closest centroid to the ith point stored as min_dist[i].
            }
	RMSE[b] = sqrt(RMSE[b]/nRows);
}

//Function definition to determine the new centroid location based on clusters
void update_centroid(double *data_array, double *centroid_array, int *data_in_cluster, int k, int nCols, int nRows){
    // For loop to traverse all cluster centroid
    for(int j = 0 ; j < k; j++){
        int n = 0;
    // For loop to traverse all data points        
        for (int i = 0; i < nRows; i++){            
            if(data_in_cluster[i] == j){
                  if(n == 0){
                       //For loop to re-initialize the all centroid to be zero
                     	for(int l = 0; l < nCols; l++){
                        *(centroid_array + j*nCols + l)  = 0;
                        }
                  }     
                //For loop to insert the data points into the appropriate centroid arrary
                  for(int l=0; l < nCols; l++){
                    *(centroid_array + j*nCols + l) = *(centroid_array + j*nCols + l) + *(data_array + i*nCols + l);
                    }
                n = n + 1;
            
            }
        }
    if(n >= 1){  
      //For loop to calculate the new centroids based on the data points under each centroid 
      for(int l=0; l < nCols; l++){
         *(centroid_array + j*nCols + l) = *(centroid_array + j*nCols + l)/n;
        }
     }

    }
}//returns null

int main(int argc, char** argv)
{
 // nRows will hold how many rows of data there are, nCols holds the number of
 // columns (attributes.) Do not change these variables. k will hold the value of k
// passed in to the program from the command line.
 int nRows, nCols, k;
 
/*
################################################################################
## Begininning of provided code to read in file
################################################################################
*/

 // Here we check to be sure that the correct number of arguments have been
 // passed in from the command line. The first argument is always the program
 // name. If not, we print and error and return error status.
 if(argc != 3)
 {
printf("\033[1;31m");
printf("\n|---------------- ERROR ---------------------------------------|\n");    
  fprintf(stderr, "%s\nYou must pass your data file  and k value "
   "(in that order)as an argument to this program.\n", USAGE_STRING);
printf("\n|---------------- ERROR ---------------------------------------|\n"); 
printf("\033[0m");  
  return 1;
 }
 // This section will safely parse the value of k passed in to the program.
 // If the argument cannot be parsed to an integer, or if it is larger than
 // INT_MAX, we error out.
 char *endptr = NULL;
 int base = 10;
 errno = 0;
 long int long_k = strtol(argv[2], &endptr, base);
 printf("\n value of long_k %d\n ",argc);
 printf("\n value is %c\n ",*(argv[2]));
 // This will trigger if an error was encountered when trying to parse the
 // input, or if the input was not a proper integer (e.g. 124A). This
 // can also trigger if the input is too long to fit even in a long int.
 if((errno != 0) || (*endptr != '\0'))
 {
printf("\033[1;31m");
printf("\n|---------------- ERROR ---------------------------------------|\n");    
  fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
  " \n", argv[2]);
  printf("\n|---------------- ERROR ---------------------------------------|\n"); 
printf("\033[0m"); 
  return 1;
 }
 if((long_k > INT_MAX) || (long_k <= 0))
 {
printf("\033[1;31m");
printf("\n|---------------- ERROR ---------------------------------------|\n");    
  fprintf(stderr, "The k-value input was:\t%ld\n"
   "K must be larger than zero, and no larger than %u.\n", long_k,
   INT_MAX);
 printf("\n|---------------- ERROR ---------------------------------------|\n"); 
printf("\033[0m"); 
  return 1;
 }
 k = (int)long_k;
 // This opens the file for reading. A return value of NULL indicates the file
 // failed to open for some reason, in which case we print out the error and
 // return an error status.
 FILE *infile = fopen(argv[1],"r");
 if(infile == NULL)
 {
printf("\033[1;31m");
printf("\n|---------------- ERROR ---------------------------------------|\n");    
  fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
  perror("Failed to open file");
  printf("\n|---------------- ERROR ---------------------------------------|\n"); 
printf("\033[0m"); 
  return 2;
 }
 // This will read in the number of rows and columns (first line of the file).
 // If it reads fewer than two things, we know the file is incorrect.
 int readIn = fscanf(infile, " %d %d", &nRows, &nCols); 
 printf("  rows : %d , cols: %d",nRows, nCols);
 if(readIn != 2)
 {
printf("\033[1;31m");
printf("\n|---------------- ERROR ---------------------------------------|\n");    
  fprintf(stderr, READ_ERROR_STRING);
  fclose(infile);
 printf("\n|---------------- ERROR ---------------------------------------|\n"); 
printf("\033[0m");
  return 1;
 }
 // Makes a stack array with nRows rows and nCols columns.
 // May be indexed with data_array[i][j].
 double data_array[nRows][nCols];

 // This loop reads in the expected number of rows and columns. If it fails to
 // read the expected number, it errors out. This doesn't catch some errors,
 // E.G. too *many* lines in the input file, but you should not be editing
 // those files for the assignment anyway.
 for (int i = 0; i < nRows; ++i)
 {
  for (int j = 0; j < nCols; ++j)
  {
  
   readIn = fscanf(infile," %lf", &(data_array[i][j]));
   if(!readIn)
   {
    printf("\033[1;31m");
    printf("\n|---------------- ERROR ---------------------------------------|\n");  
    fprintf(stderr, READ_ERROR_STRING );
    printf("\n|---------------- ERROR ---------------------------------------|\n"); 
    printf("\033[0m");
    return 1;
   }
  }
 }


 // Since we've read in all the data we need, close the file.
 fclose(infile);

/*
################################################################################
## End of code provided for reading file.
################################################################################
*/

 /*

  IMPORTANT!

  Variables you will need, which *already exist* at this point in the
  code!

  nRows: an int containing the number of rows (items) in the dataset
  
  nCols:  an int containing the number of columns(attributes per item).


  k:  an int containing the value of 'k' (number of clusters) passed
    to the program from the command line.

  data_array: a 2-dimensional double array which is nRows x nCols.
     This may be indexed like data_array[i][j], where i is
     a row index and j is a column index.
    centroid_array : 2-D double array which is k * nCols                    
 
 */

// Declaring the array for column averages and standard deviations
double avg[nCols];
double std[nCols];
// Calling the function compute_norm to normalize the all data points(observations)
compute_norm(&data_array[0][0], nRows, nCols, avg, std);
//Declaring the array for first k data points as initial centroids
double centroid_array[k][nCols]; 
int values[nRows];

// Calling the function rand_centroid_init to assign initial random centroid points
rand_centroid_init(&centroid_array[0][0], &data_array[0][0], nCols, nRows, 0, nRows - 1, &values[0], k);

//Calculating distance of each point from centroids and determining their clusters
int b;
double dist[nRows][k];
int data_in_cluster[k];
double min_dist[nRows];
double mean_sqr_dist[nRows];
double sumsqr;
double RMSE[nRows];
printf("\033[1;32m");
printf("\n\n ###############################################################################################");
printf("\n Welcome to CSE 6010 : Computational Problem Solving\n");
printf("\n Fall 2020 \n");
printf("\n Assignment 3 :");
printf("\n Amirtha Ganesh Pugazhendhi");
printf("\n GT ID: 903515950");
printf("\n Implementation of K-means Clustering Algoritm\n");
printf(" ###############################################################################################\n");
printf("\033[0m;");
printf("\033[1;33m");
printf("\n\n ###############################################################################################");
printf("\n K-Means Algorithm - Data Table - Randomized - Normalized \n");
printf(" ###############################################################################################");
printf("\033[0m;");
printf("\033[1;31m");
printf(" \n Threshold for RMSE = 1x10^-6  \n");
printf("\033[0m;");
     

// For loop to govern the number of iterations for k-means Algorithm
for(b=1; b <= 100; b++){
	RMSE[b] = 0;
    // Calling  the function allocate_cluster to identify and allocate the closest cluster to the data points 
    allocate_cluster(&data_array[0][0], &centroid_array[0][0], nRows, nCols, k, b, &data_in_cluster[0], &dist[0][0], &min_dist[0], &mean_sqr_dist[0], &RMSE[0]);
	
	if (b >= 2 && (fabs((RMSE[b] - RMSE[b - 1])/RMSE[b - 1]) < pow(10, -6))){
		break;
	}
	
    // Calling  the function update_centroid to update centroid based on points under the each centroid
    update_centroid(&data_array[0][0], &centroid_array[0][0], &data_in_cluster[0],  k, nCols, nRows);

  }
printf("\033[1;34m");
printf("\n \t|------------------------------------------------------------------------------------------------|");
printf("\n \t| Obs. No.\t|   cluster No.\t|   Iter. No.\t|  Last RMSE \t| RMSE rate \t|");
printf("\n \t|------------------------------------------------------------------------------------------------|\n");
printf("\033[0m");

	for(int i =0; i < nRows; i++){
    printf("\033[1;34m");
     	printf("|\t %d \t|\t %d \t|\t %d \t|\t %f \t|\t %f \t|\n",i+1, data_in_cluster[i]+1, b, RMSE[b], fabs((RMSE[b] - RMSE[b - 1])/RMSE[b - 1]));
	printf("\033[0m");
     }
    printf("\033[1;32m");
    printf("\n \t|-------------------------------------------------------------------------------------------|\n");
    printf("\033[0m");
    printf("\033[1;32m");
printf("\n\n ###############################################################################################");
printf("\n Welcome to CSE 6010 : Computational Problem Solving\n");
printf("\n Fall 2020 \n");
printf("\n Assignment 3 :");
printf("\n Amirtha Ganesh Pugazhendhi");
printf("\n GT ID: 903515950");
printf("\n Implementation of K-means Clustering Algoritm\n");
printf(" ###############################################################################################\n");
printf("\033[0m;");
printf("\033[1;35m");
printf("\n\n ###############################################################################################");
printf("\n K-Means Algorithm - Cluster Summary \n");
printf(" ###############################################################################################");
printf(" \n Summary \n");
printf("\033[1;31m");
printf(" \n Threshold for RMSE = 1x10^-6  \n");
printf("\033[0m;");
for(int i=0; i<nCols; i++){
    if (i%2==0){
    printf("\033[1;33m");
    printf("\n Average for column %d = %f \n",i+1,avg[i]);
    printf("\n Standard Deviation for column %d = %f \n",i+1,std[i]);
    printf("\033[0m;");
    }
    else{
    printf("\033[1;36m");
    printf("\n Average for column %d = %f \n",i+1,avg[i]);
    printf("\n Standard Deviation for column %d = %f \n",i+1,std[i]);
    printf("\033[0m;");

    }
}
printf("\033[0m;");
printf("\033[1;35m");
printf("\n|-------------------------------------------------------|");
printf("\n| Cluster No.   | Co. position  |  Co-ordinate value    |");
printf("\n|-------------------------------------------------------|\n");
printf("\033[0m");

    for(int i = 0; i < k; i++){
        for(int j = 0; j < nCols; j++){
            if (i%2==0){
            printf("\033[1;32m");
            printf("|\t %d\t|\t %d\t|\t %f\t|\n", i+1, j+1, centroid_array[i][j]);
            printf("\033[0m");
            }else{
            printf("\033[1;33m");
            printf("|\t %d\t|\t %d\t|\t %f\t|\n", i+1, j+1, centroid_array[i][j]);
            printf("\033[0m");
            }
        }  
        printf("\033[1;36m");
        printf("|-------------------------------------------------------|\n");  
        printf("\033[0m");
    }
printf("\033[1;33m");
printf("\n|---------------- END OF PROGRAM ---------------------------------------|\n"); 
printf("\033[0m");
 return 0;


}
