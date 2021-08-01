Note: 

1) Operating system : Windows 10 with WSL(Windows Subsystem for Linux)
2) Compiler used    : GCC
3) Platform/Editor  : VS Code

Program writing and compilation steps:

1) Open the VS code 
2) Create a new file and save the code as "rand_norm_kmeans_cluster.c". 
3) Develop code based on problem statement and save again (ctrl + S)
4) Now, place the input text files "WineData_2col.text" and "WineData_3col.text" in the current woring directory.
5) Go to TERMINAL and choose the  WSL (Windows Subsystem for Linux) option drop down.
6) Using the terminal, set the current working directory to the path where "rand_norm_kmeans_cluster.c" program is located
7) Type this following command within the quotes "rand_norm_kmeans_cluster.c -lm -o kmeans"  to compile the program as "kmeans"
8) Type the command "ls -al kmeans" to view or list the compiled program
9) Test 1st sample data by using typing the command "./kmeans WineData_2col.txt 6" to execute the code.
10)Test 2nd sample data by using typing the command "./kmeans WineData_3col.txt 10" to execute the code.
11) Optional command type "./kmeans WineData_3col.txt 10 >outfile.txt"


Expected output:

1) Assigment details
2) Topic of the program
3) A brief summary about the k-means cluster and its centroid.
4) Output printing the data set against their corresponding cluster number.
5) It can generate an output textfile if the optional output command typed.



