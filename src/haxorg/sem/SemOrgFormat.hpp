#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <hstd/ext/textlayouter.hpp>

namespace org::algo {
struct Formatter {
    using Res    = hstd::layout::BlockId;
    using LytStr = hstd::layout::LytStr;

    hstd::layout::BlockStore        b;
    hstd::layout::SimpleStringStore store;

    struct Context {
        bool isInline = false;
    };

    Formatter() : store{&b} {}
    Res toString(org::sem::SemId<org::sem::Org> id, Context const& ctx);
    Res newRes(org::sem::SemId<org::sem::Org> const& id) {
        return Res::Nil();
    }
    Res  str(std::string const& str) { return b.text(store.str(str)); }
    void add(Res id, Res other);

    Res toString(sem::AttrValue const& id, Context const& ctx);
    Res toString(sem::TodoKeyword const& id, Context const& ctx);
    Res toString(sem::LispCode const& id, Context const& ctx);
    Res toString(hstd::UserTime const& id, Context const& ctx) {
        return str(
            "["_ss
            + hstd::Str{id.format(hstd::UserTime::Format::OrgFormat)}
            + "]"_ss);
    }
    Res toString(sem::SubtreeCompletion const& id, Context const& ctx);
    Res toString(sem::AttrGroup const& args, Context const& ctx);
    Res toString(sem::HashTagText const& args, Context const& ctx);
    Res toString(sem::LinkTarget const& args, Context const& ctx);
    Res toString(sem::AttrList const& args, Context const& ctx);

    Res toString(
        hstd::Opt<sem::AttrGroup> const& args,
        Context const&                   ctx) {
        if (args) {
            return b.line({str(" "), toString(args.value(), ctx)});
        } else {
            return str("");
        }
    }

    Res stackAttached(
        Res                        prev,
        org::sem::SemId<sem::Stmt> stmt,
        Context const&             ctx);

    static hstd::Str format(org::sem::OrgArg id) {
        return format(id, Context{});
    }

    static hstd::Str format(org::sem::OrgArg id, Context const& ctx) {
        Formatter fmt;
        auto      result = fmt.toString(id, ctx);
        return fmt.store.toString(result);
    }

    hstd::Vec<Res> toSubnodes(
        sem::SemId<org::sem::Org> id,
        Context const&            ctx) {
        hstd::Vec<Res> result;
        for (auto const& it : id->subnodes) {
            result.push_back(toString(it, ctx));
        }

        return result;
    }

    void add_subnodes(
        Res                            result,
        org::sem::SemId<org::sem::Org> id,
        Context const&                 ctx);

#define _case(__Kind)                                                     \
    Res toString(org::sem::SemId<org::sem::__Kind> id, Context const& ctx);
    EACH_SEM_ORG_KIND(_case)
#undef _case
};
} // namespace org::algo
