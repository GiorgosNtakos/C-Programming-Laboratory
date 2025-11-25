#include <stdio.h>

int main()
{
    int n = 0, sum_for = 0, sum_while = 0, sum_do = 0;
    int sum2_for = 0, sum2_while = 0, sum2_do = 0;

    // ===============================
    // 19η άσκηση: i^2
    // ===============================

    printf("_______________________________________");
    printf("|  Athroisma twn n prwtwn tetragwnwn  |");
    printf("_______________________________________\n\n");

    printf("Dwse to orio n(thetiko akeraio): ");
    scanf("%d", &n);
    printf("\n");

    // FOR
    for(int i = 1; i <= n; i++)
    {
         sum_for += i*i;
    }

    // WHILE
    int i = 1;
    while(i <= n)
    {
        sum_while += i*i;
        i++;
    }

    // DO-WHILE
    i = 1;
    do{

       sum_do += i*i;
       i++;
    } while (i <= n);

     printf("==== Athroisma tetragwnwn ====\n");
    printf("FOR      : %d\n", sum_for);
    printf("WHILE    : %d\n", sum_while);
    printf("DO-WHILE : %d\n", sum_do);

    // ===============================
    // 19η άσκηση: i^i
    // ===============================

    printf("___________________________________________");
    printf("|  Athroisma twn n prwtwn dynamewn toy i  |");
    printf("___________________________________________\n\n");

     // FOR
    for(int i = 1; i <= n; i++)
    {
        int pow_i = 1;

        for(int j = 0; j < i; j++)
        {
            pow_i *= i;
        }

         sum2_for += pow_i;
    }

    // WHILE
    i = 1;
    while(i <= n)
    {
        int pow_i = 1;
        for(int j = 0; j < i; j++)
         {
             pow_i *= i;
         }

        sum2_while += pow_i;
        i++;
    }

    // DO-WHILE
    i = 1;
    do{

        int pow_i = 1;
        for(int j = 0; j < i; j++)
         {
             pow_i *= i;
         }

       sum2_do += pow_i;
       i++;
    } while (i <= n);

    printf("\n==== Athroisma dynamewn i^i ====\n");
    printf("FOR      : %d\n", sum2_for);
    printf("WHILE    : %d\n", sum2_while);
    printf("DO-WHILE : %d\n", sum2_do);


    return 0;

}
