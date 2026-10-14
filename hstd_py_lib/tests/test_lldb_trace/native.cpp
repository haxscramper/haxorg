#include "fixture.hpp"

#include <string_view>

int main(int count, char** arguments) {
    if (1 < count) {
        const std::string_view mode{arguments[1]};

        if (mode == "abort") {
            trace_fixture::abort_process();
        } else if (mode == "repeat") {
            trace_fixture::repeated_abort();
        }
    }

    const int result{trace_fixture::hidden_frame()};
    return result == 112 ? 0 : 1;
}
