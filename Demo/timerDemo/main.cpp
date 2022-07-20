#include <iostream>
#include "timer.h"

using namespace std;

void A() {
    std::cout << "hello world\n";
}

int main() {
    Timer t = Timer();

    t.start(1000, A);

    getchar();
    t.stop();

    std::cout << "I am Timer" <<endl;
    while(true); // Keep mail thread active
}
