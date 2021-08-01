CSE 6010 Assignment #4
Team 1)Sarah Dongyun Bi 2)Saurabh Parimal Doodhwala 3) Amirtha Ganesh Pugazhendhi 

Program description:
This program will fill out an NxN tic-tac-toe board, where N is an even number. The algorithm will follow specific rules for filling out the board, as defined below: 

1. Each row and each column must have the same number of X's as the number of O's 
2. No more than two X’s or O’s can appear in succession in any row or column.3. Each row is different from each other row and each column is different from each other column.

The program will be given an input of the board size, with some of the cells of the grid already marked with X and O. The program will fill out the rest of the board in accordance to the rules. 

For Linux:

Compiler and operating system: 
The compiler used was Clang Version 11.0.3 
This code was written on a computer with macOS Catalina Version 10.15.6 and tested in Linux Darwin 19.5.0

How to compile and run (in Linux): 
1. Navigate to the directory containing the files main.c, tictactoe.c, and tictactoe.h 
2. Ensure that the file titled "makefile" is also in the same directory
3. Type the following command to compile the program: make
4. Type the following command to run the program: ./main source_file_directory 
	where
	source_file_directory is the filepath of the starting grid  
5. The program will output the results of each iteration of the algorithm 

For Windows:

1) Operating system : Windows 10
2) compiler used    : GCC
3) Platform/Editor  : VS Code

Program writing and compilation steps:

1) Open the VS code 
2) Create a 5 new program files and save the code as "tictactoe.c","tictactoe.h", "makefile", "myboolean.h","main.c"
3) Develop code based on problem statement and save again (ctrl + S)
4) Go to TERMINAL and choose the  wsl (Windows Subsystem for Linux) option drop down.
5) Using the terminal, set the current working directory to path where program files  is located
6) Type "make" to execute file "main"
7) Type the command "./main puzzle.txt" to run the executable assignment program
8) The program will output the results of each iteration of the algorithm 

Expected output:

1) Assigment details
2) Topic of the program
3) Puzzle Grid

