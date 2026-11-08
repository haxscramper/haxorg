#include "Str.hpp"
#include <hstd_cpp_lib/stdlib/algorithms/strutils.hpp>
#include <sstream>
#include <stdexcept>

using namespace hstd;

template <typename Derived>
Derived const& StrCommon<Derived>::self() const {
    return static_cast<Derived const&>(*this);
}

template <typename Derived>
std::string_view StrCommon<Derived>::toBase() const {
    return self().asStdView();
}

template <typename Derived>
int StrCommon<Derived>::size() const {
    return static_cast<int>(toBase().size());
}

template <typename Derived>
bool StrCommon<Derived>::contains(char ch) const {
    return toBase().find(ch) != std::string_view::npos;
}

template <typename Derived>
bool StrCommon<Derived>::contains(StrView const& ch) const {
    return toBase().find(ch.asStdView()) != std::string_view::npos;
}

template <typename Derived>
StrView StrCommon<Derived>::substr(int start, int count) const {
    const int n = size();
    if (start < 0 || start > n) {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(start)
            + " but size() is " + std::to_string(n));
    }

    int usedCount = count;
    if (usedCount < 0) { usedCount = n - start; }

    if (usedCount < 0 || start + usedCount > n) {
        throw std::out_of_range(
            "String slice out of range start=" + std::to_string(start)
            + " count=" + std::to_string(usedCount) + " size()=" + std::to_string(n));
    }

    std::string_view base = toBase();
    return StrView(base.data() + start, usedCount);
}

template <typename Derived>
StrView StrCommon<Derived>::dropPrefix(StrView const& prefix) const {
    std::string_view base = toBase();
    std::string_view pfx  = prefix.asStdView();
    if (base.starts_with(pfx)) {
        return StrView(
            base.data() + pfx.size(), static_cast<int>(base.size() - pfx.size()));
    } else {
        return StrView(base);
    }
}

template <typename Derived>
StrView StrCommon<Derived>::dropSuffix(StrView const& suffix) const {
    std::string_view base = toBase();
    std::string_view sfx  = suffix.asStdView();
    if (base.ends_with(sfx)) {
        return StrView(base.data(), static_cast<int>(base.size() - sfx.size()));
    } else {
        return StrView(base);
    }
}

template <typename Derived>
char StrCommon<Derived>::at(int pos) const {
    if (0 <= pos && pos < size()) {
        return toBase()[static_cast<size_t>(pos)];
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos) + " but size() is "
            + std::to_string(size()));
    }
}

template <typename Derived>
float StrCommon<Derived>::toFloat() const {
    return std::stof(std::string(toBase()));
}

template <typename Derived>
double StrCommon<Derived>::toDouble() const {
    return std::stod(std::string(toBase()));
}

template <typename Derived>
int StrCommon<Derived>::toInt() const {
    return std::stoi(std::string(toBase()));
}

template <typename Derived>
hstd::i64 StrCommon<Derived>::toI64() const {
    return std::stoll(std::string(toBase()));
}

template <typename Derived>
hstd::u64 StrCommon<Derived>::toU64() const {
    return std::stoull(std::string(toBase()));
}

template <typename Derived>
bool StrCommon<Derived>::isFloat() const {
    try {
        toFloat();
        return true;
    } catch (...) { return false; }
}

template <typename Derived>
bool StrCommon<Derived>::isDouble() const {
    try {
        toDouble();
        return true;
    } catch (...) { return false; }
}

template <typename Derived>
bool StrCommon<Derived>::isInt() const {
    try {
        toInt();
        return true;
    } catch (...) { return false; }
}

template <typename Derived>
bool StrCommon<Derived>::isI64() const {
    try {
        toI64();
        return true;
    } catch (...) { return false; }
}

template <typename Derived>
bool StrCommon<Derived>::isU64() const {
    try {
        toU64();
        return true;
    } catch (...) { return false; }
}

