//
// Created by sergi on 28/12/2020.
//

#ifndef GIOCO_MECCANICHE_FIGHT_H
#define GIOCO_MECCANICHE_FIGHT_H
#include "gamemecs.h"
#include <stdlib.h>
#include <stdio.h>

void magic_missle (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);
void magic_missle_enemy (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);

void melee_strike (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);
void melee_strike_enemy (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);

void encounter(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enmeyequip);

boolean flee (struct character *thischar, struct character *enemy);
boolean flee_enemy (struct character *thischar, struct character *enemy);

void fight (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);
void enemyturn(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, boolean *is_fleed);
void yourturn(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker);

boolean manacost (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker, int cost);

void innermagic (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker);
void firebolt(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);
void healingword (struct character *thischar);
void shield (struct character *thischar, struct equipement *thisequip);
void plasmarays (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);

void poison_clock (struct character *thischar, struct equipement *thisequip);
void shield_clock (struct character *thischar, struct equipement *thisequip);
void bleed_clock (struct character *thischar, struct equipement *thisequip);

void applybleed(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);
void applypoison(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip);

void stances (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker);
void defensive_stance_clock (struct character *thischar, struct equipement *thisequip);
void offensive_stance_clock (struct character *thischar, struct equipement *thisequip);
void defensive_stance (struct character *thischar, struct equipement *thisequip);
void offensive_stance (struct character *thischar, struct equipement *thisequip);

void special_atk (struct character *thischar, struct equipement *thisequip, struct character *enemy, struct equipement *enemyequip);

#endif //GIOCO_MECCANICHE_FIGHT_H
