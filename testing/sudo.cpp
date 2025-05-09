#include <stdio.h>

int main() {
    int numbers[10];

    int even = 0;
    int odd = 0;

    for (int i = 0; i < 10; i++) {
        int temp;
        printf("Insert number to array = ");
        scanf("%d", &temp);
        numbers[i] = temp;
    }

    for (int i = 0; i < sizeof(numbers) / sizeof(*numbers); i++) {
        if (numbers[i] % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    printf("even = %d, odd = %d", even, odd);

    return 0;
}
