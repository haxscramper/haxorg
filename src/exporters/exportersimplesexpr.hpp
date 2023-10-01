#ifndef EXPORTERSIMPLESEXPR_HPP
#define EXPORTERSIMPLESEXPR_HPP

#include <exporters/Exporter.hpp>
#include <hstd/wrappers/textlayouter.hpp>
#include <concepts>
#include <hstd/stdlib/strutils.hpp>


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
    Res newRes(CR<sem::SemId> id) { return Res::Nil(); }

    Res string(QString const& str) { return b.text(store.str(str)); }

    void visit(Res& res, sem::SemId org);


    template <sem::NotOrg T>
    void visit(Res& res, CR<T> value) {
        res = b.line({string(escape_for_write(to_string(value)))});
    }

    template <typename T>
    void visit(Res& res, CVec<T> value) {
        res = b.stack();
        for (const auto& it : value) {
            b.add_at(res, eval(it));
        }
    }


    void visit(Res& res, CR<QDateTime> time) {
        res = string(escape_for_write(time.toString(Qt::ISODate)));
    }

    void visit(Res& res, CR<QDate> time) {
        res = string(escape_for_write(time.toString(Qt::ISODate)));
    }

    void visit(Res& res, CR<QTime> time) {
        res = string(escape_for_write(time.toString(Qt::ISODate)));
    }

    template <typename T>
    void visit(Res& res, CR<Opt<T>> value) {
        if (value) {
            res = eval(*value);
        } else {
            res = string("nil");
        }
    }

    Res eval(int value) { return string(to_string(value)); }
    Res eval(CR<Str> value) { return string(escape_for_write(value)); }

    Res eval(CR<QString> value) { return string(escape_for_write(value)); }


    template <typename T>
    Res eval(CR<T> value) {
        Res tmp = b.stack();
        visit(tmp, value);
        return b.line({string("("), tmp, string(")")});
    }

    template <typename T>
    void visitField(Res& res, char const* name, CVec<T> value) {
        if (!value.empty()) {
            if (b.at(res).isLine()) {
                b.add_at(res, string(" "));
            }
            b.add_at(
                res, b.line({string(name), string(": "), eval(value)}));
        }
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<Opt<T>> value) {
        if (value) {
            visitField(res, name, *value);
        }
    }

    template <typename T>
    void visitField(Res& res, char const* name, CR<T> value) {
        Q_ASSERT(!res.isNil());
        if (b.at(res).isLine()) {
            b.add_at(res, string(" "));
        }
        b.add_at(res, b.line({string(name), string(": "), eval(value)}));
    }

    void visitTime(Res& res, In<sem::Time> time) {
        if (time->isStatic()) {
            res = b.line(
                {string(" "), eval(time->getStatic().time.getDateTime())});
        } else {
            res = string("dynamic-time");
        }
    }

    void visitDocument(Res& res, In<sem::Document> value) {
        res = b.stack();
        for (const auto& it : value->subnodes) {
            b.add_at(res, eval(it));
        }
    }
};

extern template class Exporter<ExporterSimpleSExpr, layout::BlockId>;

#endif // EXPORTERSIMPLESEXPR_HPP
