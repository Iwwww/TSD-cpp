#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "../Exception/Exception.hpp"

namespace YMM {
    /* const int BITES = 4; */
    const int SIZE = 1024;
    class MyNumber {
        public:
            /* class Digit {
             *     public:
             *         Digit();
             *         ~Digit();
             *         
             *     // private:
             *         bool digit[BITES]{};
             * }; */
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
            friend std::istream& operator>>(std::istream &in, MyNumber& obj);
                
        
        private:
            int getFree();
            void pushLeft();

            short int mantis[SIZE]{}; // stores like: 000000012345
            short int offset = 0;
            bool sign = 0;

            // union {
                // bool d:4;
                // struct {
                    // bool a0:1;
                    // bool a1:1;
                    // bool a2:1;
                    // bool a3:1;
                    // // bool a4:1;
                    // // bool a5:1;
                    // // bool a6:1;
                    // // bool a7:1;
                // } byte;
            // } digit;

    };

}
