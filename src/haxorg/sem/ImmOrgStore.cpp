#include <hstd/stdlib/reflection_visitor.hpp>
#include "hstd/stdlib/Set.hpp"
#include "hstd/stdlib/algorithms.hpp"
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgHash.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <immer/vector_transient.hpp>
#include <immer/set_transient.hpp>
#include <immer/map_transient.hpp>
#include <immer/flex_vector_transient.hpp>
#include <immer/flex_vector.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/logger.hpp>

using namespace org;
using namespace org::imm;
using namespace hstd;
using namespace hstd::ext;

#define _cat "imm.store"

struct store_error : hstd::CRTP_hexception<store_error> {};

#define _kind(__Kind)                                                     \
    template <>                                                           \
    ImmAstKindStore<org::imm::Imm##__Kind> const*                         \
        ImmAstStore::getStoreImpl() const {                               \
        return &store##__Kind;                                            \
    }
EACH_SEM_ORG_KIND(_kind)
#undef _kind


ImmAstReplace org::imm::setSubnodes(
    ImmAdapter         target,
    ImmVec<ImmId>      subnodes,
    ImmAstEditContext& ctx) {
    LOGIC_ASSERTION_CHECK(
        !target.isNil(), "cannot set subnodes to nil node");
    Opt<ImmAstReplace> result;
    switch_node_value(
        target.id, target.ctx.lock(), [&]<typename N>(N node) {
            node.subnodes = subnodes;
            result = target.ctx.lock()->store->setNode(target, node, ctx);
        });

    return result.value();
}


template <org::imm::IsImmOrgValueType T>
ImmAstReplace ImmAstStore::setNode(
    const ImmAdapter&  target,
    const T&           value,
    ImmAstEditContext& ctx) {
    HSLOG_TRACE(_cat, "Set node value");

    for (auto const& it : allSubnodes<T>(value, ctx.ctx.lock())) {
        it.assertValid();
    }

    ImmId     result_node = getStore<T>()->add(value, ctx);
    ImmUniqId replaced    = target.uniq().update(result_node);

    LOGIC_ASSERTION_CHECK(
        !result_node.isNil(), "added node must not be nil");
    result_node.assertValid();

    auto ft = fmt1(target);
    auto fr = fmt1(replaced);
    auto w  = std::max(ft.size(), fr.size());
    AST_EDIT_MSG(fmt("| Original ID:{:<{}} {}", ft, w, target.value<T>()));
    AST_EDIT_MSG(fmt("| Replaced ID:{:<{}} {}", fr, w, value));

    ctx.updateTracking(target.id, false);
    ctx.updateTracking(result_node, true);

    auto dbg = [&](std::string section) {
        AST_EDIT_MSG(fmt("{}", section));
        auto        __scope = ctx.debug()->scopeLevel();
        auto const& imm     = ctx.ctx.lock()->currentTrack->parents;
        auto const& mut     = ctx.transientTrack.parents;

        UnorderedSet<ImmId> keys;
        for (auto const& [key, value] : imm) { keys.incl(key); }
        for (auto const& [key, value] : mut) { keys.incl(key); }
        for (auto const& key : sorted(keys | rs::to<Vec>())) {
            AST_EDIT_MSG(
                fmt("key {:<24} imm {:<32} mut {:<32}",
                    fmt1(key),
                    imm.find(key) == nullptr ? "" : fmt1(imm.at(key)),
                    mut.find(key) == nullptr ? "" : fmt1(mut.at(key))));
        }
    };

    bool verboseSubnodeSet = false;

    if (verboseSubnodeSet) { dbg("Pre remove"); }
    ctx.transientTrack.removeAllSubnodesOf(target);
    if (verboseSubnodeSet) { dbg("After remove"); }
    ctx.transientTrack.insertAllSubnodesOf(ctx->adapt(replaced));
    if (verboseSubnodeSet) { dbg("After insert remove"); }

    // LOG(INFO) << fmt("{} -> {}", replaced, target.uniq());

    return ImmAstReplace{
        .replaced = replaced,
        .original = target.uniq(),
    };
}

/// \brief Reflection path in the parent node, and the subnode that needs
/// to be assigned to the specified place.
using SubnodeAssignTarget = Pair<org::imm::ImmReflPathBase, ImmId>;
/// \brief Group of subnode values to assign to the given path in the
/// parent node.
using SubnodeVecAssignPair = Pair<
    org::imm::ImmReflPathBase,
    Vec<SubnodeAssignTarget>>;
