#pragma once
#include <iostream>
#include <vector>

namespace YMM {

class MyTree {
public:
    struct Node {
        Node(int data);

        void setData(int data);
        void setLeftNodePtr(Node*);
        void setRightNodePtr(Node*);
        
        Node* getLeftNode();
        Node* getRightNode();
        double getData();
        bool isEnd();
        void print();

        std::ostream& operator<<(std::ostream&);
    
        int data = 0;
        Node* left_node = nullptr;
        Node* right_node = nullptr;
    };

    MyTree();
    MyTree(const MyTree&);
    ~MyTree();

    bool isVoid() const;
    void clear();
    void insert(int data);
    void printTree(Node*, int) const;
    int elementsOnLevel(int);
    Node* getRootPtr() const;
    std::vector<int> getItems();
    int size();

private:
    Node* _clear(Node*);
    Node* _insert(Node*, int data);
    Node* _elementsOnLevel(Node*, int&, int, int level) const;
    Node* _getItems(Node*, std::vector<int>&);
    Node* _size(Node*, int&);

    Node* root_ptr = nullptr;

};

}
