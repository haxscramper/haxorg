#pragma once

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

using Catch::Matchers::EndsWith;
using Catch::Matchers::Message;
using Catch::Matchers::StartsWith;

#define __TEST_MAIN                                                       \
    int main(int argc, const char** argv) {                               \
        return Catch::Session().run(argc, argv);                          \
    }
