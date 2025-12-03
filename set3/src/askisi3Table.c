#include <stdio.h>
#include <string.h>

#define M 256 // μέγιστο μήκος συμβολοσειράς (Μ-1 χαρακτηρες + '\0')
#define MAX_WORDS 100 // μέγιστο αριθμός διακριτών λέξεων του A
#define MAX_POSITIONS 100 // μέγιστες εμφανίσεις κάθε λέξης στο Β
#define MAX_WORD_LEN 50 // μέγιστο μήκος λέξης

// Δομή που αποθηκεύει μια λέξη από το Α και τις θέσεις εμφάνισης της στο  Β

typedef struct{
    char word[MAX_WORD_LEN]; // η λέξη
    int positions[MAX_POSITIONS]; // πίνακας με θέσεις στο Β
    int count; // πόσες θέσεις εχουν αποθηκευτεί
} WordOcc;

// Βοηθητική συνάρτηση: αφαιρεί το '\n' στο τέλος ενός string που διαβάστηκε με fgets
void remove_newline(char *s){
    size_t len = strlen(s);
    if(len > 0 && s[len - 1] == '\n'){
        s[len - 1] = '\0';
    }
}

/* Προσθέτει τη λέξη 'token' στον πίνακα words[] μόνο αν δεν υπάρχει ήδη.
   Αν υπάρχει, απλά δεν κάνει τίποτα.
   Επιστρέφει τον τρέχοντα αριθμό διακριτών λέξεων (wordCount).
*/

int add_unique_word(WordOcc words[], int wordCount, const char *token){

    // έλεγχος αν η λέξη υπάρχει ήδη στο πίνακα
    for (int i = 0; i < wordCount; i++){
        if(strcmp(words[i].word, token) == 0){ // η λέξη υπάρχει ήδη
            return wordCount;
        }
    }

    // νεα λέξη
    if(wordCount < MAX_WORDS){
        strcpy(words[wordCount].word, token); // αντιγραφή της λέξης
        words[wordCount].count = 0; //ακόμα δεν έχει θέσεις στο Β
        wordCount++;
    } else{
        printf("WARNING: Yperbash MAX_WORDS, h lejh '%s' tha agnoeithei\n", token);
    }

    return wordCount;
}

/* Βρίσκει το index (θέση) της λέξης 'token' μέσα στον πίνακα words[].
   Αν τη βρει, επιστρέφει το index (0...wordCount-1), αλλιώς επιστρέφει -1.
*/

int find_word_index(WordOcc words[], int wordCount, const char *token){

    for(int i = 0; i < wordCount; i++){
        if(strcmp(words[i].word, token) == 0){
            return i;
        }
    }
    return -1;
}

int main(void){
    char A[M], B[M];
    WordOcc words[MAX_WORDS]; // πίνακας διακριτών λέξεων του Α
    int wordCount = 0; // πόσες διακριτές λέξεις έχουμε
    char *token;
    char *ptr;
    int index;

    printf("Dwse to keimeno A: ");
    if(fgets(A, M, stdin) == NULL){
        printf("Sfalma sthn anagnwsh toy A.\n");
        return 1;
    }
    remove_newline(A);

    printf("Dwse to keimeno B: ");
    if(fgets(B, M, stdin) == NULL){
        printf("Sfalma sthn anagnwsh toy B.\n");
        return 1;
    }
    remove_newline(B);

    /* ====== 1. Βρισκουμε τις διακριτές λέξεις του Α ===== */

    token = strtok(A, " ");
    while (token != NULL) {
        // Προσθέτουμε τη λέξη μόνο αν δεν υπάρχει ήδη
        wordCount = add_unique_word(words, wordCount, token);

        //παίρνουμε το επόμενο token
        token = strtok(NULL, " ");
    }

    /* ===== 2. Βρίσκουμε το Β και βρίσκουμε τις θέσεις κάθε λέξης =====*/

    /* Χρησιμοποιούμε strtok πάνω στο Β.
       H strtok δεν αντιγράφει, απλά βάζει '\0' στα delimeters μέσα στο Β.
       Όμως ο pointer που επιστρέφει δείχνει σε θέση μέσα στο Πραγματικό string Β.
       ’ρα -> θέση εμφάνισης = (token - B) με pointer arithmetic.
    */

    token = strtok(B, " ");
    while (token != NULL) {
        // Δείκτης στην αρχή της τρέχουσας λέξης μέσα στο Β
        ptr = token;

        //Βρίσκουμε αν αυτή η λέξη υπάρχει στη λίστα words (δηλ. ήταν στον Α)
        index = find_word_index(words, wordCount, token);

        if(index != -1){
            // Η λέξη αυτή υπήρχε στον Α => αποθηκεύουμε θέση εμφάνισης
            int pos = (int)(ptr - B); // pointer arithmetic: θέση χαρακτήρα στο Β

            if (words[index].count < MAX_POSITIONS){
                words[index].positions[words[index].count] = pos;
                words[index].count++;
            } else {
                printf("WARNING: Yperbash MAX_POSITIONS gia thn lejh '%s'\n", words[index].word);
            }
        }

        // Επόμενη λέξη στο Β
        token = strtok(NULL, " ");
    }

    /* ===== 3. Εκτύπωση αποτελεσμάτων ===== */

    printf("\nApotelesmata:\n");
    for (int i = 0; i < wordCount; i++){
        printf("Lejh: %s\n", words[i].word);
        if(words[i].count == 0){
            printf(" Den emfanizeitai sto B.\n");
        } else {
            printf(" Theseis sto B: ");
            for (int j = 0; j < words[i].count; j++){
                printf("%d ", words[i].positions[j]);
            }
            printf("\n");
        }
    }

    return 0;

}


