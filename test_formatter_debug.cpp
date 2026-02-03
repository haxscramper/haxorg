#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <format>
#include <iostream>

int main() {
    using namespace hstd;

    Vec<std::string>          v{"first", "second"};
    SmallVec<std::string, 10> sv{"first", "second"};

    std::string v_fmt  = std::format("{}", v);
    std::string sv_fmt = std::format("{}", sv);

    std::cout << "Vec format:      '" << v_fmt << "'\n";
    std::cout << "SmallVec format: '" << sv_fmt << "'\n";
    std::cout << "Are equal: " << (v_fmt == sv_fmt ? "YES" : "NO") << "\n";

    if (v_fmt != sv_fmt) {
        std::cout << "Vec length: " << v_fmt.length() << "\n";
        std::cout << "SmallVec length: " << sv_fmt.length() << "\n";
    }

    return 0;
}
