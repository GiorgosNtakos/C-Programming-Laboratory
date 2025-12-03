#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

// ΥΛΟΠΟΙΗΣΗ ΜΕ ΠΙΝΑΚΑ
// askisi2Pointer.c υλοποίηση με δείκτη

typedef struct{
    char name[25];
    char surname[25];
    float grade;
    int attempts;
    int year;
} Student;

// Διαβάζει τα στοιχεία n φοιτητών σε έναν πίνακα students[]

void readStudents(Student students[], int n){
    for (int i = 0; i < n; i++){
        printf("\n===== Foithths %d =====\n", i+1);

        printf("Onoma: ");
        scanf("%s", students[i].name);

        printf("Epwnymo: ");
        scanf("%s", students[i].surname);

        printf("Vathmos Foithth: ");
        scanf("%f", &students[i].grade);

        printf("Fores poy edwse to ma8hma: ");
        scanf("%d", &students[i].attempts);

        printf("Etos Foithth: ");
        scanf("%d", &students[i].year);


    }
}


/* Βρίσκει:
   - μέγιστο βαθμό
   - μέγιστες φορές
   - μέγιστο έτος
   και εκτυπώνει ολους τους φοιτητές που αυτά τα μέγιστα.
*/

void processStudents(Student students[], int n){

    // Αρχικοποίηση με το 1ο στοιχείο (ώστε να έχουμε βάση σύγκρισης)
    float maxGrade   = students[0].grade;
    int   maxAttempts = students[0].attempts;
    int   maxYear = students[0].year;

    // 1η διέλευση: βρίσκουμε τα μέγιστα
    for (int i = 1; i < n; i++){
        if (students[i].grade > maxGrade){
            maxGrade = students[i].grade;
        }

        if (students[i].attempts > maxAttempts){
            maxAttempts = students[i].attempts;
        }

        if (students[i].year > maxYear){
            maxYear = students[i].year;
        }
    }

    // 2η διέλευση: Εκτύπωση φοιτητών  με μέγιστο βαθμό
    printf("\n===== Foithtes me megisto vathmo (%.2f) =====\n", maxGrade);
    for(int i = 0; i < n; i++){
        if(students[i].grade == maxGrade){
            printf("%s %s\n", students[i].name, students[i].surname);
        }
    }

    // 2η διέλευση: Εκτύπωση φοιτητών  με πεισσοτερες προσπάθειες
    printf("\n===== Foithtes me tis perissoteres prospatheies (%d) =====\n", maxAttempts);
    for(int i = 0; i < n; i++){
        if(students[i].attempts == maxAttempts){
            printf("%s %s\n", students[i].name, students[i].surname);
        }
    }

    // 2η διέλευση: Εκτύπωση φοιτητών  με μεγαλύτερο έτος
    printf("\n===== Foithtes me megalytero Etos(%d) =====\n", maxYear);
    for(int i = 0; i < n; i++){
        if(students[i].year == maxYear){
            printf("%s %s\n", students[i].name, students[i].surname);
        }
    }
}


int main(void){
    int n;
    Student students[MAX_STUDENTS];

    printf("Dwse plhthos foithtwn (N): ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_STUDENTS){
        printf("Mh egkyro plhthos foithtwn (1...%d).\n", MAX_STUDENTS);
        return 1;
    }

    readStudents(students, n);

    processStudents(students, n);

    return 0;
}
