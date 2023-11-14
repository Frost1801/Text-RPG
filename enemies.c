//
// Created by sergi on 13/01/2021.
//

#include "enemies.h"
void goblin_init(struct character *GOBLIN, struct equipement *goblineq){
    strcpy(GOBLIN -> name,"Goblin"); //usiamo strcpy per mettere il nome al personaggio
    GOBLIN -> con = 8;
    GOBLIN -> cha = 6;
    GOBLIN -> dex = 14;
    GOBLIN -> intel = 6;
    eqinit(goblineq);
    charinit(GOBLIN,goblineq,FALSE);
    goblineq -> applpoison = TRUE;
    strcpy(goblineq -> wname, "goblin scimitar");
}

void ghost_init (struct character *GHOST, struct equipement *ghosteq){
    strcpy(GHOST -> name,"Ghost"); //usiamo strcpy per mettere il nome al personaggio
    GHOST -> con = 6;
    GHOST -> cha = 8;
    GHOST -> dex = 16;
    GHOST -> intel = 15;
    eqinit(ghosteq);
    charinit(GHOST,ghosteq,TRUE);
    strcpy(ghosteq -> wname, "Ghost fangs");
}

void rockgolem_init (struct character *GOLEM, struct equipement *golemeq){
    strcpy(GOLEM -> name,"Rock Golem"); //usiamo strcpy per mettere il nome al personaggio
    GOLEM -> con = 18;
    GOLEM -> cha = 3;
    GOLEM -> dex = 6;
    GOLEM -> intel = 3;
    eqinit(golemeq);
    enemyinit(GOLEM,golemeq,FALSE,5);
    GOLEM -> class = BOSS;


    strcpy(golemeq -> wname, "Rock Fists");
    strcpy(golemeq -> spatkdescr, "The golem lifts and throws a huge boulder at you");
    strcpy(golemeq -> spdeath,"The boulder crushes you to death");
}

//this is not an enemy ma è il tester
void tester_init (struct character *TESTER, struct equipement *testereq){
    strcpy(TESTER -> name,"Tester"); //usiamo strcpy per mettere il nome al personaggio
    TESTER -> con = 7;
    TESTER -> cha = 12;
    TESTER -> dex = 15;
    TESTER -> intel = 18;
    eqinit(testereq);
}