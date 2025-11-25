#include <stdio.h>

int main()
{
    int x, y, g, s, u, MKD;

    printf("_______________________________");
    printf("|  Megistos Koinos Diaireths  |");
    printf("_______________________________\n\n");

    printf("Parakalw dwste 2 thetikoys arithmoys twn opoiwn thelete na breite ton MKD: \n");
    scanf("%d %d", &x, &y);

    if (x > y){
        g = x, s = y;
    } else{
        g = y, s = x;
    }

    while (s != 0){
        u = g % s;
        g = s;
        s = u;
    }

    MKD = g;

    printf("O MKD twn dyo arithmwn einai: MKD(%d,%d) = %d\n", x, y, MKD);
    return 0;

}
