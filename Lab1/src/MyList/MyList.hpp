#pragma once
#include <ostream>
#include <iostream>
#include "../Exception/Exception.hpp"

namespace YMM {

class MyList {

    public:
    class Node {
        public:
            Node(double data);

            void setData(double data);
            void setNextNodePtr(Node*);
            void setPrevNodePtr(Node*);
            
            Node* getNextNode();
            Node* getPrevNode();
            double getData();
            bool isEnd();
            void print();

            std::ostream& operator<<(std::ostream&);
        
        private:
            double data{};
            Node* prev_node = nullptr;
            Node* next_node = nullptr;
    };

        MyList();
        MyList(double);
        MyList(const MyList& my_list);
        // add: construct MyList with arr of items [1, 2, 3]
        // MyList(double [], int);
        ~MyList();

        bool isVoid() const;
        void append(double data);
        void insert(int index, const double& data);
        void removeItem(int index);
        double pop(int index);
        double pop();
        void clear();
        void print();
        int size() const;
        int find(const double& data);
        int find(const double& data, const int begin);
        int find(const double& data, const int begin, int end);
        int rfind(const double& data);
        int rfind(const double& data, int begin);
        int rfind(const double& data, int begin, const int end);
        Node* getHeadPtr() const;
        MyList& copy();

        void setLogFileName(std::string);
        std::string getLogFileName();

        double operator[](int);
        

    private:
        Node* head_ptr = nullptr;
        std::string log_file_name = "log.log";

        template<typename T>
        T cutInput(T index, T end) {
            if (abs(index) >= end) {
                index %= end;
                Exception e;
                e.setFileName(this->log_file_name);
                e.warning("Index Cut");
            }
            if (index < 0) {
                index += end; 
            }
            return index;
        }

};
}