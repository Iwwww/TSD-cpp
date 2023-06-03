#include <iostream>
#include "hashTable/hashTable.hpp"

using std::cout;
using std::endl;

int main() {
    HashTable h;

    for (int i = 0; i < 10; i++) {
        h.insert(i, i*10);
    }

    std::cout << "2:" << h.search(2) << std::endl;
    std::cout << "6:" << h.search(6) << std::endl;

    h.remove(6);
    std::cout << "remove 6" << std::endl;
    std::cout << "6:" << h.search(6) << std::endl;

    std::cout << "insert 6" << std::endl;
    h.insert(6, 66);
    std::cout << "6:" << h.search(6) << std::endl;


    return 0;
}
