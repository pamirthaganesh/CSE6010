#include <stdio.h>
#include <stdlib.h>
#include "LLQueue.h"

// Definition of Node Data Structure
        struct Node{
                double data;
                struct Node *next;
            }*head = NULL,*tail = NULL;

// Function to create Linked link using Node data structure
// Function returns a LLQueue
LLQueue *LLQ_create(){

// Defining Linked List(LL) from the  Node data structure
// where head is the pointer to first element of LL
// tail is the pointer to last element of LL
    struct Node { 
        double key; 
        struct Node* next; 
    }*head = NULL, *tail = NULL; 
        struct LLQueue { 
        struct Node *head;
        struct Node *tail; 
    }; 
// Initializing head node pointer to a specific location
    head = (struct Node*)malloc(sizeof(struct Node));
// Checking for system memory overflow error condition
    if(head == NULL){
        printf("Unable to allocate due to lack of memory.");
    }  
// Struct function to create new linked list node. 
    else{
    struct Node* newNode(double data) 
    { 
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); 
        temp->key = data; 
        temp->next = NULL; 
        return temp; 
    } 
  
// Struct function  to create an empty Linked List Queue (LLQ) from LL
    struct LLQueue *LLQ = (struct LLQueue*)malloc(sizeof(struct LLQueue)); 
    LLQ->head = NULL;
    LLQ->tail = NULL; 
    }   
} 
// Function to insert data into LLQ
// Function returns a LLQueue element (double type data)
// Enqueue:
double LLQ_insert(LLQueue *LLQ, double k){    
// Creating a new LL node 
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node)); 
    temp->data = k;
    temp->next = NULL;
// Initializig the head pointer
    if(head == NULL){
        head = temp;
        tail =temp;
    }
// Initializig the tail pointer
    else{
        tail -> next = temp;
        tail = temp;
    }     
       printf("\033[1;32m");
       printf("\nInsertion is good \n"); 
       printf("\033[0m;");
     
 
} 
// Function to delete the first element from LLQ
// Function returns a LLQueue element (double type data)
// Dequeue:
double LLQ_delete(LLQueue *LLQ){
   if(head == NULL)
   {
      printf("\033[1;31m");
	  printf("\n Error! Queue is Empty!!!\n");
      printf("\033[0m;");
    }
   else{
      struct Node *temp = head;
      head = head -> next;
      printf("\033[1;31m");
	  printf("\nDeleted element: %f\n", temp->data);
      printf("\033[0m;");
      free(temp);
   }
}
// Function to count the total elements of  LLQ  
// Function returns the  element counts(positive integer) of LLQ
unsigned int LLQ_count(LLQueue* LLQ){
    int count = 0;
    struct Node *temp;
    temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}
// Function to print  elements of  LLQ  
// Function returns NULL
void LLQ_print(LLQueue *LLQ){
   if(head == NULL){
         printf("\033[1;31m");
      printf("\n Queue is Empty!!!\n");
      printf("\033[0m;");
   }
   else{
      struct Node *temp = head;
      while(temp->next != NULL){
      printf("\033[1;32m");
	  printf("%f--->",temp->data);
      printf("\033[0m;");
	  temp = temp -> next;
      }
      printf("\033[1;32m");
      printf("%f--->NULL\n",temp->data);
      printf("\033[0m;");
   }
}
// Function to search for a given element's availability inside LLQ  
// Function returns postion of the found element
double *LLQ_Search(LLQueue *LLQ, double data)
{
    int count = 0;
    struct Node *temp;
    temp = head;
    double *position;
// Condition to check for the element's availability at head node
    if(head->data == data){
        position = &(head->data); 
      printf("\033[1;32m");
	  printf(" \n The  value %0.3f is present in the begining of the LLQueue, at a position of %d\n",data, count);
      printf("\033[0m;");       
        
        return position;
    }   
// Condition to check for the element's availability at tail node
    if(tail->data == data){
        count = LLQ_count(LLQ);
        position = &(tail->data);
        printf("\033[1;32m");
	    printf("\n The  value %0.3f is present in the end of the LLQueue, at a position of %d\n",data, (count-1));
        printf("\033[0m;"); 
        
        return position;
    }
// Condition to check for the element's availability in middle section of LLQ
    while(temp != NULL)
    {
        count++;
        if(temp->data == data){
            position = &(temp->data) ;

        printf("\033[1;32m");
	    printf("  \n The  value  %0.3f  is present in the middle of the LLQueue, at a position of %d\n",data, (count-1));
        printf("\033[0m;"); 
            
            return position ;
        }
        temp = temp->next ;
    }
// Informing that element is not available in LLQ
    printf("\nError !! %0.3f is not present in current LLQueue\n", data);
    position = NULL ;
    return position;
}

double LLQ_Maximum(LLQueue *LLQ){
    double max=0;
//Checking if LLQ is empty
   if(head == NULL){
        printf("\033[1;31m");
	    printf("\nError!Queue is Empty!!!\n");
        printf("\033[0m;"); 
   }
   else{
      struct Node *temp = head;
      max=temp->data;
 // checking all data elements except last
      while(temp->next != NULL){
	  if(temp->data>max){
          max=temp->data;
        //   printf("\n%f\n",max);
      }
	 temp = temp -> next;
      }
      
 // checking last element
    if(temp->data>max){
        max=temp->data;
        // printf("\n%f\n",max);
    }   
        printf("\033[1;35m");
        printf("\n Max value is %f\n",max);
        printf("\033[0m;");

   }
   return max;
}

// Function to find the smallest element value inside LLQ  
// Function returns smallest element
double LLQ_Minimum(LLQueue *LLQ){
    double min=0;
//Checking if LLQ is empty
   if(head == NULL){
        printf("\033[1;31m");
	    printf("\nError!Queue is Empty!!!\n");
        printf("\033[0m;"); 
   }
   else{
      struct Node *temp = head;
      min=temp->data;
 // checking all data elements except last
      while(temp->next != NULL){
	  if(temp->data<min){
          min=temp->data;
        //   printf("\n%f\n",min);
      }
	 temp = temp -> next;
      }
      
 // checking last element
    if(temp->data<min){
        min=temp->data;
        // printf("\n%f\n",min);
    }   
        printf("\033[1;35m");
        printf("\n Min value is %f\n",min);
        printf("\033[0m;");

   }
   return min;
}
// Function to free LLQ completely 
// Function returns Null
void LLQ_free(LLQueue *LLQ)
{
    struct Node *temp;
// Checking if LLQ is empty
    if(head == NULL){
        printf("\033[1;31m");
	    printf("\nError!Queue is Empty!!!\n");
        printf("\033[0m;"); 
        return;
    }
// Free the memory complete
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }    
        printf("\033[1;31m");
        printf("\n Now deleted all LLQ elements\n");
        printf("\033[0m;"); 

}
