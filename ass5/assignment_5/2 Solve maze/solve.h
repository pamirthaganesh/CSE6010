/*
 * CSE 6010 Assignment 5
 * Created by Athulya Ram
 * Last edited on 17 October 2020
 */

#ifndef SOLVE_H
#define SOLVE_H

#define SIZE 23104 //152*152 maximum possible size of the graph.

struct LLNode {
  int vertex;
  struct LLNode* next;
};

struct LLQueue {
  int LLNode[SIZE];
  int head;
  int tail;
};

struct LLGraph {
  int numVertices;
  struct LLNode** adjLists;
  int* visited;
};

struct LLNode* createNode(int v);
struct LLGraph* createGraph(int vertices);
void addEdge(struct LLGraph* graph, int src, int dest);
struct LLQueue* createQueue();
int isEmpty(struct LLQueue* q);
void enqueue(struct LLQueue* q, int value, int size);
int LLQ_delete(struct LLQueue* q);
int is_present(int a[], int value, int size);
int FindIndex(const int a[], int size, int value );
void print_loop(int path[], int startVertex, int size);
void bfs(struct LLGraph* graph, int startVertex, int endVertex, int size);



#endif
