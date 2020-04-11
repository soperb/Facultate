#include "miscellaneous.h"


int bitCount(int n) // functie pentru a verifica daca un numar e putere a lui 2. Un numar e putere a lui 2 daca in binary este format dintr-un singur bit 1
{
    int count=0;
    while(n>0)
    {
        if(n & 1)
            ++count;
        n >>=1;
    }
    return count;
}

double findMinimum(Country *head) // functie de gasit media aritmetica cea mai mica
{
    double minimum=0;
    Country *headcopy=head->next;
    minimum=countryAverage(headcopy);
    headcopy=headcopy->next;
    while(headcopy!=head)
    {
        if(countryAverage(headcopy)<minimum)
            minimum=countryAverage(headcopy);
        headcopy=headcopy->next;
    }
    return minimum;
}


double countryAverage(Country *head) // media scorurilor jucatorilor unei tari
{
    double mean=0;
    Country* traveler=head;
    for(int i=0 ; i<traveler->nr_players; i++)
    {
        mean+=traveler->players[i].score;
    }
    mean=mean/traveler->nr_players;
    return mean;
}

//functie ce cauta scorul cel mai mare dintre toti jucatorii
int bestPlayerScore(Country *country)
{
    int i,maxScore=0;
    for(i=0 ; i<country->nr_players ; i++)
    {
        if(country->players[i].score > maxScore)
            maxScore = country->players[i].score;
    }
    return maxScore;
}

void playGames(Country **top,Q *queue, Country **winnerStack,int *noCountries,char* argv[]) // in aceasta functie pun elementele din stiva initiala in coada de meciuri,
                                                                                           // dupa care le pun in stiva winner
{

    int i,j,initialCountries=(*noCountries);
    int firstLocal=0, secondLocal=0; // variabile pentru scorurile locale ale celor doua tari
    Country *firstCountry, *secondCountry;
    firstCountry=malloc(sizeof(Country));
    secondCountry=malloc(sizeof(Country));
    //queue = createQueue();

    while(!isEmpty(*top)) // cat timp exista elemente in stiva initiala, iau primele doua tari si le pun in coada
    {
        FILE *fout = openAppend(argv);

        queue = createQueue();

        (*firstCountry)=(**top); // first country devine prima tara din stack,
        delTop(&(*top),&initialCountries);     //dupa care dam delete primei tari din stack (am incercat initial cu un pop dar dadea fail ??)

        (*secondCountry)=(**top); // la fel ca la first country
        delTop(&(*top),&initialCountries);

        enQueue(queue,(*firstCountry)); // bagam pe cele doua in coada
        enQueue(queue,(*secondCountry));

        fprintf(fout,"\n%s %d ----- %s %d",queue->front->name,queue->front->global_score,queue->rear->name,queue->rear->global_score);

        for(i=0 ; i<queue->front->nr_players ; i++)
        {
            for(j=0 ; j<queue->rear->nr_players ; j++)
            {
                fprintf(fout,"\n%s %s %d vs %s %s %d",queue->front->players[i].last_name,queue->front->players[i].first_name,queue->front->players[i].score,
                        queue->rear->players[j].last_name,queue->rear->players[j].first_name,queue->rear->players[j].score);
                if(queue->front->players[i].score == queue->rear->players[j].score) // daca este egalitate intre cei doi jucatori
                {
                    queue->front->players[i].score += 2;
                    queue->rear->players[j].score += 2;
                    firstLocal++;
                    secondLocal++;
                }
                else if (queue->front->players[i].score < queue->rear->players[j].score) // daca al doilea jucator castiga
                {
                    queue->rear->players[j].score += 5;
                    secondLocal += 3;
                }
                else // daca primul jucator castiga
                {
                    queue->front->players[i].score += 5;
                    firstLocal += 3;
                }

            }
        }
        fprintf(fout,"\n");

        queue->front->global_score += firstLocal; // dupa terminarea meciurilor adaugam scorul local final la cel global
        queue->rear->global_score += secondLocal;


        if(firstLocal == secondLocal)  // daca e egalitate cautam jucatorul cu punctajul ce mai mare
        {
            if(bestPlayerScore(queue->front) < bestPlayerScore(queue->rear))
                push(&(*winnerStack),*(queue->rear));
            else
                push(&(*winnerStack),*(queue->front));
        }

 // adaugam in stiva Winner tara cu  punctajul local mai mare
        else if (firstLocal<secondLocal)
            push(&(*winnerStack),*(queue->rear));
        else
        {
            push(&(*winnerStack),*(queue->front));
        }




        deleteQueue(queue); // meciurile s-au terminat, nu mai avem nevoie de coada
        firstLocal = 0;
        secondLocal = 0;
        fclose(fout);
    }

    (*noCountries) /= 2; // dupa ce se termina toate meciurile dintr-o etapa numarul de tari se va injumatati
}




void allGames(Country *top,Q *queue, Country **winnerStack,int *noCountries, root **node,char* argv[])
{

    int i=1;
    while((*noCountries)>1)
    {
        FILE *fout = openAppend(argv);
        fprintf(fout,"\n====== ETAPA %d ======\n",i);
        fclose(fout);
        playGames(&top,queue,winnerStack,noCountries,argv);
        printWinner(*winnerStack,(*noCountries),argv);
        winnertoTree(winnerStack, node, *noCountries);
        winnertoInit(&top,winnerStack,(*noCountries));
        i++;
    }
}