using SubnodeAssignGroup = hstd::Vec<SubnodeVecAssignPair>;

/// \brief Group a flat list of subnode updates into assignment group so
/// that changes on the same field would be grouped together.
///
/// This is made in order to allow for [[vector_field_assignment]] to work
/// in one go, since inserting subnode one by one might've overrode the
/// indexing or other elements.
SubnodeAssignGroup groupUpdatedSubnodes(
    Vec<SubnodeAssignTarget> const& updatedSubnodes) {
    Vec<SubnodeAssignTarget> sortedUpdatedSubnodes = sorted(
        updatedSubnodes,
        [](const SubnodeAssignTarget& a, const SubnodeAssignTarget& b) {
            return a.first.first().getFieldName().name
                 < b.first.first().getFieldName().name;
        });

    SubnodeAssignGroup grouped //
        = sortedUpdatedSubnodes
        | rv::group_by(
              [](const SubnodeAssignTarget& a,
                 const SubnodeAssignTarget& b) -> bool {
                  return a.first.first().getFieldName().name
                      == b.first.first().getFieldName().name;
              })
        | rv::transform([](auto const& group) -> SubnodeVecAssignPair {
              ReflPath path = group.front().first;
              return std::make_pair(
                  path,
                  group
                      | rs::to<
                          Vec<Pair<org::imm::ImmReflPathBase, ImmId>>>());
          })
        | rs::to<SubnodeAssignGroup>();

    return grouped;
}

/// \brief Const cast hack to allow value mutation -- reflection visitor
/// provides a const reference to the target object, but the origianl
/// [[input_node_for_mut_cast]] is a copy of the original node value, not a
/// reference in the store, so it is safe to mutate.
template <typename Const>
Const& mut_cast(Const const& value) {
    return const_cast<Const&>(value);
};

