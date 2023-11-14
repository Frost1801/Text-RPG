#include <stdio.h>
#include "gamemecs.h"
#include "fight.h"
#include "eqchange.h"
#include "enemies.h"
#include <stdlib.h>
#include "story.h"

int main() {
    int *rolls; //vettore che contiene i roll fatti
    int n = 4; //numero di statistiche per cui rollare

    srand(time(NULL));

    struct character PG;
    struct equipement pge;
    input_name(&PG);
    roll4stats(&rolls, n);
    printf("\n\nTime to assign your rolls");
    assignrolls(&PG,rolls,n);
    eqinit(&pge);
    class_picker(&PG,&pge);
    free(rolls);

    act1(&PG,&pge);

    /*
  

    //dichiarazione nemico goblin
    struct character GOBLIN;
    struct equipement goblineq;
    goblin_init(&GOBLIN,&goblineq);
    //fine dichiarazione goblin

    //dichiarazione nemico ghost
    struct character GHOST;
    struct equipement ghosteq;
    ghost_init(&GHOST,&ghosteq);
    //fine dichiarazione ghost

    //inizio dichiarazione golem
    struct character GOLEM;
    struct equipement golemeq;
    rockgolem_init(&GOLEM,&golemeq);
    //fine dichirazione golem

    //inizializzazione del personaggio


    //inizializzazione personaggio
        // servono per il personaggio vero
    ressprint(&PG);
    statsprint(&PG);
    
    encounter(&PG,&pge,&GOBLIN,&goblineq);
    lvup(&PG);
    encounter(&PG,&pge,&GHOST,&ghosteq);
    encounter(&PG,&pge,&GOLEM,&golemeq);

    */

/*
    //personaggio per i test
    struct character TESTER;
    struct equipement testereq;
    tester_init(&TESTER,&testereq);
    class_picker(&TESTER,&testereq);
    ressprint(&TESTER);
    statsprint(&TESTER);
    TESTER.HP = 100;
    //testereq.bleedr = 3;
    //testereq.poisonr = 3;
   // encounter(&TESTER,&testereq,&GOBLIN,&goblineq);
    lvup(&TESTER);
    //encounter(&TESTER,&testereq,&GHOST,&ghosteq);
    encounter(&TESTER,&testereq,&GOLEM,&golemeq);
    //tester
*/


    return 0;
}
