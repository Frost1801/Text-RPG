//
// Created by andre on 01/01/2021.
//

#include "eqchange.h"
void class_picker (struct character *thischar, struct equipement *thisequip){ //serbe per selezionare una classe ad inzio del gioco
    printf("**********************************************************************\n"); 
    int result;
    printf("\nIt's time to choose your class\n");
    printf("\nWhich class will you choose?\n");
    printf("\n1)Warrior: great at melee combat, cannot use magic");
    printf("\nWarriors get more HP each level and have a +1 bonus when attacking and dealing damage with melee weapons\n");
    printf("\n2)Wizard: talented spellcaster that is weaker if in phisical combat");
    printf("\nWizards get access to unique and powerful spells that they can cast using their MP and a +1 bonus when attacking and dealing damage with magic\n");
    printf("\n3)Traveller: good but not phenomenal in both spellcasting and fighting, a traveller is able to talk his way out of most situations");
    printf("\nTravellers get access to magic and have a +1 bonus on charisma checks\n");

    do{
        printf("\nChoose a class:");
        univswitch(&result,3); //chiama la switch universale con le due opzioni combattere o scappare
    }
    while (result == FALSE);
    switch (result) {
        case 1: {
            printf("\nYou choose Warrior");
            thischar -> class = WARRIOR;
            warrior_charinit(thischar,thisequip);
            break;
        }
        case 2: {
            printf("\nYou choose Wizard");
            thischar -> class = WIZARD;
            wizard_charinit(thischar, thisequip);
            break;
        }
        case 3:{
            printf("\nYou choose Traveller");
            thischar -> class = TRAVELLER;
            traveller_charinit(thischar,thisequip);
            break;
        }
        default:{
            printf("\nSomething went wrong (class_picker)");
        }
    }
}
void warrior_charinit ( struct character *thischar, struct equipement *thisequip){
    //inizializzo i bonus a partire dalle statistiche
    if (thischar -> con > 10)
        thischar -> conb = ((thischar ->con - 10)/ 2 + 1);//modificatore del danno sulle armi fisiche --> va su const MODIFICATO LA COSTITUZIONE DEI GUERRIERI
    else
        thischar -> conb = ((thischar ->con - 11+ 1)/ 2);
    if (thischar ->dex > 10)
        thischar -> dexb = ((thischar ->dex - 10)/ 2 ); //modificatore della armor class --> va su dex
    else
        thischar -> dexb = ((thischar ->dex - 11)/ 2 );
    if (thischar -> intel > 10)
        thischar -> intelb = ((thischar ->intel - 10)/ 2); //modificatore del danno e per colpire con magie --> va su int
    else
        thischar -> intelb = ((thischar ->intel - 11)/ 2);
    if (thischar->cha > 10)
        thischar ->chab = ((thischar ->cha - 10)/ 2); //bonus sul carisma --> va su carisma
    else
        thischar ->chab = ((thischar ->cha - 11)/ 2);

    //risorse base
    thischar -> ismagic = FALSE;
    thischar -> level = 1; //livello inizializzato a 1
    if (thischar -> con > 10)
        thischar ->MAXHP = (10  + thischar -> conb * thischar -> level); // la vita è 8 per ogni livello + bonus costituzione * livello  MODIFICATO VITA MASSIMA GUERRIERI
    else
        thischar ->MAXHP = (10 * thischar -> level);
    thischar -> HP = thischar -> MAXHP;
    thischar->MAXMP = 0; // se un personaggio non è magico i suoi mp sono 0
    thischar -> MP = thischar -> MAXMP;
    thischar ->AC = (10 + thischar ->dexb + thisequip ->acb); //la armor class è uguale a 10 + mod su dex + bonus equipaggiamento
    thischar -> MAXAC = thischar -> MAXAC; //armor class massima
}

