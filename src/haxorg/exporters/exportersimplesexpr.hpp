#ifndef EXPORTERSIMPLESEXPR_HPP
#define EXPORTERSIMPLESEXPR_HPP

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/wrappers/hstd_extra/textlayouter.hpp>
#include <concepts>
#include <hstd/stdlib/strutils.hpp>
#include <absl/log/check.h>


struct ExporterSimpleSExpr
    : public Exporter<ExporterSimpleSExpr, layout::BlockId> {
    using Base = Exporter<ExporterSimpleSExpr, layout::BlockId>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    using Res    = layout::BlockId;
    using LytStr = layout::LytStr;

    layout::BlockStore        b;
    layout::SimpleStringStore store;
    ExporterSimpleSExpr() : store{&b} {}
    Res newRes(CR<sem::SemId<sem::Org>> id) { return Res::Nil(); }

    Res string(std::string const& str) { return b.text(store.str(str)); }

    void visit(Res& res, sem::SemId<sem::Org> org);

    template <sem::IsOrg T>
    void visit(Res& res, CR<T> value) {
        visit(res, value.asOrg());
    }

    template <sem::NotOrg T>
    void visit(Res& res, CR<T> value) {
        res = b.line({string(escape_for_write(std::format("{}", value)))});
    }

    template <typename T>
    void visit(Res& res, CVec<T> value) {
        res = b.stack();
        for (const auto& it : value) { b.add_at(res, eval(it)); }
    }


    template <typename T>
    void visit(Res& res, CR<Opt<T>> value) {
        if (value) {
            res = eval(*value);
        } else {
            res = string("nil");
        }
    }

    Res eval(int value) { return string(fmt1(value)); }
    Res eval(CR<Str> value) { return string(escape_for_write(value)); }

    Res eval(CR<std::string> value) {
        return string(escape_for_write(value));
    }


    template <typename T>
    Res eval(CR<T> value) {
        Res tmp = b.stack();
        visit(tmp, value);
        return b.line({string("("), tmp, string(")")});
    }

    template <typename T>
    void visitField(Res& res, char const* name, CVec<T> value) {
        if (!value.empty()) {
            if (b.at(res).isLine()) { b.add_at(res, string(" ")); }
            b.add_at(
                res, b.line({string(name), string(": "), eval(value)}));
        }
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<Opt<T>> value) {
        if (value) { visitField(res, name, *value); }
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<T> value) {
        CHECK(!res.isNil());
        if (b.at(res).isLine()) { b.add_at(res, string(" ")); }
        b.add_at(res, b.line({string(name), string(": "), eval(value)}));
    }

    void visitTime(Res& res, In<sem::Time> time) {
        if (time->isStatic()) {
            res = b.line(
                {string(" "), eval(time->getStatic().time.format())});
        } else {
            res = string("dynamic-time");
        }
    }

    void visitDocument(Res& res, In<sem::Document> value) {
        res = b.stack();
        for (const auto& it : value->subnodes) { b.add_at(res, eval(it)); }
    }
};

extern template class Exporter<ExporterSimpleSExpr, layout::BlockId>;

#endif // EXPORTERSIMPLESEXPR_HPP
