//
// Created by Sarah Bi on 9/21/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"
#include "myboolean.h"

// Define global variables
int twoConsecutiveRowFlag;
int twoConsecutiveColFlag;
int checkEitherSideRowFlag;
int checkEitherSideColFlag;
int equalXAndOFlag;

/*
 * Function: checkEmpty
 * --------------------
 * Description:
 *      Determine if there are any cells in the grid that are still empty
 *      This is the while loop condition
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix

 * Returns:
 *      0 if the grid is completely filled
 *      1 if there are still empty cells
 */
int checkEmpty(char ***grid, int grid_size){
    for (int i=0; i<grid_size; i++){
        for (int j=0; j<grid_size; j++){
            if ((*grid)[i][j] == '?'){ // if there is at least one ? symbol, the grid is not full
                return 1;
            }
        }
    }
    return 0; // if iterate through whole grid and there are no ? symbols, then the grid is completely full
}


/*
 * Function: twoConsecutiveRow
 * --------------------
 * Description:
 *      Loop through the entire board
 *      Check if there are any cells with two consecutive same letters (horizontally)
 *      If there are, put the other letter on either side of them
 *      For example, if there exists a segment ? O O ? , we know it must be X O O X
 *      Since there cannot be more than 2 consecutive of the same letter
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int i- row number of the grid to check
 *      int j- column number of the grid to check
 * Returns:
 *      None
 */
void twoConsecutiveRow(char ***grid, int grid_size, int i, int j){

    if((*grid)[i][j] == (*grid)[i][j+1] && (*grid)[i][j] == 'X'){
        if((j>=1) && ((*grid)[i][j-1] == '?')){
            (*grid)[i][j-1] = 'O';
            twoConsecutiveRowFlag = 1; // set flag if change has been made
        }
        if((j+1<(grid_size -1)) && ((*grid)[i][j+2] == '?')){
            (*grid)[i][j+2] = 'O';
            twoConsecutiveRowFlag = 1; // set flag if change has been made
        }
    }
    if((*grid)[i][j] == (*grid)[i][j+1] && (*grid)[i][j] == 'O'){
        if((j>=1) && ((*grid)[i][j-1] == '?')){
            (*grid)[i][j - 1] = 'X';
            twoConsecutiveRowFlag = 1; // set flag if change has been made
        }
        if((j+1<(grid_size -1)) && ((*grid)[i][j+2] == '?')){
            (*grid)[i][j+2] = 'X';
            twoConsecutiveRowFlag = 1; // set flag if change has been made
        }
    }
}

/*
 * Function: twoConsecutiveCol
 * --------------------
 * Description:
 *      Loop through the entire board
 *      Check if there are any cells with two consecutive same letters (vertically)
 *      For example, if there exists a segment (left), we know it has to be (right)
 *      ?  X
 *      O  O
 *      O  O
 *      ?  X
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int i- row number of the grid to check
 *      int j- column number of the grid to check
 * Returns:
 *      None
 */
void twoConsecutiveCol(char ***grid, int grid_size, int i, int j){

    if((*grid)[i][j] == (*grid)[i+1][j] && (*grid)[i][j] == 'X'){
        if((i>=1) && ((*grid)[i-1][j] == '?')){
            (*grid)[i-1][j] = 'O';
            twoConsecutiveColFlag = 1; // set flag if change has been made
        }
        if((i+1<(grid_size -1)) && ((*grid)[i+2][j] == '?')){
            (*grid)[i+2][j] = 'O';
            twoConsecutiveColFlag = 1; // set flag if change has been made
        }
    }
    if((*grid)[i][j] == (*grid)[i+1][j] && (*grid)[i][j] == 'O'){
        if((i>=1) && ((*grid)[i-1][j] == '?')){
            (*grid)[i-1][j] = 'X';
            twoConsecutiveColFlag = 1; // set flag if change has been made
        }
        if((i+1<(grid_size-1)) && ((*grid)[i+2][j] == '?')){
            (*grid)[i+2][j] = 'X';
            twoConsecutiveColFlag = 1; // set flag if change has been made
        }
    }
}

