#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256 // Μέγιστο μήκος γραμμής

/*============================== ΒΟΗΘΗΤΙΚΕΣ ΣΥΝΑΡΤΗΣΕΙΣ ==============================*/

/* Δημιουργεί αρχείο διαφορών (diff):
   Συγκρίνει γραμμή γραμμή τα old_file και new_file
   Για κάθε γραμμή που διαφέρει, γράφει block στο diff_file:

   --- Line N
   file_old.txt
   <line from old txt>
   file_new.txt
   <line from new txt>
*/

void create_diff(const char *old_file, const char *new_file, const char *diff_file){
    FILE *fold = fopen(old_file, "r");
    FILE *fnew = fopen(new_file, "r");
    FILE *fdiff = fopen(diff_file, "w");

    if(!fold || !fnew || !fdiff){
        printf("Sfalma anoigmatos arxeioy(create_diff).\n");
        if (fold) fclose(fold);
        if (fnew) fclose(fnew);
        if (fdiff) fclose(fdiff);
        return;
    }

    char line_old[MAX_LINE];
    char line_new[MAX_LINE];
    int line_no = 0;

    // Διαβάζουμε γραμμή γραμμή και από τα δύο αρχεία.
    while(1){
        char *res_old = fgets(line_old, MAX_LINE, fold);
        char *res_new = fgets(line_new, MAX_LINE, fnew);

        if(!res_old && !res_new){
            // Και τα δύο έφτασα σε EOF -> τέλος
            break;
        }

        line_no++;

        /* Αν μία από τις δύο είναι null ή αν οι γραμμές διαφέρουν,
           τότε καταγράφουμε διαφορά στο diff
        */
        if(!res_old || !res_new || strcmp(line_old, line_new) != 0){
            fprintf(fdiff, "---Line %d\n", line_no);

            fprintf(fdiff, "%s\n", old_file);
            if(res_old){
                fputs(line_old, fdiff); // γράφουμε τη γραμμή όπως είναιο (με το \n της)
            } else {
                // Αν το παλιό τελείωσε νωρίτερα, βάζουμε κενή γραμμή
                fprintf(fdiff, "\n");
            }

            fprintf(fdiff, "%s\n", new_file);
            if (res_new){
                fputs(line_new, fdiff);
            } else {
                fprintf(fdiff, "\n");
            }
        }
    }

    fclose(fold);
    fclose(fnew);
    fclose(fdiff);

    printf("To arxeio diaforwn '%s' dhmioyrghthke.\n", diff_file);
}

/* Διαβάζει ένα block από το diff_file και γεμίζει:
   - *line_no με τον αριθμό γραμμής (Ν από '---Line N')
   - old_line με τη γραμμή του παλιού αρχείου
   - new_line με τη γραμμή του νέου αρχείου

   Επιστρέφει:
   1 αν διαβάστηκε block επιτυχώς
   0 αν δεν υπάρχουν άλλα blocks(EOF ή λάθος)
*/
int read_diff_block(FILE *fdiff, int *line_no, char *old_line, char *new_line){
    char buffer[MAX_LINE];

    // Διαβάζουμε την γραμμή '---Line N'
    if (!fgets(buffer, MAX_LINE, fdiff)){
        return 0; // EOF
    }

    if(sscanf(buffer, "---Line %d", line_no) != 1){
        // Δεν είναι στη μορφή που περιμένουμε
        return 0;
    }

    // Διαβάζουμε το όνομα του παλιού αρχείου (π.χ. file_old.txt) - το αγνοούμε
    if(!fgets(buffer, MAX_LINE, fdiff)) return 0;

    // Διαβάζουμε τη γραμμή του παλιού αρχείου
    if(!fgets(old_line, MAX_LINE, fdiff)) return 0;

    // Διαβάζουμε το όνομα του νεου αρχείου - το αγνοούμε
    if(!fgets(buffer, MAX_LINE, fdiff)) return 0;

    // Διαβάζουμε το όνομα του παλιού αρχείου (π.χ. file_old.txt) - το αγνοούμε
    if(!fgets(new_line, MAX_LINE, fdiff)) return 0;

    return 1;
}

