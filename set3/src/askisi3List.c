#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 256 // μέγιστο μήκος συμβολοσειράς (Μ-1 χαρακτηρες + '\0')
#define MAX_WORDS 100 // μέγιστο αριθμός διακριτών λέξεων του A
#define MAX_WORD_LEN 50 // μέγιστο μήκος λέξης

// Κόμβος λίστας για τις θέσεις εμφάνισης
typedef struct PosNode{
    int pos; // θέση εμφάνισης στο Β
    struct PosNode *next; // δείκτης στον επόμενο κόμβο
} PosNode;

// Δομή για μια λέξη και λίστα από θέσεις εμφάνισεις
typedef struct{
    char word[MAX_WORD_LEN];
    PosNode *head; // αρχή της συνδεδεμένης λίστας
} WordOccList;

// Βοηθητική συνάρτηση: αφαιρεί το '\n' στο τέλος ενός string που διαβάστηκε με fgets
void remove_newline(char *s){
    size_t len = strlen(s);
    if(len > 0 && s[len - 1] == '\n'){
        s[len - 1] = '\0';
    }
}

/* Προσθέτει μια νέα θέση pos στην αρχή της λίστας positions (head).
   Επιστρέφει τον νέο head της λίστας.
*/

PosNode* add_position(PosNode *head, int pos){
    PosNode *newNode = (PosNode *)malloc(sizeof(PosNode));
    if(newNode == NULL){
        printf("Sfalma: apotyxia desmeyshs mnhmhs.\n");
        return head; // δεν αλλάζουμε λίστα
    }
    newNode->pos = pos;
    newNode->next = head; // εισαγωγή στην αρχή
    return newNode; // νέος head
}

/* Προσθέτει νέα λέξη αν δεν υπάρχει ήδη στον πίνακα words[].
   Αν προσθετεί αρχικοποιούμε head = NULL.
*/

int add_unique_word_list(WordOccList words[], int wordCount, const char *token){

    // έλεγχος αν η λέξη υπάρχει ήδη στο πίνακα
    for (int i = 0; i < wordCount; i++){
        if(strcmp(words[i].word, token) == 0){ // η λέξη υπάρχει ήδη
            return wordCount;
        }
    }

    // νεα λέξη
    if(wordCount < MAX_WORDS){
        strcpy(words[wordCount].word, token); // αντιγραφή της λέξης
        words[wordCount].head = NULL; //αρχικά δεν έχει θέσεις
        wordCount++;
    } else{
        printf("WARNING: Yperbash MAX_WORDS, h lejh '%s' tha agnoeithei\n", token);
    }

    return wordCount;
}

/* Βρίσκει το index (θέση) της λέξης 'token' μέσα στον πίνακα words[].
   Αν τη βρει, επιστρέφει το index (0...wordCount-1), αλλιώς επιστρέφει -1.
*/

int find_word_index_list(WordOccList words[], int wordCount, const char *token){

    for(int i = 0; i < wordCount; i++){
        if(strcmp(words[i].word, token) == 0){
            return i;
        }
    }
    return -1;
}

/* Αποδεσμεύει όλη τη μνήμη των λιστών positions*/
void free_positions_lists(WordOccList words[], int wordCount){
    for(int i = 0; i < wordCount; i++ ){
        PosNode *current = words[i].head;
        while(current != NULL){
            PosNode *temp = current;
            current = current->next;
            free(temp);
        }
        words[i].head = NULL;
    }
}

int main(void){
    char A[M], B[M];
    WordOccList words[MAX_WORDS]; // πίνακας διακριτών λέξεων του Α
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
        wordCount = add_unique_word_list(words, wordCount, token);

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
        index = find_word_index_list(words, wordCount, token);

        if(index != -1){
            // Η λέξη αυτή υπήρχε στον Α => αποθηκεύουμε θέση εμφάνισης
            int pos = (int)(ptr - B); // pointer arithmetic: θέση χαρακτήρα στο Β

            // προσθέτουμε νέο κόμβο στην αρχή της λίστας για αυτή τη λέξη
            words[index].head = add_position(words[index].head, pos);
        }

        // Επόμενη λέξη στο Β
        token = strtok(NULL, " ");
    }

    /* ===== 3. Εκτύπωση αποτελεσμάτων ===== */

    printf("\nApotelesmata:\n");
    for (int i = 0; i < wordCount; i++){
        printf("Lejh: %s\n", words[i].word);
        if(words[i].head == NULL){
            printf(" Den emfanizeitai sto B.\n");
        } else {
            printf(" Theseis sto B: ");
            PosNode *current = words[i].head;
            while(current != NULL){
                printf("%d ", current->pos);
                current = current->next;
            }
            printf("\n");
        }
    }

    free_positions_lists(words, wordCount);

    return 0;

}
