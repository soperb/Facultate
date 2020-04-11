#ifndef LISTS_H_
#define LISTS_H_
#include "general.h"

void FiletoList(Country **head, int* noCountries,char* argv[]); // functie de deschidere fisier + aflarea numarului de tari + facut nodurile cu add
void add(Country *head, FILE** f); //functie de adaugare nod
double countryAverage(Country *head); // pentru a afla media scorurilor jucatorilor
double findMinimum(Country *head); // functie de gasit media aritmetica cea mai mica
void removeCountry(Country *head, int *noCountries); // functie de eliminat o tara din lista
void deleteList(Country **head);//functie de stergere a listei
void printList(Country  *head,char *argv[]); // functie pentru afisarea elementelor din lista


#endif
