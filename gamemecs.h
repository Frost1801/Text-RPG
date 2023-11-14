//
// Created by sergi on 27/12/2020.
//

#ifndef GIOCO_MECCANICHE_GAMEMECS_H
#define GIOCO_MECCANICHE_GAMEMECS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include "gamemecs.h"

#define WARRIOR 1
#define WIZARD 2
#define TRAVELLER 3
#define BOSS 4

typedef unsigned short int boolean; //definizione del cazzo del berretti
#define TRUE 1
#define FALSE 0
struct character {
    char name[20]; //statistiche di base
    int level;
    int class;
    boolean ismagic;

    int HP; //statistiche attuali
    int MP;
    int AC;

    int MAXHP; // punti vita massimi
    int MAXMP;//punti magici massimi
    int MAXAC; // ac massima

    int con; //stats generali nellle abilità
    int dex;
    int intel;
    int cha;

    int conb; //bonus attribuito alle abilità
    int dexb;
    int intelb;
    int chab;

};
struct equipement {
    char wname[20]; //nome dell'arma
    int wb; //bonus arma
    int acb; //bounus ac
    int mb; //bounus magie
    int dlb; //bounus carisma

    boolean applpoison; //se la arma applica o no sanguinamento e veleno
    boolean applbleed;

    //numero di round per cui sono attivi gli status effect
    int shieldr;
    int bleedr;
    int poisonr;

    int def_stancer; //contatore della durata dell'effetto delle stance del guerriero
    int off_stancer;


    //solo per i nemici boss
    char spatkdescr[100];
    char spdeath[100];

};

void input_name (struct character *thischar);
void clear (void);
void univswitch(int *result, int choiches);
void roll4stats(int **A, int n);

void assignrolls(struct character *thischar, int *A, int n);
void arrayfixer(int *tmp,int *j,int n, int *value);

void rd20 (int *roll);
void rd10 (int *roll);
void rd6 (int *roll);
void rd8 (int *roll);
void rd4 (int *roll);

void charinit ( struct character *thischar, struct equipement *thisequip, boolean ismagic);

void ressprint (struct character *thischar);
void equipprint (struct equipement *thisequip);
void statsprint (struct character *thischar);
void eqinit ( struct equipement *thisequip);
void turn_printer (struct character *thischar, struct equipement *thisequip);
void death ();

void enemyinit ( struct character *thischar, struct equipement *thisequip, boolean ismagic, int level);

void arrayprint (int *A, int n);
#endif //GIOCO_MECCANICHE_GAMEMECS_H
