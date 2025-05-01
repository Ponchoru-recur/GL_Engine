#include <stdio.h>
#include <iostream>

class Remote {
   public:
    void channel_one() {
        std::cout << "alien videos\n";
    }
    void channel_two() {
        std::cout << "banana tv\n";
    }

   private:
    int x;
};

int main() {
    Remote tv_remote;

    tv_remote.channel_one();
    tv_remote.channel_two();


    return 0;
}
