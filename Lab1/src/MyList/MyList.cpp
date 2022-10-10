#include "MyList.hpp"
#include <cstdlib>

 namespace YMM {
    #pragma region Item
    void MyList::Node::setData(double data) {
        this->data = data;
    }

    void MyList::Node::setNextNodePtr(Node* ptr) {
        this->next_node = ptr;
    }

    void MyList::Node::setPrevNodePtr(Node* ptr) {
        this->prev_node = ptr;
    }

    MyList::MyList::Node::Node(double data) {
        this->data = data;
    }

    MyList::MyList::Node* MyList::MyList::Node::getNextNode() {
        return this->next_node;
    }

    MyList::MyList::Node* MyList::MyList::Node::getPrevNode() {
        return this->prev_node;
    }

    double MyList::Node::getData() {
        return this->data;
    }

    bool MyList::MyList::Node::isEnd() {
        return (this->next_node == nullptr) ? true : false;
    }

    void MyList::Node::print() {
        std::cout << this->data;
    }

    std::ostream& operator<<(std::ostream& out, MyList::Node& object) {
        object.print();

        return out;
    }
    #pragma endregion Item

    MyList::MyList() {};

    MyList::MyList(double data) {
        this->head_ptr = new MyList::MyList::Node(data);
    }

    MyList::MyList(const MyList& _list) {
        MyList* list_ptr = new MyList;
        Node* current_item_ptr = _list.getHeadPtr();
        while (current_item_ptr != nullptr) {
            list_ptr->append(current_item_ptr->getData());
            current_item_ptr = current_item_ptr->getNextNode();
        }
        this->head_ptr = list_ptr->getHeadPtr();
    }

/*     MyList::MyList::MyList(double data[], int size) {
 *         if (size > 0) {
 *             this->head_ptr->setData(data[0]);
 *             int index = 1;
 *             while (size-- > 1) {
 *                 this->append(data[index++]);
 *             }
 *         }
 *     }
 *  */
    MyList::MyList::~MyList() {
        this->clear();
    }

    bool MyList::MyList::isVoid() const {
        return (this->head_ptr == nullptr) ? true : false;
    }

    void MyList::append(double data) {
        Node* item_ptr = new Node(data);
        if (!isVoid()) {
            Node* current_item_ptr = this->head_ptr;
            while (!current_item_ptr->isEnd()) {
                current_item_ptr = current_item_ptr->getNextNode();
            }
            current_item_ptr->setNextNodePtr(item_ptr);
            item_ptr->setPrevNodePtr(current_item_ptr);

        } else {
            this->head_ptr = item_ptr;
        }
    }

    void MyList::insert(int index, const double& data) {
        Node* item_ptr = new Node(data);
        if (!isVoid()) {
            int size = this->size();
            index = cutInput(index, size);
            
            if (index == 0) {
                Node* tmp_item_ptr = this->head_ptr;
                this->head_ptr = item_ptr;
                item_ptr->setNextNodePtr(tmp_item_ptr);
                if (size != 0) tmp_item_ptr->setPrevNodePtr(item_ptr);
            } else {
                Node* current_item_ptr = this->head_ptr;
                int current_index = 1;
                while (current_index++ < index && !current_item_ptr->isEnd()) {
                    current_item_ptr = current_item_ptr->getNextNode();
                }
                if (!current_item_ptr->isEnd()) {
                    Node* tmp_item_ptr = current_item_ptr->getNextNode();
                    current_item_ptr->setNextNodePtr(item_ptr);
                    item_ptr->setPrevNodePtr(current_item_ptr);
                    item_ptr->setNextNodePtr(tmp_item_ptr);
                    tmp_item_ptr->setPrevNodePtr(item_ptr);
                } else {
                    current_item_ptr->setNextNodePtr(item_ptr);
                    item_ptr->setPrevNodePtr(current_item_ptr);
                }
            }
        } else {
            this->head_ptr = item_ptr;
        }
    }

    void MyList::MyList::removeItem(int index) {
        if (!this->isVoid()) {
            int size = this->size();
            index = cutInput(index, size);
            if (index == 0) {
                Node* tmp_item_ptr = this->head_ptr;
                this->head_ptr = this->head_ptr->getNextNode();
                this->head_ptr->setPrevNodePtr(nullptr);
                delete tmp_item_ptr;
            } else {// if (index > 0 && index <= this->size()) {
                Node* current_item_ptr = this->head_ptr;
                int current_index = 1;
                while (current_index++ < index) {
                    current_item_ptr = current_item_ptr->getNextNode();
                }
                Node* tmp_item_ptr = current_item_ptr->getNextNode();
                if (index != size - 1) {
                    current_item_ptr->setNextNodePtr(tmp_item_ptr->getNextNode());
                    current_item_ptr->getNextNode()->setPrevNodePtr(current_item_ptr);
                } else {
                    current_item_ptr->setNextNodePtr(nullptr);
                }
                delete tmp_item_ptr;
            } 
        }
    }

    double MyList::MyList::pop(int index) {
        if (!this->isVoid()) {
            Node* return_item_ptr = nullptr;
            int size = this->size();
            if (index == 0) {
                return_item_ptr = this->head_ptr;
                this->head_ptr = this->head_ptr->getNextNode();
                this->head_ptr->setPrevNodePtr(nullptr);
                double data = return_item_ptr->getData();
                delete return_item_ptr;
                return data;
            } else if (index > 0 && index < size) {
                Node* current_item_ptr = this->head_ptr;
                int current_index = 1;
                while (current_index++ < index) {
                    current_item_ptr = current_item_ptr->getNextNode();
                }
                return_item_ptr = current_item_ptr->getNextNode();
                if (index != size - 1) {
                    current_item_ptr->setNextNodePtr(return_item_ptr->getNextNode());
                    current_item_ptr->getNextNode()->setPrevNodePtr(current_item_ptr);
                } else {
                    current_item_ptr->setNextNodePtr(nullptr);
                }
                double data = return_item_ptr->getData();
                delete return_item_ptr;
                return data;
            } else {
                Exception("Index Error", this->log_file_name);
            } 

        }
    } 
  
    double MyList::MyList::pop() {
        return this->pop(this->size() - 1);
    }

    void MyList::clear() {
        if (!this->isVoid()) {
            Node* current_item_ptr = this->head_ptr;
            Node* tmp_ptr = nullptr;
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
            Node* current_item_ptr = this->head_ptr;
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
            Node* current_item_ptr = this->head_ptr;
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

        if (!this->isVoid()) {
            if (begin >= 0 && end < size && begin < end) {
                int index = 0;
                Node* current_item_ptr = this->head_ptr;
                while ((current_item_ptr->getData() != data || index < begin) && index++ < end - 1) {
                    current_item_ptr = current_item_ptr->getNextNode();
                }
                if (current_item_ptr->getData() == data && index >= begin) {
                    result_index = index;
                }
            } else {
                Exception e;
                e.setFileName(this->log_file_name);
                e.error("Out of range");
                result_index = -2;
            }
        } else {
            Exception("Empty list", this->log_file_name);
        }

        return result_index;
    }

    int MyList::rfind(const double& data) {
        return find(data, 0, -1);
    }

    int MyList::rfind(const double& data, const int begin) {
        return find(data, begin, -1);
    }

    int MyList::rfind(const double& data, int begin, int end) {
        int result_index = -1;
        int size = this->size();

        if (!this->isVoid()) {
            if (begin >= 0 && end < size && begin < end) {
                Node* current_item_ptr = this->head_ptr;
                for (int index = 0; index <= end; index++) {
                    if (current_item_ptr->getData() == data && index >= begin) {
                        result_index = index;
                    }
                    current_item_ptr = current_item_ptr->getNextNode();
                }
            } else {
                Exception e;
                e.setFileName(this->log_file_name);
                e.error("Out of range");
                result_index = -2;
            }
        } else {
            Exception e;
            e.setFileName(this->log_file_name);
            e.error("Empty list");
        }

        return result_index;
    }

    MyList::Node* MyList::getHeadPtr() const {
        return this->head_ptr;
    }

    MyList& MyList::copy() {
        MyList* list_ptr = new MyList;
        Node* current_item_ptr = this->head_ptr;
        while (current_item_ptr != nullptr) {
            list_ptr->append(current_item_ptr->getData());
            current_item_ptr = current_item_ptr->getNextNode();
        }

        return *list_ptr;
    }

    double MyList::operator[](int index) {
        int size = this->size();
        index = cutInput(index, size);

        Node* current_item_ptr = this->head_ptr;
        for (int i = 0; i < index; i++) {
            current_item_ptr = current_item_ptr->getNextNode();
        }

        return current_item_ptr->getData();
    }

    void MyList::setLogFileName(std::string file_name) {
        this->log_file_name = file_name;
    }

    std::string MyList::getLogFileName() {
        return this->log_file_name;
    }
}
