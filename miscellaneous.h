#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_
#include "general.h"
#include "files.h"
#include "BST.h"
#include "queue.h"s


int bitCount(int n); // functie pentru a verifica daca un numar e putere a lui 2. Un numar e putere a lui 2 daca in binary este format dintr-un singur bit 1
double findMinimum(Country *head); // functie de gasit media aritmetica cea mai mica
double countryAverage(Country *head); // media scorurilor jucatorilor unei tari
int bestPlayerScore(Country *country); // functie ce gaseste cel mai bun scor dintre toti jucatorii
void playGames(Country **top,Q *queue, Country **winnerStack, int *noCountries,char* argv[]); // functia ce baga elementele din stiva initiala in coada, face meciurile,
                                                                                             // le baga in stiva winner, injumatateste numarul de tari la finalul etapei
void allGames(Country *top,Q* queue,Country **winnerStack,int *noCountries,root** node,char* argv[]); //functie in care sunt calculate outcome-urile tuturor meciurilor

#endif
