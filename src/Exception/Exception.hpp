#pragma once
#include <fstream>

namespace YMM {
    class Exception {
        public:
            Exception(std::string);
            Exception();
            ~Exception();
            
            void logging();
        
        private:
            std::string error{};

    };
}