/// \brief Apply all subnode updates on the current value of the
/// `updateTarget` and set a new node value. Inserts a new node value into
/// the store.
ImmAstReplace setNewSubnodes(
    ImmAdapter                updateTarget,
    SubnodeAssignGroup const& grouped,
    ImmAstEditContext&        ctx) {
    ImmAstReplace act;
    switch_node_value(
        updateTarget.id,
        updateTarget.ctx.lock(),
        [&]<typename K>(K node /* <<input_node_for_mut_cast>> */) {
            for (SubnodeVecAssignPair const& fieldGroup : grouped) {
                auto field = fieldGroup.first.first();
                LOGIC_ASSERTION_CHECK(field.isFieldName(), "");
                auto fail_field =
                    [&](int         line     = __builtin_LINE(),
                        char const* function = __builtin_FUNCTION()) {
                        throw logic_unreachable_error::init(
                            fmt("Field path {} refers to a non-ID field "
                                "and "
                                "cannot assigned",
                                field),
                            line,
                            function);
                    };

                ReflVisitor<K, org::imm::ImmReflPathTag>::visit(
                    node,
                    field,
                    // All field types are explicitly handled in the
                    // overload to avoid unexpected fallbacks if new types
                    // are used in the node fields.
                    overloaded{
                        // assignment to subnodes only works for fields
                        // that contain IDs.
                        // clang-format off
                        [&]<hstd::IsVariant V>(V const&) { fail_field(); },
                        [&]<hstd::IsEnum E>(E const&) { fail_field(); },
                        [&](ImmBox<Opt<int>> const&) { fail_field(); },
                        [&](ImmBox<int> const&) { fail_field(); },
                        [&](ImmBox<Opt<bool>> const&) { fail_field(); },
                        [&](ImmBox<bool> const&) { fail_field(); },
                        [&](bool const&) { fail_field(); },
                        [&](ImmBox<Opt<sem::BlockCodeEvalResult>> const&) { fail_field(); },
                        [&](ImmBox<Opt<sem::AttrGroup>> const&) { fail_field(); },
                        [&](ImmBox<Opt<sem::HashTagText>> const&) { fail_field(); },
                        [&](ImmBox<Opt<sem::SubtreeCompletion>> const&) { fail_field(); },
                        [&](ImmBox<Opt<UserTime>> const&) { fail_field(); },
                        [&](ImmBox<sem::BlockCodeEvalResult> const&) { fail_field(); },
                        [&](ImmBox<sem::Tblfm> const&) { fail_field(); },
                        [&](ImmBox<sem::Tblfm::Assign::Flag> const&) { fail_field(); },
                        [&](ImmBox<Opt<Str>> const&) { fail_field(); },
                        [&](org::parse::LineCol const&) { fail_field(); },
                        [&](hstd::Opt<org::parse::LineCol> const&) { fail_field(); },
                        [&](ImmBox<Str> const&) { fail_field(); },
                        [&](ImmVec<Str> const&) { fail_field(); },
                        [&](ImmVec<org::imm::ImmSymbol::Param> const&) { fail_field(); },
                        [&](ImmVec<sem::BlockCodeSwitch> const&) { fail_field(); },
                        [&](ImmVec<sem::BlockCodeLine> const&) { fail_field(); },
                        [&](ImmVec<sem::NamedProperty> const&) { fail_field(); },
                        [&](sem::LinkTarget const&) { fail_field(); },
                        [&](sem::ColumnView const&) { fail_field(); },
                        [&](ImmBox<Opt<sem::ColumnView>> const&) { fail_field(); },
                        [&](sem::DocumentExportConfig const&) { fail_field(); },
                        [&](sem::AttrValue const&) { fail_field(); },
                        [&](sem::SubtreeLogHead const&) { fail_field(); },
                        [&](sem::OrgCodeEvalOutput const&) { fail_field(); },
                        // clang-format on
                        [&]<typename FK>(
                            ImmBox<hstd::Opt<org::imm::ImmIdT<FK>>> const&
                                f) {
                            LOGIC_ASSERTION_CHECK(
                                fieldGroup.second.size() == 1,
                                "Assignment to single field cannot have "
                                "multiple values");
                            mut_cast(f) = fieldGroup.second.at(0).second;
                        },
                        [&]<typename FK>(org::imm::ImmIdT<FK> const& f) {
                            LOGIC_ASSERTION_CHECK(
                                fieldGroup.second.size() == 1,
                                "Assignment to single field cannot have "
                                "multiple values");
                            mut_cast(f) = fieldGroup.second.at(0).second;
                        },
                        [&]<typename FK>(ImmVec<ImmIdT<FK>> const& f) {
                            // <<vector_field_assignment>> overwrite the
                            // node fields with a new value.
                            hstd::Vec<ImmIdT<FK>> convKinds;
                            for (auto const& it : fieldGroup.second) {
                                convKinds.push_back(it.second.as<FK>());
                            }
                            mut_cast(f) = ImmVec<ImmIdT<FK>>{
                                convKinds.begin(), convKinds.end()};
                        },
                        [&](ImmVec<ImmId> const& f) {
                            hstd::Vec<ImmId> convKinds;
                            for (auto const& it : fieldGroup.second) {
                                convKinds.push_back(it.second);
                            }
                            mut_cast(f) = ImmVec<ImmId>{
                                convKinds.begin(),
                                convKinds.end(),
                            };
                        },
                        [&]<typename FK>(
                            ImmMap<Str, org::imm::ImmIdT<FK>> const& f) {
                            auto transient = f.transient();
                            for (auto const& key : fieldGroup.second) {
                                transient.set(
                                    key.first.at(1).getAnyKey().get<Str>(),
                                    key.second.as<FK>());
                            }
                            mut_cast(f) = transient.persistent();
                        },
                    });
            }

            act = updateTarget.ctx.lock()->store->setNode(
                updateTarget, node, ctx);
        });
    return act;
}

ImmAdapter getUpdateTarget(
    ImmAdapter const&         node,
    ImmAstReplaceGroup const& replace,
    ImmAstEditContext&        ctx) {
    Opt<ImmUniqId> edit = replace.map.get(node.uniq());
    AST_EDIT_MSG(fmt("Node {} direct edit:{}", node.id, edit), "aux");

    // If there were no modifications to the original node, use its
    // direct subnodes. Otherwise, take a newer version of the node
    // and map its subnodes instead.
    ImmAdapter updateTarget = edit ? ImmAdapter{*edit, ctx.ctx} : node;
    return updateTarget;
}

