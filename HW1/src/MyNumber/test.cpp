#include <iostream>
#include <ostream>
#include <vector>
#include "MyNumber.hpp"
#include "../Exception/Exception.hpp"

using namespace YMM;

std::string Exception::log_file_name("log.log");

int main() {
    std::cout << "Max SIZE = " << SIZE << std::endl;
    MyNumber* a = new MyNumber;
    MyNumber* b = new MyNumber;
    // std::vector<short int> an {1, 2, 3, 4};
    std::vector<short int> an {1, 2, 3, 4};
    std::vector<short int> bn {2, 6};

    a->setMantis(an);
    a->setOffset(2);
    a->normolize();

    // b.setMantis(bn);
    // b.setOffset(0);
    std::cin >> b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    // a.align(b);

    a->add(*b);
    // int input_a;
    // std::cin >> input_a;
    // a.multily(input_a);
    // a.multily(b);
    // a->pow(2);
    // a.shiftRight(5);
    // a.shiftLeft(5);
    
     
    std::cout << "a = " << a << std::endl;
    // std::cout << "b = " << b << std::endl;

    return 0;
}
