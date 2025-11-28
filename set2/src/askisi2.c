#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 20

int main(void)
{
    int freq[MAX_LEN + 1] = {0}; // συχνότητες μηκών λέξεων
    int word_len = 0;            // μήκος τρέχουσας λέξης
    int c;                       // χαρακτήρας εισόδου

    printf("Insert text:\n\n");

    /*
     * Διαβάζουμε χαρακτήρα–χαρακτήρα μέχρι EOF (Ctrl+Z σε Windows)
     */
    while ((c = getchar()) != EOF) {

        /*
         * Αν ο χαρακτήρας είναι γράμμα:
         * το μετράμε ως μέρος της λέξης
         */
        if (isalpha(c)) {
            word_len++;
        }
        else {
            /*
             * Αν ΔΕΝ είναι γράμμα (κενό, τελεία, κόμμα κτλ),
             * τότε η λέξη τελειώνει
             */
            if (word_len > 0) {
                if (word_len <= MAX_LEN)
                    freq[word_len]++;
                word_len = 0;  // μηδενισμός για την επόμενη λέξη
            }
        }
    }

    /*
     * Αν το κείμενο τελειώσει και ήμασταν ΜΕΣΑ σε λέξη,
     * την καταγράφουμε
     */
    if (word_len > 0 && word_len <= MAX_LEN) {
        freq[word_len]++;
    }

    /* ===== ΕΚΤΥΠΩΣΗ ΙΣΤΟΓΡΑΜΜΑΤΟΣ ===== */

    printf("\nWord Length | Number of Occurrences\n\n");

    for (int i = 1; i <= MAX_LEN; i++) {
        printf("%2d\t    | ", i);

        for (int j = 0; j < freq[i]; j++) {
            printf("*");
        }

        printf("\n\n");
    }

    return 0;
}