UnorderedSet<ImmUniqId> getEditParents(
    ImmAstReplaceGroup const& replace,
    ImmAstEditContext&        ctx) {
    UnorderedSet<ImmUniqId> editParents;

    for (auto const& act : replace.allReplacements()) {
        AST_EDIT_MSG(fmt("Parent chain for", act.original));
        for (auto const& parent :
             ctx->adapt(act.original.value()).getParentChain(false)) {
            AST_EDIT_MSG(fmt("> {}", parent.uniq()));
            editParents.incl(parent.uniq());
        }
    }

    AST_EDIT_MSG("Edit replaces");
    if (AST_EDIT_TRACE()) {
        auto __scope = ctx.debug()->scopeLevel();
        for (auto const& key : replace.allReplacements()) {
            AST_EDIT_MSG(fmt("[{}] -> {}", key.original, key.replaced));
        }
    }

    AST_EDIT_MSG("Node replace map");
    if (AST_EDIT_TRACE()) {
        auto __scope = ctx.debug()->scopeLevel();
        for (auto const& key : sorted(replace.nodeReplaceMap.keys())) {
            AST_EDIT_MSG(
                fmt("[{}] -> {}", key, replace.nodeReplaceMap.at(key)));
        }
    }

    AST_EDIT_MSG("Edit parents");
    if (AST_EDIT_TRACE()) {
        auto __scope = ctx.debug()->scopeLevel();
        for (auto const& key : sorted(editParents | rs::to<Vec>())) {
            AST_EDIT_MSG(fmt("[{}]", key));
        }
    }

    return editParents;
}


ImmId recurseUpdateSubnodes(
    ImmAdapter                    node,
    const ImmAstReplaceGroup&     replace,
    ImmAstEditContext&            ctx,
    UnorderedSet<ImmUniqId> const editParents,
    ImmAstReplaceEpoch&           result);

Pair<Vec<SubnodeAssignTarget>, Vec<ImmId>> getUpdatedSubnodes(
    ImmAdapter const&              updateTarget,
    ImmAstReplaceGroup const&      replace,
    ImmAstEditContext&             ctx,
    UnorderedSet<ImmUniqId> const& editParents,
    ImmAstReplaceEpoch&            result) {
    auto                     flatTargetPath = updateTarget.flatPath();
    Vec<SubnodeAssignTarget> updatedSubnodes;
    Vec<ImmId>               flatUpdatedSubnodes;
    for (auto const& sub :
         updateTarget.getAllSubnodes(updateTarget.path)) {
        auto relativePath = sub.flatPath().dropPrefix(flatTargetPath);
        LOGIC_ASSERTION_CHECK(
            relativePath.first().isFieldName(),
            "relative path for subnode update must target a field "
            "of the node");
        ImmId updated = recurseUpdateSubnodes(
            sub, replace, ctx, editParents, result);
        flatUpdatedSubnodes.push_back(updated);
        updatedSubnodes.push_back({relativePath, updated});
    }

    return {updatedSubnodes, flatUpdatedSubnodes};
}

ImmId recurseUpdateSubnodes(
    ImmAdapter                    node,
    ImmAstReplaceGroup const&     replace,
    ImmAstEditContext&            ctx,
    const UnorderedSet<ImmUniqId> editParents,
    ImmAstReplaceEpoch&           result) {
    __perf_trace("imm", "recurseUpdateSubnodes");
    auto __scope = ctx.debug()->scopeLevel();
    if (editParents.contains(node.uniq())) {
        // The node is a parent subnode for some edit.
        auto updateTarget = getUpdateTarget(node, replace, ctx);
        auto [updatedSubnodes, flatUpdatedSubnodes] = getUpdatedSubnodes(
            updateTarget, replace, ctx, editParents, result);

        // List of subnodes can be updated together with the original
        // edits. In this case there is no need to insert the same list
        // of subnodes.
        auto targetSubnodes //
            = own_view(updateTarget.getAllSubnodes(std::nullopt))
            | rv::transform([](org::imm::ImmAdapter const& it) -> ImmId {
                  return it.id;
              })
            | rs::to<Vec>();
        if (flatUpdatedSubnodes == targetSubnodes) {
            AST_EDIT_MSG(
                fmt("Updated subnodes for {} are the same as target {}",
                    node,
                    updateTarget));

            result.replaced.set(ImmAstReplace{
                .original = node.uniq(),
                .replaced = updateTarget.uniq(),
            });

            return updateTarget.id;
        } else {
            AST_EDIT_MSG(
                fmt("Updated subnodes changed: updated:{} != "
                    "target({}):{}",
                    updatedSubnodes,
                    updateTarget,
                    updateTarget->subnodes),
                "aux");

            auto grouped = groupUpdatedSubnodes(updatedSubnodes);
            auto act     = setNewSubnodes(updateTarget, grouped, ctx);
            result.replaced.set(act);
            return act.replaced.id;
        }
    } else {
        // The node is not a parent for any other replacement. If it
        // was updated, return a new version, otherwise return the same
        // node.
        if (auto edit = replace.map.get(node.uniq()); edit) {
            AST_EDIT_MSG(fmt("Replace {} -> {}", node.uniq(), *edit));
            result.replaced.incl({node.uniq(), *edit});
            return edit->id;
        } else {
            AST_EDIT_MSG(fmt("No changes in {}", node), "aux");
            return node.id;
        }
    }
}

