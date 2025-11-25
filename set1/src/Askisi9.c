#include <stdio.h>
#include <string.h>

int main()
{
    int epilogi;
    double x;
    double intses, draxmes;
    char str[6];

    printf("-________Kalosirthate ston Metatropea________-\n");
    printf("Epilejte 1 h 2 analoga me to ti thelete na metatrepsete: \n");
    printf("1) Metra se Intses\n");
    printf("2) Eyrw se Draxmes\n");

    do{

        scanf("%d", &epilogi);

        if(epilogi == 1){
            printf("Metatropi Metrwn se Intses: \n");
            strcpy(str, "Metra");
        } else if (epilogi == 2){
            printf("Metatropi Eyrwn se Draxmes: \n");
            strcpy(str, "Eyrw");
        } else{
            printf("Lathos epilogi! Epilejte 1 h 2\n");
            while (getchar() != '\n') { }// katharismo buffer
        }

    }while (epilogi != 1 && epilogi != 2);

    printf("Dwse %s gia thn metatropi: \n", str);
    scanf("%lf", &x);

    if(epilogi == 1){
        intses = x/0.0254;
        printf("Ta %.4lf metra einai %.4lf se intses\n", x,intses);
    } else {
        draxmes = x*340.75;
        printf("Ta %.4lf eyrw einai %.4lf se draxmes\n", x,draxmes);
    }

    return 0;
}
