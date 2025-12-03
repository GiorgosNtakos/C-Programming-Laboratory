#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_defs.h"

/*========================= ΕΣΩΤΕΡΙΚΟ: Μέτρημα Γραμμών στο units.txt =========================*/
static int countUnitLines(FILE *fp){
    int count = 0;
    char buf[256];

    while(fgets(buf, sizeof(buf), fp)){
        // Αγνοούμε κενές γραμμές
        if (buf[0] == '\n' || buf[0] == '\r')
            continue;
        count++;
    }

    rewind(fp); // πίσω στην αρχή
    return count;
}

/*========================= Φόρτωση τύπων μονάδων από αρχείο =========================*/
Unit *loadUnits(const char *filename, int *unitCount){
    FILE *fp = fopen(filename, "r");

    if(!fp) {
        perror("Cannot open units file");
        return NULL;
    }

    *unitCount = countUnitLines(fp);
    if(*unitCount == 0){
        fclose(fp);
        return NULL;
    }

    Unit *types = calloc(*unitCount, sizeof(Unit));
    if(!types){
        perror("Calloc unit types");
        fclose(fp);
        return NULL;
    }

    for(int i = 0; i < *unitCount; i++){
        int res = fscanf(fp, "%19s %d %d %d %d", types[i].name,
                                                 &types[i].att,
                                                 &types[i].cost,
                                                 &types[i].sup,
                                                 &types[i].code);
       if (res != 5){
        printf("Warning: bad line in %s, skipping.\n", filename);
        // απλή αντιμετώπιση: μηδενίζουμε το entry
        types[i].name[0] = '\0';
        types[i].att = types[i].cost = types[i].sup = types[i].code = 0;
       }
       types[i].num = 0;
    }
    fclose(fp);
    return types;
}

/*========================= Αρχικοποίηση / free παίκτη =========================*/
void initPlayer(Player *p, const char *playerName, Unit *unitTypes, int unitCount, int startGold){
    strncpy(p -> name, playerName, MAX_NAME_LEN - 1);
    p->name[MAX_NAME_LEN - 1] = '\0';

    p->unitCount = unitCount;
    p->gold = startGold;

    p->units = calloc(unitCount, sizeof(Unit));
    if(!p ->units){
        perror("calloc player units");
        exit(1);
    }

    for (int i = 0; i < unitCount; i++){
        p->units[i] = unitTypes[i];
        p->units[i].num = 0; // οι παιχτες ξεκινάνε χωρίς μονάδες
    }

    // αρχικοποίηση στατιστικών
    p->army_size = 0;
    p->attack_damage = 0;
    p->cost_per_round = 0;

}

void freePlayer(Player *p){
    free(p->units);
    p->units = NULL;
    p->unitCount = 0;
}

/*========================= Επαναϋπολογισμός στατιστικών παίκτη =========================*/
void recalcPlayerStats(Player *p){
    int army = 0;
    int dmg = 0;
    int upkeep = 0;

    for (int i = 0; i< p->unitCount; i++){
        army += p->units[i].num;
        dmg += p->units[i].att * p->units[i].num;
        upkeep += p->units[i].sup * p->units[i].num;
    }

    p->army_size = army;
    p->attack_damage = dmg;
    p->cost_per_round = upkeep;
}

/*========================= Εκτυπώσεις =========================*/
void printUnits(const Unit *units, int unitCount){
     printf("\n+------+--------------+-------+-------+-------+\n");
    printf("| Code | Name         |  Att  | Cost  |  Sup  |\n");
    printf("+------+--------------+-------+-------+-------+\n");
    for(int i = 0; i < unitCount; i++){
        if (units[i].name[0] == '\0') continue; // skip τις λάθος γραμμές
        printf("| %4d | %-12s | %4d | %5d | %5d  |\n", units[i].code,
                                                      units[i].name,
                                                      units[i].att,
                                                      units[i].cost,
                                                      units[i].sup);
    }
    printf("+------+--------------+-------+-------+-------+\n\n");
}

void printPlayerStatus(const Player *p){
    printf("\n========== STATUS: %s ==========\n", p->name);
    printf("Gold:                %6d\n", p->gold);
    printf("Army_size:           %6d\n", p->army_size);
    printf("Total Attack:        %6d\n", p->attack_damage);
    printf("Upkeep / round:      %6d(+: losing, -: gaining)\n", p->cost_per_round);

    printf("\n+--------------+-------+-------+-------+\n");
    printf("| Unit         |  Num  |  Att  |  Sup  |\n");
    printf("+--------------+-------+-------+-------+\n");
    for(int i = 0; i < p->unitCount; i++){
        if (p->units[i].num > 0){
            printf("| %-12.12s | %5d | %5d | %5d |\n", p->units[i].name,
                                                     p->units[i].num,
                                                     p->units[i].att,
                                                     p->units[i].sup);
        }
    }
    printf("+--------------+-------+-------+-------+\n");
    printf("============================================================\n\n");
}