ImmAstReplaceEpoch ImmAstStore::cascadeUpdate(
    ImmAdapter const&         root,
    ImmAstReplaceGroup const& replace,
    ImmAstEditContext&        ctx) {
    __perf_trace("imm", "cascadeUpdate");
    AST_EDIT_MSG("Start cascade update");
    auto                    __scope     = ctx.debug()->scopeLevel();
    UnorderedSet<ImmUniqId> editParents = getEditParents(replace, ctx);

    ImmAstReplaceEpoch result;
    AST_EDIT_MSG(fmt("Main root {}", root));
    result.root = recurseUpdateSubnodes(
        root, replace, ctx, editParents, result);
    AST_EDIT_MSG(fmt("Replace {}", result.replaced));
    return result;
}


ImmId ImmAstStore::add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx) {
    __perf_trace("imm", "ImmAstStore::Add", "kind", fmt1(data->getKind()));
    org::imm::ImmId result = org::imm::ImmId::Nil();
    switch_node_kind(
        org::imm::ImmId{data->getKind(), 0},
        [&]<typename K>(org::imm::ImmIdT<K> id) {
            result = getStore<K>()->add(data, ctx);
        });
    auto adapter = ctx->adapt(ImmUniqId{result});
    ctx.transientTrack.removeAllSubnodesOf(adapter);
    ctx.transientTrack.insertAllSubnodesOf(adapter);
    ctx.updateTracking(result, true);
    return result;
}

sem::SemId<sem::Org> ImmAstStore::get(ImmId id, const ImmAstContext& ctx) {
    sem::SemId<sem::Org> result;
    switch_node_kind(id, [&]<typename K>(org::imm::ImmIdT<K> id) {
        result = getStore<K>()->get(id, ctx);
    });

    return result;
}

const ImmOrg* ImmAstContext::at(ImmId id) const {
    id.assertValid();
    ImmOrg const* res = store->at(id);
    CHECK(res->getKind() == id.getKind());
    return res;
}

ImmId ImmAstContext::at(ImmId node, const ImmPathStep& item) const {
    node.assertValid();
    if (item.path.isSingle() && item.path.first().isIndex()) {
        return value<org::imm::ImmOrg>(node).subnodes.at(
            item.path.first().getIndex().index);
    } else {
        Opt<ImmId> result;
        switch_node_value(
            node, mshared_from_this(), [&]<typename T>(T const& value) {
                reflVisitPath<T>(
                    value,
                    item.path,
                    overloaded{
                        [&](ImmId const& id) { result = id; },
                        [&]<typename K>(ImmIdT<K> const& id) {
                            result = id.toId();
                        },
                        [&](auto const& other) {
                            LOGIC_ASSERTION_CHECK(
                                false,
                                "Path {} does not point to a field with "
                                "ID, "
                                "resolved to {}",
                                item,
                                other);
                        },
                    });
            });
        return result.value();
    }
}

ImmId ImmAstContext::at(const ImmPath& item) const {
    auto result = item.root;
    for (auto const& step : item.path) { result = at(result, step); }
    return result;
}

template <org::imm::IsImmOrgValueType T>
void ImmAstKindStore<T>::format(
    ColStream&         os,
    const std::string& linePrefix) const {
    bool       isFirst = true;
    Vec<ImmId> ids;
    for (auto const& it : values.id_map) { ids.push_back(it.second); }

    rs::sort(ids);

    for (auto const& id : ids) {
        if (!isFirst) { os << "\n"; }
        isFirst = false;
        os << fmt(
            "{}[{}]: {}", linePrefix, id.getReadableId(), values.at(id));
    }
}


void ImmAstStore::format(ColStream& os, const std::string& prefix) const {
#define _kind(__Kind)                                                     \
    if (!store##__Kind.empty()) {                                         \
        os << fmt(                                                        \
            "\n{0}[{1:-<16}] {2:016X}\n",                                 \
            prefix,                                                       \
            #__Kind,                                                      \
            u64(OrgSemKind::__Kind));                                     \
        store##__Kind.format(os, prefix + "  ");                          \
    }

    EACH_SEM_ORG_KIND(_kind)
#undef _kind
}

