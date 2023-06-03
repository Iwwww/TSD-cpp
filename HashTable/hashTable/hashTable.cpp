#include "hashTable.hpp"

int HashTable::hashFunction(int key) {
    return key % TABLE_SIZE;
}

int HashTable::hashFunction2(int key) {
    return 7 - (key % 7);  // Prime number smaller than table size
}

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

void HashTable::insert(int key, int value) {
    int hashValue = hashFunction(key);
    int stepSize = hashFunction2(key);

    // not empty and not deleted
    while (table[hashValue] != nullptr && !table[hashValue]->deleted) {
        // collision occurred, move to the next position
        hashValue = (hashValue + stepSize) % TABLE_SIZE;
    }

    // empty or deleted
    if (table[hashValue] == nullptr || table[hashValue]->deleted) {
        table[hashValue] = new HashNode(key, value);
    } else {
        // position is occupied, update the value
        table[hashValue]->value = value;
    }
}

int HashTable::search(int key) {
    int hashValue = hashFunction(key);
    int stepSize = hashFunction2(key);

    // have node
    while (table[hashValue] != nullptr) {
        // not deleted and key is the same
        if (!table[hashValue]->deleted && table[hashValue]->key == key) {
            // key found, return the corresponding value
            return table[hashValue]->value;
        }
        hashValue = (hashValue + stepSize) % TABLE_SIZE;
    }

    // Key not found
    return -1;
}

void HashTable::remove(int key) {
    int hashValue = hashFunction(key);
    int stepSize = hashFunction2(key);

    // have node
    while (table[hashValue] != nullptr) {
        // not deleted and key is the same
        if (!table[hashValue]->deleted && table[hashValue]->key == key) {
            table[hashValue]->deleted = true;
            return;
        }
        hashValue = (hashValue + stepSize) % TABLE_SIZE;
    }
}
