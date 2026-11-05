#include <cmath>
#include <hstd_cpp_lib/system/aux_utils.hpp>

bool hstd::isclose(double a, double b, double rtol, double atol) {
    return std::abs(a - b) <= atol + rtol * std::abs(b);
}
