#include <stdio.h>
#include <stdlib.h>
#include "game_defs.h"

int main(void){
    int unitCount = 0;
    Unit *unitTypes = loadUnits(UNITS_FILE, &unitCount);

    if(!unitTypes || unitCount == 0){
        printf("Failed to load units from %s\n", UNITS_FILE);
        return 1;
    }

    Player p1, p2;
    initPlayer(&p1, "Player 1", unitTypes, unitCount, START_GOLD);
    initPlayer(&p2, "Player 2", unitTypes, unitCount, START_GOLD);

    recalcPlayerStats(&p1);
    recalcPlayerStats(&p2);

    printf("Loaded %d unit types from %s.\n", unitCount, UNITS_FILE);
    printf("%s and %s start with %d gold.\n\n", p1.name, p2.name, START_GOLD);

    showRules();

    int round = 1;
    int winner = 0;

    while(winner == WIN_NONE){
        printf("\n========== ROUND %d ==========\n", round);

        int s1 = 0, s2 = 0;

        // Γύρος Player 1
        playerMenuTurn(&p1, &s1);
        if (s1){
            printf("Winner: %s\n",p2.name);
            break;
        }

        // Γύρος Player 2
        playerMenuTurn(&p2, &s2);
        if (s2){
            printf("Winner: %s\n",p1.name);
            break;
        }

        // Συντήρηση μετά τον γύρο
        applyUpkeep(&p1);
        recalcPlayerStats(&p1);

        applyUpkeep(&p2);
        recalcPlayerStats(&p2);

        printf("\nAfter upkeep:\n");
        printf("%s: gold= %d, attack= %d\n", p1.name, p1.gold, p1.attack_damage);
        printf("%s: gold= %d, attack= %d\n", p2.name, p2.gold, p2.attack_damage);

        // Έλεγχος νικητή
        winner = checkWinner(&p1, &p2);

        if(winner == WIN_NONE){
            // Προστασία: αν κάνουμε πάρα πολλούς γύρους χωρίς νικητή

            round++;
            if (round > 100){
                printf("Too many rounds without a winner. Declaring draw.\n");
                winner = DRAW;
                break;
            }
        }
    }

    if(winner == WIN_P1)
        printf("\n********** FINAL WINNER: %s **********\n", p1.name);
    else if (winner == WIN_P2)
        printf("\n********** FINAL WINNER: %s **********\n", p2.name);
    else if (winner == DRAW)
        printf("\n********** FINAL RESULT: DRAW **********\n");

    printf("\nFinal Status:\n");
    printPlayerStatus(&p1);
    printPlayerStatus(&p2);

    free(unitTypes);
    freePlayer(&p1);
    freePlayer(&p2);

    return 0;
}
