#include <iostream>
#include <string.h>
#include <chrono>
#include <thread>

#define num_elememts(a) sizeof(a) / sizeof(*a)

//Dynamically allocated example
struct test_objects{
    int func(){
        int tri[4] = {1,2,3,4};
        int *tr = new int[4];
        memcpy(tr, tri, num_elememts(tri));

        return num_elememts(tri);
    }
};

//enums is like making a new data type
//Its also alright to write everything without setting its value
//it automatically assigns a integer for each thing
void about_enums(){
    enum Days {sunday = 0, saturday = 1};
    Days today = sunday;
    switch (today)
    {
    case sunday:
        std::cout << "It is sunday" << std::endl;
        break;
    case saturday:
        std::cout << "It is saturday" << std::endl;
        break;
    default:
        break;
    }
}

//An example for recursion
void walk(int steps){
    if (steps > 0){
        std::cout << "Taking a step\n";
        walk(steps -1);
    }

}

//Overloading operator, we are re-defining the + operator to do this type of way
class Number{
    public:
        Number(int number){ x = number; }
        Number operator + (const Number &numA){
            return Number(this->x + numA.x);
        }
        void show_number(){ std::cout << x; }
        int x;
    private:

};

//This function pointer
void foo(){
    std::cout <<"printing\n";
    //void(*func)() = foo;
    //auto func = foo;
}

//Try, catch, throw
void exe(){

}

void sleep(){
    for (int i = 0; i < 20; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "executed : " << i << std::endl;
    }

}

void felix(){


    int num1, num2, quo, rem;

    printf("Please enter first number: ");
    scanf("%d", &num1);

    printf("Please enter second number: ");
    scanf("%d", &num2);




    if ( num2 == 0) {
    printf("Undefined.");
    }
    else {
        if ( rem == 0) {
            printf("This number is divisible.");
            quo = num1 / num2;
            rem = num1 % num2;
        }

        else {
            printf("This is number is not divisible");
        }
    }

}

int main(){


    felix();

    return 0;
}
