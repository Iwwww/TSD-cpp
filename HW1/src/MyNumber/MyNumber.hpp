#pragma once
#include <iostream>
#include <math.h>
#include "../Exception/Exception.hpp"

namespace YMM {
    /* const int BITES = 4; */
    const int SIZE = 10;
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
            ~MyNumber();

            void add(MyNumber&, MyNumber&);

            friend std::ostream& operator<<(std::ostream &out, const MyNumber& obj);
            friend std::istream& operator>>(std::istream &in, MyNumber& obj);
                
        
        private:
            short int offset = 0;
            short int mantis[SIZE]{}; // 000000012345
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
