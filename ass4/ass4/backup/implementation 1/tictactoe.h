//
// Created by Sarah Bi on 9/21/20.
//

#ifndef ASSIGNMENT4_TICTACTOE_H
#define ASSIGNMENT4_TICTACTOE_H

int checkEmpty(char ***grid, int grid_size);
void twoConsecutiveRow(char ***grid, int grid_size, int i, int j);
void twoConsecutiveCol(char ***grid, int grid_size, int i, int j);
void oneEitherSideRow(char ***grid, int grid_size, int i, int j);
void oneEitherSideCol(char ***grid, int grid_size, int i, int j);
void equalXAndO(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row);
void count(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row );
void printGrid(char ***grid, int grid_size);
void puzzle_solve(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col,
                  int **count_X_row, int **count_O_row, int **count_Q_row);
int rowDistinctionCheck(char ***grid,  int grid_size);
int colDistinctionCheck(char ***grid,  int grid_size);
int twoConsecutiveCheck (char ***grid, int i, int j, int grid_size, char letter);
//int CountCheck(char ***grid, int i, int j, int grid_size, char letter, int **count_X_col, int **count_O_col,
//                int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row );

#endif //ASSIGNMENT4_TICTACTOE_H
