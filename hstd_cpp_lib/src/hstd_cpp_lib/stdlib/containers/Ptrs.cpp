#include <hstd_cpp_lib/stdlib/containers/Ptrs.hpp>

template class std::unique_ptr<char, void (*)(void*)>;
