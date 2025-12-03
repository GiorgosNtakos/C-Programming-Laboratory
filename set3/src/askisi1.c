#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[50];
    double amount;
    Date date;
} Account;

/* Συνάρτηση (ιι): Διαβάζει τα στοιχεία των n λογαριασμών.
   Παίρνει:
   - accounts: Δείκτη σε Account (ουσιαστικά αρχή του δυναμικού πίνακα)
   - n: πόσα στοιχεία θα διαβάσει
   Χρησιμοποιούμε pointer αριθμητική: (accounts + i) δείχνει στον  i-οστό λογαριασμό.
*/
void readAccounts(Account *accounts, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("\n===== Logariasmos %d =====\n", i+1);

        printf("Onoma katatheth: ");
        scanf(" %49[^\n]", (accounts + i) -> name);

        printf("Poso Katatheshs: ");
        scanf("%lf", &(accounts + i)->amount);

        printf("Hmeromhnia katatheshs (dd mm yyyy): ");
        scanf("%d %d %d", &(accounts  + i)->date.day, &(accounts  + i)->date.month, &(accounts  + i)->date.year);

    }
}

/* Συνάρτηση (ιιι): Διαβάζει ένα όνομα  και:
   - Εκτυπώνει όλες τις πληροφορίες για όλους τους λογαριασμούς με αυτό το όνομα.
   - Αν είναι πάνω από ένας, εκτυπώνει και το άθροισμα των ποσών.
   Παίρνει:
   - accounts: const Account* γιατί δεν θέλουμε να το αλλάξουμε, μονο να το διαβάσουμε
   - n: πλήθος λογαριασμών
   - searchName: το όνομα προς αναζήτηση
*/
void printAccountsByName(const Account *accounts, int n, const char *searchName){
    int i;
    int count = 0; // πόσοι λογαριασμοί βρέθηκαν με αυτό το όνομα
    double sum = 0.0; // άθροισμα ποσών γιοα αυτό το όνομα

    printf("\nAnazhthsh gia onoma: %s\n", searchName);

    // Διατρέχουμε ολο τον πίνακα
    for(i = 0; i < n; i++){
        if(strcmp((accounts + i)->name, searchName) == 0){
            count++;
            sum += (accounts + i)->amount;

            printf("\n===== Bre8hke logariasmos =====\n");
            printf("Onoma Katatheth: %s\n", (accounts + i)->name);
            printf("Poso katatheshs: %.2lf\n", (accounts + i)->amount);
            printf("Hmeromhnia katatheshs: %02d/%02d/%04d\n", (accounts + i)->date.day, (accounts + i)->date.month, (accounts + i)->date.year);
        }
    }

    if(count == 0){
        printf("\nDen bre8hkan logariasmoi me ayto to onoma.\n");
    } else if(count > 1){
        printf("\nSynolo poswn gia to onoma '%s': %.2lf\n", searchName, sum);
    }
}

int main()
{
    int n; // πλήθος λογαριασμών
    Account *accounts;
    char searchName[50];

    printf("Dwse plhthos logariasmwn (n): ");
    if(scanf("%d", &n) != 1 || n <= 0){
        printf("Lathos timh gia n.\n");
        return 1;
    }

    accounts = malloc(n * sizeof(Account));
    if (accounts == NULL){
        printf("Sfalma: apotyxia desmeyshs mhnmhs.\n");
        return 1;
    }

    readAccounts(accounts, n);

    printf("\nDwse onoma katatheth pros anazhthsh: ");

    scanf(" %49[^\n]", searchName);

    printAccountsByName(accounts, n, searchName);

    free(accounts);

    return 0;
}
