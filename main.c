#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "carte.h"
#include "joueur.h"

int random(int a, int b);
bool pair(Carte* croupier, Carte* main);
Carte* merge(Carte* a, Carte* b);

int main(int argc, char** argv) {

    Carte *croupier = (Carte*) malloc(sizeof(Carte) * 5);
    Carte **hands = (Carte**) malloc(sizeof(Carte*) * 3);
    int i = 0, y = 0;

    srand(time(NULL));

    for(i = 0; i < 5; i++) {
        croupier[i].val = random(1, 13);
        croupier[i].col = random(1, 4);
    }

    for(i = 0; i < 3; i++){
        hands[i] = (Carte*) malloc(sizeof(Carte) * 2);
        for(y = 0; y < 2; y++) {
            hands[i][y].val = random(1, 13);
            hands[i][y].col = random(1, 4);
        }
    }


    printf("----- CROUPIER -----\n");

    for(i = 0; i < 5; i++) {
        printf("Carte %d : { valeur %d, couleur %d }\n", i, croupier[i].val, croupier[i].col);
    }

    printf("\n\n-----JOUEURS-----\n");

    for(i = 0; i < 3; i++) {
        printf("Joueur %d : \n", i);
        for(y = 0; y < 2; y++) {
            printf("\t Carte %d : { valeur %d; couleur %d }\n", y, hands[i][y].val, hands[i][y].col);
        }
        if(pair(croupier, hands[i])) {
            printf("PAIR\n");
        } else {
            printf("PAS PAIR\n");
        }
    }    


    free(croupier);
    for(i = 0; i < 3; i++) {
        free(hands[i]);
    }

    return EXIT_SUCCESS;
}

int random(int a, int b){
    return rand()%(b-a) +a;
}


