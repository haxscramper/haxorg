#include <cstdlib>
#include <iostream>

#include <ex_cpp_library/value.hpp>

int main() {
    int expected = std::stoi(std::getenv("EX_EXPECTED_VERSION"));

    if (ex_fixture::value() != expected) { return 1; }

    std::cout << "EX_CONAN_TEST_PACKAGE:ex_cpp_library:" << expected << '\n';
    return 0;
}