/*
 * Function: oneEitherSideRow
 * --------------------
 * Description:
 *      Loop through the entire board
 *      Check if there are any cells with Xs or Os on either side horizontally
 *      For example, if there exists a segment O ? O, we know it must be O X O
 *      Because there cannot be more than 2 Os or Xs in a row
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int i- row number of the grid to check
 *      int j- column number of the grid to check
 * Returns:
 *      None
 */
void oneEitherSideRow(char ***grid, int grid_size, int i, int j){

    // We only want to do this check on cells that are not on the vertical borders of the board (leftmost and rightmost columns)
    // Because this type of pattern that we are checking for is not possible at the border of the board
    if ((j==0) || (j==grid_size-1)){
        return;
    }
    else {
        if (((*grid)[i][j-1] == 'O') && ((*grid)[i][j+1] == 'O') && ((*grid)[i][j] == '?')){ // if both cells are either side are O, then this cell must be an X
            (*grid)[i][j] = 'X';
            checkEitherSideRowFlag = 1; // set flag if change has been made
        }
        if (((*grid)[i][j-1] == 'X') && ((*grid)[i][j+1] == 'X') && ((*grid)[i][j] == '?')){ // if both cells on either side are X, then this cell must be an O
            (*grid)[i][j] = 'O';
            checkEitherSideRowFlag = 1; // set flag if change has been made
        }
    }
}

/*
 * Function: oneEitherSideCol
 * --------------------
 * Description:
 *      Loop through the entire board
 *      Check if there are any cells with Xs or Os on either side vertically
 *      For example, if there exists a segment (left), then it must be (right)
 *      O O
 *      ? X
 *      O O
 *      Because there cannot be more than 2 Os or Xs in a row
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int i- row number of the grid to check
 *      int j- column number of the grid to check
 * Returns:
 *      None
 */
void oneEitherSideCol(char ***grid, int grid_size, int i, int j){

    // We only want to do this check on cells that are not on the vertical borders of the board (leftmost and rightmost columns)
    // Because this type of pattern that we are checking for is not possible at the border of the board
    if ((i==0) || (i==grid_size-1)){
        return;
    }
    else {
        if (((*grid)[i-1][j] == 'O') && ((*grid)[i+1][j] == 'O') && ((*grid)[i][j] == '?')){ // if both cells are either side are O, then this cell must be an X
            (*grid)[i][j] = 'X';
            checkEitherSideColFlag = 1; // set flag if change has been made
        }
        if (((*grid)[i-1][j] == 'X') && ((*grid)[i+1][j] == 'X') && ((*grid)[i][j] == '?')){ // if both cells on either side are X, then this cell must be an O
            (*grid)[i][j] = 'O';
            checkEitherSideColFlag = 1; // set flag if change has been made
        }
    }
}

/*
 * Function: equalXAndO
 * --------------------
 * Description:
 *      Loop through the entire board
 *      Check if there are the same number of Xs and Os in each row and column
 *      Create matrices of size grid_size to store the number of Xs and Os in each row and each column
 *      Rule 1: having the same number of X's and O's means that the maximum number of X's and O's each is half the grid size
 *      For example, if your grid size is 6x6, in order to have the same number of Os and Xs, you can only have 3 of each in a row/column
 *      So the maximum number is 6/2
 *      For grid_size * grid_size dimension, that number is just grid_size/2
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 * Returns:
 *      None
 */
