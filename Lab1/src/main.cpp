#include "File/File.hpp"
#include "MyList/MyList.hpp"
#include "Exception/Exception.hpp"
#include "Menu/Menu.hpp"
#include <any>
#include <vector>
#include <string>

using namespace YMM;

YMM::MyList* loadData(std::string file_name) {
    std::string line;
    YMM::MyList* list_ptr = new YMM::MyList{};
    YMM::File file(file_name, "r");
    
    while(file.readLine(line)) {
        double num = std::stod(line);
        list_ptr->append(num);
    }
    file.close();

    return list_ptr;
}

void writeData(YMM::MyList* list_ptr, std::string file_name) {
    int size = list_ptr->size();
    File file(file_name, "w");
    for (int i = 0; i < size; i++) {
        file.write(std::to_string((*list_ptr)[i])+"\n");
    }
    file.close();
}
template<typename T>
T input(std::string log_file) {
    T num = 0;
    bool flag = 1;
    while (flag) {
        if (std::cin >> num) {
            flag = 0;
        } else {
            YMM::Exception("Invalid Input", log_file);
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }

    return num;
}

void append(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "Input num: ";
    double num = input<double>(list_ptr->getLogFileName());
    list_ptr->append(num);

    params = new std::any(list_ptr);
}

void insert(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "input index: ";
    int index = input<int>(list_ptr->getLogFileName());
    std::cout << "input num: ";
    double num = input<double>(list_ptr->getLogFileName());
    list_ptr->insert(index, num);
}

void pop(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "input index: ";
    int index = input<int>(list_ptr->getLogFileName());
    std::cout << "pop: " << list_ptr->pop(index) << std::endl;
}

void remove(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "input index: ";
    int index = input<int>(list_ptr->getLogFileName());
    list_ptr->removeItem(index);
}

void clear(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    list_ptr->clear();
}

void print(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "list print: ";
    list_ptr->print();
    std::cout << std::endl;
}

void size(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "list size: " << list_ptr->size() << std::endl;
}

void find(std::any* params) {
    YMM::MyList* list_ptr= std::any_cast<YMM::MyList*>(*params);
    std::cout << "input num: ";
    double num = input<double>(list_ptr->getLogFileName());
    std::cout << "input start range: ";
    int start = input<int>(list_ptr->getLogFileName());
    std::cout << "input end range: ";
    int end = input<int>(list_ptr->getLogFileName());
    std::cout << "founded element: " << list_ptr->find(num, start, end) << std::endl;
}

void rfind(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    std::cout << "input num: ";
    double num = input<double>(list_ptr->getLogFileName());
    std::cout << "input start range: ";
    int start = input<int>(list_ptr->getLogFileName());
    std::cout << "input end range: ";
    int end = input<int>(list_ptr->getLogFileName());
    std::cout << "founded element: " << list_ptr->find(num, start, end) << std::endl;
}

void isEmpty(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    if (list_ptr->isVoid()) {
         std::cout << "list is Empty" << std::endl;
    } else {
         std::cout << "list is Not Empty" << std::endl;
    }
}


void variantTask(std::any* params) {
    YMM::MyList* list_ptr = std::any_cast<YMM::MyList*>(*params);
    int size = list_ptr->size();
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (*list_ptr)[i] * (size - i);
    }
    std::cout << "x[i] * (n - i) = " << sum << std::endl;
}

int main(int argc, char *argv[]) {
    using namespace YMM;

    // read args
    std::string load_data_file = "data1.txt";
    std::string write_data_file = "data2.txt";
    std::string log_file = "log.log";
    if (argc >= 3) {
        load_data_file = argv[1];
        write_data_file = argv[2];
        log_file = argv[3];
    }

    // data
    MyList* list_ptr = new MyList;
    list_ptr = loadData(load_data_file);
    list_ptr->setLogFileName(log_file);

    std::any* params = new std::any{list_ptr};

    Menu menu("Main", std::vector<Menu>{
            Menu("Add", std::vector<Menu>{
                    Menu("Append", append, params),
                    Menu("Insert", insert, params)
                    }, params),
            Menu("Put Away", std::vector<Menu>{
                    Menu("Pop", pop, params),
                    Menu("Remove", remove, params),
                    Menu("Clear", clear, params)
                    }, params),
            Menu("List Info", std::vector<Menu>{
                    Menu("Print", print, params),
                    Menu("Size", size, params),
                    Menu("Is Empty", isEmpty, params)
                    }, params),
            Menu("Variant Task", variantTask, params),
            }, params);
            
    menu.run();

    writeData(list_ptr, write_data_file);

    return 0;
}
