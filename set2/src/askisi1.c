#include <stdio.h>

#define SIZE 10 // μεγεθος πινακα

/* Συνάρτηση που τυπώνει τον πίνακα.
   arr  : ο πίνακας (ως δείκτης στο πρώτο στοιχείο)
   size : πόσα στοιχεία έχει
*/

void print_array(int arr[], int size){

    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    printf("\n");

}

/* Συνάρτηση που κάνει εναλλαγή (swap) δύο ακεραίων.
   Παίρνει διευθυνσεις (int *) ωστε να αλλάζει τις τιμές έξω από την συνάρτηση.
*/

void swap(int *a, int *b){

    int temp = *a; // temp κρατάει την τιμή στην οποία δείχνει το a
    *a = *b; // γράφουμε στη θέση a την τιμή απο τη θέση b
    *b = temp; // και στη θέση b γράφουμε την παλιά τιμή του a

}

/* Συνάρτηση BubbleSort
   Ταξινομεί τον πίνακα σε αύξουσα σειρά
   Κάθε φορά που γίνεται swap, τυπώνουμε τον πίνακα
*/

void bubble_sort(int arr[], int size){

    int swapped; // flag: αν έγινε κάποια ανταλλαγή σε αυτό το πέρασμα

    // Εξωτερικός βρόχος: επαναλαμβάνουμε τα "περάσματα"
    for (int pass = 0; pass < size - 1; pass++){
        swapped = 0; // στην αρχή κάθε περάσματος υποθέτουμε ότι δεν θα χρειαστεί swap

        // Εσωτερικός βρόχος: συγκρίνουμε γειτονικά ζευγάρια
        for (int i = 0; i < size - 1 - pass; i++){
            if(arr[i] > arr[i + 1]){
                // αν είναι σε λάθος σειρά, τα ανταλλάσουμε
                swap(&arr[i], &arr[i+1]); // περνάμε διευθυνσεις στοιχειων
                swapped = 1;

                // καθε φορά που γίνεται swap, δείχνουμε την τρέχουσα κατάσταση του πίνακα
                print_array(arr, size);
            }
        }
        // Αν σε ένα πέρασμα δεν έγινε κανένα swap, ο πίνακας είναι ήδη ταξινομημένος
        if(!swapped){
            break;
        }
    }

}

int main(void)

{
    int arr[SIZE]; // πινακας 10 θέσεων

    printf("Dwse %d akeraious gia taxinomisi (BubbleSort):\n", SIZE);

    // Διαβάζουμε στοιχεία στον πίνακα
    for (int i = 0; i < SIZE; i++){
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    printf("\nArxikos pinakas:\n");
    print_array(arr, SIZE);

    printf("\nTaxinomisi me BubbleSort:\n");
    bubble_sort(arr, SIZE);

    printf("\nTelikos taxinomhmenos pinakas:\n");
    print_array(arr, SIZE);

    return 0;
}
