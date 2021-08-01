CSE 6010 Assignment #6
Team 1) Amirtha Ganesh Pugazhendhi 2) Athulya Ram Sreedharan Nair 

Program description:
This program will Generate a Ring Network and Simulate a Epidemic model based on user-defined parameters.

1) Operating system : Windows 10
2) Compiler used    : GCC
3) Platform/Editor  : VS Code

Program writing and compilation steps:

Network Generation and Epidemic Model:

1) Open the VS code 
2) Create the 6 program files and save the code as "network.c","network.h", "model.c","model.h" ,"main.c","makefile"
3) Develop code based on problem statement and save again (ctrl + S)
4) Go to TERMINAL(CMD) and choose the  wsl (Windows Subsystem for Linux) option drop down.
5) Using the terminal, set the current working directory to path where program files  is located
6) Type "make" to generate executive file "main.exe"
7) Type the command "./main" to run the executable assignment program
8) The program will ask the user to enter 3 important parameters:
 1) The number of nieghbors for the each villager (less than 500)
 2) The probability of substituting a nearest-neighbor edge with a different edge
 3) The probability of disconnecting an edge once a person becomes infected

Expected output:

Terminal output with showing the following  model statistics 
• The maximum number of infected individuals in a single iteration.
• The iteration number at which the maximum number of infected individuals occurs.
• The sum of the number of currently infected and recovered individuals after the last iteration.