void wizard_charinit ( struct character *thischar, struct equipement *thisequip){
    //inizializzo i bonus a partire dalle statistiche
    if (thischar -> con > 10)
        thischar -> conb = ((thischar ->con - 10)/ 2);//modificatore del danno sulle armi fisiche --> va su const
    else
        thischar -> conb = ((thischar ->con - 11)/ 2);
    if (thischar ->dex > 10)
        thischar -> dexb = ((thischar ->dex - 10)/ 2 ); //modificatore della armor class --> va su dex
    else
        thischar -> dexb = ((thischar ->dex - 11)/ 2 );
    if (thischar -> intel > 10)
        thischar -> intelb = ((thischar ->intel - 10)/ 2 + 1); //modificatore del danno e per colpire con magie --> va su int MODIFICATA L'INTELLIGENZA
    else
        thischar -> intelb = ((thischar ->intel - 11 + 1)/ 2);
    if (thischar->cha > 10)
        thischar ->chab = ((thischar ->cha - 10)/ 2); //bonus sul carisma --> va su carisma
    else
        thischar ->chab = ((thischar ->cha - 11)/ 2);

    //risorse base
    thischar -> ismagic = TRUE;
    thischar -> level = 1; //livello inizializzato a 1
    if (thischar -> con > 10)
        thischar ->MAXHP = (8  + thischar -> conb * thischar -> level); // la vita è 8 per ogni livello + bonus costituzione * livello
    else
        thischar ->MAXHP = (8 * thischar -> level);
    thischar -> HP = thischar -> MAXHP;
    if (thischar -> ismagic ){
        thischar ->MAXMP =  (1 + thischar -> intelb) * thischar -> level; // gli slot sono 1 per livello + modificatore int * livello
        if (thischar -> MAXMP < 0)
            thischar -> MAXMP = 0; // se un personaggio ha intelligenza che poterebbe i mp nel negativo allora sono 0
    }
    else
        thischar->MAXMP = 0; // se un personaggio non è magico i suoi mp sono 0
    thischar -> MP = thischar -> MAXMP;
    thischar ->AC = (10 + thischar ->dexb + thisequip ->acb); //la armor class è uguale a 10 + mod su dex + bonus equipaggiamento
    thischar -> MAXAC = thischar -> MAXAC; //armor class massima
}
void traveller_charinit ( struct character *thischar, struct equipement *thisequip){
    //inizializzo i bonus a partire dalle statistiche
    if (thischar -> con > 10)
        thischar -> conb = ((thischar ->con - 10)/ 2);//modificatore del danno sulle armi fisiche --> va su const
    else
        thischar -> conb = ((thischar ->con - 11)/ 2);
    if (thischar ->dex > 10)
        thischar -> dexb = ((thischar ->dex - 10)/ 2 ); //modificatore della armor class --> va su dex
    else
        thischar -> dexb = ((thischar ->dex - 11)/ 2 );
    if (thischar -> intel > 10)
        thischar -> intelb = ((thischar ->intel - 10)/ 2); //modificatore del danno e per colpire con magie --> va su int
    else
        thischar -> intelb = ((thischar ->intel - 11)/ 2);
    if (thischar->cha > 10)
        thischar ->chab = ((thischar ->cha - 10)/ 2 + 1); //bonus sul carisma --> va su carisma
    else
        thischar ->chab = ((thischar ->cha - 11)/ 2 + 1); //MODIFICATO IL BONUS SU CARISMA PER IL TRAVELLER

    //risorse base
    thischar -> ismagic = TRUE;
    thischar -> level = 1; //livello inizializzato a 1
    if (thischar -> con > 10)
        thischar ->MAXHP = (8  + thischar -> conb * thischar -> level); // la vita è 8 per ogni livello + bonus costituzione * livello
    else
        thischar ->MAXHP = (8 * thischar -> level);
    thischar -> HP = thischar -> MAXHP;
    if (thischar -> ismagic){
        thischar ->MAXMP =  (1 + thischar -> intelb) * thischar -> level; // gli slot sono 1 per livello + modificatore int * livello
        if (thischar -> MAXMP < 0)
            thischar -> MAXMP = 0; // se un personaggio ha intelligenza che poterebbe i mp nel negativo allora sono 0
    }
    else
        thischar->MAXMP = 0; // se un personaggio non è magico i suoi mp sono 0
    thischar -> MP = thischar -> MAXMP;
    thischar ->AC = (10 + thischar ->dexb + thisequip ->acb); //la armor class è uguale a 10 + mod su dex + bonus equipaggiamento
    thischar -> MAXAC = thischar -> MAXAC; //armor class massima
}

