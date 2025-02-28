#pragma once

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/ext/textlayouter.hpp>
#include <concepts>
#include <hstd/stdlib/strutils.hpp>
#include <absl/log/check.h>

namespace org::algo {

struct ExporterSimpleSExpr
    : public Exporter<ExporterSimpleSExpr, hstd::layout::BlockId> {
    using Base = Exporter<ExporterSimpleSExpr, hstd::layout::BlockId>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    using Res    = hstd::layout::BlockId;
    using LytStr = hstd::layout::LytStr;

    hstd::layout::BlockStore        b;
    hstd::layout::SimpleStringStore store;
    ExporterSimpleSExpr() : store{&b} {}
    Res newRes(sem::SemId<sem::Org> const& id) { return Res::Nil(); }

    Res string(std::string const& str) { return b.text(store.str(str)); }

    void visit(Res& res, sem::SemId<sem::Org> org);

    template <sem::IsOrg T>
    void visit(Res& res, T const& value) {
        visit(res, value.asOrg());
    }

    template <org::sem::NotOrg T>
    void visit(Res& res, T const& value) {
        res = b.line(
            {string(hstd::escape_for_write(std::format("{}", value)))});
    }

    template <typename T>
    void visit(Res& res, hstd::CVec<T> value) {
        res = b.stack();
        for (const auto& it : value) { b.add_at(res, eval(it)); }
    }


    template <typename T>
    void visit(Res& res, hstd::Opt<T> const& value) {
        if (value) {
            res = eval(*value);
        } else {
            res = string("nil");
        }
    }

    Res eval(int value) { return string(hstd::fmt1(value)); }
    Res eval(hstd::Str const& value) {
        return string(escape_for_write(value));
    }

    Res eval(std::string const& value) {
        return string(hstd::escape_for_write(value));
    }


    template <typename T>
    Res eval(T const& value) {
        Res tmp = b.stack();
        visit(tmp, value);
        return b.line({string("("), tmp, string(")")});
    }

    template <typename T>
    void visitField(Res& res, char const* name, hstd::CVec<T> value) {
        if (!value.empty()) {
            if (b.at(res).isLine()) { b.add_at(res, string(" ")); }
            b.add_at(
                res, b.line({string(name), string(": "), eval(value)}));
        }
    }

    template <typename T>
    void visitField(
        Res&                res,
        char const*         name,
        hstd::Opt<T> const& value) {
        if (value) { visitField(res, name, *value); }
    }

    template <typename T>
    void visitField(Res& res, char const* name, T const& value) {
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

extern template class Exporter<ExporterSimpleSExpr, hstd::layout::BlockId>;

} // namespace org::algo
