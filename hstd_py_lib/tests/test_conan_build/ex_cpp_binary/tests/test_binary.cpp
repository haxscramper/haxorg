#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <ex_cpp_library/value.hpp>

int main(int argc, char** argv) {
    if (argc != 2) { return 1; }

    std::string command = "\"" + std::string(argv[1]) + "\"";
    FILE*       pipe    = popen(command.c_str(), "r");

    if (pipe == nullptr) { return 1; }

    char output[128] = {};

    if (fgets(output, sizeof(output), pipe) == nullptr) {
        pclose(pipe);
        return 1;
    }

    if (pclose(pipe) != 0) { return 1; }

    int expected = std::stoi(std::getenv("EX_EXPECTED_VERSION"));
    int actual   = std::stoi(output);

    if (actual != ex_fixture::value() || actual != expected) { return 1; }

    std::cout << "Binary value: " << actual << '\n';
    return 0;
}
