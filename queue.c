#include "queue.h"

Q *createQueue() // functie ce imi creeaza o coada
{
    Q *q;
    q = (Q*)malloc(sizeof(Q));
    if(q==NULL)
        return NULL;

    q->front = q->rear = NULL;
    return q;
}

void enQueue(Q *q, Country country) // functie ce imi adauga element in coada
{
    Country *newNode = (Country*)malloc(sizeof(Country));
    *newNode = country;
    newNode->next = NULL;

    //adaugam noul nod la finalul cozii
    if(q->rear==NULL) // daca nu avem niciun nod in coada
        q->rear = newNode;
    else
    {
        (q->rear)->next = newNode;
        q->rear= newNode;
    }
    if (q->front == NULL)
        q->front = q->rear; // daca e singurul element din coada
}

int isEmptyQueue(Q* queue)
{
    return(queue->front == NULL);
}


void deleteQueue(Q *queue) // functie ce sterge o coada
{
    Country *aux;
    while (!isEmptyQueue(queue))
    {
        aux = queue->front;
        queue->front = queue->front->next;
        free(aux);
    }
    queue->rear = NULL;;
}
