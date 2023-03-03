#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_typedefs.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Pair.hpp>

struct Str : public QString {
    using QString::QString;
    using QString::operator[];
    using QString::at;
    using QString::reserve;


    explicit Str(Span<QChar> view) : QString(view.data(), view.size()) {}
    explicit Str(QStringView view) : QString(view.data(), view.size()) {}
    Str(CR<QString> it) : QString(it.data(), it.size()) {}
    Str(char c) : QString(c, 1) {}
    Str(wchar_t c) : QString(to_string(c)) {}
    Str() = default;

    QChar*       data() { return QString::data(); }
    const QChar* data() const { return QString::data(); }

    Str substr(int start, int count = -1) const {
        return Str(QString::mid(start, count));
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

    template <typename A, typename B>
    QStringView at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return QStringView(this->data() + start, end);
    }

    template <typename A, typename B>
    const QStringView at(CR<HSlice<A, B>> s, bool checkRange = true)
        const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return QStringView(this->data() + start, end);
    }

    template <typename A, typename B>
    QStringView operator[](CR<HSlice<A, B>> s) {
        return at(s, false);
    }

    template <typename A, typename B>
    const QStringView operator[](CR<HSlice<A, B>> s) const {
        return at(s, false);
    }

    Span<QChar> toSpan() const {
        return Span<QChar>(const_cast<QChar*>(this->data()), size());
    }

    bool    empty() const { return size() == 0; }
    QString toBase() const { return *this; }
};

template <>
struct std::hash<Str> {
    std::size_t operator()(Str const& s) const noexcept {
        return std::hash<QString>{}(s);
    }
};

inline Str operator+(CR<QString> in, CR<Str> other) {
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