void equalXAndO(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row){

    // For each column of the matrix
    // If there are already maximum X's in that column, fill the rest with O's
    for(int j =0; j<grid_size; j++){
        if((*count_X_col)[j] == grid_size/2){
            for(int i = 0; i<grid_size; i++){
                if((*grid)[i][j] == '?'){
                    (*grid)[i][j] = 'O';
                    equalXAndOFlag = 1; // set the flag if change is made
                }
            }
        }
    }

    // For each column of the matrix
    // If there are already maximum O's in that column, fill the rest with X's
    for(int j =0; j<grid_size; j++){
        if((*count_O_col)[j] == grid_size/2){
            for(int i = 0; i<grid_size; i++){
                if((*grid)[i][j] == '?'){
                    (*grid)[i][j] = 'X';
                    equalXAndOFlag = 1; // set the flag if change is made
                }
            }
        }
    }

    // For each row of the matrix
    // If there are already maximum X's in that row, fill the rest with O's
    for(int i =0; i<grid_size; i++){
        if((*count_X_row)[i] == grid_size/2){
            for(int j = 0; j<grid_size; j++){
                if((*grid)[i][j] == '?'){
                    (*grid)[i][j] = 'O';
                    equalXAndOFlag = 1; // set the flag if change is made
                }
            }
        }
    }

    // For each row of the matrix
    // If there are already maximum O's in that row, fill the rest with X's
    for(int i =0; i<grid_size; i++){
        if((*count_O_row)[i] == grid_size/2){
            for(int j = 0; j<grid_size; j++){
                if((*grid)[i][j] == '?'){
                    (*grid)[i][j] = 'X';
                    equalXAndOFlag = 1; // set the flag if change is made
                }
            }
        }
    }
}

/*
 * Function: count
 * --------------------
 * Description:
 *      Count how many Xs, Os, and ?s are in each row and column of the grid
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int **count_X_col- 1D matrix containing the number of Xs in each column
 *      int **count_O_col- 1D matrix containing the number of Os in each column
 *      int **count_Q_col- 1D matrix containing the number of ?s in each column
 *      int **count_X_row- 1D matrix containing the number of Xs in each row
 *      int **count_O_row- 1D matrix containing the number of Os in each row
 *      int **count_Q_row- 1D matrix containing the number of Qs in each row
 * Returns:
 *      None
 */
void count(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row ){

    // Count how many Xs ,Os, ?s are in each column of the matrix
    for (int j = 0; j<grid_size; j++){
        (*count_X_col)[j] = 0;
        (*count_O_col)[j] = 0;
        (*count_Q_col)[j] = 0;
        for (int i=0; i<grid_size; i++){
            if ((*grid)[i][j] == 'X'){
                (*count_X_col)[j] = (*count_X_col)[j] + 1; // if the letter in this location is an X, increment the count
            }
            if ((*grid)[i][j] == 'O'){
                (*count_O_col)[j] = (*count_O_col)[j] + 1; // if the letter in this location is an O, increment the count
            }
            if ((*grid)[i][j] == '?'){
                (*count_Q_col)[j] = (*count_Q_col)[j] + 1; // if the letter in this location is an ?, increment the count
            }
        }
    }

    // Count how many Xs and Os are in each row of the matrix
    for(int i = 0; i<grid_size; i++){
        (*count_X_row)[i] = 0;
        (*count_O_row)[i] = 0;
        (*count_Q_row)[i] = 0;
        for (int j=0; j<grid_size; j++){
            if ((*grid)[i][j] == 'X') {
                (*count_X_row)[i] = (*count_X_row)[i] + 1; // if the letter in this location is an X, increment the count
            }
            if ((*grid)[i][j] == 'O'){
                (*count_O_row)[i] = (*count_O_row)[i] + 1; // if the letter in this location is an O, increment the count
            }
            if ((*grid)[i][j] == '?') {
                (*count_Q_row)[i] = (*count_Q_row)[i] + 1; // if the letter in this location is an Q, increment the count
            }
        }
    }
}

/*
 * Function: printGrid
 * --------------------
 * Description:
 *      Print the board to the screen
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 * Returns:
 *      None
 */
void printGrid(char ***grid, int grid_size){
    for (int i = 0; i < grid_size; i++){
        for (int j = 0; j < grid_size; j++){
            printf(" %c ", (*grid)[i][j]);
        }
        printf("\n");
    }
}

/*
 * Function: consecutiveCheck
 * --------------------
 * Description:
 *      Check to see if putting a certain letter at a specific (row,column) location will result in 3 of that letter in a row
 *      Essentially we cannot have more than 2 of a letter in a row
 *      We must make sure we follow that rule before we put a letter in a location
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int i- row that you are checking
 *      int j- column that you are checking
 *      char letter- letter that you are checking (X or O)
 * Returns:
 *      0 if it does not violate the 2 consecutive rule
 *      1- if it does
 */
