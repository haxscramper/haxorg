#include <gtest/gtest.h>
#include <hstd/system/generator.hpp>
#include <hstd/system/exceptions.hpp>


struct test_exception_1 : CRTP_hexception<test_exception_1> {};

void a() {
    throw test_exception_1::init("Throwing invalid argument in body");
}

void b() { a(); }

void c() { b(); }

generator<int> throw_1() {
    co_yield 12;
    c();
    co_yield 34;
}

TEST(Exception, GeneratorStackTrace) {
    auto gen = throw_1();
    try {
        for (auto _ : gen) {}
    } catch (std::exception& e) { std::cerr << e.what() << std::endl; }
}
