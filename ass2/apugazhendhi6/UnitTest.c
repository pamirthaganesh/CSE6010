#include <stdio.h>
#include <stdlib.h>
#include "LLQueue.h"

//  Unit Testing 


int main()
{

printf("\n\n ###############################################################################################");
printf("\n Welcome to CSE 6010 : Computational Problem Solving\n");
printf("\n Fall 2020 \n");
printf("\n Assignment 2 :");
printf(" Implementation of Linked List Queue and perform Unit testing \n");
printf(" ###############################################################################################\n");
printf("\033[1;31m");
printf("\n\n ###############################################################################################");
printf("\n Section A - Automated Unit Testing\n");
printf(" ###############################################################################################");
printf(" \n Welcome to the Automated Unit testing module \n");
printf("\033[0m;");
     
    int total;
    double  m, element=1;

//Test Case 1: Creating  an Empty LLQueue
    printf("\033[1;33m");
    printf("\nCase 1: Creating  an Empty LLQueue \n");
    printf("\033[0m;");
    printf("\033[1;32m");
    LLQueue* LLQ = LLQ_create();
    printf("\n LLQueue is created!\n");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\n LLQ :\n");
    printf("\033[0m;");
    printf("\033[1;31m");
    LLQ_print(LLQ);
    printf("\033[0m;");
    

//Test Case 2: Inserting the first element into an empty  LLQ
    printf("\033[1;33m");
    printf("\n Case 2: Inserting the first element into an empty LLQ \n");
    printf("\033[0m;");
    LLQ_insert(LLQ, element);
    printf("\033[1;32m");
    printf("\n LLQ :\n");
     printf("\033[0m;");
    LLQ_print(LLQ);
    total = LLQ_count(LLQ); 
    
    printf("\033[1;33m");
    printf("\n Total items in LLQ  are %d.\n", total);
    printf("\033[0m;");
    
// Adding additonally 4 more elements into LLQ
   printf("\033[1;36m");
   printf("\n2nd Member 25 inserted in LLQueue\n");
     printf("\033[0m;");
   LLQ_insert(LLQ, 25);
   printf("\033[1;34m");
   printf("3rd Member 3 inserted in LLQueue\n");
   printf("\033[0m;");
   LLQ_insert(LLQ, 3);
   printf("\033[1;35m");
   printf("4th Member  -45 inserted in LLQueue\n");
   printf("\033[0m;");
   LLQ_insert(LLQ, -45);
   printf("\033[1;36m");
   printf("5th Member 500 inserted in LLQueue\n");
   printf("\033[0m;");
   LLQ_insert(LLQ, 500);   
//Test Case 3: Inserting an item into a queue containing at least 4 elements.
   element = 201; 
   printf("\033[1;33m");
   printf("\nCase 3: Inserting an item into a queue containing at least 4 elements\n");
   total = LLQ_count(LLQ); 
   printf(" \n Total elements in LLQ is %d \n", total);
   printf(" \n Inserting the %0.3f  into the LLQ \n", element);

   printf("\033[0m;");
   LLQ_insert(LLQ, element);
    printf("\033[1;32m");
    printf("\033[0m;");    
    printf("\033[1;32m");
    printf("\n LLQ :\n");
    LLQ_print(LLQ);
    printf("\033[0m;");
    total = LLQ_count(LLQ); 
    printf("\033[0m;");
    printf("\033[1;33m");
    printf(" \n After insertion, total elements in LLQ is %d \n", total);
    printf("\033[0m;");


    
//Test Case 4: Returning the maximum element of the LLQ with alteast 4 elements.
    printf("\033[1;33m");
    printf("\nCase 4: Returning the maximum element of the LLQ with alteast 4 elements");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\033[0m;");
    printf("\033[1;32m");
    printf("\n LLQ :\n");
    LLQ_print(LLQ); 
    printf("\033[0m;");
    printf("\033[1;35m");  
    LLQ_Maximum(LLQ);  
    printf("\033[0m;");

//Test Case 5: Returning the minimum element of the LLQ with alteast 4 elements.
    printf("\033[1;33m");
    printf("\nCase 5: Returning the minimum element of the LLQ with alteast 4 elements");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\033[0m;");
    printf("\033[1;32m");
    printf("\n LLQ :\n");
    LLQ_print(LLQ); 
    printf("\033[0m;"); 
    printf("\033[1;34m"); 
    LLQ_Minimum(LLQ);  
    printf("\033[0m;");

//Test Case 6: Searching for an item present at the beginning, middle, and end of the LLQ with alteast 4 elements.
    printf("\033[1;33m");
    printf("\nCase 6: Searching for an item present at the beginning, middle, and end of the LLQ with alteast 4 elements \n");
    printf("\033[0m;");
    printf("\033[1;32m");
    printf("\n LLQ :\n");
    LLQ_print(LLQ);
    printf("\033[0m;");
    printf("\033[1;33m");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\033[0m;");
    printf("\033[1;33m");
    printf("\n Testing the for the Begining, End  and Middle cases\n ");
    printf("\033[0m;");
    printf("\033[1;34m");
    printf("\n 1) Testing the for the Begining \n");
    printf("\033[0m;");
    printf("\033[1;32m");
    LLQ_Search(LLQ, 1);
    printf("\033[0m;");
    printf("\033[1;35m");
    printf("\n 2) Testing the for the Middle \n"); 
    printf("\033[0m;");  
    printf("\033[1;32m"); 
    LLQ_Search(LLQ, 25);
    printf("\033[0m;");
    printf("\033[1;36m");
    printf("\n 3) Testing the for the End \n");
    printf("\033[0m;");
    printf("\033[1;32m");
    LLQ_Search(LLQ, 201);
    printf("\033[0m;");

    //Test Case 7: Searching for an item that is not present in LLQ with alteast 4 elements.
    printf("\033[1;33m");
    printf("\nCase 6: Searching for an item that is not present in LLQ with alteast 4 elements. \n");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\033[0m;");
    printf("\033[1;32m");
    printf("\n LLQ :\n");
    LLQ_print(LLQ);
    printf("\033[0m;"); 
    //Searching for an unpresent element in LLQ
    element = 2343; 
    printf("\033[1;31m");
    LLQ_Search(LLQ, element);
    printf("\033[0m;");

    //Test Case 8: Deleting all of the items in a queue containing at least 4 elements to completely free LLQ.
    printf("\033[1;33m");
    printf("\nCase 8: Deleting all of the items in a queue containing at least 4 elements to completely free LLQ.\n");
    total = LLQ_count(LLQ); 
    printf(" \n Total elements in LLQ is %d \n", total);
    printf("\033[0m;");   
    LLQ_free(LLQ);
    printf("\033[1;32m");
    printf("\n LLQ :\n");   
    LLQ_print(LLQ);
    printf("\033[0m;");

    //Test Case 9: Deleting an item from an empty queue (error case). 
    printf("\033[1;33m");
    printf("\nCase 9: Trying to delete an item from an empty queue (error case)\n");
    printf("\033[0m;");
    printf("\033[1;31m");
    LLQ_delete(LLQ);
    total = LLQ_count(LLQ); 
    printf("\033[0m;");
    printf("\033[1;33m");
    printf("\nTotal number of element(s) in queue is/are %d.\n", total);
    printf("\033[0m;");
printf("\033[1;33m");
printf("\n Scroll up to see the results of automated testing \n");
printf("\033[0m;");
printf("\033[1;31m");
printf("\n\n ###############################################################################################");
printf("\n Section B - Interactive Unit Testing\n");
printf(" ###############################################################################################");
printf("\033[0m;");

// Interactive Unit Testing 
    int choice;
    double value;
    printf("\033[1;33m");

    printf(" \n Welcome to the Interactive Unit testing module \n");
    printf("\033[0m;");
   while(1){
      printf("\033[1;35m");
      printf("\n*** MENU ***\n");
      printf("\033[0m;");
      printf("\033[1;36m");
      printf("1. Create a New Queue\n2. Insert an element in queue\n3. Delete oldest element from Queue\n4. Count number of items in queue\n5. Print all elements present in queue\n6. Search of value in LLQ \n7. Max value LLQ \n8. Min value of LLQ \n9. Clear all LLQ memory \n10. Exit \n");
      printf("\033[0m;");
      printf("\033[1;32m");
      printf("Enter your choice: ");
      printf("\033[0m;");
      scanf("%d",&choice);
      switch(choice){
     case 1: LLQ_create();break;
	  case 2: printf("\033[1;34m");
             printf("Enter the value to be insert: ");
             printf("\033[0m;");
		       scanf("%lf", &value);
		       LLQ_insert(LLQ, value);
		       break;
	  case 3: LLQ_delete(LLQ); break;
     case 4: total = LLQ_count(LLQ); 
             printf("\033[1;35m");
             printf("\nTotal number of elements are %d\n", total);
             printf("\033[0m;");
             break;
	  case 5:  LLQ_print(LLQ); break;

	  case 6: printf("\033[1;34m");
             printf("Enter the value to be be checked: ");
             printf("\033[0m;");
		       scanf("%lf", &value); 
             LLQ_Search(LLQ, value); break;
     case 7: LLQ_Maximum(LLQ); break;
     case 8: LLQ_Minimum(LLQ); break;
     case 9: LLQ_free(LLQ); break;
     case 10: break;exit(0);

	 default: printf("\033[1;31m");
             printf("\nWrong selection!!! Please try again!!!\n");
             printf("\033[0m;");
      }
   };
   
}

   
