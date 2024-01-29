#include "safequeue.h"
#include <pthread.h>
#include <stdlib.h>

int initializeQueue(PriorityQueue* queue, int maxsize)
{
    queue->nodes = (Node*)malloc(maxsize * sizeof(Node));
    queue->size = 0;
    queue->maxsize = maxsize;
    for(int i = 0; i < queue->maxsize; i++)
    {
        queue->nodes[i].data = 0;
        queue->nodes[i].priority = 0;
    }
    pthread_mutex_init(&queue->lock, NULL);
    return 0;
}

int enqueue(PriorityQueue* queue, Node node)
{
    //probably needs some availability checking stuff but should work for now
    pthread_mutex_lock(&queue->lock);
    for(int i = 0; i < queue->maxsize; i++)
    {
        if(queue->nodes[i].data == 0)
        {
            queue->nodes[i] = node;
        }
    }
    queue->size++;
    pthread_mutex_unlock(&queue->lock);
    return 0;
}

Node* dequeue(PriorityQueue* queue)
{
    pthread_mutex_lock(&queue->lock);
    int index = -1;
    int max = -1;
    for(int i = 0; i < queue->maxsize; i++)
    {
        if(queue->nodes[i].priority > max)
        {
            max = queue->nodes[i].priority;
            index = i;
        }
    }
    Node* returnNode = (Node*)malloc(sizeof(Node));
    returnNode->data = queue->nodes[index].data;
    queue->nodes[index].data = 0;
    returnNode->priority = max;
    queue->nodes[index].priority = 0;
    queue->size--;
    pthread_mutex_unlock(&queue->lock);
    
    return returnNode;
}