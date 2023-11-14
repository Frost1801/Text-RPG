//
// Created by sergio on 29/05/21.
//

#include "story.h"

void goblinEncounter(struct character *thischar,struct  equipement *thisequip, boolean arrowIn){
    int result;
    printf("(1)Sure man, what's the plan?\n");
    printf("(2)Nah i'm good i just wanna stay a slave to the goblins\n");
    univswitch(&result,2);
    if (result == 1){
        printf("Gheradius: Great, you should take down Boblin the Goblin, he is their stronghest warrior but i think you can handle it\n");
        printf("(1)Of course, I have been trained in your jedi arts by cout duku\n");
        printf("(2)I have the power of er supremo on my side, I can handle it\n");
        univswitch(&result,2);
        if (result == 1){
            printf("*Gheradius seems confused, almost as if he doesn't get the reference*\n");
            printf("Gheradius: Never heard of him\n");
        }
        if (result == 2){
            printf("*Gheradius seems impressed and looks at you with respect*\n");
        }
        printf("Gheradius: When I scream fif and kik attack Boblin the Goblin\n");
        printf("*Gheradius screams *FIF AND KIK* and his man charge into battle following his signal and engaging the goblins*\n");
        printf("*You recognise the signal and attack Boblin the goblin\n*");
        if (arrowIn){
            printf("As you approach the goblin, the arrow falls from your knee and you start to bleed\n");
            thisequip ->bleedr = 3;
            printf("This can't stop you, you have to fight\n");
        }
        struct character BOBLIN;
        struct equipement boblineq;
        goblin_init(&BOBLIN,&boblineq);
        strcpy(BOBLIN.name,"Boblin the Goblin");
        fight(thischar,thisequip,&BOBLIN,&boblineq);
    }
    if (result == 2){
        printf("*Gheradius frowns*\n");
        printf("I had you figured for a coward, but I will still fight to free you and ourselves\n");
        printf("*Gheradius screams *FIF AND KIK* and his man charge into battle following his signal and engaging the goblins*");
        printf("*This could be your chance to escape, what do you wanna do?*\n");
        printf("(1)Stay still in the cart e hope nobody notices you\n");
        printf("(2)Use the confusion around you to try and run away\n");
        univswitch(&result,2);
        if (result == 1){
            printf("Roll for stealth:\n");
            printf("Press (1) to roll\n");
            univswitch(&result,1);
            if (result == 1){
                rd20(&result);
                printf("You rolled (%d + %d) ",result,thischar ->dexb);
                if (result + thischar -> dexb > 15 ){
                    printf("*Nobody notices you and you hide in the cart*");
                }
            }
        }
        if (result == 2){

        }
    }
}

void act1 (struct character *thischar, struct  equipement *thisequip){
    printf("Gheradius: Hey, you. You're finally awake. You were trying to cross the border, right? Walked right into that Imperial ambush, same as us, and that thief over there.\n");
    printf("I hope you didn't bang your head too badly, that tarrasque hit you really hard\n");
    printf("Gheradius: How are you feeling?\n");
    printf("(1)Kinda rough, but i'm ok\n(2)*take out arrow from knee* Could be worse\n");
    int result;
    univswitch(&result,2);
    boolean arrowIn = TRUE;
    if(result == 1){
        printf("Gheradius: Well good, I want to start a rebellion to free ourselves from the goblin captors, are you in?\n");
        printf("By the way did you notice you had an arrow in the knee?\n");
        printf("(1)Yep, I know, it's totally under control\n");
        printf("(2)Yo dude you are right, gotta take this out\n");
        univswitch(&result,2);
        if (result == 1){
            printf("Gheradius: Ok man, if you think so\n");
            printf("About that rebellion, do you wanna help me take down the goblins or not?\n");
            goblinEncounter(thischar,thisequip,arrowIn);

        }
        if (result == 2){
            printf("*You gauge the arrow out of your knee, a little blood comes out but when you wrap a white bandage over it the wound magically heals*");
            arrowIn = FALSE;
            printf("Gheradius: Anyway, About that rebellion, do you wanna help me take down the goblins or not?\n");
            goblinEncounter(thischar,thisequip,arrowIn);
        }
    }
    if(result == 2){
        printf("*You gauge the arrow out of your knee, a little blood comes out but when you wrap a white bandage over it the wound magically heals*");
        arrowIn = FALSE;
        printf("Gheradius: Damn dude, are you sure you are ok? Still, I want to start a rebellion to free ourselves from the goblin captors, are you in?\n");
        goblinEncounter(thischar,thisequip,arrowIn);
    }

}