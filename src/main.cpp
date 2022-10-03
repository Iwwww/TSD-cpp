#include "File/File.hpp"
#include "MyList/MyList.hpp"
#include "Exception/Exception.hpp"
#include <fstream>
#include <iterator>
#include <ostream>
#include <string>

using namespace YMM;


const std::string LOAD_FILE_NAME = "data1.txt";
const std::string WRITE_FILE_NAME = "data2.txt";

/* 
std::cout << "Меню" << std::endl
<< "1. Append" << std::endl
<< "2. Insert" << std::endl
<< "3. Pop" << std::endl
       Remove
<< "4. Clear" << std::endl
<< "5. Print" << std::endl
<< "6. Size" << std::endl
<< "7. Find" << std::endl
<< "8. Rfind" << std::endl
<< "9. IsEmpty" << std::endl
<< "10. Считать из файла" << std::endl
<< "11. Записать в файл" << std::endl
<< "12. Заданте по варианту" << std::endl
<< "0. Выход" << std::endl
<< "->";
 * */
enum MENU {
    EXIT=0,
    APPEND,
    INSERT,
    POP,
    REMOVE,
    CLAER,
    PRINT,
    SIZE,
    FIND,
    RFIND,
    ISEMPTY,
    LOADDATA,
    WRITEFILE,
    VARIANTTASK,
};

YMM::MyList* loadData() {
    std::string line;
    YMM::MyList* list_ptr = new YMM::MyList;
    YMM::File file(LOAD_FILE_NAME, "r");
    
    while(file.readLine(line)) {
        double num = std::stod(line);
        list_ptr->append(num);
    }
    file.close();

    return list_ptr;
}

void writeData(YMM::MyList& list) {
    int size = list.size();
    File file(WRITE_FILE_NAME, "w");
    for (int i = 0; i < size; i++) {
        file.write(std::to_string(list[i])+"\n");
    }
    file.close();
}
template<typename T>
T input() {
    T num = 0;
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
    std::cout << "Input num: ";
    double num = input<double>();
    list.append(num);
}

void insert(YMM::MyList& list) {
    std::cout << "input index: ";
    int index = input<int>();
    std::cout << "input num: ";
    double num = input<double>();
    list.insert(index, num);
}

void pop(YMM::MyList& list) {
    std::cout << "input index: ";
    int index = input<int>();
    std::cout << "pop: " << list.pop(index) << std::endl;
}

void remove(YMM::MyList& list) {
    std::cout << "input index: ";
    int index = input<int>();
    list.removeItem(index);
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
    std::cout << "input num: ";
    double num = input<double>();
    std::cout << "input start range: ";
    int start = input<int>();
    std::cout << "input end range: ";
    int end = input<int>();
    std::cout << "founded element: " << list.find(num, start, end) << std::endl;
}

void rfind(YMM::MyList& list) {
    std::cout << "input num: ";
    double num = input<double>();
    std::cout << "input start range: ";
    int start = input<int>();
    std::cout << "input end range: ";
    int end = input<int>();
    std::cout << "founded element: " << list.find(num, start, end) << std::endl;
}

void isEmpty(YMM::MyList& list) {
    if (list.isVoid()) {
         std::cout << "list is Empty" << std::endl;
    } else {
         std::cout << "list is Not Empty" << std::endl;
    }
}


void variantTask(YMM::MyList& list) {
    int size = list.size();
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += list[i] * (size - i);
    }
    std::cout << "x[i] * (n - i) = " << sum << std::endl;
}

void printMenu() {
std::cout << "Меню" << std::endl
<< APPEND << ". Append" << std::endl
<< INSERT << ". Insert" << std::endl
<< POP << ". Pop" << std::endl
<< REMOVE << ". Remove" << std::endl
<< CLAER << ". Clear" << std::endl
<< PRINT << ". Print" << std::endl
<< SIZE << ". Size" << std::endl
<< FIND << ". Find" << std::endl
<< RFIND << ". Rfind" << std::endl
<< ISEMPTY << ". IsEmpty" << std::endl
<< LOADDATA << ". Считать из файла" << std::endl
<< WRITEFILE << ". Записать в файл" << std::endl
<< VARIANTTASK << ". Заданте по варианту" << std::endl
<< EXIT << ". Выход" << std::endl
<< "->";
}

int main() {
    using namespace YMM;

    // data
    MyList list;
 
    while (true) {
        printMenu();
        int choice = input<int>();
        switch (choice) {
        case APPEND:
            append(list);
            break;
        case INSERT:
            insert(list);
            break; 
        case POP:
            pop(list);
            break;
        case REMOVE:
            remove(list);
            break;
        case CLAER:
            clear(list);
            break;
        case PRINT:
            print(list);
            break;
        case SIZE:
            size(list);
            break;
        case FIND:
            find(list);
            break;
        case RFIND:
            rfind(list);
            break;
        case ISEMPTY:
            isEmpty(list);
            break;
        case LOADDATA:
            list = *loadData();
            break;
        case WRITEFILE:
            writeData(list);
            break;
        case VARIANTTASK:
            variantTask(list);
            break;
        case EXIT:
            return 0;
        }
        std::cout << "\n";
    }
    return 0;
}
