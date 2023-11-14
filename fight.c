//
// Created by sergi on 28/12/2020.
//

#include "fight.h"
void fight (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
    int checker = FALSE; //checker serve per vedere se siamo riusciti a scappare oppure no
    boolean is_fleed = FALSE;
    int tcounter = 0; //turn counter

    do {
        printf("\n**********************************************************************\n"); 
        printf("Turn: %d",tcounter);
        printf("\nYour turn:");
        bleed_clock(thischar,thisequip);
        poison_clock(thischar,thisequip);
        if (thischar -> HP > 0){
            turn_printer(thischar,thisequip);
            yourturn(thischar,thisequip,enemy,enemyequip,&checker);
            if (thischar -> class == WIZARD || thischar -> class == TRAVELLER)
                shield_clock(thischar,thisequip);
            else if (thischar -> class == WARRIOR){
                defensive_stance_clock(thischar,thisequip);
                offensive_stance_clock(thischar,thisequip);
            }
            else
                printf("\nSomething went wrong (fight clocks)");
        }

        if (enemy -> HP > 0 && checker == FALSE && thischar -> HP > 0) { // controlla se il nemico è vivo e se non siamo scappati
            bleed_clock(enemy,enemyequip);
            poison_clock(enemy,enemyequip);
            enemyturn(enemy,enemyequip,thischar,thisequip, &is_fleed); //chiamata in questo modo, il nostro nemico diventa il pg e noi diventiamo il nemico
            shield_clock(enemy,enemyequip);
        }


        tcounter ++;
    } while (checker == FALSE && is_fleed == FALSE && thischar ->HP > 0 && enemy -> HP > 0); //fa terminare il combattimento o se siamo scappati, o se siamo morti o se il nemico è morto

}
void defensive_stance_clock (struct character *thischar, struct equipement *thisequip){

    if (thisequip ->def_stancer > 0){ //controlla se la quantità di turni per cui è attivo lo shield è maggiore di 0 (default è -2)
        if (thisequip ->def_stancer== 3) //aumenta la AC solo la prima volta che si esegue ossia quando il turn counter è a 5
            thischar -> AC += 2;
        thisequip ->def_stancer --; //diminuisce i turni
    }

    else if (thisequip ->def_stancer == 0){ //quando raggiunge lo zero la armatura diminuisce di nuovo
        printf("\nDefensive stance bonus has ended!");
        printf("\nAC: %d --> %d",thischar ->AC, thischar -> AC - 2); // printiamo il cambio di AC
        thischar -> AC -= 2; //diminuiamo il valore della armatura dei 2 per cui avevamo aumentato
        thisequip ->def_stancer = -2; //settiamo i round al default ossia -2
    }


}
void offensive_stance_clock (struct character *thischar, struct equipement *thisequip){

    if (thisequip ->off_stancer > 0){ //controlla se la quantità di turni per cui è attivo lo stance è maggiore di 0 (default è -2)
        if (thisequip ->off_stancer== 3) {
            thisequip -> wb += 1;
        }//aumenta la AC solo la prima volta che si esegue ossia quando il turn counter è a 5

        thisequip ->off_stancer --; //diminuisce i turni
    }

    else if (thisequip ->off_stancer == 0){ //quando raggiunge lo zero la armatura diminuisce di nuovo
        printf("\nOffensive stance bonus has ended!");
        thisequip -> wb -= 1; //diminuiamo il valore della armatura dei 2 per cui avevamo aumentato
        thisequip ->off_stancer = -2; //settiamo i round al default ossia -2
    }


}
void shield_clock (struct character *thischar, struct equipement *thisequip){

    if (thisequip ->shieldr > 0){ //controlla se la quantità di turni per cui è attivo lo shield è maggiore di 0 (default è -2)
        if (thisequip ->shieldr == 5) //aumenta la AC solo la prima volta che si esegue ossia quando il turn counter è a 5
            thischar -> AC += 2;
        thisequip -> shieldr --; //diminuisce i turni
    }

    else if (thisequip -> shieldr == 0){ //quando raggiunge lo zero la armatura diminuisce di nuovo
        printf("\nShield spell bonus ended!");
        printf("\nAC: %d --> %d",thischar ->AC, thischar -> AC - 2); // printiamo il cambio di AC
        thischar -> AC -= 2; //diminuiamo il valore della armatura dei 2 per cui avevamo aumentato
        thisequip -> shieldr = -2; //settiamo i round al default ossia -2
    }


}
void bleed_clock (struct character *thischar, struct equipement *thisequip){
    if (thisequip -> bleedr > 0){
        if (thisequip -> bleedr == 3)
            printf("\n%s starts bleeding because of his wounds",thischar -> name);

        printf("\n%s is bleeding!",thischar ->name);
        int roll;
        rd20(&roll);
        if (roll > thischar -> con){
            rd4(&roll);
            printf("\n%s bleeds for (%d) damage",thischar -> name, roll);
            thischar -> HP -= roll;
            if (thischar -> HP <= 0){
                printf("\n%s bleeds to death\n",thischar -> name);
                death();
            }
        }
        else
            printf("\n%s is able to stop the bleeding for this round", thischar -> name);
        thisequip -> bleedr --;
    }
    else if (thisequip -> bleedr == 0){
        printf("\n%s stops bleeding!",thischar -> name);
        thisequip -> bleedr = -2;
    }

}

