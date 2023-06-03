#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>

const int TABLE_SIZE = 20;

class HashTable {
public:
    HashTable();

    void insert(int key, int value);
    int search(int key);
    void remove(int key);

private:
    struct HashNode {
        int key;
        int value;
        bool deleted;

        HashNode(): key(0), value(0), deleted(false) {}
        HashNode(int key, int value): key(key), value(value), deleted(false) {}
    };

    HashNode* table[TABLE_SIZE];

    int hashFunction(int key);
    int hashFunction2(int key);
};

#endif  // !HASHTABLE_HPP
