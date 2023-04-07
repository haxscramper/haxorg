#include <sem/SemOrg.hpp>

using namespace sem;

#define __init()                                                          \
    os << QString("  ").repeated(ctx.level) << to_string(getKind());

#define __subnodes()                                                      \
    for (const auto& sub : subnodes) {                                    \
        os << "\n";                                                       \
        sub->treeRepr(os, conf, TreeReprCtx{.level = ctx.level + 1});     \
    }

void Org::treeRepr(
    ColStream&       os,
    CR<TreeReprConf> conf,
    CR<TreeReprCtx>  ctx) const {
    __init();
    __subnodes();
}
