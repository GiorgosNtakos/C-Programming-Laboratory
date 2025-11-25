#include<stdio.h>

int main()
{
    int a, b, c, d;

    printf("Dwse 4 akeraioys arithmoys: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int nums[4] = {a, b, c, d};
    int best1 = nums[0];
    int best2 = nums[1];
    int max_sum = best1 + best2;

        // Έλεγχος όλων των ζευγαριών (6 συνολικά)
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            int sum = nums[i] + nums[j];
            if (sum > max_sum) {
                max_sum = sum;
                best1 = nums[i];
                best2 = nums[j];
            }
        }
    }

    printf("To megalytero athroisma einai: %d + %d = %d\n", best1, best2, max_sum);
}
