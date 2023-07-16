#include <fmt/core.h>
#include <fmt/ranges.h>

#include "gen_description.hpp"
#include "gen_converter.hpp"
#include "guile_wrapper.hpp"


QTextStream qcout;

namespace guile {
template <typename T>
struct convert<Vec<T>> {
    static void decode(Vec<T>& result, SCM list) {
        for (; scm_is_true(scm_pair_p(list)); list = scm_cdr(list)) {
            T temp;
            ::guile::convert<T>::decode(temp, scm_car(list));
            result.push_back(temp);
        }
    }
};

template <typename T>
struct convert<Opt<T>> {
    static void decode(Opt<T>& result, SCM list) {
        if constexpr (std::is_same_v<bool, T>) {
            result = scm_is_true(list);
        } else if (!scm_is_false(list)) {
            T out;
            ::guile::convert<T>::decode(out, list);
            result = out;
        }
    }
};

template <>
struct convert<Str> {
    static void decode(Str& result, SCM item) {
        result = Str::fromStdString(::guile::to_string(item));
    }
};
} // namespace guile

int main(int argc, const char** argv) {
    guile::init();
    SCM doc = guile::eval_file(argv[1]);
    ::guile::print(doc, std::cout);

    GenDescription description;
    ::guile::convert<GenDescription>::decode(description, doc);
    ASTBuilder builder;

    auto definitions = convert(builder, description);
    auto result      = builder.TranslationUnit({definitions});

    std::cout << builder.store.toString(result, layout::Options())
              << std::endl;
}
