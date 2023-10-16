#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Pair.hpp>

struct Str : public std::string {
    using std::string::std::string;
    using std::string::operator[];
    using std::string::reserve;


    explicit Str(Span<QChar> view) : std::string(view.data(), view.size()) {}
    explicit Str(std::stringView view) : std::string(view.data(), view.size()) {}
    Str(CR<std::string> it) : std::string(it.data(), it.size()) {}
    Str(char c) : std::string(c) {}
    Str(wchar_t c) : std::string(to_string(c)) {}
    Str() = default;

    QChar*       data() { return std::string::data(); }
    const QChar* data() const { return std::string::data(); }

    Str substr(int start, int count = -1) const {
        return Str(std::string::mid(start, count));
    }


    template <StringConvertible T>
    Str operator+(T const& other) const {
        Str result = *this;
        result.append(other);
        return result;
    }

    Str dropPrefix(CR<Str> prefix) const {
        if (startsWith(prefix)) {
            return substr(prefix.size());
        } else {
            return *this;
        }
    }

    Str dropSuffix(CR<Str> suffix) const {
        if (endsWith(suffix)) {
            return substr(0, size() - suffix.size());
        } else {
            return *this;
        }
    }

    QChar& at(int pos) {
        if (0 <= pos && pos < size()) {
            return std::string::operator[](pos);
        } else {
            throw std::out_of_range(
                "String index out of range wanted " + std::to_string(pos)
                + " but size() is " + std::to_string(size()));
        }
    }

    QChar& at(BackwardsIndex pos) { return at(size() - pos.value); }

    template <typename A, typename B>
    std::stringView at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::stringView(this->data() + start, end);
    }

    template <typename A, typename B>
    const std::stringView at(CR<HSlice<A, B>> s, bool checkRange = true)
        const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::stringView(this->data() + start, end);
    }

    template <typename A, typename B>
    std::stringView operator[](CR<HSlice<A, B>> s) {
        return at(s, false);
    }

    template <typename A, typename B>
    const std::stringView operator[](CR<HSlice<A, B>> s) const {
        return at(s, false);
    }

    Span<QChar> toSpan() const {
        Q_CHECK_PTR(this->data());
        return Span<QChar>(const_cast<QChar*>(this->data()), size());
    }

    bool    empty() const { return size() == 0; }
    std::string toBase() const { return *this; }
};

template <>
struct std::hash<Str> {
    std::size_t operator()(Str const& s) const noexcept {
        return qHash(static_cast<std::string>(s));
    }
};

inline Str operator+(CR<std::string> in, CR<Str> other) {
    Str res;
    res.append(in);
    res.append(other);
    return res;
}

inline Str operator+(const char* in, CR<Str> other) {
    Str res;
    res.append(in);
    res.append(other);
    return res;
}
