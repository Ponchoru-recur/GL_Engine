#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void toLowerCase(char arr[]) {
    for (int i = 0, counter = 0; i < 8 - 1 + 1; i++) {
        for (int j = 65; j < 90 + 1; j++) {
            if (arr[i] == j) {
                // printf("counter : %d\n", counter);
                // printf("Bulls eye : %c\n", username[i]);
                arr[i] = 97 + counter;
                break;
            }
            counter++;
        }
        counter = 0;
    }
}

int main() {
    char window = 'n';
    char student_info[5][4][30];
    int counter_students = 0;

    while (true) {
        printf("\n== Main Menu ==\n");
        printf("Choose R for register\n");
        printf("Choose L for Login\n");
        printf("Select : ");
        scanf(" %c", &window);
        // REGISTER STUDENT
        if (window == 'R' || window == 'r') {
            char firstName[10];
            char lastName[10];
            char student_ID[7];
            char password[10];

            printf("First name : ");
            scanf(" %s", &firstName);
            printf("Last name : ");
            scanf(" %s", &lastName);
            printf("Password : ");
            scanf(" %s", &password);
            printf("ID number : ");
            scanf(" %s", &student_ID);

            char username[8] = {};

            // Three letters of the last name
            username[0] = lastName[0];
            username[1] = lastName[1];
            username[2] = lastName[2];

            // First two letters of the first name
            username[3] = firstName[0];
            username[4] = firstName[1];

            // Last two digits of the ID
            username[5] = student_ID[5];
            username[6] = student_ID[4];

            // a - z = 97 - 122
            // A - Z = 65 - 90

            toLowerCase(username);

            printf("username : %s \n", username);

            // inserting username to data
            strcpy(student_info[counter_students][0], username);
            strcpy(student_info[counter_students][1], firstName);
            strcpy(student_info[counter_students][2], lastName);
            strcpy(student_info[counter_students][3], password);
            strcpy(student_info[counter_students][4], student_ID);

            counter_students++;

        } else if (window == 'L' || 'l') {
            // Login Page
            while (true) {
                int grades[5];
                printf("Please insert login details.\n");
                char username[8];
                char password[10];
                bool allow_access = false;
                printf("Username : ");
                scanf(" %s", &username);
                printf("Password : ");
                scanf(" %s", &password);
                int i = 0;
                for (; i < 6; i++) {
                    if (strcmp(username, student_info[i][0]) && strcmp(password, student_info[i][3])) {
                        allow_access = true;
                        break;
                    }
                }
                // Adding random
                srand(time(NULL));
                for (int i = 0; i < 6; i++) {
                    grades[i] = rand() % 101;
                }

                if (allow_access != true) {
                    printf("Wrong user or password.\n");
                    continue;
                } else {
                    int choice = -1;
                    do {
                        printf("\n=== Student DashBoard ===\n");
                        printf("Welcome, %s\n", student_info[i][1]);

                        printf("1. View Grades\n");
                        printf("2. Calculate Average\n");
                        printf("3. Check Grades\n");
                        printf("4. Check Pass/Fail\n");
                        printf("5. Logout\n");

                        printf("\nSelect : ");
                        scanf(" %d", &choice);

                        if (choice == 1) {
                            printf("==========================\n");
                            printf("\nMath : %d\n", grades[0]);
                            printf("Science : %d\n", grades[1]);
                            printf("English : %d\n", grades[2]);
                            printf("History : %d\n", grades[3]);
                            printf("Programming : %d\n", grades[4]);
                            printf("==========================\n\n");
                        } else if (choice == 2) {
                            printf("==========================\n");
                            printf("\nYour Average grade : %d\n", (grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5);
                            printf("==========================\n");
                        } else if (choice == 3) {
                            int pick_subject = 0;
                            printf("==========================\n");
                            printf("Choose a subject\n");
                            printf("1. Math\n");
                            printf("2. Science\n");
                            printf("3. English\n");
                            printf("4. History\n");
                            printf("5. Programming\n");
                            printf("==========================\n");
                            printf("Select : ");
                            scanf("%d", &pick_subject);

                            int sub = grades[pick_subject - 1];

                            if (sub >= 90) {
                                printf("Grade : A\n");
                            } else if (sub >= 80) {
                                printf("Grade : B\n");
                            } else if (sub >= 70) {
                                printf("Grade : C\n");
                            } else if (sub >= 60) {
                                printf("Grade : D\n");
                            } else {
                                printf("Grade : F\n");
                            }
                            printf("\n");
                        } else if (choice == 4) {
                            if ((grades[0] + grades[1] + grades[2] + grades[3] + grades[4]) / 5 > 60) {
                                printf("\nYou passed!\n");
                            } else {
                                printf("\nYou failed!\n");
                            }
                        } else if (choice == 5) {
                            break;
                        }

                    } while (choice != 0);
                }  // Here
            }

        } else if (window == 'Q' || 'q') {
            printf("bye\n");
            break;
        }
    }

    return 0;
}
