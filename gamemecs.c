//
// Created by sergi on 27/12/2020.
//

#include "gamemecs.h"


void arrayprint (int *A, int n){ //struttura di supporto per testare la roba
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("(%d)",A[i]);
    printf("\n");
}
void clear (void){
    while ( getchar() != '\n' );
}

void death (){
    printf("\nYou are dead!");
}

void univswitch(int *result, int choiches){ //trigger per un check se è uguale a 1
    char a[3];
    fgets(a,3,stdin);
    if(!strchr(a, '\n'))     //newline does not exist
        while(fgetc(stdin)!='\n');//discard until newline linee magiche che non capisco
    if (strlen(a) > 2){
        printf("\nInvalid lenght");
        *result = FALSE;
        return;
    }

    int i = strtoll(a,NULL,10);
    if (strrchr(a, ' ') != NULL || i > choiches || i < 0){ //controllo presenza di spazi nella mia stringa
        printf("\nInvalid input\n");
        *result = FALSE;
        return;
    }
    //superato questi check l'imput dovrebbe andare bene

    for (int j = 1; j <= choiches; j++){ //controlla che il nostro imput sia effettivamente tra le scelte disponibili
        if (i == j){
            *result = i;
            return;
        }
    }
    printf("\nInvalid input \n");
    *result = FALSE;


}

