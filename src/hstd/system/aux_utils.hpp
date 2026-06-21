#pragma once

#include <hstd/system/macros.hpp>

namespace hstd {

/// Helper base type for defining CRTP classes
template <typename T>
struct CRTP_this_method {
  protected:
    inline T*       _this() { return static_cast<T*>(this); }
    inline T const* _this() const { return static_cast<T const*>(this); }
};

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b


#define __ploc()                                                                         \
    std::cout << __FILE__ << ":" << __LINE__ << " at " << __func__ << std::endl;

bool isclose(double a, double b, double rtol = 1e-5, double atol = 1e-8);

} // namespace hstd
