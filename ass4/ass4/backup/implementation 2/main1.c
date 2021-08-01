#include <stdio.h>
#include <stdlib.h>
#include "tictactoe1.h"
//#include"tictactoe1.c"

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"
#define USAGE_STRING "USAGE:./executableName input_file k_value"

// Define global variables
// We use these flags to keep track of whether a change has been made from its respective function
// For example, if the twoConsecutiveRow flag = 1, that means a change has been made using the twoConsecutiveRow function
// Essentially, this means we found something that looks like ? O O ? and we were able to fill in the ? as X O O X
int flag_for_2_similar_row_char = 1;
int flag_for_2_similar_col_char = 1;
int flag_for_blank_between_2_similar_char_row = 1;
int flag_for_blank_between_2_similar_char_col = 1;
int flag_for_equal_no_of _character = 1;

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
    puzzle_solve(&grid, grid_size, &count_X_col, &count_O_col, &count_Q_col, &count_X_row, &count_O_row, &count_Q_row);

    return 0;
}







//    while (checkEmpty(&grid, grid_size) == 1) {
//
//        /*
//         * Loop through the entire board
//         * Check if there are any cells with two consecutive same letters (horizontally)
//         * If there are, put the other letter on either side of them
//         * For example, if there exists a segment ? O O ? , we know it must be X O O X
//         * Since there cannot be more than 2 consecutive of the same letter
//         */
//        //flag_for_2_similar_row_char = 0; // reset flag
//        for (int i=0; i<grid_size; ++i){
//            for (int j=0; j<(grid_size-1); ++j){
//                twoConsecutiveRow(&grid, grid_size, i, j);
//            }
//        }
//        printGrid(&grid, grid_size); // for debugging- take this out when done
//        printf("\n");
//
//        /*
//         * Loop through the entire board
//         * Check if there are any cells with two consecutive same letters (vertically)
//         */
//        //flag_for_2_similar_col_char = 0; // reset flag
//        for (int j=0; j<grid_size; ++j){
//            for (int i=0; i<(grid_size-1); ++i){
//                twoConsecutiveCol(&grid, grid_size, i, j);
//            }
//        }
//        printGrid(&grid, grid_size); // for debugging- take this out when done
//        printf("\n");
//
//        /*
//         * Loop through the entire board
//         * Check if there are any cells with an X or O on either side of it horizontally
//         */
//        flag_for_blank_between_2_similar_char_row = 0; // reset the flag
//        for (int i=0; i<grid_size; i++){
//            for (int j=0; j<grid_size; j++){
//                oneEitherSideRow(&grid, grid_size, i, j);
//            }
//        }
//        printGrid(&grid, grid_size); // for debugging- take this out when done
//        printf("\n");
//
//        /*
//         * Loop through the entire board
//         * Check if there are any cells with an X or O on either side of it vertically
//         */
//        //flag_for_blank_between_2_similar_char_col = 0; // reset the flag
//        for (int i=0; i<grid_size; i++){
//            for (int j=0; j<grid_size; j++){
//                oneEitherSideCol(&grid, grid_size, i, j);
//            }
//        }
//        printGrid(&grid, grid_size); // for debugging- take this out when done
//        printf("\n");
//
//        /*
//         * Loop through the entire board
//         * Check if there are the same number of Xs and Os in each row and column
//         */
//        //flag_for_equal_no_of _character = 0; // reset the flag
//        count(&grid, grid_size, &count_X_col, &count_O_col, &count_Q_col, &count_X_row, &count_O_row, &count_Q_row);
//        equalXAndO(&grid, grid_size, &count_X_col, &count_O_col, &count_Q_col, &count_X_row, &count_O_row, &count_Q_row);
//
//        printGrid(&grid, grid_size); // for debugging- take this out when done
//        printf("\n");


   // int empty = checkEmpty(&grid, grid_size);

    // Check conditions for being able to enter the character in the cell
//    int oRowCount = 0;
//    int oColCount = 0;
//    int xRowCount = 0;
//    int xColCount = 0;
//    int oFlag = 0; // indicates whether O can go in this cell
//    int xFlag = 0; // indicates whether X can go in this cell
//    for (int i=0; i<grid_size; i++) {
//        oRowCount = findRowCount(&grid, i, grid_size, 'O'); // find how many O's already exist in the row
//        xRowCount = findRowCount(&grid, i, grid_size, 'X'); // find how many X's already exist in the row
//        for (int j= 0; j<grid_size; j++){
//
//            oColCount = findColCount(&grid, j, grid_size, 'O'); // find how many O's already exist in the column
//            xColCount = findColCount(&grid, j, grid_size, 'X'); // find how many X's already exist in the column
//
//
//            // If the entry has not already been populated (it wasn't given as a starting point in the textfile)
//            // Determine whether an X or an O (or both) can be put there
//            if (startingPoints[i][j] != 1) {
//
//                // Check if an O can be put in the entry
//                // Rule 1: having the same number of X's and O's means that the maximum number of X's and O's each is half the grid size
//                // For example, if your grid size is 6x6, in order to have the same number of Os and Xs, you can only have 3 of each in a row/column
//                // So the maximum number is 6/2
//                // For grid_size * grid_size dimension, that number is just grid_size/2
//                if ((oRowCount < grid_size/2) && (oColCount < grid_size/2)) { // 1. Check if the maximum number of O's has already been put in the row and column
//                    if (twoConsecutive(&grid, i, j, grid_size, 'O') != 1){
//                        grid[i][j] = 'O'; // put an O in the location
//                        oFlag = 1;
//                    }// 2. Check if there are already 2 O's in a row
//
//                }
//
//                // Check if X can go in the cell
//                if ((xRowCount < grid_size/2) && (xColCount < grid_size/2)) { // 1. Check if the maximum number of O's has already been put in the row and column
//                    if (twoConsecutive(&grid, i, j, grid_size, 'O') != 1){
//                        if (oFlag == 0){ // check if an O has already been put in the location
//                            grid[i][j] = 'X'; // put an O in the location
//                        }
//                        else{ // if there is already an O in the location, put the X onto the queue
//                            printf("put x onto the queue");
//                        }
//                        xFlag = 1;
//                    }
//                }
//                // Neither an O nor an X can be put in the cell
//                // We need to backtrack and change our assignments
//                if ((oFlag == 0) && (xFlag == 0)){
//                    printf("wrong direction- need to backtrack");
//                }
//            }
//        }
//    }
    // Check if row has the same number of X's and O's
    // In order for each row to have the same number of X's and O's the maximum number of each type is grid_size / 2

    // Check no more than two X's and O's in consecutive order





