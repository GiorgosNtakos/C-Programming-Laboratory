#include <stdio.h>

int main()
{
    int N, y = 0;

    printf("Dwse enan akeraio arithmo mikrotero toy 20: \n");

    do{

        scanf("%d", &N);

        if(N >= 20  || N <= 0) {

            printf("Lathos eisodos! Prepei na dwseis arithmo 0 < N < 20. Prospathise jana\n");

        }

    } while (N >= 20 || N <= 0);

    for(int i = 1; i < (N+1);  i++)
    {
        y += 9*i*i;
    }

    printf("To apotelesma ths parastashs 3^2 + 6^2 + 9^2+...+(3*N)^2 = %d\n", y);

    return 0;
}
