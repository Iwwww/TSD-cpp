#include "File/File.hpp"
#include "MyTree/MyTree.hpp"
#include "Exception/Exception.hpp"
#include "Menu/Menu.hpp"
#include <any>
#include <vector>
#include <string>

using namespace YMM;

YMM::MyTree* loadData(std::string file_name) {
    std::string line;
    YMM::MyTree* tree_ptr = new YMM::MyTree{};
    YMM::File file(file_name, "r");
    
    while(file.readLine(line)) {
        double num = std::stod(line);
        tree_ptr->insert(num);
    }
    file.close();

    return tree_ptr;
}

void writeData(YMM::MyTree tree, std::string file_name) {
    std::vector vec = tree.getItems();
    int size = vec.size();
    File file(file_name, "w");
    for (int i = 0; i < size; i++) {
        file.write(std::to_string(vec[i])+"\n");
    }
    file.close();
}

void insert(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);

    std::cout << "input num: ";
    double num = YMM::Menu::input<double>();
    tree_ptr->insert(num);
}

void remove(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    std::cout << "input index: ";
    int index = YMM::Menu::input<int>();
//    tree_ptr->removeItem(index);
}

void clear(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    tree_ptr->clear();
}

void print(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    std::cout << "tree print: ";
    tree_ptr->printTree(tree_ptr->getRootPtr(), 0);
    std::cout << std::endl;
}

void size(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    std::cout << "tree size: " << tree_ptr->size() << std::endl;
}

void getItems(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    std::vector vec = tree_ptr->getItems();
    int size = vec.size();
    std::cout << "tree items: ";
    for (int i = 0; i < size; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void isEmpty(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    if (tree_ptr->isVoid()) {
         std::cout << "tree is Empty" << std::endl;
    } else {
         std::cout << "tree is Not Empty" << std::endl;
    }
}

void printLevel(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    int level = YMM::Menu::input<int>("Input level: ");
    std::cout << "print level " << level << ": ";
    tree_ptr->printElementsOnLevel(level);
    std::cout << std::endl;
}

void printElementsOnLevel(std::vector<std::any> params) {
    auto* tree_ptr = std::any_cast<YMM::MyTree*>(params[0]);
    int level = YMM::Menu::input<int>("Input level: ");
    std::cout << "elements count on level " << level << ": ";
    std::cout << tree_ptr->elementsOnLevel(level);
    std::cout << std::endl;
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
    MyTree* tree_ptr = nullptr;
    tree_ptr = loadData(load_data_file);
    std::vector<std::any> params{
        tree_ptr
    };

    Menu menu = Menu("Main", std::vector<Menu>{
                         Menu("Insert", insert),
                         Menu("PrintTree", print),
                         Menu("Size", size),
                         Menu("Get items", getItems),
                         Menu("Is empty", isEmpty),
                         Menu("Clear", clear),
                         Menu("Variant task", std::vector<Menu>{
                            Menu("Print level", printLevel),
                            Menu("Elements count on level", printElementsOnLevel),
                         }),

                         }, params);

    menu.run();

    writeData(*tree_ptr, write_data_file);

    return 0;
}
