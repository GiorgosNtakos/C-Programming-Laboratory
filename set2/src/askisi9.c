#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int N;

    printf("Dwse N: ");
    scanf("%d", &N);

    if (N < 2){
        printf("Den yparxoyn prwtoi arithmoi.\n");
        return 0;
    }

    // Δυναμικός πίνακας flags
    int *is_prime = malloc((N + 1) * sizeof(int));
    if (is_prime == NULL) {
        printf("Adynamia desmefshs mnhmhs.\n");
        return 1;
    }

    // Βήμα 1: Θεωρούμε όλους πρώτους
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= N; i++){
        is_prime[i] = 1;
    }


    // Βήμα 2 + 3: κόσκινο
    for (int p = 2; p*p <= N; p++){
        if (is_prime[p]){
            // σβήνουμε τα πολλαπλάσια
            for(int k = p*p; k <= N; k +=p){
                is_prime[k] = 0;
            }
        }
    }

    // Εκτύπωση πρώτων
    printf("Prwtoi arithmoi mexri to %d:\n", N);
    for (int i = 2; i < N; i++){
        if(is_prime[i]){
            printf("%d, ", i);
        }
    }
    printf("\n");

    free(is_prime);
    return 0;
}
