#include <stdio.h>
#include <stdlib.h>

// Δέσμευση μνήμης για πίνακα rows x cols

int **allocate_matrix(int rows, int cols){
    int **mat = malloc(rows * sizeof(int *));
    if (mat == NULL){
        printf("Adynamia desmefshs mnhmhs (grammes).\n");
        return NULL;
    }

    for(int i = 0; i < rows; i++){
        mat[i] = malloc(cols * sizeof(int));
        if (mat[i] == NULL){
            printf("Adynamia desmefsis mnhmhs (stili %d).\n", i);
            // καθάρισμα όσων έχουν ήδη δεσμευτεί
            for(int k = 0; k < i; k++){
                free(mat[k]);
            }
            free(mat);
            return NULL;
        }
    }
    return mat;
}

// Απελευθέρωση μνήμης πίνακα
void free_matrix(int **mat, int rows){
    if(!mat) return;
    for(int i = 0; i < rows; i++){
        free(mat[i]);
    }
    free(mat);
}

// Διάβασμα στοιχείων πίνακα
void read_matrix(int **mat, int rows, int cols, const char *name){
    printf("\nPinakas %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            printf("%s[%d][%d] = ", name, i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

// Εκτύπωση πίνακα
void print_matrix(int **mat, int rows, int cols, const char *name){
    printf("Pinakas %s (%d x %d):\n", name, rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("\t%d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


// Πολλαπλασιασμός C = A * B
// Α : n x m, Β : m x n, C : n x n
void multiply(int **A, int **B, int **C, int n, int m){
    for (int i = 0; i < n; i++){ // γραμμές του Α/C
        for (int j = 0; j < n; j++){ // στήλες του Β/C
            int sum = 0;
            for (int k = 0; k < m; k++){ // κ = 0 εως m -1
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }

    }
}

int main(void){
    int n, m;

    printf("Pol/mos pinaka A (n x m) me pinaka B (m x n)\n");
    printf("Dwste n (grammes toy A, sthles toy B): ");
    scanf("%d", &n);
    printf("Dwste m (sthles toy A, grammes toy B): ");
    scanf("%d", &m);

    if(n <= 0 || m <= 0){
        printf("Prepei n, m > 0.\n");
        return 1;
    }

    int **A = allocate_matrix(n, m);
    int **B = allocate_matrix(m, n);
    int **C = allocate_matrix(n, n);

    if (A == NULL || B == NULL || C == NULL){
        free_matrix(A, n);
        free_matrix(B, m);
        free_matrix(C, n);
        return 1;
    }

    read_matrix(A, n, m, "A");
    read_matrix(B, m, n, "B");

    printf("\n\n===== PINAKA A =====\n");
    print_matrix(A, n, m, "A");
    printf("\n===== PINAKA B =====\n");
    print_matrix(B, m, n, "B");

    multiply(A, B, C, n, m);

    printf("Apotelesma C = A * B:\n");
    print_matrix(C, n, n, "C");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}
