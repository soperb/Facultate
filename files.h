#ifndef FILES_H_
#define FILES_H_
#include "general.h"

FILE *openAppend(char* argv[]); // functie pentru deschiderea unui fisier cu rol de append
FILE *openWrite(char* argv[]); // functie pentru deschiderea unui fisier cu rol de write
char* cerinte(Player **player1, Player **player2,char* argv[]); // functie pentru citirea cerintelor

#endif
