#pragma once

#include <hstd/stdlib/Str.hpp>

struct TestParameters {
    hstd::Str corpusGlob;
};

extern TestParameters testParameters;

#include <gtest/gtest.h>
// #include <gmock/gmock.h>

// adl-based customization points is the most disgusting degenerate idea
// you can possible have. The shit doesn't work reliably, you need to do
// some fucking magic with namespaces and whatever the fuck else, it does
// not work again, and with functions you need to specify the concrete type
// for every type. If this was a structure I could've used `std::format`
// with some form of concept here, if the library was actually written with
// this in mind.
//
// And this pile of vomit stopped working at random. Fuck this shit, I
// cannot believe anyone would even consider writing a library that would
// depend on ADL for customization points. It is a pure unmitigated
// disaster with no way to debug or consistently provide implementation.
#define GTEST_ADL_PRINT_TYPE(__type)                                      \
    namespace testing {                                                   \
        inline std::string PrintToString(__type const& value) {           \
            return fmt1(value);                                           \
        }                                                                 \
                                                                          \
        namespace internal {                                              \
            template <typename Other>                                     \
            class FormatForComparison<__type, Other> {                    \
              public:                                                     \
                static ::std::string Format(const __type& value) {        \
                    return fmt1(value);                                   \
                }                                                         \
            };                                                            \
        }                                                                 \
    } // namespace testing


GTEST_ADL_PRINT_TYPE(hstd::Str);
