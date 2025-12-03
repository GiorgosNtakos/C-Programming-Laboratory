#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include <stdio.h>

/*========================= CONSTANTS =========================*/
#define MAX_NAME_LEN 20
#define START_GOLD 50      // αρχικό balance
#define WIN_GOLD 200       // νίκη αν φτάσεις τόσα gold
#define WIN_ATTACK_DIFF 20 // νίκη αν έχεις > 20 επίθεση απο τον αντίπαλο
#define WIN_NONE 0
#define WIN_P1 1
#define WIN_P2 2
#define DRAW 3
#define UNITS_FILE "units.txt"

/*========================= STRUCTS =========================*/

// Τύπος μονάδας
typedef struct {
    char name[20]; // όνομα μονάδας
    int att;       // επίθεση
    int cost;      // κόστος αγοράς
    int sup;       // συντήρηση ανά γύρο (+ χανει, - κερδίζει)
    int code;      // κωδικός επιλογής
    int num;       // πόσες έχει ο παίκτης
} Unit;

// Παίκτης
typedef struct {
    char name[MAX_NAME_LEN]; // πίνακας μονάδων
    Unit *units;             // Δυναμικός πίνακας τύπων μονάδων
    int unitCount;           // πόσοι τύποι μονάδων υπάρχουν
    int gold;                // χρυσός που έχει
    int army_size;           // συνολικός αριθμός μονάδων (αθροισμα num)
    int attack_damage;       // συνολικό damage (αθροισμα att*num)
    int cost_per_round;       // συνολική συντήρηση ανά γύρο (sum sup*num)
} Player;

/*========================= FUNCTIONS =========================*/

// Φορτώνει τους τύπους μονάδων από το αρχείο. Επιστρέφει δυναμικό πίνακα.
Unit *loadUnits(const char *filename, int *unitCount);

// Αρχικοποιεί έναν παίκτη με όνομα, αρχικό gold και αντιγραφή του πίνακα unitTypes.
void initPlayer(Player *p, const char *playerName, Unit *unitTypes, int unitCount, int startGold);

// Απελευθερώνει τη μνήμη ενός παίκτη
void freePlayer(Player *p);

// Επαναϋπολογίζει army_size, attack_damaga, cost_per_round, από τα units[].
void recalcPlayerStats(Player *P);

// Εκτυπώνει όλα τα διαθέσιμα unit types (όπως τα βλέπει ο παίκτης)
void printUnits(const Unit *units, int unitCount);

// Εκτυπώνει τα συνολικά stats του παίκτη (gold, army, attack κτλ.)
void printPlayerStatus(const Player *p);

// Εμφανίζει τους κανόνες του παιχνιδιού
void showRules(void);

// Υπολογίζει την καθαρή συντήρηση (cost_per_round).
int calcUpkeep(const Player *p);

// Εφαρμόζει τη συντήρηση στον παίκτη (gold = gold - cost_per_round).
void applyUpkeep(Player *p);

// Αγοράζει 1 μονάδα με βάση το code (μέσα από menu).
void buyUnit(Player *p);

// Μενού για έναν γύρο παίκτη
void playerMenuTurn(Player *p, int *surrederFlag);

// Αναγνωρίζει τον νικητή : 0 -> κανένας νικητής, 1 -> νικη P1, 2 -> νίκη P2, 3 -> Ισοπαλία.
int checkWinner(const Player *p1, const Player *p2);

#endif // GAME_DEFS_H