template <typename Derived>
Str StrCommon<Derived>::replaceAll(StrView const& from, StrView const& to) const {
    Str              result(toBase());
    std::string_view fromView = from.asStdView();
    std::string_view toView   = to.asStdView();

    if (fromView.empty()) { return result; }

    size_t startPos = 0;
    while ((startPos = result.find(fromView, startPos)) != std::string::npos) {
        result.replace(startPos, fromView.size(), toView.data(), toView.size());
        startPos += toView.size();
    }
    return result;
}

template <typename Derived>
Str StrCommon<Derived>::repeated(int N) const {
    Str result;
    if (N <= 0 || self().empty()) { return result; }

    std::string_view base = toBase();
    result.reserve(static_cast<size_t>(size()) * static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) { result.append(base); }

    return result;
}

template <typename Derived>
int StrCommon<Derived>::runeLen() const {
    return rune_length(std::string(toBase()));
}

StrView::StrView(std::string_view view) : std::string_view(view.data(), view.size()) {}
StrView::StrView(std::string const& view) : std::string_view(view.data(), view.size()) {}

StrView::StrView(char const* conv) : std::string_view(conv) {}

StrView::StrView(char const* conv, int size)
    : std::string_view(conv, static_cast<size_t>(size)) {}

StrView::StrView(Str const& str)
    : std::string_view(str.data(), static_cast<size_t>(str.size())) {}

std::string_view StrView::asStdView() const { return *this; }

Str StrView::str() const { return Str(*this); }

Str::Str(Span<char> view) : std::string(view.data(), view.size()) {}

Str::Str(std::string_view view) : std::string(view.data(), view.size()) {}

Str::Str(StrView view) : std::string(view.data(), view.size()) {}

Str::Str(char const* conv) : std::string(conv) {}

Str::Str(char const* conv, int size) : std::string(conv, static_cast<size_t>(size)) {}

Str::Str(std::string const& it) : std::string(it.data(), it.size()) {}

Str::Str(int count, char c) : std::string(static_cast<size_t>(count), c) {}

Str::Str(char c) : std::string(1, c) {}

char* Str::data() { return std::string::data(); }

const char* Str::data() const { return std::string::data(); }

std::string_view Str::asStdView() const {
    return std::string_view(std::string::data(), std::string::size());
}

StrView Str::view() const { return StrView(asStdView()); }

char& Str::at(int pos) {
    if (0 <= pos && pos < size()) {
        return std::string::operator[](static_cast<size_t>(pos));
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos) + " but size() is "
            + std::to_string(size()));
    }
}

char& Str::at(BackwardsIndex pos) { return at(size() - pos.value); }
char  Str::at(BackwardsIndex pos) const { return at(size() - pos.value); }

void Str::append(Str const& str) {
    std::string::append(str.data(), static_cast<size_t>(str.size()));
}

void Str::append(StrView const& str) { std::string::append(str.data(), str.size()); }

void Str::append(std::string str) { std::string::append(str.data(), str.size()); }
void Str::append(std::string_view str) { std::string::append(str.data(), str.size()); }

void Str::append(char const* str) { std::string::append(str); }

Span<char> Str::toSpan() const {
    return Span<char>(const_cast<char*>(this->data()), size());
}

std::string const& Str::toBase() const { return *this; }

Str Str::operator+(Str const& other) const {
    Str res;
    res.append(*this);
    res.append(other);
    return res;
}

template class hstd::StrCommon<hstd::Str>;
template class hstd::StrCommon<hstd::StrView>;

Str operator+(std::string const& in, hstd::Str const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

Str operator+(char const* in, hstd::Str const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

Str operator+(char const* in, hstd::StrView const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

Str operator+(std::string_view in, hstd::StrView const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

hstd::Str operator""_ss(char const* value, unsigned long size) {
    return hstd::Str(value, static_cast<int>(size));
}

hstd::StrView operator""_svs(char const* value, unsigned long size) {
    return hstd::StrView(value, static_cast<int>(size));
}

Str operator+(char const* in, std::string_view const& other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}

Str operator+(Str const& in, char const* other) {
    hstd::Str res;
    res.append(in);
    res.append(other);
    return res;
}


char StrView::at(BackwardsIndex pos) const { return at(size() - pos.value); }
