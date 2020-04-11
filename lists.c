#include "lists.h"
#include "files.h"


void add(Country *head, FILE** f) //functie de adaugare nod
{
    Country *newNode, *tail=head->next;
    char str[BUFSIZ];

    newNode=(Country*)malloc(sizeof(Country)); //creez un nou nod
    fscanf(*f,"%d %s",&newNode->nr_players, str); // citesc din fisier numarul de jucatori si numele tarii(stochez numele tarii intr-un auxiliar)
    newNode->name=malloc(strlen(str)+1); //alocare pentru numele tarii
    strcpy(newNode->name,str);
    newNode->global_score=0; //by default, scorul global initial este 0;
    newNode->players=malloc(sizeof(Player)*newNode->nr_players);
    for(int i=0 ; i<newNode->nr_players ; i++)
    {
        fscanf(*f,"%s",str); //citesc numele de familie la fel cum am facut cu numele tarii
        newNode->players[i].last_name=malloc(strlen(str)+1);
        strcpy(newNode->players[i].last_name,str);

        fscanf(*f,"%s",str); // procedez la fel si pentru prenume
        newNode->players[i].first_name=malloc(strlen(str)+1);
        strcpy(newNode->players[i].first_name,str);

        fscanf(*f, "%d", &newNode->players[i].score); //scorul jucatorului
    }
    while(tail->next != head)
        tail=tail->next; //ma deplasez spre 'finalul' listei

    //adaug noul nod la final si fac legaturile next/prev corespunzatoare
    tail->next=newNode;
    newNode->next=head;
    newNode->prev=tail;
    head->prev=newNode;
}


void FiletoList(Country **head, int* noCountries,char* argv[]) // functie de deschidere fisier + aflarea numarului de tari + facut nodurile cu add
{
    FILE *finput;
    if((finput=fopen(argv[2],"r"))==NULL)
    {
        printf("Eroare la deschiderea date.in pentru citire");
        exit(55);
    }
    fscanf(finput,"%d",noCountries);

    (*head)=(Country*)malloc(sizeof(Country));
    (*head)->next=(*head); //lista circulara dublu inlantuita
    (*head)->prev=(*head);

    for(int i=0; i<(*noCountries); i++) // stim numarul de tari, deci stim cate noduri avem de creat cu add
        add(*head,&finput);
    fclose(finput);
}


void removeCountry(Country *head, int *noCountries) // functie de eliminat o tara
{
    Country *traveler= head->next, *temp;


    while( bitCount(*noCountries)!=1 ) // verific daca numarul de tari e o puterea a lui 2
    {
        traveler=head->next;
        while(traveler!=head)
        {
            if(countryAverage(traveler)==findMinimum(head))
            {
                temp=traveler;
                if(traveler->next != head)
                    (traveler->next)->prev=traveler->prev;
                else
                {
                    (traveler->prev)->next=head;
                    head->prev=traveler->prev;
                }
                if(traveler->prev!= head)
                    (traveler->prev)->next=traveler->next;
                else
                {
                    (traveler->next)->prev=head;
                    head->next=traveler->next;
                }
                (*noCountries)--; // de fiecare data cand elimin o tara decrementez numarul de tari existente

                free(temp);
                break;
            }

            traveler=traveler->next;
        }
    }
}



void deleteList(Country **head) //functie de stergere a listei
{
    Country *temp = (*head)->next, *aux = temp;
    while(temp != (*head))
    {
        temp = temp->next;
        free(aux);
        aux = temp;
    }
    free(head);
}

// functie ce afiseaza numele tarilor din lista
void printList(Country* head,char* argv[])
{
    FILE *fout = openWrite(argv);

    Country *travel=head->next; // pornim cu primul element legit, de dupa santinela
    while(travel != head)
    {
        fprintf(fout,"%s\n",travel->name);
        travel = travel->next;
    }
    fclose(fout);

}
