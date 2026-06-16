#include <hstd/system/aux_utils.hpp>
#include <cmath>

bool hstd::isclose(double a, double b, double rtol, double atol) {
    return std::abs(a - b) <= atol + rtol * std::abs(b);
}
