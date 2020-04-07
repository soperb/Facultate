#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>

//structura pentru jucator
typedef struct Player
{
    char *last_name;
    char *first_name;
    int score;
} Player;

//structura pentru tara
typedef struct Country
{
    char *name;
    int nr_players;
    int global_score;
    Player *players;
    struct Country* next;
    struct Country* prev;
} Country;

typedef struct Queue
{
    Country *front;
    Country *rear;
} Q;

typedef struct root
{
    Player* jucator;
    struct root *left;
    struct root *right;
} root;

typedef struct stackTree// structura pentru nod din stiva
{
    root *treeNode;
    struct stackTree *next;
} stackTree;

//structura pentru stiva
/*typedef struct stackNode
{
    Country countryElem;
    struct stackNode *next;
}stackNode;
*/
/*typedef struct nodeCountry
{
    Country country;
    struct  nodeCountry* next;
    struct  nodeCountry* prev;
} NC;*/

void add(Country *head, FILE** f); //functie de adaugare nod
void FiletoList(Country **head, int* noCountries,char* argv[]); // functie de deschidere fisier + aflarea numarului de tari + facut nodurile cu add
double countryAverage(Country *head); // pentru a afla media scorurilor jucatorilor
double findMinimum(Country *head); // functie de gasit media aritmetica cea mai mica
void removeCountry(Country *head, int *noCountries); // functie de eliminat o tara din lista
char* cerinte(Player **player1, Player **player2,char* argv[]); // functie pentru citirea cerintelor
void ReadbetweenPlayers(root** player1, root** player2); // functie ce citeste cei doi jucatori din cerinte.in
void printList(Country  *head,char *argv[]); // functie pentru afisarea elementelor din lista
int bitCount(int n); // functie de calculat numarul de biti in binary al unui numar, necesar pentru a vedea daca un numar este putere a lui 2.
void push(Country **top, Country added); // functia de adaugat elemente in varful stivei
int isEmpty(Country *top); // functie ce verifica daca e plina/goala stiva
Country* ListToStack(Country* head, Country** top); // functie ce imi pune elementele din lista in stiva
void printStack(Country *top, int noCountries); // functie de afisare a stivei
void deleteList(Country **head); // functie pentru stergerea listei inlantuite
Q *createQueue(); // functie ce imi creeaza o coada
void enQueue(Q *q, Country country); // functie ce imi adauga element in coada
void playGames(Country **top,Q *queue, Country **winnerStack, int *noCountries,char* argv[]); // functia ce baga elementele din stiva initiala in coada, face meciurile, le baga in stiva winner
void winnertoTree(Country **winnerStack, root **node, int noCountries);
void delTop(Country **top, int *remCountries); // functie de eliminat top-ul stack-ului
void delTopnoCountries(Country** top, int remCountries); // functie ce elimina top-ul stack-ului, fara a modifica numarul de tari
void allGames(Country *top,Q* queue,Country **winnerStack,int *noCountries,root** node,char* argv[]); //functie in care sunt calculate outcome-urile tuturor meciurilor
void printWinner (Country *winnerStack,int noCountries,char *argv[]); // afisarea echipelor castigatoare
void reverseStack(Country **top, int noCountries);
void winnertoInit(Country **initTop,Country **winnerTop, int noCountries); // functie ce imi pune elementele din stiva winner in stiva initiala
FILE *openAppend(char* argv[]); // functie pentru deschiderea unui fisier cu rol de append
FILE *openWrite(char* argv[]); // functie pentru deschiderea unui fisier cu rol de write
root* minValue(root* node); // functie de aflarea valorii minime dintr-un BST
root* deleteNode(root* node,Player *toDelete); // functie ce sterge un nod din BST
root* InsertNode(root* node,Player *toAdd,int noCountries); // functie ce adauga un element in BST
root* changeScores(root* node,Player *toChange); // functie ce imi actualizeaza valorile din BST
void printClasament(root * node,char *argv[]); // functie pentru afisarea clasamentului (cerinta 4)
void printDecOrder(root *node, FILE *fout);
void BTtoBST(root* node,root** newBST,int noCountries);
stackTree* BTtoStack(root* node);
root* StacktoBST (stackTree* top);
void deleteBT(root *node);
int isEmptyTree(stackTree *top); // functie ce verifica daca e plina/goala stiva pentru tree
void betweenPlayers(root* node,Player* player1,Player* player2,char* argv[]);
int bestPlayerScore(Country *country);
void inorderTraversal(root* node, Player* player1, Player* player2,int *distance );