void lvup (struct character *thischar){
    if (thischar -> HP > 0){
        if (thischar -> class == TRAVELLER || thischar -> class == WIZARD){
            printf("\nLEVEL UP!");
            int tmp;
            int tmp1;
            int tmp2;

            tmp1 = thischar -> MAXHP;
            tmp2 = thischar -> MAXMP;
            tmp = thischar -> level;
            thischar ->level ++;
            if (thischar -> con > 10)
                thischar ->MAXHP = (8  + thischar -> conb) * thischar -> level; // la vita è 8 per ogni livello + bonus costituzione * livello
            else
                thischar ->MAXHP = (8 * thischar -> level);

            if (thischar -> ismagic == TRUE ){
                thischar ->MAXMP =  (1 + thischar -> intelb) * thischar -> level; // gli slot sono 1 per livello + modificatore int * livello
                if (thischar -> MAXMP < 0)
                    thischar -> MAXMP = 0; // se un personaggio ha intelligenza che poterebbe i mp nel negativo allora sono 0
            }
            else
                thischar->MAXMP = 0; // se un personaggio non è magico i suoi mp sono 0
            printf("\n%s:",thischar ->name);
            printf("\nLv: %d --> Lv: %d",tmp, thischar -> level); //stampa i cambi di vita massima, livello e mana
            printf("\nHP: %d --> HP: %d",tmp1,thischar -> MAXHP);
            if (thischar -> class == WIZARD || thischar -> class == TRAVELLER) {
                printf("\nMP: %d --> MP: %d",tmp2,thischar -> MAXMP);
            }
            //aggiorna la vita attuale e i mp attuali
            thischar -> HP = thischar -> HP + (thischar ->MAXHP - tmp1);
            thischar -> MP = thischar -> MP + (thischar ->MAXMP - tmp2);
        }
        else if (thischar -> class == WARRIOR){
            printf("\nLEVEL UP!");
            int tmp;
            int tmp1;
            int tmp2;

            tmp1 = thischar -> MAXHP;
            tmp = thischar -> level;
            thischar ->level ++;
            if (thischar -> con > 10)
                thischar ->MAXHP = (10  + thischar -> conb) * thischar -> level; // la vita è 8 per ogni livello + bonus costituzione * livello
            else
                thischar ->MAXHP = (10 * thischar -> level);

            printf("\n%s:",thischar ->name);
            printf("\nLv: %d --> Lv: %d",tmp, thischar -> level); //stampa i cambi di vita massima, livello e mana
            printf("\nHP: %d --> HP: %d",tmp1,thischar -> MAXHP);

            //aggiorna la vita attuale e i mp attuali
            thischar -> HP = thischar -> HP + (thischar ->MAXHP - tmp1);
        }
        else
            printf("\nSomething went wrong (level up)");

    }
}

void full_rest (struct character *thischar){
    thischar -> HP = thischar -> MAXHP;
    thischar -> MP = thischar -> MAXMP;
}






void lsplusone (struct equipement *thisequip){
    strcpy(thisequip ->wname,"Longsword + 1");
    thisequip -> wb = 1; //bonus armi fisiche
    thisequip -> acb = 0; // bonus dato dall'armatura
    thisequip -> mb = 0; //bonus dato alle armi magiche
    thisequip ->dlb = 0; //bonus dato nei dialoghi
}
void magestaff (struct equipement *thisequip){
    strcpy(thisequip ->wname,"Mage Staff ");
    thisequip -> wb = 0; //bonus armi fisiche
    thisequip -> acb = 0; // bonus dato dall'armatura
    thisequip -> mb = 1; //bonus dato alle armi magiche
    thisequip ->dlb = 0; //bonus dato nei dialoghi
}
