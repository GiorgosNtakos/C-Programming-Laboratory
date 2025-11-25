#include<stdio.h>

int main()
{
    int F0 = 0, F1 = 1, N;

    printf("___________________________");
    printf("|  Fibonacci    Sequence  |");
    printf("___________________________\n\n");

    printf("Parakalw dwste enan akeraio gia to orio ths akoloythias Fibonacci: \n");
    scanf("%d", &N);

    if(N > 20) N = 20;

    printf("%d\t%d\t", F0, F1);
    int count = 2;

    for(int i = 2; i < N; i++)
    {
        printf("%d\t", F1+F0);
        count++;
        int temp = F1;
        F1 += F0;
        F0 = temp;
        if (count == 5){
            printf("\n\n");
            count = 0;
        }
    }

    return 0;
}
