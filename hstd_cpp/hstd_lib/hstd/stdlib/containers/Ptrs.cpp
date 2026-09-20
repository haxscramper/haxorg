#include <hstd/stdlib/containers/Ptrs.hpp>

template class std::unique_ptr<char, void (*)(void*)>;
