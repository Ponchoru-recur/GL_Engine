#include <iostream>
#include <memory>


class person {
    public:
    void walk() {
        std::cout << "person took a bunch of steps" << std::endl;
    }
    ~person(){
        std::cout << "This got destroyed\n";
    }
};


void foo(std::unique_ptr<person> a){
    a->walk();
}


int main() {

   std::unique_ptr<int> banana = std::make_unique<int>(5);

   std::unique_ptr<person> Sam = std::make_unique<person>();


    foo(std::move(Sam));

    return 0;
}
