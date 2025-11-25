#include <stdio.h>

int main()
{
    int  n, original, reversed = 0;

    printf("Dwse enan thetiko akeraio pentapsifio arithmo: \n");

    do{

        scanf("%d", &n);

        if(n < 10000  || n > 99999) {

            printf("Lathos eisodos! Prepei na dwseis arithmo 10000 < n < 99999. Prospathise jana\n");
            while (getchar() != '\n') { }

        }

    } while (n < 10000  || n > 99999);

    original = n;

    while(n > 0)
    {
        int digit = n % 10; // Pairnoyme to teleytaio pshfio
        reversed = 10*reversed + digit; // Prosthetoyme to pshfio ston anastrameno
        n /= 10; // Afairoyme to pshfio poy phrame apo ton arxiko arithmo
    }

    printf("O arithmos %d anastrafhke se %d\n", original, reversed);

    return 0;

}
