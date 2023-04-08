#include <sem/SemOrg.hpp>

using namespace sem;

#define __args                                                            \
    ColStream &os, CR<Org::TreeReprConf> conf, CR<Org::TreeReprCtx> ctx


void init(Org const* org, __args) {
    os << QString("  ").repeated(ctx.level) << os.green()
       << to_string(org->getKind()) << os.end();
    if (conf.withOriginalId) {
        os << " ID:" << org->original.id.getUnmasked();
    }

    if (conf.withLineCol && org->loc.has_value()) {
        auto& [line, col] = org->loc.value();
        os << " " << os.cyan() << line << ":" << col << os.end();
    }
}

#define __subnodes()                                                      \
    for (const auto& sub : subnodes) {                                    \
        os << "\n";                                                       \
        sub->treeRepr(os, conf, TreeReprCtx{.level = ctx.level + 1});     \
    }


void Org::treeRepr(__args) const {
    init(this, os, conf, ctx);
    __subnodes();
}

void Leaf::treeRepr(__args) const {
    init(this, os, conf, ctx);
    os << " " << os.yellow() << escape_literal(text) << os.end();
}
