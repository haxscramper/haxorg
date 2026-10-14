#include <cassert>
#include <kiwi/kiwi.h>

#include <cmath>
#include <iostream>

int main() {
    kiwi::Variable x("x");
    kiwi::Variable y("y");
    kiwi::Solver   solver;

    solver.addConstraint(x + y == 10);
    solver.addConstraint(x - y == 4);
    solver.updateVariables();

    assert(std::fabs(x.value() - 7.0) < 1e-9 && std::fabs(y.value() - 3.0) < 1e-9);
    std::cout << "kiwi wrap OK" << std::endl;
}
