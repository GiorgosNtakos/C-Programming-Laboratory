#include <stdio.h>
#include <math.h>

int main()
{
    int x, y;
    int sum;
    double power_xy;
    double log_x, log_y;

    printf("Dwse enan akeraio arithmo x: ");
    scanf("%d", &x);
    printf("Dwse enan akeraio arithmo y: ");
    scanf("%d", &y);

    // 1) ’θροισμα
    sum = x + y;
    printf("\n1) Athroisma:\n");
    printf("sum = %d + %d = %d\n", x, y, sum);

    // 2) Μεγαλύτερος
    printf("\n2) Megalyteros arithmos:\n");
    if(x > y){
        printf("Megalyteros einai o x = %d\n", x);
    }
    else if(x < y){
         printf("Megalyteros einai o y = %d\n", y);
    } else {
         printf("   O x kai o y einai isoi: %d = %d\n", x, y);
    }

    // 3) x^y
    // pow επιστρέφει double, οπότε καλύπτουμε και αρνητικούς εκθέτες
    power_xy = pow(x,y);
    printf("\n3) Dynamh x^y:\n");
    printf("To apotelesma ths prajhs x^y = %d^%d = %.6lf\n", x, y, power_xy);


    // 4) Δεκαδικοί λογάριθμοι (log10)
    printf("\n4) Dekadikoi logarithmoi:\n");
    if (x>0){

        log_x = log10(x);
        printf("To apotelesma toy log10(x) einai: log10(%d) = %.6lf\n", x, log_x);

    } else {

        printf("H log10(x) den orizetai gia x <= 0.\n");

    }

    if (y>0){

        log_y = log10(y);
        printf("To apotelesma toy log10(y) einai: log10(%d) = %.6lf\n", y, log_y);

    } else {

        printf("H log10(y) den orizetai gia y <= 0.\n");

    }

    return 0;
}

