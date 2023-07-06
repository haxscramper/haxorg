#include <hstd/stdlib/Ptrs.hpp>

template class std::unique_ptr<char, void (*)(void*)>;
