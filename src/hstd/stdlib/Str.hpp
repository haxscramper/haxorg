#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <format>

namespace hstd {

struct [[refl(R"({"backend": {"target-backends": ["c"]}})")]] Str
    : public std::string {
    using std::string::operator[];
    using std::string::reserve;

    explicit Str(Span<char> view)
        : std::string(view.data(), view.size()) {}
    explicit Str(std::string_view view)
        : std::string(view.data(), view.size()) {}
    [[refl(R"({"unique-name": "StrFromCString"})")]] Str(const char* conv);
    Str(const char* conv, int size);
    Str(std::string const& it);
    explicit Str(int count, char c);
    Str(char c);
    Str()                 = default;
    Str(Str const& other) = default;

    [[refl]] char*       data();
    [[refl]] const char* data() const;

    Str substr(int start, int count = -1) const;


    [[refl]] Str dropPrefix(Str const& prefix) const;
    [[refl]] Str dropSuffix(Str const& suffix) const;
    [[refl(R"({"unique-name": "atIndex"})")]] char at(int pos) const;
    char&                                          at(int pos);
    Str          replaceAll(Str const& from, Str const& to) const;
    char&        at(BackwardsIndex pos);
    Vec<Str>     split(char delimiter) const;
    Vec<Str>     split(Str const& delimiter) const;
    float        toFloat() const;
    float        toDouble() const;
    int          toInt() const;
    void         append(Str const& str);
    [[refl]] int size() const;
    bool         contains(char ch) const;
    bool         contains(Str const& ch) const;

    Str join(Vec<Str> const& items) const;
    Str repeated(int N) const;

    template <typename A, typename B>
    std::string_view at(HSlice<A, B> const& s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::string_view(this->data() + start, end);
    }

    template <typename A, typename B>
    const std::string_view at(
        HSlice<A, B> const& s,
        bool                checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::string_view(this->data() + start, end);
    }

    template <typename A, typename B>
    std::string_view operator[](HSlice<A, B> const& s) {
        return at(s, false);
    }

    template <typename A, typename B>
    const std::string_view operator[](HSlice<A, B> const& s) const {
        return at(s, false);
    }

    Span<char> toSpan() const {
        return Span<char>(const_cast<char*>(this->data()), size());
    }

    bool               empty() const;
    std::string const& toBase() const;

    inline Str operator+(Str const& other) {
        Str res;
        res.append(*this);
        res.append(other);
        return res;
    }

    int runeLen() const;
};
} // namespace hstd


inline hstd::Str operator+(std::string const& in, hstd::Str const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

inline hstd::Str operator+(const char* in, hstd::Str const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}


template <class CharT>
struct std::formatter<hstd::Str, CharT>
    : std::formatter<std::string, CharT> {
    template <typename FormatContext>
    auto format(hstd::Str const& p, FormatContext& ctx) const {
        return std::formatter<std::string, CharT>::format(p.toBase(), ctx);
    }
};

template <>
struct std::hash<hstd::Str> : std::hash<std::string> {};

inline hstd::Str operator""_ss(char const* value, unsigned long size) {
    return hstd::Str(value, size);
}