int main(int argc, char* argv[])
{
    char numeCerinte[BUFSIZ], numeDate[BUFSIZ], numeRezultate[BUFSIZ] ;

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
    {
        betweenPlayers(BST,player1,player2,argv);
    }

    return 0;
}


void printList(Country* head,char* argv[])
{
    FILE *fout = openWrite(argv);
    Country *travel=head->next;
    int i;
    while(travel != head)
    {
        fprintf(fout,"%s\n",travel->name);
        travel = travel->next;
    }
    fclose(fout);

}

void printStack(Country *top, int noCountries)
{
    Country *traveler = top;
    int i,j;
    for (i=0 ; i<noCountries; i++)
    {
        printf("%s\n",traveler->name);
        traveler = traveler->next;
    }

}

char* cerinte(Player **player1,Player **player2,char *argv[]) // functie pentru citirea cerintelor
{
    FILE *fcerinte;
    int i,scor1,scor2;
    char scorS1[BUFSIZ],scorS2[BUFSIZ];
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
    //printf("%s %s %s %s %s %s",nume1,prenume1,scorS1,nume2,prenume2,scorS2);

    if(scor1<scor2)
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

int isEmptyQueue(Q* queue)
{
    return(queue->front == NULL);
}

void delTop(Country** top, int *remCountries) // functie de sters elementul din varful stivei, modific si numarul tarilor. ex: cand pun tarile din stiva initiala in stiva winners
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
void delTopnoCountries(Country** top, int remCountries) // functie de sters elementul din varful stivei. nu modific numarul de tari (ex: cand pun tarile din winners in stiva initiala)
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

Country* ListToStack(Country* head, Country** top) // functie de pus elementele din lista in stiva
{
    Country *traveler = head->next;
    while(traveler != head)
    {
        push(top,(*traveler));
        traveler = traveler->next;
    }
    //traveler->next = NULL;
    //push(top, (*traveler));
    //deleteList(&head);
    return (*top);
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

Q *createQueue() // functie ce imi creeaza o coada
{
    Q *q;
    q = (Q*)malloc(sizeof(Q));
    if(q==NULL)
        return NULL;

    q->front = q->rear = NULL;
    return q;
}

void enQueue(Q *q, Country country) // functie ce imi adauga element in coada
{
    Country *newNode = (Country*)malloc(sizeof(Country));
    *newNode = country;
    newNode->next = NULL;

    //adaugam noul nod la finalul cozii
    if(q->rear==NULL) // daca nu avem niciun nod in coada
        q->rear = newNode;
    else
    {
        (q->rear)->next = newNode;
        q->rear= newNode;
    }
    if (q->front == NULL)
        q->front = q->rear; // daca e singurul element din coada
}

void deleteQueue(Q *queue) // functie ce sterge o coada
{
    Country *aux;
    while (!isEmptyQueue(queue))
    {
        aux = queue->front;
        queue->front = queue->front->next;
        free(aux);
    }
    queue->rear = NULL;;
}

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

void playGames(Country **top,Q *queue, Country **winnerStack,int *noCountries,char* argv[]) // in aceasta functie pun elementele din stiva initiala in coada de meciuri, le pun in stiva winner
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
        (*firstCountry)=(**top);
        delTop(&(*top),&initialCountries);
        (*secondCountry)=(**top);
        delTop(&(*top),&initialCountries);
        enQueue(queue,(*firstCountry));
        enQueue(queue,(*secondCountry));

        fprintf(fout,"\n%s %d ----- %s %d",queue->front->name,queue->front->global_score,queue->rear->name,queue->rear->global_score);

        for(i=0 ; i<queue->front->nr_players ; i++)
        {
            for(j=0 ; j<queue->rear->nr_players ; j++)
            {
                fprintf(fout,"\n%s %s %d vs %s %s %d",queue->front->players[i].last_name,queue->front->players[i].first_name,queue->front->players[i].score,queue->rear->players[j].last_name,queue->rear->players[j].first_name,queue->rear->players[j].score);
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


        if(firstLocal == secondLocal) // adaugam in stiva Winner tara cu punctajul local mai mare
        {
            if(bestPlayerScore(queue->front) < bestPlayerScore(queue->rear))
                push(&(*winnerStack),*(queue->rear));
            else
                push(&(*winnerStack),*(queue->front));
        }

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

void winnertoTree(Country **winnerStack, root **node, int noCountries)
{
    root* newBST = NULL;

    if(noCountries == 4 ) // daca sunt ultimele 4 tari ramase trebuie doar introduse in BST
    {
        Country *temp = *winnerStack;
        while(temp != NULL)
        {
            int i;
            for(i=0 ; i<temp->nr_players; i++)
            {
                *node = InsertNode(*node,&temp->players[i],noCountries);
            }
            temp = temp->next;
        }
    }
    if(noCountries == 1) // la ultima tara ramasa, BST-ul initial devine BT, intrucat scorurile se modifica
    {
        BTtoBST(*node,&newBST,noCountries);
        deleteBT(*node);
        *node = newBST;
    }
}

void BTtoBST(root* node, root** newBST,int noCountries)
{
    if(node == NULL)
        return;
    BTtoBST(node->left,newBST,noCountries);
    (*newBST) = InsertNode(*newBST,node->jucator,noCountries);
    BTtoBST(node->right,newBST,noCountries);
}


void deleteBT(root *node) // stergerea arborelui, intrucat 'schimb' arborele
{
    if(!node)
        return;
    deleteBT(node->left);
    deleteBT(node->right);
    free(node);
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

void winnertoInit(Country **initTop,Country **winnerTop, int noCountries)
{
    while(!isEmpty(*winnerTop))
    {
        push(&(*initTop),*(*winnerTop));
        delTopnoCountries(winnerTop,noCountries);
    }

}

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

root* newNode (Player *toAdd) // functie ce imi creeaza un nou nod
{
    root *node = (root*)malloc(sizeof(root));
    node->jucator = toAdd;
    node->left = node->right = NULL;
    return node;
}

root* InsertNode(root* node,Player *toAdd,int noCountries) // functie ce insereaza un nou nod in BST
{
    if ( node == NULL )
        return newNode(toAdd);
    if(noCountries == 1)
    {
        if(toAdd->score == node->jucator->score) // cazul in care au acelasi scor
        {
            if(strcmp(toAdd->last_name,node->jucator->last_name)<0) // daca cel pe care il adaugam are numele mai mic dpdv lexicografic
            {
                node->jucator = toAdd;
            }
            else if(!strcmp(toAdd->last_name,node->jucator->last_name)) // daca au acelasi nume dpdv lexicografic
            {
                if(strcmp(toAdd->first_name,node->jucator->first_name)<0) // comparam prenumele si il adaugam daca are numele mai mic decat nodul deja prezent, altfel in lasam asa
                    node->jucator = toAdd;
                else
                    return node;
            }
            return node;

        }
    }

    if(toAdd->score < node->jucator->score)
        node->left = InsertNode(node->left, toAdd,noCountries);
    else
        node->right = InsertNode(node->right,toAdd,noCountries);
    return node;
}

root* minValue(root* node) // functie ce cauta minimul dintr-ul BST
{
    root* traveler = node;
    while(traveler->left != NULL)
        traveler = traveler->left;
    return traveler;
}

root* deleteNode(root* node,Player *toDelete) // functie ce sterge un nod din BST
{
    if(node == NULL)
        return node;
    if(!strcmp(node->jucator->first_name,toDelete->first_name) && !strcmp(node->jucator->last_name,toDelete->last_name)) // daca a gasit jucatorul de sters (acelasi nume)
    {
        if(node->left == NULL) // daca e un singur copil
        {
            root* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            root *temp = node->left;
            free(node);
            return temp;
        }
        root *temp = minValue(node->right); // daca are 2 copii, gasim minimul din subarborele drept pentru a schimba pozitiile
        node->jucator = temp->jucator;
        node->right = deleteNode(node->right,temp->jucator);
    }
    node->left = deleteNode(node->left,toDelete);
    node->right = deleteNode(node->right,toDelete);
    return node;
}

void printDecOrder(root* node, FILE* fout) // daca parcurgem DRS arborele, vom obtine elementele in ordine descrescatoare
{
    if (node == NULL)
        return;
    printDecOrder(node->right,fout);
    fprintf(fout,"%s %s %d\n",node->jucator->last_name,node->jucator->first_name,node->jucator->score);
    printDecOrder(node->left,fout);
}

void printClasament(root * node,char* argv[]) // functie pentru afisarea clasamentului (cerinta 4)
{
    FILE *fout = openAppend(argv);
    fprintf(fout,"\n====== CLASAMENT JUCATORI ======\n");
    printDecOrder(node,fout);
    fclose(fout);
}

bool existaJucator(root* node, Player *jucator)
{
    if(!node)
        return false;

    if(node->jucator->score == jucator->score && (!strcmp(node->jucator->first_name,jucator->first_name)) && (!strcmp(node->jucator->last_name,jucator->last_name)))
        return true;

    if(node->jucator->score > jucator->score)
        return existaJucator(node->left,jucator);
    return existaJucator(node->right,jucator);
}

root *LCA(root *node, Player* player1, Player* player2) // functie pentru aflarea Lowest Common Ancestor recursiv
{
    root* lowComAnc;
    if(!node)
        return NULL;

    root *LCA_L = NULL;
    root *LCA_R  = NULL;

    LCA_L = LCA(node->left,player1,player2);
    LCA_R = LCA(node->right,player1,player2);

    if(node->jucator->score == player1->score)
        return node;
    if(node->jucator->score == player2->score)
        return node;

    if(LCA_L && LCA_R)
    {
        lowComAnc = node;
        return lowComAnc;
    }

    if(LCA_L)
        return LCA_L;
    if(LCA_R)
        return LCA_R;
    return NULL;

}

int nodeDistance(root* node, Player* jucator)
{
    if(!node)
        return 0;
    if(node->jucator->score == jucator->score && (!strcmp(node->jucator->first_name,jucator->first_name)) && (!strcmp(node->jucator->last_name,jucator->last_name)) )
        return 0;
    else if (node->jucator->score > jucator->score)
        return (1+nodeDistance(node->left,jucator));
    else
        return (1+nodeDistance(node->right,jucator));
}

void inorderTraversal(root* node, Player* player1, Player* player2,int *distance )
{

    if(!node)
        return;
    inorderTraversal(node->left,player1,player2,distance);
    if(node->jucator->score < player1->score && node->jucator->score > player2->score)
    (*distance)++;
    inorderTraversal(node->right,player1,player2,distance);

}

void betweenPlayers(root* node,Player *player1,Player *player2,char* argv[])
{
    FILE *fout = openAppend(argv);
    root *lowCommAnc = NULL;
    if(!existaJucator(node,player1))
    {
        fprintf(fout,"\n%s %s nu poate fi identificat!\n",player1->last_name,player1->first_name);
        return;
    }

    if(!existaJucator(node,player2))
    {
        fprintf(fout,"\n%s %s nu poate fi identificat!\n",player2->last_name,player2->first_name);
        return;
    }

   int distanceBetween=0;
   inorderTraversal(node,player1,player2,&distanceBetween);
   fprintf(fout,"\n%d",distanceBetween);
   fclose(fout);
}

