#include <stdio.h>

#define PAGIO 12.0;
#define time_cost  0.02
#define sms_cost   0.14
#define FPA        0.23

int main()
{
    int code;
    double total;
    long unsigned time, sms;

    printf("___________________________");
    printf("|   Tmob Mobile Company   |");
    printf("___________________________\n\n");

    printf("Dwste ton tetrapsifio kwdiko toy pelath: ");
    scanf("%d", &code);
    printf("\nDwste to xrono omilia sas: ");
    scanf("%lu", &time);
    printf("\nDwste ton arithmo twn mhnymatwn: ");
    scanf("%lu", &sms);

    double aforologito = time_cost * time + sms * sms_cost + PAGIO;

    total = aforologito + FPA * aforologito;

    printf("\nTmob account\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("Customer code\ttime\tSMS\tFPA\t|\t TOTAL\n");
    printf("\t%d\t%lu\t%lu\t%.2lf\t|\t %.2lf\n", code, time, sms, FPA*aforologito, total);
    printf("_______________________________________________________________________________________________________________\n");

    return 0;

}