int twoConsecutiveCheck(char ***grid, int i, int j, int grid_size, char letter){

 //  If it is in the first row
    if (i==0){
        if (j==0) { // if cell is on top left edge of the board
          if ((((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check right in the row
                ((((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)))) { // check downwards in the column
                return 1;
            }
          else{
              return 0;
          }
        }
       else if (j==grid_size-1){ // if cell is on top right edge of the board
           if ((((*grid)[i][j-1] == letter) && ((*grid)[i][j-2] == letter)) || // check 2 left in the row
               ((((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)))) { // check 2 downwards in the column
               return 1;
           }
           else{
               return 0;
           }
       }
       // If is in the middle of the row
       // It will violate the consecutive rule if
       // 1. The immediate two left cells have the letter
       // 2. The immediate two right cells have the letter
       // 3. One to the left and one to the right have the letter
       // 4. The immediate two below cells have the letter
       else {
           if ((((*grid)[i][j - 1] == letter) && ((*grid)[i][j - 2] == letter)) || // check 2 left in the row
               (((*grid)[i][j + 1] == letter) && ((*grid)[i][j + 2] == letter)) || // check 2 right in the row
               (((*grid[i][j - 1]) == letter) && ((*grid)[i][j + 1] == letter)) || // check 1 left and 1 right in the row
               (((*grid)[i + 1][j]) == letter) && ((*grid)[i + 2][j] == letter)) { // check 2 down in the column
               return 1;
           }
           else {
               return 0;
           }
       }
    }

   // If it is in the last row
   else if (i==grid_size-1){
       if (j==0) { // if cell is on bottom left edge of the board
           if ((((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
               ((((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)))) { // check 2 up in the column
               return 1;
           }
           else {
               return 0;
           }
       }
       else if (j==grid_size-1){ // if cell is on bottom right edge of the board
           if ((((*grid)[i][j-1] == letter) && ((*grid)[i][j-2] == letter)) || //check 2 left in the row
               ((((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)))) { // check 2 up in the column
               return 1;
           }
           else {
               return 0;
           }
       }
       // If is in the middle of the row
       //    It will violate the consecutive rule if
       //    1. The immediate two left cells have the letter
       //    2. The immediate two right cells have the letter
       //    3. One to the left and one to the right have the letter
       //    4. The immediate two above cells have the letter
       else{
           if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                (((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
                (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) || // check 1 left and 1 right
                (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) ) { // check 2 above
               return 1;
           }
           else {
               return 0;
           }
       }
   }

   else if (j==0){ // if it is the first column
       if (i == 1){ // if it is in the second row
           // It will violate the consecutive rule if
           // 1. The immediate two on the right have the letter
           // 2. The immediate two below have the letter
           // 3. One above and one below have the letter
           if ((((*grid)[i][j+1]==letter) && ((*grid)[i][j+2]==letter)) || // check 2 right in the row
                    (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
                    (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) ){ // check 1 above and 1 below
               return 1;
           }
           else {
               return 0;
           }
       }
       else if (i==grid_size-2){ // if it is in the second to last row
           // It will violate the consecutive rule if
           // 1. The immediate two on the right have the letter
           // 2. The immediate two above have the letter
           // 3. One above and one below have the letter
           if ((((*grid)[i][j+1]==letter) && ((*grid)[i][j+2]==letter)) || // check 2 right
               (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
               (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) ){ // check 1 above and 1 below
               return 1;
           }
           else {
               return 0;
           }
       }
           //    No need to check if it is in the top left or bottom left, since that has already been checked
           //    It will violate the consecutive rule if
           //    1. The immediate two right cells have the letter
           //    2. The immediate two above cells have the letter
           //    3. The immediate two below cells have the letter
           //    4. One above and one below cells have the letter
       else {
           if ((((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
               (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
               (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
               (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter))) { // check 1 above and 1 below
               return 1;
           } else {
               return 0;
           }
       }
   }


   else if (j==grid_size-1){ // if it is the last column

       if (i==1){ // if it is in first row
           // It will violate the consecutive rule if
           // 1. The immediate two left have the letter
           // 2. The immediate two below have the letter
           // 3. One above and one below have the letter
           if ((((*grid)[i][j-1]==letter) && ((*grid)[i][j-2] == letter)) || // check 2 left
               (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
               (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) ){ // check 1 above and 1 below
               return 1;
           }
           else {
               return 0;
           }

       }

       else if (i==grid_size-2){ // if it is the second to last row
           // It will violate the consecutive rule if
           // 1. The immediate two right have the letter
           // 2. The immediate two above have the letter
           // 3. One above and one below
           if ((((*grid)[i][j-1]==letter) && ((*grid)[i][j-2] == letter)) || // check 2 left
               (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
               (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) ){ // check 1 above and 1 below
               return 1;
           }
           else {
               return 0;
           }
       }

        // No need to check if it is in the top right or bottom right, since that has already been checked
        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two above cells have the letter
        // 3. The immediate two below cells have the letter
        // 4. One above and one below cells have the letter
       else if ((((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
            (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
            (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
            (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) ){ // check 1 above and 1 below
           return 1;
       }
       else {
           return 0;
       }
   }

    //If its in the second row
   else if (i==1){

       if(j==1){ //its in 2nd row and 2nd column
            // It will violate the consecutive rule if
            // 1. The immediate two right cells have the letter
            // 2. The immediate two below cells have the letter
            // 3. One above and one below cells have the letter
            // 4. One right and one left cells have the letter
            if ((((*grid)[i][j+1]==letter) && ((*grid)[i][j+2]==letter)) || // check 2 right in the row
                    (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
                    (((*grid)[i-1][j] == letter) && ((*grid)[i+1][j] == letter)) || // check 1 above and 1 below
                    (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) ){ // check 1 right and 1 left
                return 1;
                }
            else {
                return 0;
            }
       }

       else if (j==grid_size-2){ // it's in 2nd last column and 2nd row

        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two below cells have the letter
        // 3. One above and one below cells have the letter
        // 4. One right and one left cells have the letter
            if ((((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                    (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
                    (((*grid)[i-1][j] == letter) && ((*grid)[i+1][j] == letter)) || // check 1 above and 1 below
                    (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) ){ // check 1 right and 1 left
                return 1;
            }
            else {
                return 0;
            }
       }
       else { // if is in the middle of the 2ndrow
        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two right cells have the letter
        // 3. One to the left and one to the right have the letter
        // 4. One above and one below cells have the letter
        // 5. The immediate two below cells have the letter
           if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                (((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
                (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) || // check 1 left and 1 right
                (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) || // check 1 above and 1 below
                (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) ){ // check 2 below
               return 1;
           }
           else {
               return 0;
           }
       }
   }

    //If its in the second last row
   else if (i==grid_size-2){
       if(j==1){ //its in 2nd column
        // It will violate the consecutive rule if
        // 1. The immediate two right cells have the letter
        // 2. The immediate two above cells have the letter
        // 3. One above and one below cells have the letter
        // 4. One right and one left cells have the letter
            if ( (((*grid)[i][j+1]==letter) && ((*grid)[i][j+2]==letter)) || // check 2 right in the row
                    (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
                    (((*grid)[i-1][j] == letter) && ((*grid)[i+1][j] == letter)) || // check 1 above and 1 below
                    (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) ){ // check 1 right and 1 left
                return 1;
            }
            else {
                return 0;
            }
       }

       else if (j==grid_size-2) {// Its in 2nd last column
        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two above cells have the letter
        // 3. One above and one below cells have the letter
        // 4. One right and one left cells have the letter
            if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                    (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
                    (((*grid)[i-1][j] == letter) && ((*grid)[i+1][j] == letter)) || // check 1 above and 1 below
                    (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) ){ // check 1 right and 1 left
                return 1;
            }
            else {
                return 0;
            }
       }
       else { // if is in the middle of the 2nd last row
        //    It will violate the consecutive rule if
        //    1. The immediate two left cells have the letter
        //    2. The immediate two right cells have the letter
        //    3. One to the left and one to the right have the letter
        //    4. One above and one below cells have the letter        
        //    5. The immediate two above cells have the letter
           if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                (((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
                (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter)) || // check 1 left and 1 right
                (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) || // check 1 above and 1 below
                (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) ){ // check 2 above
               return 1;
           }
           else {
               return 0;
           }
       }
   }

   else if (j==1){ // if it is the second column
    //    No need to check if this column is at the intersection of 2nd row or 2nd last row, since that has already been checked
    //    It will violate the consecutive rule if
    //    1. The immediate two right cells have the letter
    //    2. The immediate two above cells have the letter
    //    3. The immediate two below cells have the letter
    //    4. One above and one below cells have the letter
    //    5. One left and one right cells have the letter
       if ( (((*grid)[i][j+1]==letter) && ((*grid)[i][j+2]==letter)) || // check 2 right in the row
            (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
            (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
            (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) || // check 1 above and 1 below
            (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter))){  //check 1 left and 1 right
           return 1;
       }
       else {
           return 0;
       }
   }
   else if (j==grid_size-1){ // if it is the second last column

        // No need to check if this column is at the intersection of 2nd row or 2nd last row, since that has already been checked
        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two above cells have the letter
        // 3. The immediate two below cells have the letter
        // 4. One above and one below cells have the letter
        // 5. One left and one right cells have the letter
       if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
            (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
            (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
            (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) || // check 1 above and 1 below
            (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter))){  //check 1 left and 1 right
           return 1;
       }
       else {
           return 0;
       }
   }             

   else{
        // It will violate the consecutive rule if
        // 1. The immediate two left cells have the letter
        // 2. The immediate two right cells have the letter
        // 3. The immediate two below cells have the letter
        // 4. The immediate two above cells have the letter
        // 5. One above and one below cells have the letter
        // 6. One left and one right cells have the letter
        if ( (((*grid)[i][j-1]==letter) && ((*grid)[i][j-2]==letter)) || // check 2 left in the row
                (((*grid)[i][j+1] == letter) && ((*grid)[i][j+2] == letter)) || // check 2 right in the row
                (((*grid)[i+1][j] == letter) && ((*grid)[i+2][j] == letter)) || // check 2 below
                (((*grid)[i-1][j] == letter) && ((*grid)[i-2][j] == letter)) || // check 2 above
                (((*grid)[i+1][j] == letter) && ((*grid)[i-1][j] == letter)) || // check 1 above and 1 below
                (((*grid)[i][j-1] == letter) && ((*grid)[i][j+1] == letter))) {  //check 1 left and 1 right
            return 1;
        }
        else {
            return 0;
        }
    }
}

/*
 * Function: puzzle_solve
 * --------------------
 * Description:
 *      Recursive function for solving the grid
 *      General steps
 *          0. Check termination condition
 *          1. Fill out as many parts of the grid as possible
 *          2. Find the first cell with a ?
 *          3. Check to see if an X can be put in this cell
 *              3a. If yes, put the X there
 *              3b. Call the recursive function
 *          4. Check to see if an O can be put in this cell
 *              4a. If yes, put an O there
 *              4b. Call recursive function
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 *      int **count_X_col- 1D matrix containing the number of Xs in each column
 *      int **count_O_col- 1D matrix containing the number of Os in each column
 *      int **count_Q_col- 1D matrix containing the number of ?s in each column
 *      int **count_X_row- 1D matrix containing the number of Xs in each row
 *      int **count_O_row- 1D matrix containing the number of Os in each row
 *      int **count_Q_row- 1D matrix containing the number of ?s in each row
 * Returns:
 *      None
 */
void puzzle_solve(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int  **count_Q_col, int **count_X_row,
                  int **count_O_row, int **count_Q_row){

    int new_i; // new i location to put letter for recursion
    int new_j; // new j location to put letter for recursion
    int location_found = 0; // flag for determining if a ? has been found for recursion

    // Reset flags so that every time we call the recursive function, we go into the while loop at least once
    // Can also implement this with a do while loop, but it works right now the way it is
    // Don't want to mess with it
    twoConsecutiveRowFlag = 1;
    twoConsecutiveColFlag = 1;
    checkEitherSideRowFlag = 1;
    checkEitherSideColFlag = 1;
    equalXAndOFlag = 1;

    // Check for termination condition
    // The termination condition is that:
    // 1. The entire board has been filled out AND
    // 2. All rows are distinct
    // 3. All columns are distinct
    if ((checkEmpty(grid, grid_size) == 0)
    && (rowDistinctionCheck(grid, grid_size)==0)
    && (colDistinctionCheck(grid, grid_size)==0)){
        printGrid(grid, grid_size);
        exit(0);
    }

    // If we do not meet the termination condition, we need to continue solving the board
    else{

        // Fill out as much of the board as we can using the rules that we have
        while ((twoConsecutiveRowFlag == 1) || (twoConsecutiveColFlag == 1) || (checkEitherSideRowFlag == 1)
        || (checkEitherSideColFlag == 1) || (equalXAndOFlag == 1)){

            printGrid(grid, grid_size);
            printf("\n");

            /*
             * Loop through the entire board
             * Check if there are any cells with two consecutive same letters (horizontally)
             * If there are, put the other letter on either side of them
             * For example, if there exists a segment ? O O ? , we know it must be X O O X
             * Since there cannot be more than 2 consecutive of the same letter
             */
            twoConsecutiveRowFlag = 0;
            for (int i=0; i<grid_size; i++){
                for (int j=0; j<grid_size-1; j++){
                    twoConsecutiveRow(grid, grid_size, i, j);
                }
            }
            printGrid(grid, grid_size);
            printf("\n");

            /*
             * Loop through the entire board
             * Check if there are any cells with two consecutive same letters (vertically)
             * For example, if there exists a segment (left), we know it has to be (right)
             */
            twoConsecutiveColFlag = 0;
            for (int j=0; j<grid_size; j++){
                for (int i=0; i<grid_size-1; i++){
                    twoConsecutiveCol(grid, grid_size, i, j);
                }
            }
            printGrid(grid, grid_size);
            printf("\n");

            /*
             * Loop through the entire board
             * Check if there are any cells with an X or O on either side of it horizontally
             */
            checkEitherSideRowFlag = 0; // reset the flag
            for (int i=0; i<grid_size; i++){
                for (int j=0; j<grid_size; j++){
                    oneEitherSideRow(grid, grid_size, i, j);
                }
            }
            printGrid(grid, grid_size); // for debugging- take this out when done
            printf("\n");

            /*
             * Loop through the entire board
             * Check if there are any cells with an X or O on either side of it vertically
             */
            checkEitherSideColFlag = 0; // reset the flag
            for (int i=0; i<grid_size; i++){
                for (int j=0; j<grid_size; j++){
                    oneEitherSideCol(grid, grid_size, i, j);
                }
            }
            printGrid(grid, grid_size);
            printf("\n");

            /*
             * Loop through the entire board
             * Check if there are the same number of Xs and Os in each row and column
             */
            count(grid, grid_size, count_X_col, count_O_col, count_Q_col, count_X_row, count_O_row, count_Q_row);
            equalXAndOFlag = 0;
            equalXAndO(grid, grid_size, count_X_col, count_O_col, count_Q_col, count_X_row, count_O_row, count_Q_row);
            printGrid(grid, grid_size);
            printf("\n");
        }

        // Find first ? in the grid
        for (int i=0; i<grid_size; i++){
            for (int j=0; j<grid_size; j++){
                if (((*grid)[i][j] == '?') && (location_found == 0)){
                    new_i = i;
                    new_j = j;
                    location_found = 1;
                }
            }
        }

        // Count how many Xs, Os, and ?s are in each row and column
        count(grid, grid_size, count_X_col, count_O_col, count_Q_col, count_X_row, count_O_row, count_Q_row);

        // Check if X can go in the location
        // 1. The maximum number of X's have not already been placed in the row AND
        // 2. The maximum number of X's have not already been placed in the column AND
        // 3. Placing an X in the spot will not create 3X's in row
        // 4. Placing an X there will not violate the rule that all rows have to be distinct
        // 5. Placing an X there will not violate the rule that all columns have to be distinct
        if (((*count_X_row)[new_i] < grid_size/2)
            && ((*count_X_col)[new_j] < grid_size/2)
            && (twoConsecutiveCheck(grid, new_i, new_j, grid_size, 'X') == 0)){

            // Place an X in the location
            (*grid)[new_i][new_j] = 'X';
            printGrid(grid, grid_size);
            printf("\n");

            // Call recursive function

            puzzle_solve(grid, grid_size, count_X_col, count_O_col, count_Q_col, count_X_row, count_O_row, count_Q_row);

        }

        else if (((*count_O_row)[new_i] < grid_size/2)
                 && ((*count_O_col)[new_j] < grid_size/2)
                 && (twoConsecutiveCheck(grid, new_i, new_j, grid_size, 'O') == 0)) {

            // Place an X in the location
            (*grid)[new_i][new_j] = 'O';
            printGrid(grid, grid_size);
            printf("\n");

            // Call recursive function
            puzzle_solve(grid, grid_size, count_X_col, count_O_col, count_Q_col, count_X_row, count_O_row, count_Q_row);

        }
    }
    return ;
}

/*
 * Function: rowDistinctionCheck
 * --------------------
 * Description:
 *      Function to check if all rows are distinct (no two rows are the same)
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 * Returns:
 *      0 if the rows are distinct
 *      1 if not
 */
int rowDistinctionCheck(char ***grid,  int grid_size){

    //Taking each row and comparing with other rows
    // The ith row will be compared to the kth row
    // We will select components from row i and row k for each column j
    for (int i = 0; i < (grid_size); ++i){
        for (int k = 0; k < (grid_size) ; ++k){
            int temp = 1; // variable to keep track of comparison result
            if(i!=k){ //condition required so that we don't compare a row with itself
                for (int j = 0; j < (grid_size ) ; ++j){
                    if(grid[i][j] != grid[k][j]){ // if we get at least one non-matching element, we wont compare any further and select next row
                        temp = 0; // temp changes to zero so that we can know that the rows i and k are distinct
                        break ; // to break out of the for loop involving j
                    }
                }
            }

            if (temp == 1){ // rows i and k are same
                return 1;
            }
        }
    }
    return 0; // all rows are distinct, hence returning 0
}

/*
 * Function: colDistinctionCheck
 * --------------------
 * Description:
 *      Function to check if all columns are distinct (no two columns are the same)
 * Params:
 *      char ***grid- 2D matrix containing the tic tac toe board
 *      int grid_size- dimensions of the square grid matrix
 * Returns:
 *      0 if the columns are distinct
 *      1 if not
 */
int colDistinctionCheck(char ***grid,  int grid_size){

    // Taking each column and comparing with other rows
    // The jth column will be compared to the kth column
    // We will select components from column j and column k for each row i
    for (int j = 0; j < (grid_size); ++j){
        for (int k = 0; k < (grid_size) ; ++k){
            int temp = 1; // variable to keep track of comparison result
            if(j !=k){ // condition required so that we don't compare a column with itself
                for (int i = 0; i < (grid_size ) ; ++i){
                    if(grid[i][j] != grid[i][k]){ // if we get at least one non-matching element, we won't compare any further and select next column
                        temp = 0; // temp changes to zero so that we can know that the columns i and k are distinct
                        break ; // to break out of the for loop involving i
                    }
                }
            }

            if (temp == 1){ // columns j and k are same, so we break out of the function
                return 1;
            }

        }
    }

    return 0; // all columns are distinct, hence returning 0
}

//int CountCheck(char ***grid, int i, int j, int grid_size, char letter, int **count_X_col, int **count_O_col,
//                int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row ){
//
//    // Checking whether if we can place X in a row/column by checking it's count in that row/column
//    // If count is more than or equal to (grid_size)/2, then we cannot place the X
//    if(letter == 'X'){//When inserting X
//        if((*count_X_row)[i] > (grid_size/2) || (*count_X_col)[j] > (grid_size/2) ){//condition check
//            return 1;
//        }
//    }
//
//    //Checking whether if we can place O in a row/column by checking it's count in that row/column
//    //If count is more than or equal to (grid_size)/2, then we cannot place the O
//    if(letter == 'O'){//When inserting O
//        if((*count_O_row)[i] > (grid_size/2) || (*count_O_col)[j] > (grid_size/2) ){//condition check
//            return 1;
//        }
//    }
//}
