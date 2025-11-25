#include <stdio.h>
#include <math.h>

int main()
{
    double x1, x2;
    double y1, y2;
    double ea;
    int flag;

    do{

        printf("Dwse tis syntetagmenes 2 shmeiwn sto epipedo. H morfi einai typoy x1 y1 x2 y2: \n");
        flag = scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

        if(flag != 4) {

            printf("Lathos eisodos! Prepei na dwseis pragmatikous arithmous gia tis syntetagmenes.\n");
            while (getchar() != '\n') { }// katharismo buffer

        }

    } while (flag != 4);

    double dx = x2 - x1;
    double dy = y2 - y1;

    ea = sqrt(dx*dx + dy*dy);
    printf("H Eykleidia apostash twn dyo shmeiwn A = (%lf,%lf) kai B = (%lf, %lf) einai ish me %lf\n", x1, y1, x2, y2, ea);

    return 0;

}

