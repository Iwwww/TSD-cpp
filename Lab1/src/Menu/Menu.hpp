#pragma once
#include "../Exception/Exception.hpp"
#include <iostream>
#include <string>
#include <any>
#include <vector>

namespace YMM {

    class Menu {
        public:
            using func = void(*)(std::any*);
            Menu(std::string lable, func function, std::any* params);
            Menu(std::string lable, std::vector<Menu> menus, std::any* params);
            Menu(const Menu& menu);

            void run();
            void printMenu();
            std::string getLable();

            template<typename T>
            static T input() {
                T num = 0;
                bool flag = true;
                while (flag) {
                    if (std::cin >> num) {
                        flag = false;
                    } else {
                        Exception::warning("Invalid Input");
                        std::cin.clear();
                        while (std::cin.get() != '\n');
                    }
                }

                return num;
            }

        private:
            std::string lable{};
            std::vector<Menu> menus{};
            func function = nullptr;
            std::any* params = nullptr;
    };
}
