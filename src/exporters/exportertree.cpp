#include <exporters/exportertree.hpp>

void ExporterTree::visitField(
    int&         arg,
    const char*  name,
    In<sem::Org> org) {

    __scope();
    indent();
    os << name << ":"
       << "\n";
    Base::visitField(arg, name, org);
}

void ExporterTree::visitField(
    int&             i,
    const char*      name,
    CVec<sem::SemId> org) {
    if (skipAsEmpty(org)) {
        return;
    }

    __scope();
    indent();
    os << name << ":\n";
    for (const auto& [idx, sub] : enumerate(org)) {
        __scope();
        indent();
        os << "[" << idx << "]:\n";
        visit(i, sub);
    }
}

void ExporterTree::init(In<sem::Org> org) {
    auto ctx = stack.back();
    indent();
    os << os.green() << to_string(org->getKind()) << os.end();

    if (conf.withSubnodeIdx && ctx.subnodeIdx != -1) {
        os << " [" << ctx.subnodeIdx << "]";
    }

    if (conf.withOriginalId) {
        os << " ID:" << org->original.id.getUnmasked();
    }

    if (conf.withLineCol && org->loc.has_value()) {
        auto& [line, col, pos] = org->loc.value();
        os << " " << os.cyan() << line << ":" << col << "(" << pos << ")"
           << os.end();
    }
    os << "\n";
}
