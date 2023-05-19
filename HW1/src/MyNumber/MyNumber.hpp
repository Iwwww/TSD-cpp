#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "../Exception/Exception.hpp"

namespace YMM {
    const int SIZE = 64;
    class MyNumber {
        public:
            MyNumber();
            MyNumber(int);
            MyNumber(std::string);
            MyNumber(const MyNumber& _number);
            ~MyNumber();

            void add(MyNumber&);
            void pow(int);
            void multily(int);
            void multily(MyNumber&); 
            void setMantis(std::vector<short int>);
            void setOffset(short int offset);
            void setSign(bool sign);
            void shiftRight(short int digit);
            void shiftLeft(short int digit);
            void normolize();
            void align(MyNumber&);

            friend std::ostream& operator<<(std::ostream &out, const MyNumber& obj);
            friend std::ostream& operator<<(std::ostream &out, const MyNumber* obj);
            friend std::istream& operator>>(std::istream &in, MyNumber& obj);
            friend std::istream& operator>>(std::istream &in, MyNumber* obj);
                
        
        private:
            int getFree();
            void pushLeft();

            short int mantis[SIZE]{}; // stores like: 000000012345
            short int offset = 0;
            bool sign = 0;
    };

}
