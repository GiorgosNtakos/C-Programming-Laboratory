#include <stdio.h>
#include <stdlib.h>

#define USER_PIN 2014
#define START_BALANCE 100UL

int main()
{
    system("chcp 65001 > nul");
    unsigned long balance = START_BALANCE, metrhta;
    int pin, epilogi;


    printf("___________________________________");
    printf("|   Welcome to ATM of Ceid's Bank |");
    printf("___________________________________\n\n");

    printf("Parakalw plhktrologiste to PIN trapezis sas: ");

    do
    {
        scanf("%d", &pin);
        printf("\n");

        if(pin != USER_PIN){
            printf("Lathos PIN! Parakalw dokimaste jana: ");
            while (getchar() != '\n') { }// katharismo buffer
        }

    } while (pin != USER_PIN);

     while (1) {
    printf("Epilejte mia apo tis parakatw epiloges patwntas to antistoixo plhktro: \n\n");
    printf("1) Diathesimo Ypoloipo\n");
    printf("2) Katathesh metrhtwn\n");
    printf("3) Analhpsh Metrhtwn\n");
    printf("4) Exodos\n");

    do
    {
        scanf("%d", &epilogi);
        if(epilogi < 1 || epilogi > 4){
            printf("Mh egkyrh epilogh! Parakalw dialejte enan arithmo apo to 1 ews 4: ");
            while (getchar() != '\n') { }// katharismo buffer
        }
    } while(epilogi <1 || epilogi >4);

    switch(epilogi){

        case 1:
            printf("\nTo diathesimo ypoloipo sas einai: %lu \u20AC\n", balance);
            break;
        case 2:
            printf("\nDwste to poso to opoio thelete na katathesete: ");
            scanf("%lu", &metrhta);
            balance += metrhta;
            break;
        case 3:
            printf("\nDwste to poso to opoio thelete na kanete analipsi(To ATM dinei mono xartonomismata twn 20 eyrw): ");
            do{
                scanf("%lu", &metrhta);
                if(metrhta % 20 != 0){
                    printf("\nMh egkyrh Analhpsh! Parakalw dialejte ena poso pollaplasio toy  20: ");
                    while (getchar() != '\n') { }// katharismo buffer
                } else if (metrhta > balance){
                    printf("\nMh egkyrh Analhpsh! To poso poy epilejate einai megalytero apo to diathesimo ypoloipo. Prospathiste jana: ");
                    while (getchar() != '\n') { }// katharismo buffer
                }

            } while (metrhta > balance || metrhta % 20 != 0);
            balance -= metrhta;
            break;
        case 4:
            printf("Telos Synallagis! Parakalw Afaireste thn karta sas.");
            return 0;

        default:
            printf("Mh egkyrh epilogi.\n");
    }
}

    return 0;

}