void ImmAstContext::format(ColStream& os, const std::string& prefix)
    const {
    os << fmt("{}ImmAstStore\n", prefix);
    store->format(os, prefix + "  ");
}

ImmAdapter ImmAstContext::adapt(const ImmUniqId& id) const {
    return org::imm::ImmAdapter{id, mweak_from_this()};
}

ImmAdapter ImmAstContext::adaptUnrooted(const ImmId& id) const {
    return org::imm::ImmAdapter{
        org::imm::ImmUniqId{id, {}}, mweak_from_this()};
}


ImmAstVersion ImmAstContext::getEditVersion(
    const org::imm::ImmAdapter&                                      root,
    Func<ImmAstReplaceGroup(ImmAstContext::Ptr, ImmAstEditContext&)> cb) {
    auto ctx     = getEditContext();
    auto replace = cb(shared_from_this(), ctx);
    return finishEdit(ctx, ctx.store().cascadeUpdate(root, replace, ctx));
}

ImmAstContext::Ptr ImmAstContext::finishEdit(ImmAstEditContext& ctx) {
    return SharedPtrApi::shared(
        store,
        std::make_shared<ImmAstTrackingMap>(
            ctx.transientTrack.persistent()),
        debug);
}


ImmAstVersion ImmAstContext::finishEdit(
    ImmAstEditContext&        ctx,
    const ImmAstReplaceEpoch& epoch) {
    auto newContext = finishEdit(ctx);
    return ImmAstVersion{.context = newContext, .epoch = epoch};
}

ImmId ImmAstContext::add(
    sem::SemId<sem::Org> data,
    ImmAstEditContext&   ctx) {
    return store->add(data, ctx);
}

ImmAstVersion ImmAstContext::addRoot(sem::SemId<sem::Org> data) {
    __perf_trace("imm", "addRoot");
    auto edit = getEditContext();
    auto root = add(data, edit);
    return ImmAstVersion{
        .epoch   = ImmAstReplaceEpoch{.root = root},
        .context = edit.finish(),
    };
}

ImmAstVersion ImmAstContext::init(sem::SemId<sem::Org> root) {
    return addRoot(root);
}


struct AddContext {
    ImmAstContext* store;
};

template <>
struct SerdeDefaultProvider<sem::SubtreeLogHead::Priority> {
    static sem::SubtreeLogHead::Priority get() {
        return sem::SubtreeLogHead::Priority{};
    }
};

using SemId_t = sem::SemId<sem::Org>;
using ImmId_t = org::imm::ImmId;


template <typename Sem, typename Imm>
struct ImmSemSerde {};


template <>
struct ImmSemSerde<SemId_t, ImmId_t> {
    static ImmId_t to_immer(SemId_t const& id, ImmAstEditContext& ctx) {
        return ctx.ctx.lock()->store->add(id, ctx);
    }

    static SemId_t from_immer(
        ImmId_t const&       id,
        ImmAstContext const& ctx) {
        return ctx.store->get(id, ctx);
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<sem::SemId<SemType>, org::imm::ImmIdT<ImmType>> {
    static org::imm::ImmIdT<ImmType> to_immer(
        sem::SemId<SemType> const& id,
        ImmAstEditContext&         ctx) {
        return ctx.ctx.lock()
            ->store->add(id.asOrg(), ctx)
            .template as<ImmType>();
    }

    static sem::SemId<SemType> from_immer(
        org::imm::ImmIdT<ImmType> const& id,
        ImmAstContext const&             ctx) {
        return ctx.store->get(id, ctx).template as<SemType>();
    }
};


template <IsEnum SemType, IsEnum ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, ImmAstEditContext& ctx) {
        return static_cast<ImmType>(value);
    }

    static SemType from_immer(
        ImmType const&       value,
        ImmAstContext const& ctx) {
        return static_cast<SemType>(value);
    }
};