void poison_clock (struct character *thischar, struct equipement *thisequip){
    if (thisequip -> poisonr > 0){
        if (thisequip -> poisonr == 3)
            printf("\n%s is poisoned!",thischar -> name);
        int roll;
            rd4(&roll);
            printf("\n%s takes (%d) poison damage\n",thischar -> name, roll);
            thischar -> HP -= roll;
        if (thischar -> HP <= 0){
            printf("\n%s dies because of poison\n",thischar -> name);
            death();
        }
        thisequip -> poisonr --;
    }
    else if (thisequip -> poisonr == 0){
        printf("\nThe poison effect stops!");
        thisequip -> poisonr = -2;
    }

}


void yourturn(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker){


    int result;//usato nella universalswitch
if (thischar -> class == WIZARD || thischar -> class == TRAVELLER){
    printf("\n(1)Melee attack\n(2)Standard Magic attack\n(3)Inner Magic\n(4)Flee\n");
    univswitch(&result,4);
    switch (result) { //facciamo una switch sulle varie opzioni che ha il pg durante il suo turno
        case 1:
            melee_strike(thischar,thisequip,enemy,enemyequip);
            break;
        case 2:
            magic_missle(thischar,thisequip,enemy,enemyequip);
            break;
        case 3:
            innermagic(thischar,thisequip,enemy,enemyequip,checker);
            break;
        case 4:{
            *checker = flee(thischar,enemy); //siccome flee è una boolean è TRUE se scappiamo mentre è false altrimenti
            break;
        }
        default:
            printf("\nSomething went wrong (yourturn_wizard_traveller)");


    }
}
else if (thischar -> class == WARRIOR){ //per il warrior abbiamo una switch con solo 3 opzioni siccome non può usare la inner magic
    printf("\n(1)Melee attack\n(2)Warrior stance\n(3)Flee\n");
    univswitch(&result,3);
    switch (result) { //facciamo una switch sulle varie opzioni che ha il pg durante il suo turno
        case 1:
            melee_strike(thischar,thisequip,enemy,enemyequip);
            break;
        case 2:
            stances(thischar,thisequip,enemy,enemyequip,checker);
            break;
        case 3:{
            *checker = flee(thischar,enemy);
            break;
        }
        default:
            printf("\nSomething went wrong (yourturn_warrior)");


    }
}

}
void enemyturn(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, boolean *is_fleed){
    printf("\n\n%s's turn!",thischar -> name); //le azioni del nemico sono attaccare con la magia se è magico e attaccare con la arma se  non lo è
    printf("\n%s: %d",thischar ->name,thischar ->HP);
    int roll;
    if (thischar ->HP < thischar -> MAXHP/3 && thischar ->HP < enemy -> HP ){

        rd20(&roll);
        if (roll > 10){
            *is_fleed = flee_enemy(thischar,enemy);
            return;
        }
    }
    if (thischar -> class == BOSS){
        rd20(&roll);
        if (roll > 17){
            special_atk(thischar,thisequip,enemy,enemyequip);
            return;
        }

    }
    if (thischar -> ismagic == TRUE && thischar -> intel > thischar -> con)
        magic_missle_enemy(thischar,thisequip,enemy,enemyequip);
    else if (thischar -> ismagic == FALSE)
        melee_strike_enemy(thischar,thisequip,enemy,enemyequip);
}

