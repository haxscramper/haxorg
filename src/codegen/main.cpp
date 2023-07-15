#include <fmt/core.h>
#include <fmt/ranges.h>

#include "gen_description.hpp"
#include "gen_converter.hpp"


QTextStream qcout;

int main(int argc, const char** argv) {
    YAML::Node doc = YAML::LoadFile(argv[1]);

    GenDescription description = doc.as<GenDescription>();
    ASTBuilder     builder;

    auto definitions = convert(builder, description);
    auto result      = builder.TranslationUnit({definitions});

    std::cout << builder.store.toString(result, layout::Options())
              << std::endl;
}
