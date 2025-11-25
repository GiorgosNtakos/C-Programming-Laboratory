#include <stdio.h>

int main()
{
    printf("N\t2*N\t3*N\t10*N\n");
    for(int i = 1; i <= 10; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i, 2*i, 3*i, 10*i);
    }
    return 0;
}