boolean flee (struct character *thischar, struct character *enemy){ //funzione che gestisce la fuga
    printf("\nYou try to flee from the fight");
    printf("\nPress (1) to roll on dexterity");
    int checker = 0; // serve per vedere se abbiamo inserito il giusto valore nella universalswitch
    while (checker == FALSE)
        univswitch(&checker,1);
    int your_roll;
    int enemy_roll;
    rd20(&your_roll); // confrtontiamo il tuo roll con quello del nemico
    rd20(&enemy_roll);
    printf("\nYou rolled %d + %d", your_roll, thischar ->dexb);
    printf("\nYour enemy rolled %d + %d", enemy_roll, enemy ->dexb);

    if ((your_roll + thischar -> dexb) > enemy_roll + enemy ->dexb){ // siamo scappati
        printf("\nYou successfully escape the fight");
        return TRUE;
    }

    else{ // non riusciamo a scappare
        printf("\nYou try to run but you are caught");
        return FALSE;
    }

}
boolean flee_enemy (struct character *thischar, struct character *enemy){ //funzione che gestisce la fuga
    printf("\n%s tries to flee from the fight",thischar -> name);
    printf("\nPress (1) to try and stop them\nPress (2) to let them flee\n");
    int checker = 0; // serve per vedere se abbiamo inserito il giusto valore nella universalswitch
    while (checker == FALSE)
        univswitch(&checker,2);

    if (checker == 1){
        int your_roll;
        int enemy_roll;
        rd20(&your_roll); // roll del nemico in questo caso
        rd20(&enemy_roll); // questo è il tuo roll
        printf("\n%s rolled %d + %d", thischar -> name,your_roll, thischar ->dexb);
        printf("\nYou rolled %d + %d", enemy_roll, enemy ->dexb);

        if ((your_roll + thischar -> dexb) > enemy_roll + enemy ->dexb){ // siamo scappati
            printf("\nYou try to stop the %s, but it's too quick for you",thischar -> name);
            return TRUE;
        }

        else{ // non riusciamo a scappare
            printf("\nYou block the %s and prevent it from running away",thischar -> name);
            return FALSE;
        }
    }
    else if (checker == 2){
        printf("\nYou let the %s excape",thischar -> name);
        return TRUE;
    }
    else{
        printf("\nSomething went wrong (flee_enemy)");
        return FALSE;
    }

}
void magic_missle_enemy (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip) { //funzione attacco magic missle del nemico
    int roll;
    rd20(&roll); //rolla il dado per colpire
    printf("\n%s tries to attack you with magic",thischar -> name);
    printf("\nEnemy rolled (%d + %d)",roll, (thischar ->intelb + thisequip ->mb));

    if ((roll + thischar ->intelb + thisequip ->mb) >= (enemy -> AC + enemyequip -> acb) ){ // controlliamo se il roll + bonus int + bonus eventuale da armi supera la AC
        rd10(&roll); // rolliamo un d10 per il danno
        printf("\n%s hit you for (%d) force damage",thischar -> name, roll + thisequip -> mb);
        enemy ->HP -= (roll + thisequip -> mb); //sottrae il danno fatto dalla tua vita
        if (enemy -> HP <= 0){ //se ti uccide
            printf("\nThe %s strikes you on the chest with a red beam of force, suddenly everithing goes dark", thischar -> name);
            printf("\n%s killed %s using magic missle",thischar ->name, enemy ->name);
        }
    }
    else if ((roll + thischar ->intelb + thisequip ->mb) < (enemy -> AC + enemyequip -> acb) ) // se il roll è meno della AC
        printf("\nEnemy attack misses you");
    else
        printf("\nSomething went wrong (magic missle enemy)");
}
void melee_strike_enemy (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip) {
    printf("\nThe %s attacks you with his %s",thischar-> name, thisequip -> wname);
    int roll;
    boolean crit = FALSE; //serve per vedere se hai crittato
    int i = 0; // sevbe puramente come buffer per fare il critico
    int tmp = 0; // serve come appoggio per la somma dei danni in caso di critico
    rd20(&roll); // roll per colpire
    printf("\n%s rolled (%d + %d)",thischar -> name, roll, (thischar ->conb + thisequip ->wb));
    if (roll == 20){ // se rolli un 20 critti
        printf("\nCritical Hit!");
        crit = TRUE;
    }

    if ((roll +thischar ->conb + thisequip ->wb) >= (enemy -> AC + enemyequip -> acb) || crit == TRUE){ // danno in caso di non critico critico
        if (crit == FALSE){
            rd6(&roll); //roll per il danno
            enemy ->HP -= (roll + thisequip -> wb); // sottrae il danno
            printf("\n%s hits you for (%d) phisical damage",thischar -> name, roll + thisequip -> wb);
        }
        else { //hai crittato
            while (i != 2){
                rd6(&roll); //roll per il danno
                tmp +=roll; // si esegue due volte e poi esce
                i++;
            }
            printf("\n%s hits you for (%d) phisical damage",thischar -> name, tmp + thisequip -> wb);
            enemy ->HP -= (tmp + thisequip -> wb);

        }
        if (thisequip -> applbleed == TRUE)
            applybleed(thischar, thisequip,enemy,enemyequip);
        if (thisequip -> applpoison == TRUE)
            applypoison(thischar,thisequip,enemy,enemyequip);


        if (enemy -> HP <= 0){ // se ti uccide
            printf("\nThe %s hits you too hard and you fall to the ground", thischar -> name);
            printf("\n%s killed %s using %s",thischar ->name, enemy ->name, thisequip -> wname);
        }
    }
    else if ((roll +thischar ->conb + thisequip ->wb) < (enemy -> AC + enemyequip -> acb)) // non supera la AC
        printf("\n%s attack misses you",thischar -> name);
    else
        printf("\nSomething went wrong (Melee strike enemy)");
}