void showRules(void){
    printf("\n========== GAME RULES ==========\n");
    printf("- You and your opponent buy units in turns.\n");
    printf("- Each unit type has:\n");
    printf("    * att  : attack per unit.\n");
    printf("    * cost : gold to buy 1 unit.\n");
    printf("    * sup  : upkeep per round (sup > 0 = cost, sup < 0 = income).\n");
    printf("- Each round:\n");
    printf("    1) Player 1 has a menu of actions.\n");
    printf("    2) Player 2 has a menu of actions.\n");
    printf("    3) Upkeep is applied (gold changes by cost_per_round.\n");
    printf("- Win conditions:\n");
    printf("    * Reach at least %d gold and have more gold than the oppenent,\n", WIN_GOLD);
    printf("      OR\n");
    printf("    * Have at least %d more attack than the oppenent.\n", WIN_ATTACK_DIFF);
    printf("      OR\n");
    printf("    * Enemy Player has negative gold balance(If both players have negative gold balance, then winner determined by the total attack damage of the player).\n");
    printf("- You can also surrender from your turn menu.\n");
    printf("============================================================\n\n");
}

/*========================= Οικονομία/ Συντήρηση =========================*/
int calcUpkeep(const Player *p){
    return p->cost_per_round; // έχουμε 'cache' από recalcPlayerStats
}
void applyUpkeep(Player *p){
    /* cost_per_round = sum(sup*num)
       Αν sup > 0 -> χάνουμε gold
       Αν sup < 0 -> κερδίζουμε gold
    */

    p -> gold -= p->cost_per_round;
}

/*========================= Αγορά Μονάδων =========================*/
void buyUnit(Player *p){
    int code;
    printUnits(p->units, p->unitCount);
    printf("%s, enter unit code to buy (0 to cancel): ", p->name);

    if(scanf("%d", &code) != 1){
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF){}
        printf("Invalid input. Cancelling purchase.\n");
        return;
    }

    if (code == 0){
        printf("Purchase cancelled.\n");
        return;
    }

    for (int i = 0; i < p->unitCount; i++){
        if (p->units[i].code == code){
            if(p->gold < p->units[i].cost){
                printf("Not enough gold to buy %s (cost %d).\n", p->units[i].name, p->units[i].cost);
                return;
            }
            p->gold -= p->units[i].cost;
            p->units[i].num++;
            recalcPlayerStats(p);
            printf("You bought 1 %s. New gold: %d\n", p->units[i].name, p->gold);
            return;
        }
    }

    printf("No unit with code %d.\n", code);
}

/*========================= Μενού γύρου Παίκτη =========================*/
void playerMenuTurn(Player *p, int *surrenderFlag){
    int done = 0;

    while(!done){
        printf("========== %s's TURN MENU ==========\n", p->name);
        printf("1. View gold & gold per round\n");
        printf("2. View army stats\n");
        printf("3. Buy units\n");
        printf("4. Show game rules\n");
        printf("5. End turn\n");
        printf("6. Surrender\n");
        printf("Choice: ");

        int choice;
        if (scanf("%d", &choice) != 1){
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF){}
            printf("Invalid Input.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                int delta = calcUpkeep(p);
                printf("\n[Economy for %s]\n", p->name);
                printf("Current gold: %d\n", p->gold);
                if (delta > 0)
                    printf("Losing %d gold per round.\n", delta);
                else if (delta < 0)
                    printf("Gaining %d gold per round.\n", -delta);
                else
                    printf("Neither losing nor gaining gold per round.\n");
                printf("\n");
                break;
            }
            case 2:
                printPlayerStatus(p);
                break;
            case 3:
                buyUnit(p);
                break;
            case 4:
                showRules();
                break;
            case 5:
                done = 1;
                break;
            case 6:
                printf("%s surrendered!\n", p->name);
                *surrenderFlag = 1;
                done = 1;
                break;
            default:
                printf("Invalid choise. Please pick 1-6.\n");
                break;
        }
    }
}

/*========================= Έλεγχος νικητή =========================*/
int checkWinner(const Player *p1, const Player *p2){
    // Περίπτωση πτώχευσης
    if (p1->gold < 0 && p2->gold >= 0)
        return WIN_P2;
    if (p2->gold < 0 && p1->gold >= 0)
        return WIN_P1;
    if (p1->gold < 0 && p2->gold < 0){
        if(p1->attack_damage > p2->attack_damage)
            return WIN_P1;
        if(p2->attack_damage > p1->attack_damage)
            return WIN_P2;
        if(p1->attack_damage == p2->attack_damage)
            return DRAW; // ΙΣΟΠΑΛΙΑ
    }

    // Νίκη με βάση gold
    if (p1->gold >= WIN_GOLD && p1->gold > p2->gold)
        return WIN_P1;
    if(p2->gold >= WIN_GOLD && p2->gold > p1->gold)
        return WIN_P2;

    // Νίκη με βάση διαφορά επίθεσης
    if (p1->attack_damage >= p2->attack_damage + WIN_ATTACK_DIFF)
        return WIN_P1;
    if (p2->attack_damage >= p1->attack_damage + WIN_ATTACK_DIFF)
        return WIN_P2;

    return WIN_NONE; //κανένας ακόμα
}
