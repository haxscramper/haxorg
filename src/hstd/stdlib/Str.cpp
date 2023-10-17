#include "Str.hpp"

Str Str::dropPrefix(CR<Str> prefix) const {
    if (prefix.starts_with(prefix)) {
        return substr(prefix.size());
    } else {
        return *this;
    }
}

Str Str::dropSuffix(CR<Str> suffix) const {
    if (suffix.ends_with(suffix)) {
        return substr(0, size() - suffix.size());
    } else {
        return *this;
    }
}

char& Str::at(int pos) {
    if (0 <= pos && pos < size()) {
        return std::string::operator[](pos);
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos)
            + " but size() is " + std::to_string(size()));
    }
}

void Str::replaceAll(const std::string& from, const std::string& to) {
    size_t startPos = 0;
    while ((startPos = this->find(from, startPos)) != std::string::npos) {
        this->replace(startPos, from.length(), to);
        startPos += to.length();
    }
}

Vec<Str> Str::split(char delimiter) const {
    Vec<Str>           tokens;
    Str                token;
    std::istringstream tokenStream(*this);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

Vec<Str> Str::split(const Str& delimiter) const {
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

std::string Str::repeated(int N) const {
    Str result;
    result.reserve(size() * N);
    for (int i = 0; i < N; ++i) {
        result += *this;
    }
    return result;
}
