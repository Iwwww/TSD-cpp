#include "Menu.hpp"
#include <chrono>
#include <iterator>
#include <string>
#include <vector>

namespace YMM {
    Menu::Menu(std::string lable, func function, std::any* params) { this->lable = lable;
        this->function = function;
        this->params = params;
    }

    Menu::Menu(std::string lable, std::vector<Menu> menus, std::any* params) {
        this->lable = lable;
        this->menus = menus;
        this->params = params;
    }

    Menu::Menu(const Menu& menu) {
        this->lable = menu.lable;
        this->menus = menu.menus;
        this->function = *&menu.function;
        this->params = menu.params;
    }

    void Menu::run() {
        bool flag = true;
        while (flag) {
            int select{};
            printMenu();

            if (this->function == nullptr) {
                do {
                    std::cout << "Select >> ";
                    std::cin >> select;
                } while (select == -1 || select > menus.size());

                select--;
                std::cout << std::endl;

                if (select == -1) {
                    // exit
                    flag = false;
                } else {
                    menus[select].run();
                }

            } else {
                // run function
                function(this->params);
                flag = false;
            }
        }
    }

    void Menu::printMenu() {
        if (this->function == nullptr) {
            std::cout << "\n\n";
            std::cout << "MENU:" << this->getLable() << std::endl;
            std::cout << "**====**" << std::endl;
        }

        for (int i = 0; i < this->menus.size(); i++) {
            std::cout << i + 1 << ". " << this->menus[i].getLable() << std::endl;
        }
    }

    std::string Menu::getLable() {
        return this->lable;
    }
}
