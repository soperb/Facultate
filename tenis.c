#include "general.h"
#include "files.h"
#include "lists.h"
#include "stack.h"
#include "queue.h"
#include "miscellaneous.h"
#include "BST.h"



int main(int argc, char* argv[])
{
    Country *head=NULL, *stackTop=NULL, *winnerStack=NULL;

    Q *q;

    root* BST = NULL;

    Player *player1 = NULL, *player2 = NULL;

    int noCountries;

    char *tasks=cerinte(&player1,&player2,argv); // functia ce citeste cerintele ce trebuie efectuate

    if(tasks[1] == '0' && tasks[0] == '1') // pentru cerinta 1, bagam tarile in lista dupa care printam lista
    {
        FiletoList(&head,&noCountries,argv);
        printList(head,argv);
    }
    else if(tasks[1] == '1' ) // pentru cerinta 2 intai eliminam tarile necesare, abia apoi printam lista finala
    {
        FiletoList(&head,&noCountries,argv);
        removeCountry(head,&noCountries);
        printList(head,argv);
    }

    //pentru cerinta 3
    if(tasks[2] == '1')
    {
        stackTop = ListToStack(head,&stackTop); // bagam tarile din lista intr-un stack
        stackTop->prev->next = NULL;
        allGames(stackTop,q,&winnerStack,&noCountries,&BST,argv); //realizam meciurile intre toate tarile
    }
    //pentru cerinta 4
    if(tasks[3] == '1')
        printClasament(BST,argv);

    if(tasks[4] == '1')
        betweenPlayers(BST,player1,player2,argv);

    return 0;
}

