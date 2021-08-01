#ifndef LLQueue_H
#define LLQueue_H

typedef struct LLQueue
{
    double data;
}LLQueue;

LLQueue *LLQ_create();

double LLQ_insert(LLQueue *LLQ, double k) ;

double LLQ_delete(LLQueue *LLQ);

void LLQ_print(LLQueue *LLQ);

unsigned int LLQ_count(LLQueue *LLQ);

double *LLQ_Search(LLQueue *LLQ, double data);

double LLQ_Maximum(LLQueue *LLQ);

double LLQ_Minimum(LLQueue *LLQ);

void LLQ_free(LLQueue *LLQ);


#endif
