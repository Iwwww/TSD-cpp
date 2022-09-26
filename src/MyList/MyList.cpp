#include "MyList.hpp"

 namespace YMM {
    #pragma region Item
    void MyList::Item::setData(double data) {
        this->data = data;
    }

    void MyList::Item::setNextNodePtr(Item* ptr) {
        this->next_node = ptr;
    }

    MyList::MyList::Item::Item(double data) {
        this->data = data;
    }

    MyList::MyList::Item* MyList::MyList::Item::getNextNode() {
        return this->next_node;
    }

    double MyList::Item::getData() {
        return this->data;
    }

    bool MyList::MyList::Item::isEnd() {
        return (this->next_node == nullptr) ? true : false;
    }

    void MyList::Item::print() {
        std::cout << this->data;
    }

    std::ostream& operator<<(std::ostream& out, MyList::Item& object) {
        object.print();

        return out;
    }
    #pragma endregion Item

    MyList::MyList::MyList() {};

    MyList::MyList::MyList(double data) {
        this->head_ptr = new MyList::MyList::Item(data);
    }

    // MyList::MyList::MyList(double data[], int size) {
        // if (size > 0) {
            // this->head_ptr->setData(data[0]);
            // int index = 1;
            // while (size-- > 1) {
                // this->append(data[index++]);
            // }
        // }
    // }

    MyList::MyList::~MyList() {
        this->clear();
    }

    bool MyList::MyList::isVoid() const {
        return (this->head_ptr == nullptr) ? true : false;
    }

    void MyList::append(double& data) {
        Item* item_ptr = new Item(data);
        if (!isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            while (!current_item_ptr->isEnd()) {
                current_item_ptr = current_item_ptr->getNextNode();
            }
            current_item_ptr->setNextNodePtr(item_ptr);

        } else {
            this->head_ptr = item_ptr;
        }
    }

    void MyList::insert(int index, const double& data) {
        Item* item_ptr = new Item(data);
        if (!isVoid()) {
            if (index == 0) {
                Item* tmp_item_ptr = this->head_ptr;
                this->head_ptr = item_ptr;
                item_ptr->setNextNodePtr(tmp_item_ptr);
            } else {
                Item* current_item_ptr = this->head_ptr;
                int current_index = 1;
                while (current_index++ < index && !current_item_ptr->isEnd()) {
                    current_item_ptr = current_item_ptr->getNextNode();
                }
                if (!current_item_ptr->isEnd()) {
                    Item* tmp_item_ptr = current_item_ptr->getNextNode();
                    current_item_ptr->setNextNodePtr(item_ptr);
                    item_ptr->setNextNodePtr(tmp_item_ptr);
                } else {
                    current_item_ptr->setNextNodePtr(item_ptr);
                }
            }
        } else {
            this->head_ptr = item_ptr;
        }
    }

    void MyList::MyList::removeItem(int index) {
        if (!isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            int current_index = -1; // -1 beacuse need priveouse item
            while (current_index++ != index) {
                current_item_ptr = current_item_ptr->getNextNode();
            }
            if (current_index == 0) {
                delete current_item_ptr->getNextNode();

            } else if (!current_item_ptr->isEnd()) {
                // skip one node
                current_item_ptr->setNextNodePtr(current_item_ptr->getNextNode()->getNextNode());
            }
        }
    }

    void MyList::clear() {
        if (!this->isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            Item* tmp_ptr = nullptr;
            while (current_item_ptr != nullptr) {
                tmp_ptr = current_item_ptr;
                current_item_ptr = current_item_ptr->getNextNode();
                delete tmp_ptr;
            }
            this->head_ptr = nullptr;
        }
    }

    void MyList::MyList::print() {
        if (!this->isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            while (!current_item_ptr->isEnd()) {
                std::cout << *current_item_ptr << " ";
                current_item_ptr = current_item_ptr->getNextNode();
            }
            std::cout << *current_item_ptr << " ";
        }
    }

    int MyList::size() const {
        int size = 0;
        if (!this->isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            size = 1;
            while (!current_item_ptr->isEnd()) {
                size++;
                current_item_ptr = current_item_ptr->getNextNode();
            }
        }
    
        return size;
    }

    int MyList::find(const double& data) {
        return find(data, 0, -1);
    }

    int MyList::find(const double& data, const int begin) {
        return find(data, begin, -1);
    }

    int MyList::find(const double& data, const int begin, int end) {
        int result_index = -1;
        int size = this->size();
        if (end == -1) {
            end = size;
        }
        if (begin > size || begin < 0) {
            return -2;
        }

        if (!this->isVoid()) {
            int index = 0;
            Item* current_item_ptr = this->head_ptr;
            while ((current_item_ptr->getData() != data || index < begin) && index <= end) {
                current_item_ptr = current_item_ptr->getNextNode();
                index++;
            }
            if (current_item_ptr->getData() == data && index >= begin) {
                result_index = index;
            }
        }

        return result_index;
    }

    int MyList::rfind(const double& data) {
        return find(data, 0, -1);
    }

    int MyList::rfind(const double& data, const int begin) {
        return find(data, begin, -1);
    }

    int MyList::rfind(const double& data, const int begin, int end) {
        int result_index = -1;
        int size = this->size();
        if (end == -1) {
            end = size;
        }
        if (begin > size || begin < 0) {
            return -2;
        }

        if (!this->isVoid()) {
            Item* current_item_ptr = this->head_ptr;
            for (int index = 0; index <= end; index++) {
                if (current_item_ptr->getData() == data && index >= begin) {
                    result_index = index;
                }
                current_item_ptr = current_item_ptr->getNextNode();
            }
        }

        return result_index;
    }

    std::ostream& operator<<(std::ostream& out, MyList& object) {
        object.print();

        return out;
    }

    double MyList::operator[](int index) {
        if (index > 0 || index < 0) {
            int size = this->size();
            index %= size;
            if (index < 0) {
                index += size; // rest (not add)
            }
        }

        Item* current_item_ptr = this->head_ptr;
        for (int i = 0; i < index; i++) {
            current_item_ptr = current_item_ptr->getNextNode();
        }

        return current_item_ptr->getData();
    }
}
