#include <stdio.h>

int main()
{
    char d = '0';

    printf("___________________________");
    printf("|  Characters ASCII CODE  |");
    printf("___________________________\n\n");

    for(int i = 1; i <= 79; i++)
    {
        printf("%c(%d)\t", d, d);
        d++;
        if(i % 10 == 0){
            printf("\n\n");
        }
    }

    return 0;
}
