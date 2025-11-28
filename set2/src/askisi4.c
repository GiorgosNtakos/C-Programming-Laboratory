#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N 3 // Ποσες λέξεις θα έχει ο πίνακας
#define M 13 // Μεγιστο μηκος λέξης (+1 για '\0')
#define SHIFT 5 // σταθερή μετατόπιση για το κρυπτοσύστημα

// Δομή που κρατάει μια λέξη και το μήκος της
struct word_pair{
    char word[M]; // η ίδια η λέξη
    int length; // το μήκος της (χωρίς το '\0')
};

//(α) Γέμισμα πίνακα με N λέξεις και υπολογισμός μήκους
void fill_table(struct word_pair table[], int n){
    for(int i = 0; i < n; i++){
        printf("Dwse leksi %d (xwris kena, mexri %d xaraktires): ", i + 1, M - 1);
        //%12s : για να μην ξεπεράσουμε το όριο M
        scanf("%12s", table[i].word);

        // Υπολογισμός μήκους με srtlen
        table[i].length = (int)strlen(table[i].word);
    }
}

// Βοηθητική: κωδικοποίηση ενος χαρακτήρα (Aa-Zz)
char encode_char(char c, int shift){
    if (c >= 'A' && c <= 'Z'){
        int pos = c - 'A';
        pos = (pos + shift) % 26;
        return (char) ('A' + pos);
    } else if (c >= 'a' && c <= 'z'){
        int pos = c - 'a';
        pos = (pos + shift) % 26;
        return (char) ('a' + pos);
    } else{
        // Αν είναι ψηφίο ή αλλο σύμβολο, το αφήνουμε όπως είναι
        return c;
    }
}

//(β1) Κωδικοποίηση μιας συμβολοσειράς: in -> out με μετατόπιση shift
void encode_word(const char *in, char *out, int shift){
    int i = 0;
    while (in[i] != '\0'){
        out[i] = encode_char(in[i], shift);
        i++;
    }
    out[i] = '\0';
}

//(β2) Εφαρμογή κρυπτογράφησης σε ολες τις λέξεις του πίνακα
void encode_table(struct word_pair table[], int n, int shift){
    for(int i = 0; i < n; i++){
        // Κωδικοποιούμε τη λέξη table[i].word πάνω στον εαυτό της
        char temp[M];
        encode_word(table[i].word, temp, shift);
        strcpy(table[i].word, temp);
        // Το μήκος δεν αλλάζει
    }
}

//(γ) Αναζήτηση pattern σε κάθε λέξη του πίνακα
void search_in_table(struct word_pair table[], int n, const char *pattern){
    int pat_len = (int)strlen(pattern);

    if (pat_len == 0){
        printf("To pattern einai keno.\n");
        return;
    }

    for (int i = 0; i < n; i++){
        int found_any = 0;
        printf("Leksi %d: %s\n", i + 1, table[i].word);
        printf("Theseis: \n");

        // Απλή γραμμική αναζήτηση υποσυμβολοσειράς
        for (int pos = 0; pos <= table[i].length - pat_len; pos++){
            // Συγκρίνουμε το substring που ξεκινά στη θέση pos με το pattern
            if(strncmp(&table[i].word[pos], pattern, pat_len) == 0){
                printf("[%d,%d] -> \"", pos, pos + pat_len - 1); //εκτυπώνουμε θέση
                for (int k = 0; k < pat_len; k++) {
                    putchar(table[i].word[pos + k]);
                }
                printf("\"\n");
                found_any = 1;
            }
        }

        if(!found_any){
            printf("Kamia emfanisi");
        }
        printf("\n");
    }
}

int main(void){
    struct word_pair word_table[N];

    // (α) Γεμισμα πίνακα με Ν λέξεις και μήκη
    printf("=== GEMISMA PINAKA ===\n");
    fill_table(word_table, N);

    printf("\nArxikes lekseis:\n");
    for (int i = 0; i < N; i++){
        printf("Leksi %d: %s (mikos = %d)\n", i + 1, word_table[i].word, word_table[i].length);
    }

    // (β) Κρυπτογράφηση όλων των λέξεων με μετατόπιση 5
    printf("\n=== KRYPTOGRAFISI ME METATOPISI %d ===\n", SHIFT);
    encode_table(word_table, N, SHIFT);

    printf("\nKwdikopoihmenes lekseis:\n");
    for(int i = 0; i < N; i++){
        printf("Leksi %d: %s\n", i + 1, word_table[i].word);
    }

    //(γ) Αναζήτηση pattern
    char pattern[M];
    printf("\nDwse pattern gia anazitisi (xwris kena): ");
    scanf("%12s", pattern);

    printf("\n=== APOTELESMATA ANAZHTHSHS TOY \"%s\" ===\n", pattern);
    search_in_table(word_table, N, pattern);

    return 0;
}
