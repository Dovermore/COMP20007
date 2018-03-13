/* Xulin Yang, 904904, time: 2018-2-27 19:46:25, description: UVA p100137
*/

#include <stdio.h>

#define MAX_PEOPLE 1000

int main(int argc, char **argv) {
    int num, i, count;
    double money[MAX_PEOPLE], sum, mean, extra;
    scanf("%d", &num);

    while (num != 0) {
        sum = 0.0;
        mean = 0.0;
        for (i = 0; i < num; i++) {
            scanf("%lf", &(money[i]));
            sum += money[i];
        }

        mean = sum / (1.0 * num);
        mean = (int)(mean*100.0) / 100.0;

        extra = 0.0;
        count = 0;

        for (i = 0; i < num; i++) {
            if (money[i] > (mean + 0.01)) {
                extra += (money[i] - (mean + 0.01));
                count++;
            }
        }
    
        if ((count * 0.01) > (sum - mean * num)) {
            extra += count * 0.01 - sum + mean * num;
        }

        printf("$%.2lf\n", extra);

        scanf("%d", &num);
    }

    return 0;
}
