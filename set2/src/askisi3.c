#include <stdio.h>
#include <ctype.h>  // strlen
#include <string.h> // toupper, isalpha
#include <stdlib.h> // system()

#define MAX_WORD 50 // μεγιστο μηκος λεξης
#define MAX_TRIES 3 // πόσες προσπάθειες έχει ο δεύτερος παικτης

/* Συνάρτηση ελέγχου ύπαρξης χαρακτήρα σε λέξη.
   word : η λέξη (πινακας char -> δηλαδη δεικτης σε char)
   ch   : ο χαρακτήρας που ψάχνουμε (κεφαλαίο)
   Επιστρέφει 1 αν υπάρχει τουλάχστον μια φορά, αλλιώς 0.
*/

int char_in_word(const char word[], char ch){

    int i = 0;

    while (word[i] != '\0') { // διατρέχουμε τη λέξη μέχρι το τέλος της
            if (word[i] == ch){
                return 1; // βρέθηκε χαρακτήρας
            }
            i++;

    }

    return 0; // δεν βρέθηκε χαρακτήρας
}

/* Συνάρτηση για καθαρισμός οθόνης.
   Στα Windows: cls
   Σε  Linux/Mac: clear
*/
void clear_screen(void){

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* Συνάρτηση που τυπώνει την "τρέχουσα μάσκα" της λέξης.
   π.χ. _ Α _ _ Ε
*/

void print_mask(const char mask[]){
    int i = 0;
    while (mask[i] != '\0'){
        printf("%c ", mask[i]);
        i++;
    }
    printf("\n");
}

int main(void)
{
    char secret[MAX_WORD + 1];    // λέξη που δίνει ο p1
    char mask[MAX_WORD + 1];      // μασκα για την εμφάνιση στον p2 (ex. _ _ _ _)
    int used[26] = {0};           // ποιά γράμματα έχουν ήδη δοκιμαστεί (Α-Ζ)
    int attempts_left = MAX_TRIES; // μετρητής προσπαθειών
    int len, found_letters = 0;   // μήκος λέξης & πόσα γράμματα έχουν βρεθεί
    char guess;                   // το γράμμα που μαντεύει ο p2

    // ================= ΠΡΩΤΟΣ ΠΑΙΚΤΗΣ – ΔΙΝΕΙ ΤΗ ΛΕΞΗ ==================
    printf("Paixth 1, dwse mia leksi(xwris kena): ");
    scanf("%50s", secret); // διαβάζουμε μεχρι 50 χαρακτήρες χωρίς κενά

    // Μετατροπή της λέξης σε ΚΕΦΑΛΑΙΑ, για να κάνουμε πιο εύκολη σύγκριση
    len = strlen(secret);
    for (int i = 0; i < len; i++){
        secret[i] = (char)toupper((unsigned char)secret[i]);
    }

    // Δημιουργούμε τη μάσκα: τόσα '_' όσοι και οι χαρακτήρες της λέξης

    for (int i = 0; i < len; i++){
        mask[i] = '_';
    }
    mask[len] = '\0'; // τερματικός χαρακτήρας για το mask

    // Καθαρισμός οθόνης
    clear_screen();

    // ================= ΔΕΥΤΕΡΟΣ ΠΑΙΚΤΗΣ – ΠΑΙΧΝΙΔΙ =====================

    while (attempts_left > 0 && found_letters < len){
        printf("Leksi: ");
        print_mask(mask); // δείχνουμε τι έχει βρεθεί μέχρι τώρα

        printf("Prospatheies poy apomenoun: %d\n", attempts_left);
        printf("Dwse ena gramma: ");

        // Το space prin %c ειναι για αγνοήσει τυχόν \n(πχ. πατωντας enter) που έχει μείνει στο input buffer
        scanf(" %c", &guess);

        // Μετατροπή σε κεφαλαιο

        guess = (char)toupper((unsigned char)guess);

        // Αν δεν είναι γράμμα, αγνόησε το
        if(!isalpha((unsigned char)guess)){
            printf("Prepei na dwseis gramma A-Z.\n\n");
            continue;
        }

        // Έλεγχος αν έχει ήδη δοκιμαστεί αυτό το γράμμα
        int index = guess - 'A'; // A -> 0, B -> 1,..., Z -> 25(ASCII: 'A' = 65)
        if(used[index]){
            printf("To gramma '%c' exei hdh epilexthei.\n\n", guess);
            continue;
        }
        used[index] = 1; // σημειώνουμε οτι αυτό το γράμμα χρησιμοποίηθηκε

        // Έλεγχος αν το γράμμα υπάρχει στη μυστίκη λέξη
        if(char_in_word(secret, guess)){
            //αποκαλύπτουμε όλες τις θέσεις όπου υπάρχεδι αυτό το γράμμα
            int newly_found = 0;
            for(int i = 0; i < len; i++){
                if(secret[i] == guess && mask[i] == '_'){
                    mask[i] = guess;
                    newly_found++;
                }
            }
            found_letters += newly_found;

            printf("Swsto! To gramma '%c' yparxei sti leksh.\n\n", guess);
        } else{
            attempts_left--;
            printf("Lathos. To gramma '%c' den yparxei sth leksh.\n\n", guess);
        }
    }
    // ================= ΤΕΛΟΣ ΠΑΙΧΝΙΔΙΟΥ – ΑΠΟΤΕΛΕΣΜΑ ====================

    if(found_letters == len){
        printf("Sygxaritiria! Vrhkes thn leksh: %s\n", secret);
    } else {
        printf("Den exeis alles prospatheies. H leksh htan: %s\n", secret);
    }

    return 0;
}
