#pragma once

#include <hstd/stdlib/Str.hpp>

struct TestParameters {
    Str corpusGlob;
};

extern TestParameters testParameters;

#include <gtest/gtest.h>
#include <gmock/gmock.h>


namespace testing {
// FIXME despite documentation claim that 'PrintTo' must only be defined
// in the same namespace as the type (`Str`) I had to explicitly
// specialize / the internal template for this to work. It does not seem
// like a big
// issue but https://github.com/google/googletest/blob/main/docs/advanced.md#teaching-googletest-how-to-print-your-values
// this still needs to be investigated.
/// \internal
template <>
inline ::std::string PrintToString(const QString& str) {
    std::string        result;
    std::ostringstream escaped_str;
    for (QChar c : str) {
        if (c == '\n') {
            result += "\\n";
        } else if (c == '\t') {
            result += "\\t";
        } else {
            result += QString(c).toStdString();
        }
    }

    return result;
}

template <>
inline ::std::string PrintToString(const Str& str) {
    PrintToString(str.toBase());
}
} // namespace testing
