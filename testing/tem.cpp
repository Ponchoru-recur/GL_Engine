#include <stdio.h>

int main() {
    int array[] = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
    int select = 0;
    printf("Select number to find : ");
    scanf("%d", &select);

    int counter = 0;
    for (int i = 0; i < 10; i++) {
        if (array[i] == select) {
            printf("array[%d]\n", i);
            counter++;
        }
    }
    if (counter <= 0) {
        printf("Selected number does not exist.\n");
    }
}
