#ifndef STACK_H_
#define STACK_H_
#include "general.h"
#include "files.h"

void push(Country **top,Country added); // functie de adaugat un element in varful stivei
void delTop(Country **top, int *remCountries); // functie de eliminat top-ul stack-ului
void delTopnoCountries(Country** top, int remCountries); // functie ce elimina top-ul stack-ului, fara a modifica numarul de tari
int isEmpty(Country *top); // functie ce verifica daca e plina/goala stiva
Country* ListToStack(Country* head, Country** top); // functie de pus elementele din lista in stiva
void winnertoInit(Country **initTop,Country **winnerTop, int noCountries); // functie ce imi pune elementele din stiva winner in stiva initiala
void printWinner (Country *winnerStack,int noCountries,char *argv[]); // afisarea echipelor castigatoare

#endif
