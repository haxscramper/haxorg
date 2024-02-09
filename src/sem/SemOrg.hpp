#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <functional>


#include <sem/SemOrgBase.hpp>

//#include <sem/SemOrgTypes_old.hpp>
#include <sem/SemOrgTypes.hpp>


#define EACH_ORG_NESTED_TYPE(__IMPL)                                      \
    __IMPL(sem::Code::Switch)                                             \
    __IMPL(sem::Code::Switch::LineStart)                                  \
    __IMPL(sem::Code::Switch::CalloutFormat)                              \
    __IMPL(sem::Code::Switch::RemoveCallout)                              \
    __IMPL(sem::Code::Switch::EmphasizeLine)                              \
    __IMPL(sem::Code::Switch::Dedent)                                     \
    __IMPL(sem::SubtreeLog::Priority)                                     \
    __IMPL(sem::SubtreeLog::Note)                                         \
    __IMPL(sem::SubtreeLog::Refile)                                       \
    __IMPL(sem::SubtreeLog::Clock)                                        \
    __IMPL(sem::SubtreeLog::State)                                        \
    __IMPL(sem::SubtreeLog::Tag)                                          \
    __IMPL(sem::Subtree::Property)                                        \
    __IMPL(sem::Subtree::Property::Created)                               \
    __IMPL(sem::Subtree::Property::Unnumbered)                            \
    __IMPL(sem::Subtree::Property::Blocker)                               \
    __IMPL(sem::Subtree::Property::ExportOptions)                         \
    __IMPL(sem::Subtree::Property::Visibility)                            \
    __IMPL(sem::Subtree::Property::Effort)                                \
    __IMPL(sem::Subtree::Property::Ordered)                               \
    __IMPL(sem::Subtree::Property::ExportLatexClass)                      \
    __IMPL(sem::Subtree::Property::ExportLatexClassOptions)               \
    __IMPL(sem::Subtree::Property::ExportLatexCompiler)                   \
    __IMPL(sem::Subtree::Property::ExportLatexHeader)                     \
    __IMPL(sem::Subtree::Property::Origin)                                \
    __IMPL(sem::Subtree::Property::Trigger)                               \
    __IMPL(sem::Subtree::Property::Nonblocking)                           \
    __IMPL(sem::Time::Static)                                             \
    __IMPL(sem::Time::Dynamic)                                            \
    __IMPL(sem::Symbol::Param)                                            \
    __IMPL(sem::Time::Repeat)                                             \
    __IMPL(sem::Link::Id)                                                 \
    __IMPL(sem::Link::Raw)                                                \
    __IMPL(sem::Link::Person)                                             \
    __IMPL(sem::Link::Footnote)                                           \
    __IMPL(sem::Link::File)                                               \
    __IMPL(sem::Include::Example)                                         \
    __IMPL(sem::Include::Export)                                          \
    __IMPL(sem::Include::OrgDocument)                                     \
    __IMPL(sem::Include::Src)

namespace sem {
template <typename T>
concept NotOrg = !(
    std::derived_from<typename remove_smart_pointer<T>::type, sem::Org>
    || std::derived_from<T, Org>);

/// \brief  Compile-time check whether the element is an org-mode node or
/// an org-mode ID
template <typename T>
concept IsOrg = std::
    derived_from<typename remove_sem_org<T>::type, sem::Org>;

}; // namespace sem

#define __hack_fmt(__kind)                                                \
    template <>                                                           \
    struct std::formatter<__kind> : std::formatter<std::string> {         \
        template <typename FormatContext>                                 \
        FormatContext::iterator format(                                   \
            __kind const&  p,                                             \
            FormatContext& ctx) const {                                   \
            std::formatter<std::string> fmt;                              \
            return fmt.format(enum_serde<__kind>::to_string(p), ctx);     \
        }                                                                 \
    };


__hack_fmt(OrgBigIdentKind);
__hack_fmt(OrgNodeKind);
__hack_fmt(sem::DocumentOptions::BrokenLinks);
__hack_fmt(sem::DocumentOptions::Visibility);
__hack_fmt(sem::Export::Format);
__hack_fmt(sem::Include::Kind);
__hack_fmt(sem::Link::Kind);
__hack_fmt(sem::ListItem::Checkbox);
__hack_fmt(sem::Subtree::Period::Kind);
__hack_fmt(sem::SubtreeLog::Kind);
__hack_fmt(sem::Time::Repeat::Mode);
__hack_fmt(sem::Time::Repeat::Period);

__hack_fmt(sem::Code::Switch::Kind);
__hack_fmt(sem::Time::TimeKind);
__hack_fmt(sem::Subtree::Property::Kind);
__hack_fmt(sem::Code::Exports);
__hack_fmt(sem::Subtree::Property::SetMode);
__hack_fmt(sem::Subtree::Property::InheritanceMode);
__hack_fmt(sem::Subtree::Property::Visibility::Level);
