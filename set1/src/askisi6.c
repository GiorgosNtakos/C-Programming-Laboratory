#include <stdio.h>

int main()
{

    float F;
    float C;

    printf("Dwse thn thermokrasia se bathmous fahrenheit: ");
    scanf("%f", &F);

    C = (5.0/9.0)*(F - 32);

    printf("F = %.1f\tC = %.1f", F, C);

    return 0;

}
