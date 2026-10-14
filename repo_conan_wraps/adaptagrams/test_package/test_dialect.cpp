#include <iostream>
#include <sstream>

#include <libdialect/io.h>

int main() {
    // TGLF: two nodes followed by an edge.
    std::istringstream input(
        "0 0 0 10 10\n"
        "1 100 0 10 10\n"
        "#\n"
        "0 1\n"
        "#\n");

    const auto graph = dialect::buildGraphFromTglf(input);

    if (!graph) {
        std::cerr << "Dialect failed to construct a graph\n";
        return 1;
    }

    return 0;
}
