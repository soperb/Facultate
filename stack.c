#include "stack.h"

void push(Country **top,Country added) // functie de adaugat un element in varful stivei
{
    Country *newNode = (Country*)malloc(sizeof(Country));
    (*newNode) = added;
    newNode->next = (*top);
    (*top) = newNode;

}

int isEmpty(Country *top) // functie ce verifica daca e plina/goala stiva
{
    return top==NULL;
}

Country* ListToStack(Country* head, Country** top) // functie de pus elementele din lista in stiva
{
    Country *traveler = head->next;
    while(traveler != head)
    {
        push(top,(*traveler));
        traveler = traveler->next;
    }
    return (*top);
}


void delTop(Country** top, int *remCountries) // functie de sters elementul din varful stivei, modific si numarul tarilor.
                                               //ex: cand pun tarile din stiva initiala in stiva winners
{
    if(*remCountries == 0)
        (*top) = NULL;
    else
    {
        Country *temp = (*top);
        Country *aux = temp->next;

        if(aux != NULL)
            (*top) = (*top)->next;
        else
            (*top) = NULL;

        free(temp);
        (*remCountries)--;
    }

}

void delTopnoCountries(Country** top, int remCountries) // functie de sters elementul din varful stivei. nu modific numarul de tari
                                                         //(ex: cand pun tarile din winners in stiva initiala)
{
    if(remCountries == 0)
        (*top) = NULL;
    else
    {
        Country *temp = (*top);
        Country *aux = temp->next;

        if(aux != NULL)
            (*top) = (*top)->next;
        else
            (*top) = NULL;

        free(temp);
    }

}

//functie ce imi ia tarile din stiva winners si le pune inapoi in stiva initiala
void winnertoInit(Country **initTop,Country **winnerTop, int noCountries)
{
    while(!isEmpty(*winnerTop))
    {
        push(&(*initTop),*(*winnerTop));
        delTopnoCountries(winnerTop,noCountries);
    }

}


void printWinner (Country *winnerStack,int noCountries,char* argv[]) // functie ce printeaza stiva winner
{
    FILE *fout = openAppend(argv);
    Country *traveler = winnerStack;
    int i;
    fprintf(fout,"\n=== WINNER ===\n");
    for (i=0 ; i<noCountries; i++)
    {
        fprintf(fout,"%s --- %d\n",traveler->name,traveler->global_score);
        traveler = traveler->next;
    }
    fclose(fout);
}

