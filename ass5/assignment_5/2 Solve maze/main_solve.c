/*
 * CSE 6010 Assignment 5
 * Created by Athulya Ram
 * Last edited on 17 October 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "solve.h"

#define USAGE_STRING "./<exe name> Generated_Maze_File.txt"
#define LINEBUF_SIZE 2048
static char line_buffer[LINEBUF_SIZE];

int main(int argc, char const *argv[]) {
    
    // First, check if the correct number of arguments are passed. 
    if(argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        fprintf(stderr, "%s\n", USAGE_STRING);
        return 1;
    }

    // Read the file passed into the program.
    FILE *f = fopen(argv[1],"r");

    // If the file could not be opened, show an error.
    if(f == NULL) {
        fprintf(stderr, "Could not open the file '%s'.\n", argv[1]);
        perror("Error");
        return -1;
    }

    // Define variable for number of rows, number of columns, start-vertex, and finish-vertex.
    int nrow, ncol, startVertex, endVertex;

    // Scan the first two lines of text file and store the values into the appropriate variable.
    if(fscanf(f, "%d%d", &nrow, &ncol) != 2)
        exit(1);
    if(fscanf(f, "%d%d", &startVertex, &endVertex) != 2)
        exit(1);
    
    // Define the size of the graph as total number of vertices = number of columns * number of rows 
    int size = nrow*ncol;
    // Create a graph of this size.
    struct LLGraph* graph = createGraph(size);

    // Loop through all the lines.
    for (int ii=0; ii<size+1;ii++) {
        // Read each line into a buffer line.
        char *line = fgets(line_buffer, LINEBUF_SIZE, f);
        // If there is no next line, return -1.
        if(line == NULL) {
            return -1;
        }
        // Define the length of the line.
        size_t line_length = strlen(line);
        // Get a pointer for each element of the line.
        char *endptr = line;
        // Loop to the end of the line.
        while(*endptr != '\0') {   // Skip whitespace.
            while(isspace(*endptr) && (*endptr != '\n')) {
                endptr++;
            }

            // If we reach a newline or a \0, we have reached the end of the line. Go to the next line.
            if((*endptr == '\n') || (*endptr == '\0')) {
                break;
            }
            char *next_num = endptr;
            errno = 0;
            // Get the connected vertex from the line.
            int edge = strtol(next_num, &endptr, 10);
            // Add an edge from the line to the connected vertex found.
            addEdge(graph, ii-1, edge);
            // For testing purposes, uncomment this line.
            // This is to verify that the edges added are correct (compare with text file).
            /*
            printf("Edge added: %d, %d\n", ii-1, edge);
            */
        }
    }
    // After the text file is read and the graph is created, close the file.
    fclose(f);
    // Run the BFS algorithm to find the path from startVertex to the endVertex
    // on a given graph with number of vertices = size.
    bfs(graph, startVertex, endVertex, size);
    return 0;
}