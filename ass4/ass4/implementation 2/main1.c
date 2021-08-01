#include <stdio.h>
#include <stdlib.h>
#include "tictactoe1.h"
//#include"tictactoe1.c"

// Developed by the team Sarah Bi , Amirtha Ganesh , Surabh  on 9/26/20.

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"
#define USAGE_STRING "USAGE:./executableName input_file k_value"

// Define global variables
// We use these flags to keep track of whether a change has been made from its respective function
// For example, if the check_for_2_similar_char_in_row flag = 1, that means a change has been made using the check_for_2_similar_char_in_row function
// Essentially, this means we found something that looks like ? O O ? and we were able to fill in the ? as X O O X
int flag_for_2_similar_row_char = 1;
int flag_for_2_similar_col_char = 1;
int flag_for_blank_between_2_similar_char_row = 1;
int flag_for_blank_between_2_similar_char_col = 1;
int flag_for_equal_no_of_character = 1;

int main (int argc, char** argv) {

    // Read in text file data
    int grid_size; // dimensions of the matrix given

    // Check the number of inputs passed into the program
    // The first input is the name of the program, the second is the input file name
    // So there should be 2 inputs passed in
    if(argc != 2) {
        fprintf(stderr, "%s\nYou must pass your data file as an argument to this program.\n", USAGE_STRING);
        return 1;
    }

    // This opens the file for reading. A return value of NULL indicates the file
    // failed to open for some reason, in which case we print out the error and
    // return an error status.
    FILE *infile = fopen(argv[1],"r");
    if(infile == NULL) {
        fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
        perror("Failed to open file");
        return 2;
    }

    // This will read in the dimensions of the matrix (first line of the file).
    // If it reads fewer (or more) than 1 thing, we know the file is incorrect.
    int readIn = fscanf(infile, " %d", &grid_size);

    if(readIn != 1) {
        fprintf(stderr, READ_ERROR_STRING);
        fclose(infile);
        return 1;
    }

    // Make tic-tac-toe board
    // Makes a square 2D array of size grid_size * grid_size
    // May be indexed with grid[i][j]
    char** grid;
    grid = (char**)malloc(sizeof(char*) *grid_size);
    for (int i = 0; i<grid_size; i++){
        grid[i] = (char*)malloc(sizeof(char)*grid_size);
    }

    // Enter the data from the textfile into the 2D grid matrix
    //int count = 0; // keep track of how many of the cells are already given by the input textfile
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            readIn = fscanf(infile," %c", &(grid[i][j])); // enter the data into the 2D array
            if(!readIn) {
                fprintf(stderr, READ_ERROR_STRING );
                return 1;
            }
        }
    }

    // Since we've read in all the data we need, close the file.
    fclose(infile);

    printf("\033[1;32m");
printf("\n\n ###############################################################################################");
printf("\n Welcome to CSE 6010 : Computational Problem Solving\n");
printf("\n Fall 2020 \n");
printf("\n Assignment 4 :");
printf("\n Team 1)Sarah Dongyun Bi 2)Saurabh Parimal Doodhwala 3) Amirtha Ganesh Pugazhendhi");
printf("\n Tic-Tac-Toe Puzzle solving \n");
printf(" ###############################################################################################\n");
printf("\033[0m;");
printf("\033[1;33m");
printf("\n\n ###############################################################################################");
printf("\n Tic-Tac-Toe Grid\n");
printf(" ###############################################################################################");
printf("\033[0m;");
printf("\033[1;33m");

     

    // Create counters to keep track of how many Xs, Os, and ?s are in each row and column
    int *count_X_col;
    count_X_col = (int*)malloc(sizeof(int) *grid_size);

    int *count_O_col;
    count_O_col = (int*)malloc(sizeof(int) *grid_size);

    int *count_X_row;
    count_X_row = (int*)malloc(sizeof(int) *grid_size);

    int *count_O_row;
    count_O_row = (int*)malloc(sizeof(int) *grid_size);

    int *count_Q_row;
    count_Q_row = (int*)malloc(sizeof(int) *grid_size);
    
    int *count_Q_col;
    count_Q_col = (int*)malloc(sizeof(int) *grid_size);

    // Call recursive function to solve the grid
    solve_the_puzzle(&grid, grid_size, &count_X_col, &count_O_col, &count_Q_col, &count_X_row, &count_O_row, &count_Q_row);
    printf(" ###############################################################################################\n");
    printf("\033[0m;");
    return 0;
}





