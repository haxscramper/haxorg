#include <cstdlib>
#include <iostream>

#include <ex_cpp_library/value.hpp>

int main() {
    int expected = std::stoi(std::getenv("EX_EXPECTED_VERSION"));
    int actual   = ex_fixture::value();

    std::cout << "Library value: " << actual << '\n';
    return actual == expected ? 0 : 1;
}
