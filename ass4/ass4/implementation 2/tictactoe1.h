//
// Developed by the team Sarah Bi , Amirtha Ganesh , Surabh  on 9/26/20.
//

#ifndef ASSIGNMENT4_TICTACTOE_H
#define ASSIGNMENT4_TICTACTOE_H

int check_for_empty_cells(char ***grid, int grid_size);
void check_for_2_similar_char_in_row(char ***grid, int grid_size, int i, int j);
void check_for_2_similar_char_in_col(char ***grid, int grid_size, int i, int j);
void check_for_blank_between_2_similar_char_row(char ***grid, int grid_size, int i, int j);
void check_for_blank_between_2_similar_char_col(char ***grid, int grid_size, int i, int j);
void check_for_equal_no_of_character(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row);
void count(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col, int **count_X_row, int **count_O_row, int **count_Q_row );
void print_the_grid(char ***grid, int grid_size);
int check_for_row_duplicate(char ***grid,  int grid_size);
int check_for_col_duplicate(char ***grid,  int grid_size);
int check_for_possible_violation (char ***grid, int i, int j, int grid_size, char letter);
// Total puzzle solver helper function
void solve_the_puzzle(char ***grid, int grid_size, int **count_X_col, int **count_O_col, int **count_Q_col,
                  int **count_X_row, int **count_O_row, int **count_Q_row);

#endif //ASSIGNMENT4_TICTACTOE_H
