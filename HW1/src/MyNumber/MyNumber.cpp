#include "MyNumber.hpp"
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

namespace YMM {
    MyNumber::MyNumber() {}

    MyNumber::MyNumber(int num) {
    }

    MyNumber::MyNumber(std::string num) {
    }

    MyNumber::MyNumber(const MyNumber& _number) {
        for (int i = 0; i < SIZE; i++) {
            this->mantis[i] = _number.mantis[i];
        }
        this->offset = _number.offset;
        this->sign = _number.sign;
    }

    MyNumber::~MyNumber(){}

    void MyNumber::pow(int degree) {
        short int mem = 0;
        MyNumber old_number = *this;
        for (int i = 1; i < degree; i++) {
            std::cout << "i = " << i << std::endl;
            std::cout << "this " << *this << std::endl;
            this->multily(old_number);
        }

    }

    void MyNumber::multily(int number) {
        short int mem = 0;
        if (number < 0) {
            this->sign = !this->sign;
            number = std::abs(number);
        }
        for (int i = SIZE - 1; i >= 0; i--) {
            int tmp = this->mantis[i] * number + mem;
            this->mantis[i] = tmp % 10;
            mem = tmp / 10;
        }
        if (mem != 0) {
            this->shiftRight(mem);
            this->offset++;
        }

        this->normolize();
    }

    void MyNumber::multily(MyNumber& obj) {
        MyNumber buffer = obj;
        this->align(buffer);

        MyNumber mem;
        int free = buffer.getFree();
        for (int i = SIZE - 1; i > free; i--) {
            MyNumber tmp = *this;
            tmp.multily(buffer.mantis[i]);
            for (int j = 0; j < SIZE - 1 - i; j++) {
                tmp.shiftLeft(0);
            }
            mem.add(tmp);
            // std::cout << "tmp = " << tmp << std::endl;
            // std::cout << "mem = " << mem << std::endl;
            // std::cout << "obj.mantis[i] = " << buffer.mantis[i] << std::endl;
        }
        *this = mem;
        // std::cout << this->offset << " " << buffer.offset << std::endl;
        this->offset = this->offset + buffer.offset - 1;

        this->normolize();
    }

    void MyNumber::add(MyNumber& obj) {
        MyNumber buffer = obj;
        this->align(buffer);

        short int mem = 0;
        for (int i = SIZE - 1; i >= 0; i--) {
            short int tmp = this->mantis[i] + buffer.mantis[i] + mem;
            this->mantis[i] = tmp % 10;
            mem = tmp / 10;
        }
        if (mem != 0) {
            this->shiftRight(mem);
            this->offset--;
        }

        this->normolize();
    }

    void MyNumber::setMantis(std::vector<short int> mantis) {
        int size = mantis.size();
        for (int i = SIZE - size; i < SIZE; i++) {
            this->mantis[i] = mantis[i - SIZE + size];
        }
    }
    
    void MyNumber::setOffset(short int offset) {
        this->offset = offset;
    }

    void MyNumber::setSign(bool sign) {
        // 0 +
        // 1 -
        this->sign = sign;
    }

    void MyNumber::shiftRight(short int digit) {
        for (int i = SIZE - 1; i > 0; i--) {
            this->mantis[i] = this->mantis[i - 1];
        }

        // set digit at first last place
        int zero_count = 0;
        while (this->mantis[zero_count + 1] == 0 && zero_count < SIZE - 1) {
            zero_count++;
        }
        this->mantis[zero_count] = digit;
    }
    
    void MyNumber::shiftLeft(short int digit) {
        for (int i = 0; i < SIZE - 1; i++) {
            this->mantis[i] = this->mantis[i + 1];
        }

        this->mantis[SIZE - 1] = digit;
    }

    std::ostream& operator<<(std::ostream &out, const MyNumber& obj) {
        if (obj.sign) {
            std::cout << '-';
        }
        std::cout << "0.";
        // find begin of mantis
        int start_mantis = SIZE;
        for (int i = 0; i <= SIZE; i++) {
            if (obj.mantis[i] != 0) {
                start_mantis = i;
                break;
            }
        }

        // if mantis is zero
        if (start_mantis == SIZE) {
            std::cout << 0;
        } else {
            for (int i = start_mantis; i < SIZE; i++) {
                std::cout << obj.mantis[i];
            }
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

    int MyNumber::getFree() {
        int buffer = 0;
        while (this->mantis[buffer] == 0 && buffer < SIZE) {
            buffer++;
        }
        return buffer - 1;
    }

    void MyNumber::pushLeft() {
        short int offset = this->getFree();
        for (int i = 0; i < offset; i++) {
            this->shiftLeft(0);
            this->offset--;
        }
    }

    void MyNumber::normolize() {
        int count = 0;
        while (this->mantis[SIZE - 1] == 0 && count++ < SIZE) {
            this->shiftRight(0);
            this->offset++;
        }
    }

    void MyNumber::align(MyNumber& obj) {
        if (this->offset > obj.offset) {
            while (this->offset != obj.offset) {
                this->shiftLeft(0);
                this->offset--;
            }
        }
        if (this->offset < obj.offset) {
            while (this->offset != obj.offset) {
                obj.shiftLeft(0);
                obj.offset--;
            }
        }
    }
}
