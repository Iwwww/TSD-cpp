#include "Exception.hpp"
#include "../File/File.hpp"

int main() {
    using namespace YMM;

    File file("test.txt", "w");
    file.write("Hello");
    YMM::Exception e;
    e.warning("warnign");
}
