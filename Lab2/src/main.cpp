// Variant 28
#include "MyTree/MyTree.hpp"
#include <iostream>
#include <vector>
using std::endl;

using namespace YMM;

int main() {
    MyTree tree;
    MyTree::Node *node = new MyTree::Node(0);

    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(-2);
    tree.insert(-1);
    tree.insert(-4);

    tree.printTree(tree.getRootPtr(), 0);
    int level = 2;
    std::cout << "elementsOnLevel(" << level << "): " << tree.elementsOnLevel(level) << endl;

    std::cout << "all elements: ";
    std::vector<int> vec = tree.getItems();
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << endl;

    std::cout << "size: " << tree.size() << endl;

    std::cout << "printElementsOnLevel(" << level << "): ";
    tree.printElementsOnLevel(level);
    std::cout << endl;

    return 0;
}
