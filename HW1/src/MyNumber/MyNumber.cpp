#include "MyNumber.hpp"
#include <cctype>
#include <iostream>
#include <string>

namespace YMM {
    MyNumber::MyNumber() {}

    MyNumber::MyNumber(int num) {
    }

    MyNumber::MyNumber(std::string num) {
    }

    MyNumber::~MyNumber(){}

    void MyNumber::add(MyNumber& obj1, MyNumber& obj2) {
        short int mem = 0;
        for (int i = 0; i < SIZE; i++) {
            short int tmp = obj1.mantis[i] + obj2.mantis[i] + mem;
            obj1.mantis[i] = tmp % 10;
            mem = tmp / 10;
        }
    }
    
    std::ostream& operator<<(std::ostream &out, const MyNumber& obj) {
        if (obj.sign) {
            std::cout << '-';
        }
        std::cout << "0.";
        // find begin of mantis
        int start_range_mantis = 0;
        for (int i = 0; i < SIZE; i++) {
            if (obj.mantis[i] != 0) {
                start_range_mantis = i;
                break;
            }
        }
        for (int i = start_range_mantis; i < SIZE; i++) {
            std::cout << obj.mantis[i];
        }
        std::cout << "E";
        std::cout << obj.offset;

        return out;
    }

    std::istream& operator>>(std::istream &in, MyNumber& obj) {
        /* example:
         * +0.123456E5
         * -0.123456e5
         *  +++     ++  ---> this symbols are requiare */

        std::string tmp = "";
        in >> tmp;
        int size = tmp.size();
        char ch[1] = "";
        int i = 0;
        int offset_count = 0;
        int offset = 0;
        bool bad_flag = false;

        if (tmp[0] == '+') i++;
        else if (tmp[0] == '-') {
            i++; 
            obj.sign = 1;
        }

        if (tmp[i] != '0') {
            std::cout << "Wrong number format: no first zero" << std::endl;
            // Exception::error("Input Error");
            i = size - 1;
            bad_flag = true;
        } else {
            i++;
        }

        if (tmp[i] != '.') {
            std::cout << "Wrong number format: undefined dot" << std::endl;
            // Exception::error("Input Error");
            i = size;
            bad_flag = true;
        } else {
            i++;
        }

        int mantis_length = 0;
        while (i < size && tmp[i] != 'E' && tmp[i] != 'e') {
            offset_count++;
            i++;
        }
        for (int m = 0; m < offset_count; m++) {
            ch[0] = tmp[i - offset_count + m];
            short int n = std::stoi(ch);
            obj.mantis[SIZE - offset_count + m] = n;
        }

        if (tmp[i] == 'E' || tmp[i] == 'e') {
            i++;
            // check for sign
            bool degree_sign = false;
            if (tmp[i] == '-') {
                degree_sign = true;
                i++;
            } else if (tmp[i] == '+') {
                i++;
            }

            int count = 0;
            char ch[4]{};
            while (i < size) {
                ch[count] = tmp[i];
                count++;
                i++;
            }
            offset = std::stoi(ch);
            if (degree_sign) offset *= -1;
        } else {
            std::cout << "requiare 'E' or 'e'" << std::endl;
            bad_flag = true;
        }

        if (!bad_flag) {
            obj.offset = offset;
        }

        std::cout << "mantis: " << obj << std::endl;
        std::cout << "offset: " << obj.offset << std::endl;
        std::cout << "sign: " << obj.sign << std::endl;

        return in;
    }
}
