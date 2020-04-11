

#include "files.h"

FILE *openWrite(char* argv[]) // functie pentru deschiderea unui fisier cu rol de write
{
    FILE *fout;
    if((fout = fopen(argv[3],"w")) == NULL)
    {
        fprintf(fout,"eroare la deschiderea rezultate.out pentru scriere");
        exit(-55);
    }
    return fout;
}


FILE *openAppend(char* argv[]) // functie pentru deschiderea unui fisier cu rol de append
{
    FILE *fout;
    if((fout = fopen(argv[3],"a")) == NULL)
    {
        fprintf(fout,"eroare la deschiderea rezultate.out pentru append");
        exit(-55);
    }
    return fout;
}


char* cerinte(Player **player1,Player **player2,char *argv[]) // functie pentru citirea cerintelor
{
    FILE *fcerinte;
    int i,scor1,scor2;
    char nume1[BUFSIZ],nume2[BUFSIZ];
    char prenume1[BUFSIZ],prenume2[BUFSIZ];
    char *c = (char*)malloc(5* sizeof(char)); // 5*sizeof(char) pentru ca sunt 5 cerinte

    if((fcerinte=fopen( argv[1],"r"))==NULL)
    {
        printf("Eroare la deschiderea cerinte.in pentru citire");
        exit(55);
    }

    for(i=0; i<5; i++)
        fscanf(fcerinte,"%c %[ ]",&c[i]); // %[ ] pentru a ignora spatiul dintre cerinte, sa nu fie pus in vector

    fscanf(fcerinte,"%s %s %d %s %s %d",nume1,prenume1,&scor1,nume2,prenume2,&scor2);

    if(scor1<scor2) // facem in asa fel incat player1 sa fie mereu cel cu scorul mai mare
    {
        *player1 = (Player*)malloc(sizeof(Player));
        *player2 = (Player*)malloc(sizeof(Player));

        (*player1)->first_name = (char*)malloc(sizeof(char) * (strlen(nume2)+1));
        (*player2)->first_name = (char*)malloc(sizeof(char) * (strlen(nume1)+1));
        (*player1)->last_name = (char*)malloc(sizeof(char) * (strlen(prenume2)+1));
        (*player2)->last_name = (char*)malloc(sizeof(char) * (strlen(prenume1)+1));

        strcpy((*player1)->first_name,prenume2);
        strcpy((*player2)->first_name,prenume1);
        strcpy((*player1)->last_name,nume2);
        strcpy((*player2)->last_name,nume1);
        (*player1)->score = scor2;
        (*player2)->score = scor1;
    }
    else
    {


        *player1 = (Player*)malloc(sizeof(Player));
        *player2 = (Player*)malloc(sizeof(Player));

        (*player1)->first_name = (char*)malloc(sizeof(char) * (strlen(nume1)+1));
        (*player2)->first_name = (char*)malloc(sizeof(char) * (strlen(nume2)+1));
        (*player1)->last_name = (char*)malloc(sizeof(char) * (strlen(prenume1)+1));
        (*player2)->last_name = (char*)malloc(sizeof(char) * (strlen(prenume2)+1));



        strcpy((*player1)->first_name,prenume1);
        strcpy((*player2)->first_name,prenume2);
        strcpy((*player1)->last_name,nume1);
        strcpy((*player2)->last_name,nume2);
        (*player1)->score = scor1;
        (*player2)->score = scor2;
    }
    fclose(fcerinte);
    return c;
}
