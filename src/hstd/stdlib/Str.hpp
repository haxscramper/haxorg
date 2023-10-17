#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Pair.hpp>

struct Str : public std::string {
    using std::string::operator[];
    using std::string::reserve;

    explicit Str(Span<char> view)
        : std::string(view.data(), view.size()) {}
    explicit Str(std::string_view view)
        : std::string(view.data(), view.size()) {}
    Str(const char* conv) : std::string(conv) {}
    Str(CR<std::string> it) : std::string(it.data(), it.size()) {}
    Str(char c) : std::string(1, c) {}
    Str(wchar_t c) : std::string(to_string(c)) {}
    Str() = default;

    char*       data() { return std::string::data(); }
    const char* data() const { return std::string::data(); }

    Str substr(int start, int count = -1) const {
        return Str(std::string::substr(start, count));
    }


    Str dropPrefix(CR<Str> prefix) const {
        if (prefix.starts_with(prefix)) {
            return substr(prefix.size());
        } else {
            return *this;
        }
    }

    Str dropSuffix(CR<Str> suffix) const {
        if (suffix.ends_with(suffix)) {
            return substr(0, size() - suffix.size());
        } else {
            return *this;
        }
    }

    char& at(int pos) {
        if (0 <= pos && pos < size()) {
            return std::string::operator[](pos);
        } else {
            throw std::out_of_range(
                "String index out of range wanted " + std::to_string(pos)
                + " but size() is " + std::to_string(size()));
        }
    }

    void replaceAll(const std::string& from, const std::string& to) {
        size_t startPos = 0;
        while ((startPos = this->find(from, startPos))
               != std::string::npos) {
            this->replace(startPos, from.length(), to);
            startPos += to.length();
        }
    }

    char& at(BackwardsIndex pos) { return at(size() - pos.value); }

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

    bool        empty() const { return size() == 0; }
    std::string toBase() const { return *this; }
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