template <IsVariant SemType, IsVariant ImmType>
struct ImmSemSerde<SemType, ImmType> {
    static ImmType to_immer(SemType const& value, ImmAstEditContext& ctx) {
        ImmType result = variant_from_index<ImmType>(value.index());
        std::visit(
            [&](auto& out) {
                using ImmVariantItem = std::remove_cvref_t<decltype(out)>;
                // get the incoming variant type the `value.index()`
                using SemVariantItem = std::variant_alternative_t<
                    boost::mp11::mp_find<ImmType, ImmVariantItem>::value,
                    SemType>;

                out = ImmSemSerde<SemVariantItem, ImmVariantItem>::
                    to_immer(std::get<SemVariantItem>(value), ctx);
            },
            result);
        return result;
    }

    static SemType from_immer(
        ImmType const&       value,
        ImmAstContext const& ctx) {
        SemType result = variant_from_index<SemType>(value.index());
        std::visit(
            [&](auto& out) {
                using SemVariantItem = std::remove_cvref_t<decltype(out)>;
                using ImmVariantItem = std::variant_alternative_t<
                    boost::mp11::mp_find<SemType, SemVariantItem>::value,
                    ImmType>;

                out = ImmSemSerde<SemVariantItem, ImmVariantItem>::
                    from_immer(std::get<ImmVariantItem>(value), ctx);
            },
            result);
        return result;
    }
};

template <
    typename SemKey,
    typename SemValue,
    typename ImmKey,
    typename ImmValue>
