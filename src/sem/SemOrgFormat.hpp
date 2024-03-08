#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/wrappers/textlayouter.hpp>

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
    Res toString(SemId<Org> id, CR<Context> ctx);
    Res newRes(CR<sem::SemId<Org>> id) { return Res::Nil(); }
    Res str(std::string const& str) { return b.text(store.str(str)); }

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
