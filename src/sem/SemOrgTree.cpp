#include <sem/SemOrg.hpp>

using namespace sem;

#define __args                                                            \
    ColStream &os, CR<Org::TreeReprConf> conf, Org::TreeReprCtx ctx

namespace {
void indent(ColStream& os, Org::TreeReprCtx ctx) {
    os << QString("  ").repeated(ctx.level);
}

void init(Org const* org, __args) {
    indent(os, ctx);
    os << os.green() << to_string(org->getKind()) << os.end();

    if (conf.withSubnodeIdx && ctx.subnodeIdx != -1) {
        os << " [" << ctx.subnodeIdx << "]";
    }

    if (conf.withOriginalId) {
        os << " ID:" << org->original.id.getUnmasked();
    }

    if (conf.withLineCol && org->loc.has_value()) {
        auto& [line, col] = org->loc.value();
        os << " " << os.cyan() << line << ":" << col << os.end();
    }
}

void fieldInit(CR<QString> name, ColStream& os, Org::TreeReprCtx ctx) {
    indent(os, ctx);
    os << os.green() << name << ":" << os.end();
}

void _subnodes(Org const* org, __args, bool asField = false) {
    if (conf.doSkipSubnodesOf(org)) {
        return;
    }


    if (asField) {
        fieldInit("subnodes", os, ctx);
    }

    int idx = 0;
    for (const auto& sub : org->subnodes) {
        if (!conf.doSkip(sub.get())) {
            os << "\n";
            sub->treeRepr(
                os,
                conf,
                Org::TreeReprCtx{
                    .level = ctx.level + 1, .subnodeIdx = idx});
        }
        ++idx;
    }
}


template <typename T>
void writeField(CR<QString> name, CR<T> field, __args) {
    fieldInit(name, os, ctx);
    os << " " << field;
}


template <typename T>
void writeField(CR<QString> name, CR<Wrap<T>> field, __args) {
    fieldInit(name, os, ctx);
    field->treeRepr(os, conf, {.level = ctx.level + 1});
}

template <typename T>
void writeField(CR<QString> name, CR<Opt<T>> field, __args) {
    if (field.has_value()) {
        writeField(name, field.value(), os, conf, ctx);
    } else {
        fieldInit(name, os, ctx);
        os << " None(" << os.green() << demangle(typeid(T).name())
           << os.end() << ")";
    }
}

template <typename T>
void writeField(CR<QString> name, CR<Vec<T>> field, __args) {
    fieldInit(name, os, ctx);
    if (field.size() == 0) {
        os << " 0 items";
    } else {
        int idx = 0;
        for (const auto& sub : field) {
            os << "\n";
            writeField(
                "[" + to_string(idx) + "]",
                sub,
                os,
                conf,
                {.level = ctx.level + 1});
        }
        ++idx;
    }
}

template <typename T, typename FieldType>
void field(
    T const*    org,
    CR<QString> name,
    FieldType T::*fieldPtr,
    __args) {
    writeField(name, (org->*fieldPtr), os, conf, ctx);
}

#define __field(type, name) field(this, #name, &type::name, os, conf, ctx);

} // namespace

void Org::treeRepr(__args) const {
    init(this, os, conf, ctx);
    _subnodes(this, os, conf, ctx);
}

void Leaf::treeRepr(__args) const {
    init(this, os, conf, ctx);
    os << " " << os.yellow() << escape_literal(text) << os.end();
}

void Subtree::treeRepr(__args) const {
    init(this, os, conf, ctx);
    ++ctx.level;
    os << "\n";
    __field(Subtree, level);
    os << "\n";
    __field(Subtree, todo);
    os << "\n";
    __field(Subtree, completion);
    os << "\n";
    __field(Subtree, tags);
    os << "\n";
    __field(Subtree, title);
    os << "\n";
    __field(Subtree, description);
    os << "\n";
    __field(Subtree, logbook);
    os << "\n";
    _subnodes(this, os, conf, ctx, true);
}
