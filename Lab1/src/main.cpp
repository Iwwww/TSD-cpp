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

void writeData(YMM::MyList list, std::string file_name) {
    int size = list.size();
    File file(file_name, "w");
    for (int i = 0; i < size; i++) {
        file.write(std::to_string((list)[i])+"\n");
    }
    file.close();
}

void append(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "Input num: ";
    double num = YMM::Menu::input<double>();
    list_ptr->append(num);
}

void insert(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "input index: ";
    int index = YMM::Menu::input<int>();
    std::cout << "input num: ";
    double num = YMM::Menu::input<double>();
    list_ptr->insert(index, num);
}

void pop(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "input index: ";
    int index = YMM::Menu::input<int>();
    std::cout << "pop: " << list_ptr->pop(index) << std::endl;
}

void remove(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "input index: ";
    int index = YMM::Menu::input<int>();
    list_ptr->removeItem(index);
}

void clear(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    list_ptr->clear();
}

void print(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "list print: ";
    list_ptr->print();
    std::cout << std::endl;
}

void size(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "list size: " << list_ptr->size() << std::endl;
}

void find(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "input num: ";
    double num = YMM::Menu::input<double>();
    std::cout << "input start range: ";
    int start = YMM::Menu::input<int>();
    std::cout << "input end range: ";
    int end = YMM::Menu::input<int>();
    std::cout << "founded element: " << list_ptr->find(num, start, end) << std::endl;
}

void rfind(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    std::cout << "input num: ";
    double num = YMM::Menu::input<double>();
    std::cout << "input start range: ";
    int start = YMM::Menu::input<int>();
    std::cout << "input end range: ";
    int end = YMM::Menu::input<int>();
    std::cout << "founded element: " << list_ptr->find(num, start, end) << std::endl;
}

void isEmpty(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    if (list_ptr->isVoid()) {
         std::cout << "list is Empty" << std::endl;
    } else {
         std::cout << "list is Not Empty" << std::endl;
    }
}


void variantTask(std::vector<std::any> params) {
    auto* list_ptr = std::any_cast<YMM::MyList*>(params[0]);
    int size = list_ptr->size();
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (*list_ptr)[i] * (size - i);
    }
    std::cout << "x[i] * (n - i) = " << sum << std::endl;
}


std::string YMM::Exception::log_file_name = "log.log";

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

    Exception::setLogFileName(log_file);

    // data
    MyList* list_ptr = nullptr;
    list_ptr = loadData(load_data_file);
    std::vector<std::any> params{
        list_ptr
    };

    Menu menu = Menu("Main", std::vector<Menu>{
            Menu("Add", std::vector<Menu>{
                    Menu("Append", append),
                    Menu("Insert", insert)
                    }),
            Menu("Put Away", std::vector<Menu>{
                    Menu("Pop", pop),
                    Menu("Remove", remove),
                    Menu("Clear", clear)
                    }),
            Menu("Find", std::vector<Menu>{
                    Menu("Find", find),
                    Menu("RFind", rfind)
                    }),
            Menu("List Info", std::vector<Menu>{
                    Menu("Print", print),
                    Menu("Size", size),
                    Menu("Is Empty", isEmpty)
                    }),
            Menu("Variant Task", variantTask),
            }, params);
            
    menu.run();

    writeData(*list_ptr, write_data_file);

    return 0;
}
