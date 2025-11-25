#include <stdio.h>

int main() {
    int n;

    printf("Dwse enan dipsifio arithmo: ");
    scanf("%d", &n);

    // Elegxos dipsifiou
    if (n < 10 || n > 99) {
        printf("Prepei na dwseis dipsifio arithmo!\n");
        return 0;
    }

    int tens = n / 10;   // dekades
    int ones = n % 10;   // monades

    int result = tens * 1000 + tens * 100 + ones * 10 + ones;

    printf("To apotelesma einai: %d\n", result);

    return 0;
}
