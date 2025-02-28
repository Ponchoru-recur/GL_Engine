#include <iostream>
#include <string.h>

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


int main(){

    std::cout <<"Program is running!" << std::endl;

    Number a(1);
    Number b(2);

    Number c = a + b;

    std::cout << c.x;

    return 0;
}
