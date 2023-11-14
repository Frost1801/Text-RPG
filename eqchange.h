//
// Created by andre on 01/01/2021.
//

#ifndef MAIN_C_EQCHANGE_H
#define MAIN_C_EQCHANGE_H
#include "gamemecs.h"
void lvup (struct character *thischar);
void class_picker (struct character *thischar, struct equipement *thisequip);

void warrior_charinit ( struct character *thischar, struct equipement *thisequip);
void wizard_charinit ( struct character *thischar, struct equipement *thisequip);
void traveller_charinit ( struct character *thischar, struct equipement *thisequip);
void full_rest (struct character *thischar);
#endif //MAIN_C_EQCHANGE_H
