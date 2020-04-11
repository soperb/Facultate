#ifndef GENERAL_H_
#define GENERAL_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>


// structura pentru jucator
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


#endif

