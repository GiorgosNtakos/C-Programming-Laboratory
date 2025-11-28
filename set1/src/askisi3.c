#include <stdio.h>
#include <math.h>

int main()
{
    double x;
    double f1, f2;
    int flag;

    do{

        printf("Dwse enan pragmatiko arithmo gia to x: ");
        flag = scanf("%lf", &x);

        if(flag != 1) {

            printf("Lathos eisodos! Prepei na dwseis pragmatiko arithmo.\n");
            while (getchar() != '\n') { }

        }

        } while (flag != 1);



    // Πρώτη συνάρτηση: f(x) = x^5 - x^3 + 3x

    f1 = pow(x,5) - pow(x,3) + 3 * x;

    // Δεύτερη συνάρτηση: f(x) = e^x + 4ln(x) - x^2
    // Πρέπει το x > 0 για να ορίζεται το ln(x)

    if (x > 0){

        f2 = exp(x) + 4 * log(x) - pow(x,2);

        printf("f(x) = x^5 - x^3 + 3x = %.6lf\n", f1);
        printf("f(x) = e^x + 4ln(x) - x^2 = %.6lf\n", f2);

    } else {

        printf("f(x) = x^5 - x^3 + 3x = %.6lf\n", f1);
        printf("H f2(x) den orizetai gia x <= 0 logw tou log(x).\n");

    }

    return 0;
}

