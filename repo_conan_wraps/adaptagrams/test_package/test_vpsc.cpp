#include <cmath>
#include <iostream>

#include <libvpsc/constraint.h>
#include <libvpsc/solve_VPSC.h>
#include <libvpsc/variable.h>

int main() {
    vpsc::Variable   left(0, 0.0);
    vpsc::Variable   right(1, 0.0);
    vpsc::Constraint separation(&left, &right, 10.0);

    vpsc::Variables   variables{&left, &right};
    vpsc::Constraints constraints{&separation};

    {
        vpsc::IncSolver solver(variables, constraints);
        solver.solve();
    }

    const double gap = right.finalPosition - left.finalPosition;

    if (!std::isfinite(gap) || std::abs(gap - 10.0) > 1e-6) {
        std::cerr << "Unexpected VPSC separation: " << gap << '\n';
        return 1;
    }

    return 0;
}
