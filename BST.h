#ifndef BST_H_
#define BST_H_
#include "general.h"
#include "files.h"

//structura pentru un nod de arbore
typedef struct root
{
    Player* jucator;
    struct root *left;
    struct root *right;
} root; // structura unui nod din bst


 root* newNode (Player *toAdd); // functie ce imi creeaza un nou nod
 root* InsertNode(root* node,Player *toAdd,int noCountries); // functie ce insereaza un nou nod in BST
 void BTtoBST(root* node,root** newBST,int noCountries); // functie ce imi face dintr-un binary tree un BST
 void deleteBT(root *node); // functie de stergere a unui binary tree
 void winnertoTree(Country **winnerStack, root **node, int noCountries); // functie ce imi ia jucatorii din stack-ul WINNERS si ii pune intr-un BST
 bool existaJucator(root* node, Player *jucator); // functie ce afla daca exista jucatorul respectiv in BST
 void inorderTraversal(root* node, Player* player1, Player* player2,int *distance ) ;  // parcurgem BST in inordine, pentru a afla nr. de jucatori
 void printDecOrder(root *node, FILE *fout); // daca parcurgem DRS arborele, vom obtine elementele in ordine descrescatoare
 void printClasament(root * node,char *argv[]); // functie pentru afisarea clasamentului (cerinta 4)
 void betweenPlayers(root* node,Player* player1,Player* player2,char* argv[]); // functia ce afiseaza numarul de jucatori intre cei doi jucatori din cerinte.in

#endif