void magic_missle (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip) {
    printf("\nYou point your hand at the enemy and a magical beam hurls towards them");
    int roll; // rolla il d20
    rd20(&roll);
    printf("\nYou rolled (%d + %d)",roll, (thischar ->intelb + thisequip ->mb));

    if ((roll + thischar ->intelb + thisequip ->mb) >= (enemy -> AC + enemyequip -> acb) ){ // supera la AC
        rd10(&roll); // rolla i danni
        printf("\nYou hit the %s for (%d) force damage",enemy -> name, roll + thisequip -> mb);
        enemy ->HP -= (roll + thisequip -> mb); // sottrae la vita
        if (enemy -> HP <= 0){ // se lo uccidi
            printf("\nThe enemy crumbles to the ground in a cloud of smoke");
            printf("\n%s killed %s using magic missle",thischar ->name, enemy ->name);
        }
    }
    else if ((roll + thischar ->intelb + thisequip ->mb) < (enemy -> AC + enemyequip -> acb) ) // se non superi la AC
        printf("\nYour attack misses the target");
    else
        printf("\nSomething went wrong (magic missle)");
}
void melee_strike (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip) {
    printf("\nYou strike at the enemy with your weapon");
    int roll;
    boolean crit = FALSE;
    int i = 0;
    int tmp = 0;
    rd20(&roll);
    printf("\nYou rolled (%d + %d)",roll, (thischar ->conb + thisequip ->wb));
    if (roll == 20){
        printf("\nCritical Hit!");
        crit = TRUE;
    }

    if ((roll +thischar ->conb + thisequip ->wb) >= (enemy -> AC + enemyequip -> acb) || crit == TRUE){
        if (crit == FALSE){
            rd6(&roll); //roll per il danno
            enemy ->HP -= (roll + thisequip -> wb);
            printf("\nYou hit the creature for (%d) phisical damage", roll + thisequip -> wb);
        }
        else { //hai crittato
            while (i != 2){
                rd6(&roll); //roll per il danno
                tmp +=roll;
                i++;
            }
            printf("\nYou hit the creature for (%d) phisical damage", tmp + thisequip -> wb);
            enemy ->HP -= (tmp + thisequip -> wb);

        }
        if (thisequip -> applbleed == TRUE)
            applybleed(thischar, thisequip,enemy,enemyequip);
        if (thisequip -> applpoison == TRUE)
            applypoison(thischar,thisequip,enemy,enemyequip);


        if (enemy -> HP <= 0){
            printf("\nThe enemy drops before your eyes in a pond of its blood");
            printf("\n%s killed %s using %s",thischar ->name, enemy ->name, thisequip -> wname);
        }
    }
    else if ((roll +thischar ->conb + thisequip ->wb) < (enemy -> AC + enemyequip -> acb))
        printf("\nYour attack misses the target");
    else
        printf("\nSomething went wrong (Melee strike)");
}

