// variant 25
#include "Exception/Exception.hpp"
#include "Menu/Menu.hpp"
#include "MyNumber/MyNumber.hpp"
#include <any>
#include <vector>
#include <string>

using std::vector;
using YMM::MyNumber;

using namespace YMM;

void view(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    std::cout << "Number = " << number_ptr;
}

void intput(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    // MyNumber tmp;
    std::cout << "Input number in '(zn)0.m Е N' format: ";
    std::cin >> number_ptr;
    // number_ptr = *tmp;
}

void pow(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    int num = YMM::Menu::input<int>("Input int value: ");
    YMM::MyNumber tmp = *number_ptr;
    tmp.pow(num);
    std::cout << "Pow(" << *number_ptr << ", " << num << ") = " << tmp << std::endl;
}

void add(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    MyNumber num;
    std::cout << "Input number in '(zn)0.m Е N' format: ";
    std::cin >> num;
    YMM::MyNumber tmp = *number_ptr;
    tmp.add(num);
    std::cout << "Add(" << *number_ptr << ", " << num << ") = " << tmp << std::endl;
}

void multipliy(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    MyNumber num;
    std::cout << "Input number in '(zn)0.m Е N' format: ";
    std::cin >> num;
    YMM::MyNumber tmp = *number_ptr;
    tmp.multily(num);
    std::cout << "Multiply(" << *number_ptr << ", " << num << ") = " << tmp << std::endl;
}


void multipliy_short(std::vector<std::any> params) {
    auto* number_ptr = std::any_cast<YMM::MyNumber*>(params[0]);
    int num = YMM::Menu::input<int>("Input int value: ");
    YMM::MyNumber tmp = *number_ptr;
    tmp.multily(num);
    std::cout << "multipliy short(" << *number_ptr << ", " << num << ") = " << tmp << std::endl;
}


std::string YMM::Exception::log_file_name = "log.log";

int main(int argc, char *argv[]) {
    using namespace YMM;

    // read args
    std::string log_file = "log.log";
    Exception::setLogFileName(log_file);


    // data
    MyNumber* number_ptr = new MyNumber;
    std::vector<std::any> params{
        number_ptr
    };

    // init default value
    vector<short int> an{1, 2, 3, 4};
    number_ptr->setMantis(an);
    number_ptr->setOffset(2);
    number_ptr->normolize();

    Menu menu = Menu("Main", std::vector<Menu>{
                         Menu("View", view),
                         Menu("Input", intput),
                         Menu("Pow", pow),
                         Menu("Other", std::vector<Menu>{
                             Menu("View", view),
                             Menu("Input", intput),
                             Menu("Add", add),
                             Menu("Multiply", multipliy),
                             Menu("Multiply short", multipliy_short),
                              })
                         }, params);

    menu.run();

    return 0;
}
