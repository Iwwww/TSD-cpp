#pragma once
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


        private:
            std::string lable{};
            std::vector<Menu> menus{};
            func function = nullptr;
            std::any* params = nullptr;
            int level = 0;

    };
}
