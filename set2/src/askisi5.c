#include <stdio.h>

// Αρχικοποίηση Πίνακα
void initialize_table(int n, int table[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            table[i][j] = 0;
        }
    }
    printf("Arxikopoihsh Pinaka Pascal\n");
    table[0][0] = table[1][0] = table[1][1] = 1;

}

// Γεμισμα πίνακα: Πρώτη Στήλη = 1 ολα, Στήλη = Γραμμή  τοτε = 1( η διαγωνιος δηλαδη) αλλιώς  είναι το άθροισμα του στοιχείου ακριβώς από πάνω συν το στοιχείο
// από τα αριστερά του στοιχείου ακριβώς από πάνω
void fill_table(int n, int table[n][n])
{
    for(int i = 2; i < n; i++){
        for(int j = 0; j < n; j++)
        if(j == 0){
            table[i][j] = 1;
        } else if( j == i){
            table[i][j] = 1;
        } else{
            table[i][j] = table[i - 1][j] + table[i - 1][j - 1];
        }
    }
}



int main(void)
{
    int n;

    printf("================= TRIGWNO PASCAL =================\n\n");
    printf("Dwste  to plythos twn grammwn(n) kai twn steilwn(n) poy tha exei o dysdiastatos pinakas(thetikes akeraies times mono): ");
    scanf("%d", &n);

    int table[n][n];

    initialize_table(n, table);
    fill_table(n, table);

    // Εκτύπωση πίνακα
    printf("\nTrigwno Pascal gia n = %d:\n", n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }



}
