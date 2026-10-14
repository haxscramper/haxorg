#pragma once

#include <csignal>
#include <cstdlib>

namespace trace_fixture {

struct Point {
    int x;
    int y;
};

struct Envelope {
    Point       point;
    int         numbers[3];
    const char* label;
};

[[gnu::noinline]] int inspect(
    int             count,
    Point           point,
    Envelope const& envelope,
    int*            pointer) {
    volatile int result{count + point.x + point.y + envelope.point.x + *pointer};

    return result;
}

[[gnu::noinline]] int hidden_frame() {
    Point    point{.x = 17, .y = 29};
    Envelope envelope{.point = point, .numbers = {3, 5, 8}, .label = "fixture"};
    int      value{42};

    return inspect(7, point, envelope, &value);
}

[[gnu::noinline]] void abort_process() { std::abort(); }

void repeat_signal(int signal) {
    std::signal(signal, SIG_DFL);
    std::raise(signal);
}

[[gnu::noinline]] void repeated_abort() {
    std::signal(SIGABRT, repeat_signal);
    std::raise(SIGABRT);
}

} // namespace trace_fixture
