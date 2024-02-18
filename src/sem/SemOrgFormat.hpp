#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/wrappers/textlayouter.hpp>

namespace sem {
struct Formatter {
    using Res    = layout::BlockId;
    using LytStr = layout::LytStr;

    layout::BlockStore        b;
    layout::SimpleStringStore store;

    Formatter() : store{&b} {}
    Res toString(SemId<Org> id);
    Res newRes(CR<sem::SemId<Org>> id) { return Res::Nil(); }
    Res str(std::string const& str) { return b.text(store.str(str)); }

    static Str format(OrgArg id) {
        Formatter fmt;
        auto      result = fmt.toString(id);
        return fmt.store.toString(result);
    }

    Vec<Res> toSubnodes(sem::SemId<Org> id) {
        Vec<Res> result;
        for (auto const& it : id->subnodes) {
            result.push_back(toString(it));
        }

        return result;
    }

    void add_subnodes(Res result, SemId<Org> id);

#define _case(__Kind) Res toString(sem::SemId<__Kind> id);
    EACH_SEM_ORG_KIND(_case)
#undef _case
};
} // namespace sem
