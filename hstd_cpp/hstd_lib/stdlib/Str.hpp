#pragma once

#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/system/basic_typedefs.hpp>
#include <string>
#include <string_view>

namespace hstd {

class Str;
class StrView;

template <typename Derived>
class StrCommon {
  public:
    [[refl]] int     size() const;
    bool             contains(char ch) const;
    bool             contains(StrView const& ch) const;
    StrView          substr(int start, int count = -1) const [[clang::lifetimebound]];
    StrView          dropPrefix(StrView const& prefix) const;
    StrView          dropSuffix(StrView const& suffix) const;
    char             at(int pos) const;
    float            toFloat() const;
    double           toDouble() const;
    int              toInt() const;
    hstd::u64        toU64() const;
    hstd::i64        toI64() const;
    bool             isFloat() const;
    bool             isDouble() const;
    bool             isInt() const;
    bool             isU64() const;
    bool             isI64() const;
    Str              replaceAll(StrView const& from, StrView const& to) const;
    Str              repeated(int N) const;
    int              runeLen() const;
    std::string_view toBase() const [[clang::lifetimebound]];

  protected:
    Derived const& self() const [[clang::lifetimebound]];
};

class [[gsl::Pointer]] StrView
    : public std::string_view
    , public StrCommon<StrView> {
  public:
    using std::string_view::operator[];
    using std::string_view::at;
    using StrCommon<StrView>::size;
    using StrCommon<StrView>::contains;
    using StrCommon<StrView>::substr;

    StrView() = default;
    StrView(std::string_view view [[clang::lifetimebound]]);
    StrView(std::string const& view [[clang::lifetimebound]]);
    [[refl(R"({"unique-name": "StrViewFromCString"})")]] StrView(char const* conv);
    StrView(char const* conv, int size);
    StrView(Str const& str [[clang::lifetimebound]]);

    std::string_view asStdView() const [[clang::lifetimebound]];

    template <typename A, typename B>
    StrView at(HSlice<A, B> const& s, bool checkRange = true) const
        [[clang::lifetimebound]] {
        const auto [start, end] = getSpan(StrCommon<StrView>::size(), s, checkRange);
        return StrView(data() + start, end);
    }

    char at(BackwardsIndex pos) const;

    template <typename A, typename B>
    StrView operator[](HSlice<A, B> const& s) const [[clang::lifetimebound]] {
        return at(s, false);
    }

    Str str() const;
};

struct [[refl(R"({"backend": {"target-backends": ["c"]}})"), gsl::Owner]] Str
    : public std::string
    , public StrCommon<Str> {
    using std::string::operator[];
    using std::string::at;
    using std::string::reserve;
    using StrCommon<Str>::size;
    using StrCommon<Str>::substr;
    using StrCommon<Str>::contains;

    explicit Str(Span<char> view);
    explicit Str(std::string_view view);
    explicit Str(StrView view);
    [[refl(R"({"unique-name": "StrFromCString"})")]] Str(char const* conv);
    Str(char const* conv, int size);
    Str(std::string const& it);
    explicit Str(int count, char c);
    Str(char c);
    Str()                 = default;
    Str(Str const& other) = default;

    [[refl]] char*       data();
    [[refl]] const char* data() const;

    std::string_view asStdView() const [[clang::lifetimebound]];
    StrView          view() const [[clang::lifetimebound]];

    char& at(int pos);
    char& at(BackwardsIndex pos);
    char  at(BackwardsIndex pos) const;

    void append(Str const& str);
    void append(StrView const& str);
    void append(std::string str);
    void append(std::string_view str);
    void append(char const* str);

    Span<char> toSpan() const;

    std::string const& toBase() const;

    Str operator+(Str const& other) const;
    template <typename A, typename B>
    StrView at(HSlice<A, B> const& s, bool checkRange = true) const
        [[clang::lifetimebound]] {
        const auto [start, end] = getSpan(StrCommon<Str>::size(), s, checkRange);
        return StrView(data() + start, end - start + 1);
    }

    template <typename A, typename B>
    StrView operator[](HSlice<A, B> const& s) const [[clang::lifetimebound]] {
        return at(s, false);
    }
};

} // namespace hstd

hstd::Str     operator+(std::string const& in, hstd::Str const& other);
hstd::Str     operator+(char const* in, hstd::Str const& other);
hstd::Str     operator+(char const* in, hstd::StrView const& other);
hstd::Str     operator+(char const* in, std::string_view const& other);
hstd::Str     operator+(hstd::Str const& in, char const* other);
hstd::Str     operator+(std::string_view in, hstd::StrView const& other);
hstd::Str     operator""_ss(char const* value, unsigned long size);
hstd::StrView operator""_svs(char const* value, unsigned long size);

template <class CharT>
struct fmt::formatter<hstd::Str, CharT> : fmt::formatter<std::string_view, CharT> {
    hstd::fmt_iter format(hstd::Str const& p, fmt::format_context& ctx) const {
        return fmt::formatter<std::string_view, CharT>::format(p.asStdView(), ctx);
    }
};

template <class CharT>
struct fmt::formatter<hstd::StrView, CharT> : fmt::formatter<std::string_view, CharT> {
    hstd::fmt_iter format(hstd::StrView const& p, fmt::format_context& ctx) const {
        return fmt::formatter<std::string_view, CharT>::format(p.asStdView(), ctx);
    }
};

template <>
struct std::hash<hstd::Str> : std::hash<std::string> {};

template <>
struct std::hash<hstd::StrView> : std::hash<std::string_view> {};


/// \brief User literal with longer name that is safe enough to be included in all headers
/// by default.
constexpr hstd::StrView operator""_str_view(char const* str, std::size_t len) noexcept {
    return hstd::StrView(str, len);
}
