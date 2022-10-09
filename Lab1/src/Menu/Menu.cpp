#include "Menu.hpp"

namespace YMM {
    Menu::Menu(std::string lable, func function, std::any params) {
        this->lable = lable;
        this->function = function;
        this->params = params;
    }

    Menu::Menu(std::string lable, Menu menu, std::any params) {
        this->lable = lable;
        *this->menu = menu;
        this->params = params;
    }

    void Menu::run() {
        if (this->function) {
            return this->function(params);
        } 
    }

    void Menu::printMenu() {
        std::cout << lable << std::endl;
    }
}
