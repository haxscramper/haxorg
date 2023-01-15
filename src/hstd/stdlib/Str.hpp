#pragma once

#include <string>
#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Pair.hpp>

struct Str : public std::string {
    using std::string::string;
    using std::string::operator[];
    using std::string::at;

    Str(std::string_view view) : std::string(view.data(), view.size()) {}
    Str(CR<std::string> it) : std::string(it.data(), it.size()) {}
    Str() = default;

    Str substr(int start, int count = npos) const {
        return Str(std::string::substr(start, count));
    }

    bool startsWith(const std::string& prefix) const {
        return find(prefix) == 0;
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

    bool endsWith(const std::string& suffix) const {
        return rfind(suffix) == length() - suffix.length();
    }

    bool contains(const std::string& sub) const {
        return find(sub) != std::string::npos;
    }

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


    Str rightAligned(int n, char c = ' ') {
        Str res;
        if (size() < n) {
            res.append(n - size(), c);
        }
        res.append(*this);
        return res;
    }

    Str leftAligned(int n, char c = ' ') {
        auto s = *this;
        if (s.size() < n) {
            s.append(n - s.size(), c);
        }
        return s;
    }
};
