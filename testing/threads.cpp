#include <stdio.h>

void A(){
    int monthly_salary = 0;

    scanf("%d", &monthly_salary);

    if (monthly_salary < 0) {
        printf("Invalid : You can't use negative input!\n");
    } else if (monthly_salary >= 100000){
        printf("Upper Class\n");
    } else if (monthly_salary >= 20000) {
        printf("Middle Class");
    } else {
        printf("Poor\n");
    }

}

void B(){
    int inputOne = 0;
    int inputSecond = 0;

    printf("Insert first input : ");
    scanf("%d", &inputOne);

    printf("Insert Second input : ");
    scanf("%d", &inputSecond);



    if (inputSecond == 0){
        printf("Error : you can't divide by 0\n");
        return;
    } else if (inputOne % inputSecond == 0){
        printf("This is divisible!");
    } else {
        printf("The remainder of %d and %d is %d", inputOne, inputSecond, inputOne % inputSecond);
    }


}

void Fantasy() {
    int select = 0, class_, health = 0, strength = 0,  Int = 0;
    printf("Choose your class: \n1. Warrior\n2. Mage\n3. Rogue\n");
    printf("Enter your choice : ");
    scanf("%d", &class_);
    //Warrior
    if (class_ == 1){
        printf("\nYou have chosen to be a warrior!\n");
        printf("Select your weapon of choice!\n");
        printf("1. Sword\n2. Axe\n");
        printf("Enter your choice : ");
        scanf("%d", &select);
        if (select == 1){
            printf("You have chosen the Sword\n");
        } else if (select == 2){
            printf("You have chosen the Axe\n");
        }
    // Mage
    } else if (class_ == 2){
        printf("\nYou have chosen to be a Mage!\n");
        printf("Select your weapon of choice!\n");
        printf("1. Staff\n2. Wand\n");
        printf("Enter your choice : ");
        scanf("%d", &select);
        if (select == 1){
            printf("You have chosen the Staff\n");
        } else if (select == 2){
            printf("You have chosen the Wand\n");
        }
    // Rogue
    } else {
        class_ = 3;
        printf("\nYou have chosen to be a Rogue!\n");
        printf("Select your weapon of choice!\n");
        printf("1. Daggers\n2. Bow\n");
        printf("Enter your choice : ");
        scanf("%d", &select);
        if (select == 1){
            printf("You have chosen the Daggers\n");
        } else if (select == 2){
            printf("You have chosen the Bow\n");
        }
    }
    printf("\nEnter your focus!\n");
    printf("1. Attack\n2. Defense\n");
    printf("Enter your choice : ");
    scanf("%d", &select);
    if (class_ == 1){ //Warrior
        if (select == 1){
            health = 150, strength = 120, Int = 40;
        } else {
            health = 200, strength = 90, Int = 40;
        }
    } else if (class_ == 2){ //Mage
        if (select == 1){
            health = 80, strength = 30, Int = 150;
        } else {
            health = 100, strength = 20, Int = 120;
        }
    } else {
        if (select == 1){
            health = 100, strength = 80, Int = 60;
        } else {
            health = 120, strength = 60, Int = 60;
        }
    }
    if (select == 1) {
        printf("\nAttack Focus : Health %d, Strength %d, Intelligence %d", health, strength, Int);
    } else {
        printf("\nDefence Focus : Health %d, Strength %d, Intelligence %d", health, strength, Int);
    }

    printf("\nCharacter creation complete!");

}

void Days_of_the_week(){
    int select = 0;
    printf("Select day : ");
    scanf("%d", &select);
    printf("it is ");
    switch (select)
    {
    case 1:
        printf("Sunday!");
        break;
    case 2:
        printf("Monday!");
        break;
    case 3:
        printf("Tuesday!");
        break;
    case 4:
        printf("Wednesday!");
        break;
    case 5:
        printf("Thursday!");
        break;
    case 6:
        printf("Friday!");
        break;
    case 7:
        printf("Saturday!");
    default:
        printf("invalid input");
        break;
    }
}

void Grading_system(){

    char input = 'o';

    printf("insert input : ");
    scanf("%c", &input);

    switch (input)
    {
    case 'A':
        printf("You got a A!");
        break;
    case 'B':
        printf("You got a B!");
        break;
    case 'C':
        printf("You got a C!");
        break;
    case 'D':
        printf("You got a D!");
        break;
    case 'E':
        printf("You got a E!");
        break;
    case 'F':
        printf("You got an F!\nYOU FAILED!");
        break;
    default:
        printf("Not a valid input!");
        break;
    }
}

void calculator(){
    char input = '1';
    int num1, num2;

    printf("Enter first num : ");
    scanf("%d", &num1);
    printf("Enter second num : ");
    scanf("%d", &num2);
    // printf("\nOperators : +, -, *, /, %\n");
    printf("insert operator : ");
    scanf(" %c", &input);

    switch (input){
    case '+':
        printf("%d + %d = %d", num1, num2, num1 + num2);
        break;
    case '-':
        printf("%d - %d = %d", num1, num2, num1 - num2);
        break;
    case '*':
        printf("%d + %d = %d", num1, num2, num1 * num2);
        break;
    case '/':
        if (num2 == 0){
            printf("cannot divide by 0");
        } else {
            printf("%d + %d = ", num1, num2, num1 / num2);
        }
        break;
    case '%':
        printf("%d + %d = ", num1, num2, num1 * num2);
        break;
    default:
        printf("invalid operator!");
        break;
    }

}

int main() {

    Fantasy();



    return 0;
}