struct ImmSemSerde<
    UnorderedMap<SemKey, SemValue>,
    ImmMap<ImmKey, ImmValue>> {
    static ImmMap<ImmKey, ImmValue> to_immer(
        UnorderedMap<SemKey, SemValue> const& value,
        ImmAstEditContext&                    ctx) {
        ImmMap<ImmKey, ImmValue> result;
        auto                     tmp = result.transient();
        for (auto const& [key, value] : value) {
            tmp.insert({
                ImmSemSerde<SemKey, ImmKey>::to_immer(key, ctx),
                ImmSemSerde<SemValue, ImmValue>::to_immer(value, ctx),
            });
        }
        return tmp.persistent();
    }

    static UnorderedMap<SemKey, SemValue> from_immer(
        ImmMap<ImmKey, ImmValue> const& value,
        ImmAstContext const&            ctx) {
        UnorderedMap<SemKey, SemValue> result;
        for (auto const& [key, value] : value) {
            result.insert({
                ImmSemSerde<SemKey, ImmKey>::from_immer(key, ctx),
                ImmSemSerde<SemValue, ImmValue>::from_immer(value, ctx),
            });
        }
        return result;
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<Opt<SemType>, Opt<ImmType>> {
    static Opt<ImmType> to_immer(
        Opt<SemType> const& value,
        ImmAstEditContext&  ctx) {
        Opt<ImmType> base{};
        if (value) {
            base = ImmSemSerde<SemType, ImmType>::to_immer(
                value.value(), ctx);
        }
        return base;
    }

    static Opt<SemType> from_immer(
        Opt<ImmType> const&  value,
        ImmAstContext const& ctx) {
        Opt<SemType> base{};
        if (value) {
            base = ImmSemSerde<SemType, ImmType>::from_immer(
                value.value(), ctx);
        }
        return base;
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<Vec<SemType>, ImmVec<ImmType>> {
    static ImmVec<ImmType> to_immer(
        Vec<SemType> const& value,
        ImmAstEditContext&  ctx) {
        if (value.empty()) {
            return ImmVec<ImmType>{};
        } else {
            Vec<ImmType> tmp;
            tmp.reserve(value.size());
            for (auto const& sub : value) {
                tmp.push_back(
                    ImmSemSerde<SemType, ImmType>::to_immer(sub, ctx));
            }
            return ImmVec<ImmType>{tmp.begin(), tmp.end()};
        }
    }

    static Vec<SemType> from_immer(
        ImmVec<ImmType> const& value,
        ImmAstContext const&   ctx) {
        Vec<SemType> tmp{};
        for (auto const& sub : value) {
            tmp.push_back(
                ImmSemSerde<SemType, ImmType>::from_immer(sub, ctx));
        }
        return tmp;
    }
};

#define __same_type(__T)                                                  \
    template <>                                                           \
    struct ImmSemSerde<__T, __T> {                                        \
        static __T to_immer(__T const& value, ImmAstEditContext& ctx) {   \
            return value;                                                 \
        }                                                                 \
                                                                          \
        static __T from_immer(                                            \
            __T const&           value,                                   \
            ImmAstContext const& ctx) {                                   \
            return value;                                                 \
        }                                                                 \
    };

__same_type(int);
__same_type(Str);
__same_type(float);
__same_type(bool);
__same_type(std::string);
__same_type(UserTime);
__same_type(sem::NamedProperty);
__same_type(sem::DocumentExportConfig);
__same_type(sem::BlockCodeSwitch);
__same_type(sem::BlockCodeEvalResult);
__same_type(sem::BlockCodeLine);
__same_type(sem::Tblfm);
__same_type(sem::LinkTarget);
__same_type(sem::ColumnView);
__same_type(sem::AttrGroup);
__same_type(sem::AttrList);
__same_type(sem::AttrValue);
__same_type(sem::SubtreeCompletion);
__same_type(sem::HashTagText);
__same_type(sem::SubtreeLogHead);
__same_type(sem::SubtreePath);
__same_type(org::parse::LineCol);
__same_type(org::sem::OrgCodeEvalOutput);


template <typename SemType, typename ImmType>
struct ImmSemSerde<SemType, ImmBox<ImmType>> {
    static ImmBox<ImmType> to_immer(
        SemType const&     value,
        ImmAstEditContext& ctx) {
        return ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
    }

    static SemType from_immer(
        ImmBox<ImmType> const& value,
        ImmAstContext const&   ctx) {
        return ImmSemSerde<SemType, ImmType>::from_immer(value.get(), ctx);
    }
};


template <typename SemType, typename ImmType>
void assign_immer_field(
    ImmType&           field,
    SemType const&     value,
    ImmAstEditContext& ctx) {
    field = ImmSemSerde<SemType, ImmType>::to_immer(value, ctx);
}

template <typename SemType, typename ImmType>
void assign_sem_field(
    SemType&             field,
    ImmType const&       value,
    ImmAstContext const& ctx) {
    field = ImmSemSerde<SemType, ImmType>::from_immer(value, ctx);
}


#include "ImmOrgSerde.tcc"

ImmId imm::immer_from_sem(
    const sem::SemId<sem::Org>& id,
    ImmAstEditContext&          ctx) {
    return ImmSemSerde<SemId_t, ImmId_t>::to_immer(id, ctx);
}


sem::SemId<sem::Org> imm::sem_from_immer(
    const ImmId&         id,
    const ImmAstContext& ctx) {
    return ImmSemSerde<SemId_t, ImmId_t>::from_immer(id, ctx);
}


sem::SemId<sem::Org> ImmAstContext::get(ImmId id) {
    return store->get(id, *this);
}

template <IsImmOrgValueType ImmType>
ImmId_t imm::ImmAstKindStore<ImmType>::add(
    SemId_t            data,
    ImmAstEditContext& ctx) {


    using SemType = imm_to_sem_map<ImmType>::sem_type;
    if (!data->is(SemType::staticKind)) {
        throw store_error::init(fmt(
            "Cannot create store value of kind {} from node of kind {}",
            ImmType::staticKind,
            data->getKind()));
    }


    ImmType value = ImmSemSerde<SemType, ImmType>::to_immer(
        *data.as<SemType>(), ctx);

    CHECK(data->getKind() == ImmType::staticKind);
    return add(value, ctx);
}

template <IsImmOrgValueType T>
ImmId ImmAstKindStore<T>::add(const T& value, ImmAstEditContext& ctx) {
    auto  mask   = ImmId::combineMask(T::staticKind);
    ImmId result = values.add(value, mask);
    HSLOG_TRACE(_cat, fmt("Insert value to kind store, {}", value));
    HSLOG_TRACE(_cat, fmt("Result ID {}", result));

    CHECK(result.getKind() == value.getKind())
        << fmt(R"(
result.getValue(): {:064b}
result.getKind():  {:064b}
data->getKind():   {:064b}
mask:              {:064b}
)",
               result.getValue(),
               u64(result.getKind()),
               u64(value.getKind()),
               mask);

    return result;
}


template <IsImmOrgValueType T>
sem::SemId<sem::Org> ImmAstKindStore<T>::get(
    ImmId                id,
    const ImmAstContext& ctx) {
    if (id.isNil()) {
        return sem::SemId<sem::Org>::Nil();
    } else {
        using SemType = imm_to_sem_map<T>::sem_type;
        auto result   = sem::SemId<SemType>::New();
        *result.value = ImmSemSerde<SemType, T>::from_immer(
            ctx.value<T>(id), ctx);

        return result.asOrg();
    }
}


#define forward_declare(__Kind)                                           \
    template class org::imm::ImmAstKindStore<org::imm::Imm##__Kind>;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
