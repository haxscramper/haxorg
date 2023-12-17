export module hstd.stdlib.Str;

import hstd.system.string_convert;
import hstd.system.basic_typedefs;
import hstd.stdlib.Slice;
import hstd.stdlib.Span;
import hstd.stdlib.Pair;
import hstd.stdlib.Vec;
export import std;
import hstd.stdlib.BackwardsIndex;
import std;

export {
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
    Str(int count, char c) : std::string(count, c) {}
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

template <class CharT>
struct std::formatter<Str, CharT> : std::formatter<std::string, CharT> {
    template <typename FormatContext>
    auto format(const Str& p, FormatContext& ctx) const {
        return std::formatter<std::string, CharT>::format(p.toBase(), ctx);
    }
};

template <>
struct std::hash<Str> : std::hash<std::string> {};
}
