module hstd.stdlib.Str;

Str Str::dropPrefix(CR<Str> prefix) const {
    if (this->starts_with(prefix)) {
        return substr(prefix.size());
    } else {
        return *this;
    }
}

Str Str::dropSuffix(CR<Str> suffix) const {
    if (this->ends_with(suffix)) {
        return substr(0, size() - suffix.size());
    } else {
        return *this;
    }
}

char Str::at(int pos) const {
    if (0 <= pos && pos < size()) {
        return std::string::operator[](pos);
    } else {
        throw std::out_of_range(
            "String index out of range wanted " + std::to_string(pos)
            + " but size() is " + std::to_string(size()));
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

Str Str::replaceAll(const Str& from, const Str& to) const {
    size_t startPos = 0;
    Str    result   = *this;
    while ((startPos = result.find(from, startPos)) != std::string::npos) {
        result.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return result;
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

Str Str::repeated(int N) const {
    Str result;
    result.reserve(size() * N);
    for (int i = 0; i < N; ++i) {
        result += *this;
    }
    return result;
}

int Str::runeLen() const {
    int count = 0;
    for (int i = 0; i < length();) {
        unsigned char byte = static_cast<unsigned char>(at(i));
        if (byte <= 127) {
            i += 1;
        } else if ((byte >> 5) == 0b110) {
            i += 2;
        } else if ((byte >> 4) == 0b1110) {
            i += 3;
        } else if ((byte >> 3) == 0b11110) {
            i += 4;
        } else if ((byte >> 2) == 0b111110) {
            i += 5;
        } else if ((byte >> 1) == 0b1111110) {
            i += 6;
        } else {
            i += 1;
        }
        count++;
    }
    return count;
}
