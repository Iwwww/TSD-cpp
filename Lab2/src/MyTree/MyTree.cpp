#include "MyTree.hpp"
#include <vector>

namespace YMM {
using std::vector;

#pragma region Node
MyTree::MyTree::Node::Node(int data) {
    this->data = data;
}
void MyTree::Node::setData(int data) {
    this->data = data;
}

void MyTree::Node::setLeftNodePtr(Node* ptr) {
    this->left_node = ptr;
}

void MyTree::Node::setRightNodePtr(Node* ptr) {
    this->right_node = ptr;
}

MyTree::MyTree::Node* MyTree::MyTree::Node::getLeftNode() {
    return this->left_node;
}

MyTree::MyTree::Node* MyTree::MyTree::Node::getRightNode() {
    return this->right_node;
}

double MyTree::Node::getData() {
    return this->data;
}

bool MyTree::MyTree::Node::isEnd() {
    if (this->left_node == nullptr && this->right_node == nullptr) {
        return true;
    }
    return false;
}

void MyTree::Node::print() {
    std::cout << this->data;
}

std::ostream& operator<<(std::ostream& out, MyTree::Node& obj) {
    obj.print();

    return out;
}
#pragma region Node
MyTree::MyTree() {};

MyTree::MyTree(const MyTree& _list) {
    MyTree* list_ptr = new MyTree;
    Node* current_item_ptr = _list.getRootPtr();
    // copy Nodes here
    this->root_ptr = list_ptr->getRootPtr();
}

MyTree::MyTree::~MyTree() {
    this->clear();
}

bool MyTree::MyTree::isVoid() const {
    return (this->root_ptr == nullptr) ? true : false;
}

void MyTree::insert(int data) {
    this->_insert(this->getRootPtr(), data);
}

MyTree::Node* MyTree::_insert(Node* t, int data) {
    if (this->isVoid()) {
        this->root_ptr = new Node(data);
        t = this->root_ptr;
        return t;
    }

    if (t == nullptr) {
        return new Node(data);
    } 
    if (data == t->getData()) {
        return t;
    } else if (data < t->getData()) {
        t->setLeftNodePtr(_insert(t->getLeftNode(), data));
    } else {
        t->setRightNodePtr(_insert(t->getRightNode(), data));
    }

    return t;
}

void MyTree::clear() {
    if (this->getRootPtr() == nullptr) return;
    this->_clear(this->getRootPtr());
    this->root_ptr = nullptr;
}

MyTree::Node* MyTree::_clear(Node* t) {
    if (t->isEnd()) return t;

    if (t->getLeftNode() != nullptr) {
        t->setLeftNodePtr(_clear(t->getLeftNode()));
        delete t->getLeftNode();
    }
    if (t->getRightNode() != nullptr) {
        t->setRightNodePtr(_clear(t->getRightNode()));
        delete t->getRightNode();
    }

    return t;
}

void MyTree::MyTree::printTree(Node* t, int n) {
    if (t != nullptr) {
        printTree(t->getRightNode(), n + 1);
        for (int i = 0; i < n; i++) {
            std::cout << "  ";
        }
        std::cout << t->getData();
        printTree(t->getLeftNode(), n + 1);
    } else {
        std::cout << std::endl;
    }
}

int MyTree::elementsOnLevel(int level) {
    int return_value = 0;
    Node* root_ptr = this->getRootPtr();
    if (root_ptr != nullptr) {
        _elementsOnLevel(root_ptr, return_value, 0, level);
    }
    return return_value;
}

MyTree::Node* MyTree::_elementsOnLevel(Node* t, int& return_value, int current_level, int level) {
    if (level == current_level) {
        return_value++;
    } else {
        if (t->isEnd()) return t;
        current_level++;
        if (t->getLeftNode() != nullptr) {
            _elementsOnLevel(t->getLeftNode(), return_value, current_level, level);
        }
        if (t->getRightNode() != nullptr) {
            _elementsOnLevel(t->getRightNode(), return_value, current_level, level);
        }
        current_level--;
    }

    return t;
}

void MyTree::printElementsOnLevel(int level) {
    if (this->getRootPtr() != nullptr) {
        this->_printElementsOnLevel(this->getRootPtr(), 0, level);
    }
}

MyTree::Node* MyTree::_printElementsOnLevel(Node* t, int current_level, int level) {
    if (level == current_level) {
        std::cout << t->getData() << " ";
    } else {
        if (t->isEnd()) return t;
        current_level++;
        if (t->getLeftNode() != nullptr) {
            _printElementsOnLevel(t->getLeftNode(), current_level, level);
        }
        if (t->getRightNode() != nullptr) {
            _printElementsOnLevel(t->getRightNode(), current_level, level);
        }
        current_level--;
    }

    return t;
}

MyTree::Node* MyTree::getRootPtr() const {
    return this->root_ptr;
}

std::vector<int> MyTree::getItems() {
    vector<int> vec{};
    if (this->getRootPtr() == nullptr) return vec;
    this->_getItems(this->getRootPtr(), vec);
    return vec;
}

MyTree::Node* MyTree::_getItems(Node* t, std::vector<int>& vec) {
    vec.push_back(t->getData());
    if (t->isEnd()) {
        return t;
    }

    if (t->getLeftNode() != nullptr) {
        _getItems(t->getLeftNode(), vec);
    }
    if (t->getRightNode() != nullptr) {
        _getItems(t->getRightNode(), vec);
    }
    return t;
}

int MyTree::size() const {
    int size = 0;
    if (this->getRootPtr() == nullptr) return 0;
    _size(this->getRootPtr(), size);
    return size;
}

MyTree::Node* MyTree::_size(Node* t, int& size) const {
    if (t != nullptr) {
        size++;
        if (t->isEnd()) {
            return t;
        }
        if (t->getLeftNode() != nullptr) {
            _size(t->getLeftNode(), size);
        }
        if (t->getRightNode() != nullptr) {
            _size(t->getRightNode(), size);
        }
    }
    return t;
}

void MyTree::remove(int data) {
    if (this->getRootPtr() == nullptr) return;
    this->_remove(this->getRootPtr(), nullptr, data);
}

MyTree::Node* MyTree::_remove(Node* t, Node* prev_t, int data) {
    if (t->getData() == data) {
        if (prev_t != nullptr) {
            prev_t->setLeftNodePtr(t->getLeftNode());
            prev_t->setRightNodePtr(t->getRightNode());
        }
        delete t;
    } else {
        if (t->isEnd()) return t;
        prev_t = t;
        if (t->getLeftNode() != nullptr) {
            _remove(t->getLeftNode(), prev_t, data);
        }
        if (t->getRightNode() != nullptr) {
            _remove(t->getRightNode(), prev_t, data);
        }
    }

    return t;
}
} // namespace YMM
