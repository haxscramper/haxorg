#include <fmt/core.h>
#include <fmt/ranges.h>

#include "gen_description.hpp"
#include "gen_converter.hpp"
#include "guile_wrapper.hpp"


QTextStream qcout;

int main(int argc, const char** argv) {
    guile::init();
    SCM doc = guile::eval_file(argv[1]);
    std::cout << doc << std::endl;

    //    GenDescription description = doc.as<GenDescription>();
    //    ASTBuilder     builder;

    //    auto definitions = convert(builder, description);
    //    auto result      = builder.TranslationUnit({definitions});

    //    std::cout << builder.store.toString(result, layout::Options())
    //              << std::endl;
}
