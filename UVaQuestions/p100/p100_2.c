#include <stdio.h>

#define min(a, b) ((a) <= (b) ? (a) : (b))   
#define max(a, b) ((a) >= (b) ? (a) : (b))

int cycle(int num, int times);

int main(int argc, char **argv) {
    int num1, num2, maximum, n1, n2, i, tmp;

    while (scanf("%d %d", &num1, &num2) != EOF) {
        maximum = 0;
        n1 = min(num1, num2);
        n2 = max(num1, num2);

        for (i = n1; i <= n2; i++) {
            tmp = cycle(i, 0);
            if (tmp > maximum) {
                maximum = tmp;
            }
        }

        printf("%d %d %d\n", num1, num2, maximum);
    }

    return 0;
}

int cycle(int num, int times) {
    if (num == 1) {
        times++;
        return times;
    } else if (num % 2 == 1) {
        cycle(num * 3 + 1, times + 1);
    } else if (num % 2 == 0) {
        cycle(num / 2, times + 1);
    } else {
        printf("error.\n");
        return 0;
    }
}