CSE 6010 Assignment #5
Team 1) Amirtha Ganesh Pugazhendhi 2) Athulya Ram Sreedharan Nair 

Program description:
This program will Generate and Solve an NxM Maze.

1) Operating system : Windows 10
2) compiler used    : GCC
3) Platform/Editor  : VS Code

Program writing and compilation steps:

MAZE Generation:

1) Open the VS code 
2) Create a 4 new program files and save the code as "generate.c","generate.h", "main_generate.c" ,"makefile"
3) Develop code based on problem statement and save again (ctrl + S)
4) Go to TERMINAL(CMD) and choose the  wsl (Windows Subsystem for Linux) option drop down.
5) Using the terminal, set the current working directory to path where program files  is located
6) Type "make" to generate executive file "main_generate.exe"
7) Type the command "./main_generate.exe row col rowxcol.txt" to run the executable assignment program
8) The program will out a text with maze dimension, start and end node ,and adjacency list of all nodes.

Expected output:

A Text file representing graph nodes with adjacency List.

MAZE Solution:
1) Open the VS code 
2) Create a 4 new program files and save the code as "solve.c","solve.h", "main_solve.c" ,"makefile"
3) Develop code based on problem statement and save again (ctrl + S)
4) Go to TERMINAL(CMD) and choose the  wsl (Windows Subsystem for Linux) option drop down.
5) Using the terminal, set the current working directory to path where program files  is located
6) Type "make" to generate executive file "main_solve.exe"
7) Type the command "./main_solve rowxcol.txt" to run the executable assignment program
8) The program will output the solution path to the maze.
Expected output:

Terminal output with solution path for the input maze(Graph).