void charinit ( struct character *thischar, struct equipement *thisequip, boolean ismagic){
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
        thischar ->chab = ((thischar ->cha - 10)/ 2); //bonus sul carisma --> va su carisma
    else
        thischar ->chab = ((thischar ->cha - 11)/ 2);

    //risorse base
    thischar -> ismagic = ismagic;
    thischar -> level = 1; //livello inizializzato a 1
    if (thischar -> con > 10)
        thischar ->MAXHP = (8  + thischar -> conb )* thischar -> level; // la vita è 8 per ogni livello + bonus costituzione * livello
    else
        thischar ->MAXHP = (8 * thischar -> level);
    thischar -> HP = thischar -> MAXHP;
    if (ismagic == TRUE ){
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

void enemyinit ( struct character *thischar, struct equipement *thisequip, boolean ismagic, int level){
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
        thischar ->chab = ((thischar ->cha - 10)/ 2); //bonus sul carisma --> va su carisma
    else
        thischar ->chab = ((thischar ->cha - 11)/ 2);

    //risorse base
    thischar -> ismagic = ismagic;
    thischar -> level = level; //livello
    if (thischar -> con > 10)
        thischar ->MAXHP = (8  + thischar -> conb )* thischar -> level; // la vita è 8 per ogni livello + bonus costituzione * livello
    else
        thischar ->MAXHP = (8 * thischar -> level);
    thischar -> HP = thischar -> MAXHP;

    if (ismagic == TRUE ){
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

void eqinit ( struct equipement *thisequip){ //inizializza l'equipaggiamento e gli status effect

    //bonus dati dall'equipaggiamento (inizializzati a zero)
    strcpy(thisequip ->wname,"Longsword");
    thisequip -> wb = 0; //bonus armi fisiche
    thisequip -> acb = 0; // bonus dato dall'armatura
    thisequip -> mb = 0; //bonus dato alle armi magiche
    thisequip ->dlb = 0; //bonus dato nei dialoghi

    thisequip ->shieldr = -2;
    thisequip ->bleedr = -2;
    thisequip -> poisonr = -2;

    thisequip -> applbleed = FALSE;
    thisequip -> applpoison = FALSE;

    thisequip -> def_stancer = -2;
    thisequip -> off_stancer = -2;

}

void statsprint (struct character *thischar){ //stampa i bonus dati dalle statistiche
    printf("\n\nStats:         Bonus:");
    printf("\nConstitution:  %d (%d)",thischar -> con, thischar ->conb);
    printf("\nDexterity:     %d (%d)",thischar -> dex, thischar -> dexb);
    printf("\nIntelligence:  %d (%d)",thischar -> intel, thischar -> intelb);
    printf("\nCharisma:      %d (%d)",thischar -> cha, thischar -> chab);
}
void ressprint (struct character *thischar){ //printa le risorse del personaggio
    printf("\n\nResources:");
    printf("\nHP: %d/%d",thischar -> HP,thischar -> MAXHP);
    if (thischar -> class == WIZARD || thischar -> class == TRAVELLER)
        printf("\nMP: %d/%d",thischar -> MP,thischar -> MAXMP);
    printf("\nAC: %d",thischar -> AC);
}
void equipprint (struct equipement *thisequip){ //stampa i bonus equipaggiamento
    printf("\n\nEquipement bonus:");
    printf("\nWeapon Bonus:%d",thisequip ->wb);
    printf("\nArmour class Bonus:%d",thisequip ->acb);
    printf("\nMagic Bonus:%d",thisequip ->mb);
    printf("\nCharisma Bonus:%d",thisequip ->dlb);
}

void rd20 (int *roll){ //rolla 1 d20
    *roll = ((rand() % 20) + 1);
}
void rd10 (int *roll){ //rolla 1 d10
    *roll = ((rand() % 10) + 1);
}
void rd6 (int *roll){ //rolla 1 d6
    *roll = ((rand() % 6) + 1);
}
void rd8 (int *roll){ //rolla 1 d8
    *roll = ((rand() % 8) + 1);
}
void rd4 (int *roll){ //rolla 1 d4
    *roll = ((rand() % 4) + 1);
}

void bubble_sort(int a[], int n) { //bubble sort rubato online perchè quello dello sberre faceva schifo
    int i, j, tmp;
    for (i = 0; i < n; i++) {   // loop n times - 1 per element
        for (j = 0; j < n - i - 1; j++) { // last i elements are sorted already
            if (a[j] > a[j + 1]) {  // swop if order is broken
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void turn_printer (struct character *thischar, struct equipement *thisequip){ //serve per stampare le stats ad inizio turno del combattimento
    if (thischar -> class == WARRIOR){
        printf("\n%s    Class:Warrior\nHP:%d/%d AC:%d",thischar -> name,thischar->HP,thischar -> MAXHP,thischar -> AC);
        if (thisequip -> def_stancer > 0 || thisequip -> bleedr > 0 || thisequip -> poisonr > 0 || thisequip -> off_stancer){
            printf("\nActive effects:");
            if (thisequip -> off_stancer > 0 )
                printf("\nOffensive Stance: %d turn/s remaning",thisequip -> off_stancer);
            if (thisequip -> def_stancer > 0 )
                printf("\nDefensive Stance: %d turn/s remaning",thisequip -> def_stancer);
            if (thisequip -> bleedr > 0 )
                printf("\nBleeding: %d turn/s remaning",thisequip -> bleedr);
            if (thisequip -> poisonr > 0 )
                printf("\nPoisoned: %d turn/s remaning",thisequip -> poisonr);
        }
    }
    if (thischar -> class == WIZARD){
        printf("\n%s   Class:Wizard\nHP:%d/%d MP:%d/%d AC:%d",thischar -> name,thischar->HP,thischar -> MAXHP,thischar -> MP, thischar -> MAXMP,thischar -> AC);
        if (thisequip -> shieldr > 0 || thisequip -> bleedr > 0 || thisequip -> poisonr > 0){
            printf("\nActive effects:");
            if (thisequip -> shieldr > 0 )
                printf("\nShield: %d turn/s remaning",thisequip -> shieldr);
            if (thisequip -> bleedr > 0 )
                printf("\nBleeding: %d turn/s remaning",thisequip -> bleedr);
            if (thisequip -> poisonr > 0 )
                printf("\nPoisoned: %d turn/s remaning",thisequip -> poisonr);
        }
    }
    if (thischar -> class == TRAVELLER){
        printf("\n%s    Class:Traveller\nHP:%d/%d MP:%d/%d AC:%d",thischar -> name,thischar->HP,thischar -> MAXHP,thischar -> MP, thischar -> MAXMP,thischar -> AC);
        if (thisequip -> shieldr > 0 || thisequip -> bleedr > 0 || thisequip -> poisonr > 0){
            printf("\nActive effects:");
            if (thisequip -> shieldr > 0 )
                printf("\nShield: %d turn/s remaning",thisequip -> shieldr);
            if (thisequip -> bleedr > 0 )
                printf("\nBleeding: %d turn/s remaning",thisequip -> bleedr);
            if (thisequip -> poisonr > 0 )
                printf("\nPoisoned: %d turn/s remaning",thisequip -> poisonr);
        }
    }
}

void input_name (struct character *thischar){ //funzione per prendere in imput il nome del personaggio
    int checker;
    printf("\nWell, what is your name than?\n");
    do {
        printf("\nInsert character name:");
        fgets(thischar->name, 20, stdin); //usiamo fgets, gli facciamo prendere 21 caratteri così si accorge quando la lunghezza è maggiore di 20
        checker = 1;
        if (strlen(thischar->name) > 20) { //controllo lunghezza maggiore di 20
            printf("\nError, invalid character lenght: must be less than 20 characters");
            checker = 0;
        }

        if (strlen(thischar->name) < 4) { //controllo lunghezza minore di 3
            printf("\nError, invalid character lenght: must be at least 3 characters");
            checker = 0;
        }
        if (strrchr(thischar-> name,' ') != NULL){ //controllo presenza di spazi
            printf("\nError, invalid input: name must not contain spaces");
            checker = 0;
        }
    }
    while (checker == 0); //continua fino a quando non va bene checker
    strtok(thischar -> name, "\n"); // rimuove lo /n a caso che veniva con fgets
    printf("\nWelcome, %s",thischar -> name);
}

void roll4stats(int **A, int n){ //rollare per le stats, 3 d6 fatti n volte, dove n è il numero di abilità per cui rollare
    int checker;
    do {
        printf("\nPress (1) to roll:");
        univswitch(&checker,1);
    }
    while (checker == FALSE); //qui uso il mio universal trigger per rollare
    int *tmp;
    (*A) = (int*)malloc(sizeof(int)*n); //allocazione due vettori, A che contiene i roll effettivi e tmp che è un vettore di supporto
    tmp = malloc(sizeof(int)*(n + 1));
    printf("\nYou rolled:");
    for (int i = 0;i < n + 1; i++){
        tmp[i] = ((rand() % 6 + 1) + (rand() % 6 + 1) + (rand() % 6 + 1)); //randomizza e printa n + 1 elementi, il + 1serve perchè una sarà scartata
        printf("(%d) ",tmp[i]);
    }
    bubble_sort(tmp,(n+ 1)); //sortiamo gli elementi dell'array in modo che il numero più piccolo sia sempre nella prima posizione
    printf("\nThe smallest roll (%d) will be discarded",tmp[0]);
    for (int i = 1, j = 0; i < n + 1; i++){ //copiamo in A gli elementi di tmp tranne il primo che è il primo
        (*A)[j] = tmp[i];
        j++;
    }

}

void arrayfixer(int *tmp,int *j,int n, int *value){ //serve per escludere le stats già selezionate da quelle mostrate
    int k = 0;
    int input;
    int checker = 1;
    for (int i = 0;i < n - *j; i++){ //stampa le stats disponibili per la selezione, j aumenta ad ogni esecuzione di arrayfixer
        printf("%d)(%d)\n",(i + 1),tmp[i]);
    }
    do{
        scanf("%d",&input); //prende l'imput della stat da selezionare
        if (input > n - *j){
            checker = 0;
            printf("\nInvalid input, please input a valid number:\n");
        }
        else
            checker = 1;

    }
    while (checker == 0);

    //continua a chiederlo fino a quando non va bene l'imput

    *value = tmp [(input - 1)]; //ritorna il valore di value in modo che possa essere assegnato

    while (tmp[k] != tmp[input - 1]) //avanza fino a quando k = elemento prima di input
        k++;

    if (k != n - 1){ //controlla se non siamo al penultimo elemento
        for (int i = k; i < n; i++) //partiamo dall'elemento
            tmp[i] = tmp [i + 1];
    }
    *j = *j + 1; //aumenta j in modo che stampi meno elementi via via che ne selezioniamo


}
void assignrolls(struct character *thischar, int *A, int n){
    int tmp [n];
    for (int i = 0; i < n; i++) //inizializzazione di counter come uguale ad A
        tmp [i] = A[i];


    int j = 0;
    int value;
    printf("\nSelect the roll to assign to constitution\n");
    arrayfixer(tmp,&j,n, &value);
    thischar -> con = value;
    printf("\nSelect the roll to assign to dexterity\n");
    arrayfixer(tmp,&j,n, &value);
    thischar -> dex = value;
    printf("\nSelect the roll to assign to intelligence\n");
    arrayfixer(tmp,&j,n, &value);
    thischar -> intel = value;
    printf("\nSelect the roll to assign to charisma\n");
    arrayfixer(tmp,&j,n, &value);
    thischar -> cha = value;
    clear(); // serve per risolvere il problema di un buffer che non era pulito
}