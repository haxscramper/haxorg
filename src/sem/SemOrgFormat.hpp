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
    Res toString(SemId id);
    Res newRes(CR<sem::SemId> id) { return Res::Nil(); }
    Res str(std::string const& str) { return b.text(store.str(str)); }

    void add_subnodes(Res result, SemId id);

#define _case(__Kind) Res toString(sem::SemIdT<__Kind> id);
    EACH_SEM_ORG_KIND(_case)
#undef _case
};
} // namespace sem