void encounter(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
   if (thischar -> HP > 0){
       int result;
       printf("\n\nYou find a %s",enemy ->name);
       printf("\nWhat do you want to do?");
       printf("\n(1)Fight\n(2)Try to flee\n");

       do{
           univswitch(&result,2); //chiama la switch universale con le due opzioni combattere o scappare
       }
       while (result == FALSE);
       if (result == 1)
           fight(thischar,thisequip,enemy,enemyequip);


       else if (result == 2)
           if (flee(thischar,enemy) == FALSE){ // se non riesci a scappare, il nemico inizia facendo il primo attacco
               enemyturn(enemy,enemyequip,thischar,thisequip,FALSE); // chiamato nell'ordine in cui tu sei il nemico e il nemico è il pc
               fight(thischar,thisequip,enemy,enemyequip); // chiamata la funzione per la fight
           }
   }

}

void innermagic (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker){
    int result;
    printf("\nInner Magic");
    printf("\n(1)Firebolt - Cost: 2MP\n  \"deals 2d10 fire damage\" ");
    printf("\n(2)Healing Word - Cost: 2MP\n  \"Restores 1d8 + int life\" ");
    printf("\n(3)Shield - Cost: 3 MP\n  \"Increases your AC rating by 2 for the next 5 turns \" ");
    printf("\n(4)Plasma Rays - Cost 5 MP\n  \"Hurl 3 orbs of plasma at the enemy and deal 2d6 damage for each  \" ");
    printf("\n(5)Back\n");
    do{

        univswitch(&result,5); //chiama la switch universale con le opzioni della inner magic
    }
    while (result == FALSE);
    switch (result) { //facciamo una switch sulle varie opzioni c
        case 1:{
            if (manacost(thischar,thisequip,enemy,enemyequip,checker,2) == TRUE) {
                firebolt(thischar, thisequip, enemy, enemyequip);

            }
            break;
        }
        case 2:{
            if (manacost(thischar,thisequip,enemy,enemyequip,checker,2) == TRUE){
                healingword(thischar);

            }
            break;
        }
        case 3:{
            if (thisequip ->shieldr < 0){
                if (manacost(thischar,thisequip,enemy,enemyequip,checker,3) == TRUE){
                    shield(thischar, thisequip);

                }
                break;
            }
            if (thisequip -> shieldr >= 0){
                printf("\nShield is already active, effect is not stackable");
                yourturn(thischar,thisequip,enemy,enemyequip,checker);

            }
            break;
        }
        case 4:{
            if (manacost(thischar,thisequip,enemy,enemyequip,checker,5) == TRUE){
                plasmarays(thischar,thisequip,enemy,enemyequip);

            }
            break;
        }
        case 5: {
            yourturn(thischar,thisequip,enemy,enemyequip,checker);
            break;
        }

        default:
            break;

    }
}

