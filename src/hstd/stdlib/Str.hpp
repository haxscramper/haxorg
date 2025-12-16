#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Pair.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <format>

namespace hstd {

struct Str : public std::string {
    using std::string::operator[];
    using std::string::reserve;

    explicit Str(Span<char> view)
        : std::string(view.data(), view.size()) {}
    explicit Str(std::string_view view)
        : std::string(view.data(), view.size()) {}
    Str(const char* conv) : std::string(conv) {}
    Str(const char* conv, int size) : std::string(conv, size) {}
    Str(CR<std::string> it) : std::string(it.data(), it.size()) {}
    explicit Str(int count, char c) : std::string(count, c) {}
    Str(char c) : std::string(1, c) {}
    Str()                 = default;
    Str(Str const& other) = default;

    char*       data() { return std::string::data(); }
    const char* data() const { return std::string::data(); }

    Str substr(int start, int count = -1) const {
        return Str(std::string::substr(start, count));
    }


    Str      dropPrefix(CR<Str> prefix) const;
    Str      dropSuffix(CR<Str> suffix) const;
    char     at(int pos) const;
    char&    at(int pos);
    Str      replaceAll(const Str& from, const Str& to) const;
    char&    at(BackwardsIndex pos) { return at(size() - pos.value); }
    Vec<Str> split(char delimiter) const;
    Vec<Str> split(const Str& delimiter) const;
    float    toFloat() const { return std::stof(*this); }
    float    toDouble() const { return std::stod(*this); }
    int      toInt() const { return std::stoi(*this); }
    void     append(Str const& str) { std::string::append(str.toBase()); }
    int      size() const { return static_cast<int>(std::string::size()); }
    bool contains(char ch) const { return find(ch) != std::string::npos; }
    bool contains(Str const& ch) const {
        return find(ch) != std::string::npos;
    }


    Str repeated(int N) const;

    template <typename A, typename B>
    std::string_view at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::string_view(this->data() + start, end);
    }

    template <typename A, typename B>
    const std::string_view at(CR<HSlice<A, B>> s, bool checkRange = true)
        const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return std::string_view(this->data() + start, end);
    }

    template <typename A, typename B>
    std::string_view operator[](CR<HSlice<A, B>> s) {
        return at(s, false);
    }

    template <typename A, typename B>
    const std::string_view operator[](CR<HSlice<A, B>> s) const {
        return at(s, false);
    }

    Span<char> toSpan() const {
        return Span<char>(const_cast<char*>(this->data()), size());
    }

    bool               empty() const { return size() == 0; }
    std::string const& toBase() const { return *this; }

    inline Str operator+(CR<Str> other) {
        Str res;
        res.append(*this);
        res.append(other);
        return res;
    }

    int runeLen() const;
};
} // namespace hstd


inline hstd::Str operator+(
    hstd::CR<std::string> in,
    hstd::CR<hstd::Str>   other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

inline hstd::Str operator+(const char* in, hstd::CR<hstd::Str> other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}


template <class CharT>
struct std::formatter<hstd::Str, CharT>
    : std::formatter<std::string, CharT> {
    template <typename FormatContext>
    auto format(const hstd::Str& p, FormatContext& ctx) const {
        return std::formatter<std::string, CharT>::format(p.toBase(), ctx);
    }
};

template <>
struct std::hash<hstd::Str> : std::hash<std::string> {};

inline hstd::Str operator""_ss(char const* value, unsigned long size) {
    return hstd::Str(value, size);
}
