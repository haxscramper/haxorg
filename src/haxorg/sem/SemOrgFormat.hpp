#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <hstd/wrappers/hstd_extra/textlayouter.hpp>

namespace sem {
struct Formatter {
    using Res    = layout::BlockId;
    using LytStr = layout::LytStr;

    layout::BlockStore        b;
    layout::SimpleStringStore store;

    struct Context {
        bool isInline = false;
    };

    Formatter() : store{&b} {}
    Res  toString(SemId<Org> id, CR<Context> ctx);
    Res  newRes(CR<sem::SemId<Org>> id) { return Res::Nil(); }
    Res  str(std::string const& str) { return b.text(store.str(str)); }
    void add(Res id, Res other);

    Res toString(sem::AttrValue const& id, CR<Context> ctx);
    Res toString(UserTime const& id, CR<Context> ctx) {
        return str(
            "["_ss + Str{id.format(UserTime::Format::OrgFormat)} + "]"_ss);
    }
    Res toString(sem::SubtreeCompletion const& id, CR<Context> ctx);
    Res toString(sem::AttrGroup const& args, CR<Context> ctx);
    Res toString(sem::HashTagText const& args, CR<Context> ctx);
    Res toString(sem::LinkTarget const& args, CR<Context> ctx);
    Res toString(sem::AttrList const& args, CR<Context> ctx) {
        Res res = b.stack();
        for (auto const& it : enumerator(args.items)) {
            if (!it.is_first()) { b.add_at(res, str(" ")); }
            b.add_at(res, toString(it.value(), ctx));
        }
        return res;
    }

    Res toString(Opt<sem::AttrGroup> const& args, CR<Context> ctx) {
        if (args) {
            return b.line({str(" "), toString(args.value(), ctx)});
        } else {
            return str("");
        }
    }

    Res stackAttached(Res prev, SemId<sem::Stmt> stmt, CR<Context> ctx);

    static Str format(OrgArg id) { return format(id, Context{}); }

    static Str format(OrgArg id, CR<Context> ctx) {
        Formatter fmt;
        auto      result = fmt.toString(id, ctx);
        return fmt.store.toString(result);
    }

    Vec<Res> toSubnodes(sem::SemId<Org> id, CR<Context> ctx) {
        Vec<Res> result;
        for (auto const& it : id->subnodes) {
            result.push_back(toString(it, ctx));
        }

        return result;
    }

    void add_subnodes(Res result, SemId<Org> id, CR<Context> ctx);

#define _case(__Kind) Res toString(sem::SemId<__Kind> id, CR<Context> ctx);
    EACH_SEM_ORG_KIND(_case)
#undef _case
};
} // namespace sem
