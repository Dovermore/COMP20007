/* Xulin Yang, 904904, time: 2018-2-27 15:37:36, description: UVA p100
*/

#include <stdio.h>

#define INPUT_NUM 2
#define TOTAL 1000
#define COLUMN 2

#define min(a, b) ((a) <= (b) ? (a) : (b))   
#define max(a, b) ((a) >= (b) ? (a) : (b))

int cycle(int num, int times, int initial, int *arr);
int find_max(int lower, int upper, int *arr);

int main(int argc, char **argv) {
    int num1, num2, i;
    int arr[TOTAL];

    for (i = 1; i < TOTAL+1; i++) {
        arr[i-1] = cycle(i, 0, i, arr);
    }

    while (scanf("%d %d", &num1, &num2) != EOF) {
        printf("%d %d %d\n", min(num1, num2), max(num1, num2), find_max(min(num1, num2), max(num1, num2), arr));
    }

    return 0;
}

int find_max(int lower, int upper, int *arr) {
    int i, max = 0;
    for (i = lower - 1; i < upper; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int cycle(int num, int times, int initial, int *arr) {
    if (num == 1) {
        times++;
        return times;
    } else if (num < initial) {
        return times + arr[num-1];
    } else if (num % 2 == 1) {
        cycle(num * 3 + 1, times + 1, initial, arr);
    } else if (num % 2 == 0) {
        cycle(num / 2, times + 1, initial, arr);
    } else {
        printf("error.\n");
        return 0;
    }
}