void firebolt(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
    printf("\nYou point your finger at the enemy and mumble words of power");
    thischar ->MP -=2; //diminuisce i punti magici del personaggio
    int roll, roll1;
    rd20(&roll); // roll per colpire
    printf("\nYou rolled (%d + %d)",roll, (thischar ->intelb + thisequip ->mb));

    if ((roll + thischar ->intelb + thisequip ->mb) >= (enemy -> AC + enemyequip -> acb) ){ // supera la AC
        rd10(&roll);// rolla i danni
        rd10(&roll1); //abbiamo bisogno di due roll perché rolla 2 d10
        printf("\nYou hit the %s for (%d) fire damage",enemy -> name, roll + thisequip -> mb + roll1);
        enemy ->HP -= (roll + thisequip -> mb + roll1); // sottrae la vita
        if (enemy -> HP <= 0){ // se lo uccidi
            printf("\nThe %s catches fire and burns to ashes",enemy ->name);
            printf("\n%s killed %s using firebolt",thischar ->name, enemy ->name);
        }
    }
    else if ((roll + thischar ->intelb + thisequip ->mb) < (enemy -> AC + enemyequip -> acb) ) // se non superi la AC
        printf("\nYour attack misses the target");
    else
        printf("\nSomething went wrong (firebolt)");
}
void plasmarays (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
    printf("\nYou focus your mind on the enemy and 3 spheres of plasma leap from your eyes");
    thischar ->MP -=5; //diminuisce i punti magici del personaggio
    int roll, roll1;
    boolean isdead = FALSE; //serve per smettere di attaccare il nemico se è morto

    for (int i = 1; i < 4 && isdead == FALSE ; i++){ //esegue 3 volte per il numero di sfere che abbiamo
        printf("\nOrb n.%d",i);
        rd20(&roll); // roll per colpire
        printf("\nYou rolled (%d + %d)",roll, (thischar ->intelb + thisequip ->mb));
        if ((roll + thischar ->intelb + thisequip ->mb) >= (enemy -> AC + enemyequip -> acb) ){ // supera la AC
            rd6(&roll);// rolla i danni
            rd6(&roll1);
            printf("\nYou hit the %s for (%d) plasma damage",enemy -> name, roll + thisequip -> mb + roll1);
            enemy ->HP -= (roll + thisequip -> mb + roll1); // sottrae la vita
            if (enemy -> HP <= 0){ // se lo uccidi
                printf("\nThe %s's mind and body shatters against your blows and he drops to the ground with burnt eyes",enemy ->name);
                printf("\n%s killed %s using Plasma rays",thischar ->name, enemy ->name);
                isdead = TRUE;
            }
        }
        else if ((roll + thischar ->intelb + thisequip ->mb) < (enemy -> AC + enemyequip -> acb) ) // se non superi la AC
            printf("\nYour attack %d misses the target",i);
        else
            printf("\nSomething went wrong (Plasam rays)");
    }

}
void healingword (struct character *thischar){
    thischar ->MP -=2;
    int roll, tmp;
    printf("\nYou place both hands on your chest and a magical light starts to radiate from them");
    rd8(&roll);
    printf("\nYou heal yourself for %d HP",(roll + thischar -> intelb ));
    tmp = thischar -> HP;
    if (roll + thischar -> intelb + thischar -> HP >= thischar -> MAXHP)
        thischar -> HP = thischar -> MAXHP;
    else if (roll + thischar -> intelb + thischar -> HP < thischar -> MAXHP)
        thischar -> HP = thischar -> HP + roll + thischar -> intelb;
    printf("\nHP:%d --> %d",tmp,thischar -> HP);
}
void shield (struct character *thischar, struct equipement *thisequip){
    printf("\nYou pray to the gods and a magical aura of protection starts to surround you");
    printf("\nAC: %d --> %d",thischar ->AC, thischar -> AC + 2);
    thisequip -> shieldr = 5;
    thischar -> MP -= 3;
}

boolean manacost (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker, int cost){
    if (thischar -> MP < cost){
        printf("\nNot Enough Mana!");
        yourturn(thischar,thisequip,enemy,enemyequip,checker);
        return  FALSE;
    }
    else
        return TRUE;
}

