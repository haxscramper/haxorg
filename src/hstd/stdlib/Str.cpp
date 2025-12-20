#include "Str.hpp"
#include <hstd/stdlib/strutils.hpp>

using namespace hstd;

Str hstd::Str::dropPrefix(CR<Str> prefix) const {
    if (this->starts_with(prefix)) {
        return substr(prefix.size());
    } else {
        return *this;
    }
}

Str hstd::Str::dropSuffix(CR<Str> suffix) const {
    if (this->ends_with(suffix)) {
        return substr(0, size() - suffix.size());
    } else {
        return *this;
    }
}

char hstd::Str::at(int pos) const {
    if (0 <= pos && pos < size()) {
        return std::string::operator[](pos);
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos)
            + " but size() is " + std::to_string(size()));
    }
}

char& hstd::Str::at(int pos) {
    if (0 <= pos && pos < size()) {
        return std::string::operator[](pos);
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos)
            + " but size() is " + std::to_string(size()));
    }
}

Str hstd::Str::replaceAll(const Str& from, const Str& to) const {
    size_t startPos = 0;
    Str    result   = *this;
    while ((startPos = result.find(from, startPos)) != std::string::npos) {
        result.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return result;
}

Vec<Str> hstd::Str::split(char delimiter) const {
    Vec<Str>           tokens;
    Str                token;
    std::istringstream tokenStream(*this);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

Vec<Str> hstd::Str::split(const Str& delimiter) const {
    Vec<Str> tokens;
    size_t   start = 0;
    size_t   end   = this->find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(this->substr(start, end - start));
        start = end + delimiter.length();
        end   = this->find(delimiter, start);
    }

    tokens.push_back(this->substr(start, end));

    return tokens;
}

Str Str::join(const Vec<Str>& items) const {
    Str res;
    for (int i = 0; i < items.size(); ++i) {
        if (0 < i) { res += ", "; }
        res += items.at(i);
    }

    return res;
}

Str hstd::Str::repeated(int N) const {
    Str result;
    result.reserve(size() * N);
    for (int i = 0; i < N; ++i) { result += *this; }
    return result;
}

int hstd::Str::runeLen() const { return rune_length(*this); }
