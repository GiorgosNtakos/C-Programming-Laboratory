#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    int D;
    double x1,x2;

    do{

        printf("Dwse tis times twn statherwn a, b, c: ");
        scanf("%d %d %d", &a, &b, &c);

        if(a == 0){

            printf("Gia a = 0 den orizetai deyterobathmia ejiswsh. Dwse a != 0.\n");
            while (getchar() != '\n') { }// katharismo buffer

        }

    }while (a == 0);

    D = b*b - 4*a*c;

    if(D > 0){
        x1 = (-b + sqrt(D))/(2.0*a);
        x2 = (-b - sqrt(D))/(2.0*a);
        printf("H deyterobathmia ejiswsh %dx^2 + %dx + %d = 0 me D = %d exei dyo lyseis: x1 = %.6lf kai x2 = %.6lf\n", a, b, c, D, x1, x2);
    } else if (D == 0){
        x1 = -b/(2.0*a);
        printf("H deyterobathmia ejiswsh %dx^2 + %dx + %d = 0 me D = %d exei mia lysh: x1 = %.6lf\n", a, b, c, D, x1);
    } else{
        printf("H deyterobathmia ejiswsh %dx^2 + %dx + %d = 0 me D = %d einai adynath sto pedio orismoy R\n", a, b, c, D);
        /* An theloyme na to epektinoyme kai stoys migadikoys arithmoys tote exoyme m2 migadikes rizes:
        
            x1 = realPart + imagPart*i 
            x2 = realPart - imagPart*i
            
            opoy realPart kai imagPart:
            
            realPart = -b / (2*a)
            imagPart = sqrt(-D) / (2*a)
            
        */
    }

    return 0;

}
