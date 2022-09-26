#pragma once

#include <iterator>
#include <ostream>
#include <iostream>
#include "../Exception/Exception.hpp"
namespace YMM {

class MyList {

    public:
    class Item {
        public:
            Item(double data);

            void setData(double data);
            void setNextNodePtr(Item*);
            
            Item* getNextNode();
            double getData();
            bool isEnd();
            void print();

            std::ostream& operator<<(std::ostream&);
        
        private:
            double data{};
            Item* next_node = nullptr;
    };

        MyList();
        MyList(double);
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
        int rfind(const double& data, const int begin);
        int rfind(const double& data, const int begin, const int end);

        double operator[](int);
        

    private:
        Item* head_ptr = nullptr;

};
}
