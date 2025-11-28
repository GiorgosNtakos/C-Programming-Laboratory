#include <stdio.h>
#include <stdlib.h>

// Συνάρτηση που επιστρέφει πίνακα με τα αθροίσματα των γραμμών

int *row_sums(int **table, int rows, int cols){

    int *sums = malloc(rows * sizeof(int));

    if (sums == NULL){
        printf("Adynamia desmefshs mnhmhs\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++){
        sums[i] = 0;
        for (int j = 0; j < cols; j++){
            sums[i] += table[i][j];
        }
    }

    return sums;
}

int main(void)
{
    int rows, cols;

    printf("Dwse arithmo grammwn: ");
    scanf("%d", &rows);
    printf("Dwse arithmo sthlwn: ");
    scanf("%d", &cols);

    // Δέσμευση 2D πίνακα
    int **table = malloc(rows * sizeof(int*));

    if (table == NULL){
        printf("Adynamia desmefshs mnhmhs\n");
        return 1;
    }

    for (int i = 0; i < rows; i++){
        table[i] = malloc(cols * sizeof(int));
        if(table[i] == NULL){
            printf("Adynamia desmefsis mhnmhs\n");
            return 1;
        }
    }

    // Αναγνωση στοιχείων
    printf("Dwse ta stoixeia toy pinaka:\n");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            scanf("%d", &table[i][j]);
        }
    }

    // Κλήση συνάρτησης
    int *sums = row_sums(table, rows, cols);

    // Εκτύπωση νέου πίνακα 1-D
    printf("Athroisma grammwn:\n");
    for(int i = 0; i < rows; i++){
        printf("Grammi %d: %d\n", i, sums[i]);
    }

    // Ελευθερωση μνημης

    free(sums);

    for(int i = 0; i < rows; i++){
        free(table[i]);
    }

    free(table);

    return 0;
}
