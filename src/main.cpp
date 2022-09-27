#include "MyList/MyList.hpp"
#include "Exception/Exception.hpp"
#include <fstream>
#include <ostream>
#include <string>

using namespace YMM;

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
    std::string file_name = "data1.txt";
    std::ifstream file(file_name);
    YMM::MyList* list = new YMM::MyList;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            double num = std::stod(line);
            list->append(num);
        }
    } else {
        YMM::Exception("File 'data1.txt' is not open");
    }
    return list;
}

void writeData(YMM::MyList& list) {
    std::string data;
    std::string file_name = "data2.txt";
    std::ofstream file(file_name);
    if (file.is_open()) {
        int size = list.size();
        for (int i = 0; i < size; i++) {
            file << list[i] << std::endl;
        }
    } else {
        YMM::Exception("File 'data2.txt' is not open");
    }
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
