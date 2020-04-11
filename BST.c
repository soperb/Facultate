#include "BST.h"

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

// in momentul in care numarul de tari este egal cu 4 aceasta functie ia jucatorii din stiva winners si
// face un BST din ei.
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

 // dupa ce s-au mai facut meciuri creste scorul, BST-ul vechi se modifica si nu mai e BST
 // aceasta functie creeaza un nou BST din arborele vechi
 // eliberarea de memorie se face in functia winnertoTree
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



// functie ce verifica daca exista un jucator in arbore
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

// pentru cerinta 5 s-ar fi putut afla numarul de jucator si folosindu-ne de LCA prin doua metode,
// insa am ales sa parcurg BST in inordine. Intrucat e deja sortat pot contoriza cati jucatori se
// afla intre cele doua scoruri la parcugere
void inorderTraversal(root* node, Player* player1, Player* player2,int *distance )
{

    if(!node)
        return;
    inorderTraversal(node->left,player1,player2,distance);
    if(node->jucator->score < player1->score && node->jucator->score > player2->score)
        (*distance)++;
    inorderTraversal(node->right,player1,player2,distance);

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

void betweenPlayers(root* node,Player *player1,Player *player2,char* argv[])
{
    FILE *fout = openAppend(argv);
    //daca nu exista unul dintre jucatori
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
   //parcurgem inorder si incrementam distanta atunci cand e cazul
   inorderTraversal(node,player1,player2,&distanceBetween);
   fprintf(fout,"\n%d",distanceBetween);
   fclose(fout);
}