void applybleed(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
    if (thisequip -> applbleed == TRUE){ //conntrolla se applybleed è true, se sì rolla un d20
        int roll;
        rd20(&roll);
        if (roll > 12 + thischar -> conb){ //controlla se il roll' è maggiore di 12 + bonus const
            printf("\n%s hits %s with his %s",thischar -> name, enemy -> name, thisequip -> wname);
            printf("\n%s starts bleeding!",enemy -> name);
            enemyequip -> bleedr = 3;
        }
    }
}
void applypoison(struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip){
    if (thisequip -> applpoison == TRUE){
        int roll;
        rd20(&roll);
        if (roll > 17){
            printf("\n%s hits %s with his %s",thischar -> name, enemy -> name, thisequip -> wname);
            printf("\n%s has been poisoned",enemy -> name);
            enemyequip -> poisonr = 3;
        }
    }
}

void stances (struct character *thischar, struct equipement *thisequip, struct character *enemy,struct equipement *enemyequip, int *checker){
    int result;
    printf("\nWarrir Stances");
    printf("\n(1)Offensive stance\n  \"Take a more offensive stance and receive a +1 to damage and dice rolls to hit with melee weapons for 3 turns\" ");
    printf("\n(2)Defensive stance\n  \"Bolster your defence and recive a +2 bonus to AC for 3 turns\" ");
    printf("\n(3)Back\n");
    do{

        univswitch(&result,3); //chiama la switch universale con le opzioni delle stances
    }
    while (result == FALSE);

    switch (result) { //facciamo una switch sulle varie opzioni c
        case 1:{
            if (thisequip -> def_stancer != -2 || thisequip -> off_stancer != -2){
                printf("\nYou can't use two stances in contemporary");
                yourturn(thischar,thisequip,enemy,enemyequip,checker);
            }
            else {
                offensive_stance(thischar,thisequip);
            }

            break;
        }
        case 2:{
            if (thisequip -> def_stancer != -2 || thisequip -> off_stancer != -2){
                printf("\nYou can't use two stances in contemporary");
                yourturn(thischar,thisequip,enemy,enemyequip,checker);
            }
            else {
                defensive_stance(thischar,thisequip);
            }
            break;
        }
        case 3: {
            yourturn(thischar,thisequip,enemy,enemyequip,checker);
            break;
        }

        default:
            break;

    }
}

void defensive_stance (struct character *thischar, struct equipement *thisequip){
    printf("\nYou take a defensive and cautious approach to the battle and focus on your defence");
    printf("\nAC: %d --> %d",thischar ->AC, thischar -> AC + 2);
    thisequip -> def_stancer = 3;
}
void offensive_stance (struct character *thischar, struct equipement *thisequip){
    printf("\nYou change your approach to battle and concentrate on the offence");
    printf("\nDamage and attack rolls are increased by one!");
    thisequip -> off_stancer = 3;
}

void special_atk (struct character *thischar, struct equipement *thisequip, struct character *enemy, struct equipement *enemyequip){
    printf("\n%s",thisequip -> spatkdescr);//diminuisce i punti magici del personaggio
    int roll, roll1;
    rd20(&roll); // roll per colpire
    printf("\n%s rolled (%d + %d)",thischar -> name,roll, (thischar ->intelb + thisequip ->mb));

    if ((roll + thischar ->intelb + thisequip ->mb) >= (enemy -> AC + enemyequip -> acb) ){ // supera la AC
        int dmg = 0;
        for (int i = 0; i < thischar -> level; i ++){
            rd6(&roll);// rolla i danni
            dmg += roll;
        }

        printf("\n%s hits for (%d) damage",thischar -> name, dmg);
        enemy ->HP -= (dmg + thisequip -> mb); // sottrae la vita
        if (enemy -> HP <= 0){ // se lo uccidi
            printf("%s %s",enemy -> name, thisequip -> spdeath);
        }
    }
    else if ((roll + thischar ->intelb + thisequip ->mb) < (enemy -> AC + enemyequip -> acb) ) // se non superi la AC
        printf("\n%s attack misses you", thischar -> name);
    else
        printf("\nSomething went wrong (special atk)");
}