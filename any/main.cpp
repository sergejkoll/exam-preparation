#include <iostream>
#include "any.hpp"

int main() {
    any s;
    s = 1;

    std::cout << any_cast<int>(s) << std::endl;

    std::string aab = "aab";
    s = aab;

    std::cout << any_cast<std::string>(s) << std::endl;

    float a = 12.1;
    s = a;
    std::cout << any_cast<float>(s) << std::endl;

    any* p;

    p = reinterpret_cast<any *>(1);
//    std::cout << any_cast<int>(p) << std::endl;

    std::cout << "done!" << std::endl;
    return 0;
}
