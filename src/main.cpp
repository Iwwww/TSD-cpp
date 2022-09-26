#include "MyList/MyList.hpp"
#include "Exception/Exception.hpp"
#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include <fstream>
#include <ostream>
#include <string>

using namespace YMM;
YMM::MyList loadData() {
    std::string line;
    std::ifstream file("data.txt");
    YMM::MyList list;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            double num = std::stod(line);
            list.append(num);
        }
    }
    return list;
}

void writeData(YMM::MyList& list) {
    std::string data;
    std::ofstream file("data.txt");
    if (file.is_open()) {
        int size = list.size();
        for (int i = 0; i < size; i++) {
            file << list[i] << std::endl;
        }
    }
}

double inputD() {
    double num = 0;
    bool flag = 1;
    while (flag) {
        if (std::cin >> num) {
            flag = 0;
        } else {
            YMM::Exception("Invalid Input");
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }

    return num;
}

double inputI() {
    int num = 0;
    bool flag = 1;
    while (flag) {
        if (std::cin >> num) {
            flag = 0;
        } else {
            YMM::Exception("Invalid Input");
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }

    return num;
}

void append(YMM::MyList& list) {
    std::cout << "Input num: " << std::endl;
    double num = inputD();
    list.append(num);
}

void insert(YMM::MyList& list) {
    std::cout << "input index: " << std::endl;
    double index = inputI();
    std::cout << "input num: " << std::endl;
    double num = inputD();
    list.insert(index, num);
}

void pop(YMM::MyList& list) {
    std::cout << "input index: " << std::endl;
    double index = inputI();
    std::cout << "pop: " << list.pop(index);
}

void clear(YMM::MyList& list) {
    list.clear();
}

void print(YMM::MyList& list) {
    std::cout << "list print: ";
    list.print();
    std::cout << std::endl;
}

void size(YMM::MyList& list) {
    std::cout << "list size: " << list.size() << std::endl;
}

void find(YMM::MyList& list) {
    std::cout << "input num: " << std::endl;
    double num = inputD();
    std::cout << "input start range: " << std::endl;
    int start = inputI();
    std::cout << "input end range: " << std::endl;
    int end = inputI();
    std::cout << "founded element: " << list.find(num, start, end);
}

void rfind(YMM::MyList& list) {
    std::cout << "input num: " << std::endl;
    double num = inputD();
    std::cout << "input start range: " << std::endl;
    int start = inputI();
    std::cout << "input end range: " << std::endl;
    int end = inputI();
    std::cout << "founded element: " << list.find(num, start, end);
}

void isEmpty(YMM::MyList& list) {
    if (list.isVoid()) {
         std::cout << "list is Empty" << std::endl;
    } else {
         std::cout << "list is Not Empty" << std::endl;
    }
}


void variantTask(YMM::MyList& list) {
    MyList positive_list;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] < 0) {
            double tmp_i = list.pop(i);
            positive_list.append(tmp_i);
        }
    }

    MyList negative_list;
    std::cout << std::endl;
    for (int i = list.size() - 1; i >= 0; i--) {
        negative_list.append(list[i]);
    }

    list.clear();

    for (int i = 0; i < negative_list.size(); i++) {
        list.append(negative_list[i]);
    }

    for (int i = 0; i < positive_list.size(); i++) {
        list.append(positive_list[i]);
    }

    positive_list.clear();
    negative_list.clear();
}

void printMenu() {
std::cout << "Меню" << std::endl
<< "1. Append" << std::endl
<< "2. Insert" << std::endl
<< "3. Pop" << std::endl
<< "4. Clear" << std::endl
<< "5. Print" << std::endl
<< "6. Size" << std::endl
<< "7. Find" << std::endl
<< "8. Rfind" << std::endl
<< "9. IsEmpty" << std::endl
<< "10. Записать в файл" << std::endl
<< "11. Заданте по варианту" << std::endl
<< "0. Выход" << std::endl
<< "->";
}

int main() {
    using namespace YMM;

    // data
    MyList list = loadData();
 
    while (true) {
        printMenu();
        int choice = inputI();
        switch (choice) {
        case 1:
            append(list);
            break;
        case 2:
            insert(list);
            break; case 3:
            pop(list);
            break;
        case 4:
            clear(list);
            break;
        case 5:
            print(list);
            break;
        case 6:
            size(list);
            break;
        case 7:
            find(list);
            break;
        case 8:
            rfind(list);
            break;
        case 9:
            isEmpty(list);
            break;
        case 10:
            writeData(list);
        case 11:
            variantTask(list);
            break;
        case 0:
            return 0;
        }
    }
    return 0;
}
