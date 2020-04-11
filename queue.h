#ifndef QUEUE_H_
#define QUEUE_H_
#include "general.h"

//structura pentru coada
typedef struct Queue
{
    Country *front;
    Country *rear;
} Q;

Q *createQueue(); // functie ce imi creeaza o coada
void enQueue(Q *q, Country country); // functie ce imi adauga element in coada
int isEmptyQueue(Q* queue); // functie pentru verificare daca e goala sau plina coada
void deleteQueue(Q *queue); // functie ce sterge o coada
#endif