/* Εφαρμόζει το diff:
   Παίρνει base_file (π.χ. file_old.txt) + diff_file
   και παράγει out_file(π.χ file_patched που θα ειναι το ιδιο με το file_new)

   Στην ουσία:
   - Διαβάζουμε όλο το base_file γραμμή γραμμή/
   - Παράλληλα διαβάζουμε τα blocks από το diff_file.
   - Αν η τρέχουσα γραμμή line_no δεν είναι σε block -> γράφουμε την αυθεντική γραμμή.
   - Αν line_no == block.line_no -> γράφουμε τη νέα γραμμή από το diff (αγνοώντας την παλιά).
   */
void apply_diff(const char *base_file, const char *diff_file, const char *out_file){
    FILE *fbase = fopen(base_file, "r");
    FILE *fdiff = fopen(diff_file, "r");
    FILE *fout = fopen(out_file, "w");

    if(!fbase || !fdiff || !fout){
        printf("Sfalma anoigmatos arxeioy(apply_diff).\n");
        if (fbase) fclose(fbase);
        if (fdiff) fclose(fdiff);
        if (fout) fclose(fout);
        return;
    }

    int current_diff_line = -1; // ποιά γραμμή του base έχει diff
    char diff_old[MAX_LINE]; // η παλιά γραμμή (δεν τη χρησιμοποιούμε πολύ)
    char diff_new[MAX_LINE]; // η νέα γραμμή (αυτή θα γράψουμε)
    int has_diff_block;

    // Διαβάζουμε το πρώτο block από το diff (αν υπάρχει)
    has_diff_block = read_diff_block(fdiff, &current_diff_line, diff_old, diff_new);

    char line_base[MAX_LINE];
    int line_no = 0;

    // Διαβάζουμε το base_file γραμμή γραμμή
    while (fgets(line_base, MAX_LINE, fbase)){
        line_no++;

        if(has_diff_block && line_no == current_diff_line){
            // Αυτή η γραμμή έχει διαφορά σύμφωνα με το diff

            // Γράφουμε τη νέα γραμμή στο out_file
            fputs(diff_new, fout);

            has_diff_block = read_diff_block(fdiff, &current_diff_line, diff_old, diff_new);
        } else{
            // Γραμμή χωρίς diff -> την αντιγράφουμε όπως είναι
            fputs(line_base, fout);
        }
    }

    fclose(fbase);
    fclose(fdiff);
    fclose(fout);

    printf("To arxeio '%s' dhmioyrghthhke (apo %s + %s).\n", out_file, base_file, diff_file);
}

/*============================== MAIN ==============================*/
int main(void){
    int choise;
    char old_name[100], new_name[100], diff_name[100], out_name[100];

    printf("1. Dhmioyrgia diff (sygkrish dyo arxeiwn)\n");
    printf("2. Efarmogh diff (palio arxeio + diff -> neo arxeio)\n");
    printf("Dwse epilogh (1 h 2): ");
    if(scanf("%d", &choise) != 1){
        printf("Lathos sthn eisodo.\n");
        return 1;
    }

    if (choise == 1){
        printf("Onoma palioy arxeioy (p.x. file_old.txt): ");
        scanf("%s", old_name);
        printf("Onoma neoy arxeioy (p.x. file_new.txt): ");
        scanf("%s", new_name);
        printf("Onoma arxeioy diaforwn (p.x. diff.txt): ");
        scanf("%s", diff_name);

        create_diff(old_name, new_name, diff_name);
    } else if (choise == 2){
        printf("Onoma arxeioy bashs (p.x. file_old.txt): ");
        scanf("%s", old_name);
        printf("Onoma arxeioy diaforwn (p.x. diff.txt): ");
        scanf("%s", diff_name);
        printf("Onoma arxeioy ejodoy (p.x. file_patched.txt): ");
        scanf("%s", out_name);

        apply_diff(old_name, diff_name, out_name);
    } else{
        printf("Mh egkyrh epilogh.\n");
    }

    return 0;
}
