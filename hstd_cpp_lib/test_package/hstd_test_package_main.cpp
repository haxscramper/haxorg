#include <hstd/stdlib/containers/Vec.hpp>

int main() {
    hstd::Vec<int> test;
    int            idx = test.push_back_idx(123);
    LOGIC_ASSERTION_CHECK_FMT(
        idx == 0, "Push back must generate index of the inserted item, got {}", idx);
    return 0;
}
