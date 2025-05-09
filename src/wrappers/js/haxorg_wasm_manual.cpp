#include "haxorg_wasm_manual.hpp"

void haxorg_wasm_manual_register() {
#define __cast(__Kind)                                                    \
    emscripten::function(                                                 \
        "cast_to_" #__Kind,                                               \
        +[](org::sem::SemId<org::sem::Org> const& node)                   \
            -> org::sem::SemId<org::sem::__Kind> {                        \
            return node.as<org::sem::__Kind>();                           \
        });

    EACH_SEM_ORG_KIND(__cast)

#undef __cast
}
