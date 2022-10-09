#include <iostream>
#include <string>
#include <any>

namespace YMM {
    class Menu {
        public:
            using func = void(*)(std::any);
            Menu(std::string lable, func, std::any);
            Menu(std::string lable, Menu, std::any);

            void run();
            void printMenu();

        private:
            std::string lable{};
            func function{};
            Menu* menu{};
            std::any params;

    };
}
