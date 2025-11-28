#include <stdio.h>

#define N 3

void gaussian(double A[N][N+1], double x[N]){
    for (int k = 0; k < N; k++){
        double pivot = A[k][k];
        if (pivot == 0){
            printf("Mhdenikos pivot.\n");
            return;
        }
        for (int j = k; j <= N; j++){
            A[k][j] /= pivot;
        }
        for( int i = k + 1; i < N; i++){
            double factor = A[i][k];
            for(int j = k; j <= N; j++){
                A[i][j] -= factor * A[k][j];
            }
        }
    }

    for (int i = N-1; i >= 0; i--) {
        x[i] = A[i][N];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
    }
}

int main(void){
    double A[N][N+1];
    double x[N];

    printf("Dwse toys syntelestes toy systhmatos 3x3 (ka8e grammi A kai meta to deksi melos): \n");
    for (int i = 0; i < N; i++){
        printf("Grammi %d: a%d1 a%d2 a%d3 b%d: ", i+1, i+1, i+1, i+1, i+1);
        for(int j = 0; j <= N; j++){
            scanf("%lf",&A[i][j]);
        }
    }

    printf("Systhma %dx%d:\n", N, N);

    for (int i = 0; i < N; i++) {
        printf("%+.4lfx1 %+.4lfx2 %+.4lfx3 = %+.4lf\n", A[i][0], A[i][1], A[i][2], A[i][N]);
    }




    gaussian(A, x);

    printf("Lyseis:\n");
    for(int i = 0; i < N; i++){
        printf("x%d = %.4lf\n", i+1, x[i]);
    }

    return 0;
}
