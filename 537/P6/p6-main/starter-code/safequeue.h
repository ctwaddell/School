#include <pthread.h>

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

typedef struct _node
{
    int data;
    int priority;
} Node;

typedef struct _queue
{
    Node* nodes;
    int maxsize;
    int size;
    pthread_mutex_t lock;
} PriorityQueue;

int initializeQueue(PriorityQueue* queue, int maxsize);

int enqueue(PriorityQueue* queue, Node node);

Node* dequeue(PriorityQueue* queue);



#endif