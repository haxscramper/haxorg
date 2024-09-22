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

using namespace org;

struct store_error : CRTP_hexception<store_error> {};

#define _kind(__Kind)                                                     \
    template <>                                                           \
    ImmAstKindStore<Imm##__Kind> const* ImmAstStore::getStoreImpl()       \
        const {                                                           \
        return &store##__Kind;                                            \
    }
EACH_SEM_ORG_KIND(_kind)
#undef _kind


ImmAstReplace org::setSubnodes(
    ImmAdapter         target,
    ImmVec<ImmId>      subnodes,
    ImmAstEditContext& ctx) {
    LOGIC_ASSERTION_CHECK(
        !target.isNil(), "cannot set subnodes to nil node");
    Opt<ImmAstReplace> result;
    switch_node_value(target.id, *target.ctx, [&]<typename N>(N node) {
        node.subnodes = subnodes;
        result        = target.ctx->store->setNode(target, node, ctx);
    });

    return result.value();
}


template <org::IsImmOrgValueType T>
ImmAstReplace ImmAstStore::setNode(
    const ImmAdapter&  target,
    const T&           value,
    ImmAstEditContext& ctx) {

    auto visit_node = overloaded{
        [&](org::ImmSubtree const& subtree, ImmId node, bool add) {
            if (auto id = subtree.treeId.get(); id) {
                if (add) {
                    ctx.track.subtrees.set(*id, node);
                } else {
                    ctx.track.subtrees.erase(*id);
                }
            }
        },
        [&](org::ImmAnnotatedParagraph const& par, ImmId node, bool add) {
            if (par.getAnnotationKind()
                == org::ImmAnnotatedParagraph::AnnotationKind::Footnote) {
                auto id = par.getFootnote().name.get();
                if (add) {
                    ctx.track.footnotes.set(id, node);
                } else {
                    ctx.track.footnotes.erase(id);
                }
            }
        },
        [&](auto const& nodeValue, ImmId node, bool add) {},

    };

    for (auto const& it : allSubnodes<T>(value, *ctx.ctx)) {
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

    visit_node(target.value<T>(), target.id, false);
    visit_node(value, result_node, true);

    return ImmAstReplace{
        .replaced = replaced,
        .original = target.uniq(),
    };
}

Vec<Pair<ReflPath, Vec<ImmId>>> groupUpdatedSubnodes(
    Vec<Pair<ReflPath, ImmId>> const& updatedSubnodes) {
    Vec<Pair<ReflPath, ImmId>> sortedUpdatedSubnodes = sorted(
        updatedSubnodes,
        [](const Pair<ReflPath, ImmId>& a,
           const Pair<ReflPath, ImmId>& b) {
            return a.first.first().getFieldName().name
                 < b.first.first().getFieldName().name;
        });

    Vec<Pair<ReflPath, Vec<ImmId>>> grouped //
        = sortedUpdatedSubnodes
        | rv::group_by(
              [](const Pair<ReflPath, ImmId>& a,
                 const Pair<ReflPath, ImmId>& b) -> bool {
                  return a.first.first().getFieldName().name
                      == b.first.first().getFieldName().name;
              })
        | rv::transform([](auto group) -> Pair<ReflPath, Vec<ImmId>> {
              ReflPath   path = group.front().first;
              Vec<ImmId> ids //
                  = group
                  | rv::transform(
                        [](const Pair<ReflPath, ImmId>& p) -> ImmId {
                            return p.second;
                        })
                  | rs::to<Vec<ImmId>>;
              return std::make_pair(path, ids);
          })
        | rs::to<Vec<Pair<ReflPath, Vec<ImmId>>>>();

    return grouped;
}

ImmAstReplace updateFieldMutations(
    ImmAdapter                             updateTarget,
    Vec<Pair<ReflPath, Vec<ImmId>>> const& grouped,
    ImmAstEditContext&                     ctx) {
    ImmAstReplace act;
    switch_node_value(
        updateTarget.id, *updateTarget.ctx, [&]<typename K>(K node) {
            for (Pair<ReflPath, Vec<ImmId>> const& fieldGroup : grouped) {
                auto field = fieldGroup.first.first();
                LOGIC_ASSERTION_CHECK(field.isFieldName(), "");
                ReflVisitor<K>::visit(
                    node,
                    field,
                    overloaded{
                        [&]<typename FieldKind>(
                            immer::box<std::optional<
                                org::ImmIdT<FieldKind>>> const& field) {
                            LOGIC_ASSERTION_CHECK(
                                fieldGroup.second.size() == 1, "");
                            const_cast<immer::box<
                                std::optional<org::ImmIdT<FieldKind>>>&>(
                                field)
                                = fieldGroup.second.at(0);
                        },
                        [&](Vec<ImmId> const& targetIdField) {
                            const_cast<Vec<ImmId>&>(targetIdField) = fieldGroup
                                                                         .second;
                        },
                    });
            }

            act = updateTarget.ctx->store->setNode(
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


ImmAstReplaceEpoch ImmAstStore::cascadeUpdate(
    ImmAdapter const&         root,
    ImmAstReplaceGroup const& replace,
    ImmAstEditContext&        ctx) {
    AST_EDIT_MSG("Start cascade update");
    auto __scope = ctx.debug.scopeLevel();

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
    {
        auto __scope = ctx.debug.scopeLevel();
        for (auto const& key : replace.allReplacements()) {
            AST_EDIT_MSG(fmt("[{}] -> {}", key.original, key.replaced));
        }

        for (auto const& key : sorted(replace.nodeReplaceMap.keys())) {
            AST_EDIT_MSG(
                fmt("[{}] -> {}", key, replace.nodeReplaceMap.at(key)));
        }
    }

    AST_EDIT_MSG("Edit parents");
    {
        auto __scope = ctx.debug.scopeLevel();
        for (auto const& key : sorted(editParents | rs::to<Vec>())) {
            AST_EDIT_MSG(fmt("[{}]", key));
        }
    }

    Func<ImmId(ImmAdapter node)> aux;
    ImmAstReplaceEpoch           result;

    aux = [&](ImmAdapter node) -> ImmId {
        auto __scope = ctx.debug.scopeLevel();
        if (editParents.contains(node.uniq())) {
            // The node is a parent subnode for some edit.
            auto updateTarget = getUpdateTarget(node, replace, ctx);

            auto flatTargetPath = updateTarget.flatPath();
            Vec<Pair<ReflPath, ImmId>> updatedSubnodes;
            Vec<ImmId>                 flatUpdatedSubnodes;
            for (auto const& sub :
                 updateTarget.getAllSubnodes(updateTarget.path)) {
                auto relativePath = sub.flatPath().dropPrefix(
                    flatTargetPath);
                LOGIC_ASSERTION_CHECK(
                    relativePath.first().isFieldName(),
                    "relative path for subnode update must target a field "
                    "of the node");
                ImmId updated = aux(sub);
                flatUpdatedSubnodes.push_back(updated);
                updatedSubnodes.push_back({relativePath, updated});
            }


            // List of subnodes can be updated together with the original
            // edits. In this case there is no need to insert the same list
            // of subnodes.
            auto targetSubnodes //
                = own_view(updateTarget.getAllSubnodes(std::nullopt))
                | rv::transform([](org::ImmAdapter const& it) -> ImmId {
                      return it.id;
                  })
                | rs::to<Vec>();
            if (flatUpdatedSubnodes != targetSubnodes) {
                AST_EDIT_MSG(
                    fmt("Updated subnodes changed: updated:{} != "
                        "target({}):{}",
                        updatedSubnodes,
                        updateTarget,
                        updateTarget->subnodes),
                    "aux");

                auto grouped = groupUpdatedSubnodes(updatedSubnodes);
                auto act     = updateFieldMutations(
                    updateTarget, grouped, ctx);
                result.replaced.set(act);
                return act.replaced.id;
            } else {
                return updateTarget.id;
            }
        } else {
            // The node is not a parent for any other replacement. If it
            // was updated, return a new version, otherwise return the same
            // node.
            if (auto edit = replace.map.get(node.uniq()); edit) {
                result.replaced.incl({node.uniq(), *edit});
                return edit->id;
            } else {
                AST_EDIT_MSG(fmt("No changes in {}", node), "aux");
                return node.id;
            }
        }
    };

    AST_EDIT_MSG(fmt("Main root {}", root));
    result.root = aux(root);
    return result;
}


ImmId ImmAstStore::add(sem::SemId<sem::Org> data, ImmAstEditContext& ctx) {
    org::ImmId result = org::ImmId::Nil();
    switch_node_kind(
        org::ImmId{data->getKind(), 0},
        [&]<typename K>(org::ImmIdT<K> id) {
            result = getStore<K>()->add(data, ctx);
        });
    return result;
}

sem::SemId<sem::Org> ImmAstStore::get(ImmId id, const ImmAstContext& ctx) {
    sem::SemId<sem::Org> result;
    switch_node_kind(id, [&]<typename K>(org::ImmIdT<K> id) {
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
        return value<org::ImmOrg>(node).subnodes.at(
            item.path.first().getIndex().index);
    } else {
        Opt<ImmId> result;
        switch_node_value(node, *this, [&]<typename T>(T const& value) {
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

template <org::IsImmOrgValueType T>
void ImmAstKindStore<T>::format(
    ColStream&                        os,
    const UnorderedMap<ImmId, ImmId>& parents,
    const std::string&                linePrefix) const {
    bool       isFirst = true;
    Vec<ImmId> ids;
    for (auto const& it : values.id_map) { ids.push_back(it.second); }

    rs::sort(ids);

    for (auto const& id : ids) {
        if (!isFirst) { os << "\n"; }
        isFirst = false;
        os << fmt(
            "{}[{}] (parent {}): {}",
            linePrefix,
            id.getReadableId(),
            parents.get(id),
            values.at(id));
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
        store##__Kind.format(os, parents, prefix + "  ");                 \
    }

    EACH_SEM_ORG_KIND(_kind)
#undef _kind
}

void ImmAstContext::format(ColStream& os, const std::string& prefix)
    const {
    os << fmt("{}ImmAstStore\n", prefix);
    store->format(os, prefix + "  ");
}

ImmAdapter ImmAstContext::adapt(const ImmUniqId& id) {
    return org::ImmAdapter{id, this};
}


ImmAstVersion ImmAstContext::getEditVersion(
    const org::ImmAdapter&                                           root,
    Func<ImmAstReplaceGroup(ImmAstContext& ast, ImmAstEditContext&)> cb) {
    auto ctx     = getEditContext();
    auto replace = cb(*this, ctx);
    return finishEdit(ctx, ctx.store().cascadeUpdate(root, replace, ctx));
}

ImmAstContext ImmAstContext::finishEdit(ImmAstEditContext& ctx) {
    ImmAstContext result = *this;
    result.parents       = ctx.track.persistent();
    return result;
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

ImmRootAddResult ImmAstContext::addRoot(sem::SemId<sem::Org> data) {
    auto edit = getEditContext();
    auto root = add(data, edit);
    return ImmRootAddResult{.root = root, .context = edit.finish()};
}

ImmAstVersion ImmAstContext::init(sem::SemId<sem::Org> root) {
    auto [store, imm_root] = addRoot(root);
    ImmAstReplace replace{
        .original = std::nullopt,
        .replaced = imm_root,
    };

    ImmAstVersion result{
        .context = store,
        .epoch   = ImmAstReplaceEpoch{.root = imm_root},
    };
    return result;
}


struct AddContext {
    ImmAstContext* store;
};

template <>
struct SerdeDefaultProvider<org::ImmSubtreeLog::Priority> {
    static org::ImmSubtreeLog::Priority get() {
        return org::ImmSubtreeLog::Priority{};
    }
};

template <typename Sem, typename Imm>
struct ImmSemSerde {};

using SemId_t = sem::SemId<sem::Org>;
using ImmId_t = org::ImmId;

template <>
struct ImmSemSerde<SemId_t, ImmId_t> {
    static ImmId_t to_immer(SemId_t const& id, ImmAstEditContext& ctx) {
        return ctx.ctx->store->add(id, ctx);
    }

    static SemId_t from_immer(
        ImmId_t const&       id,
        ImmAstContext const& ctx) {
        return ctx.store->get(id, ctx);
    }
};

template <typename SemType, typename ImmType>
struct ImmSemSerde<sem::SemId<SemType>, org::ImmIdT<ImmType>> {
    static org::ImmIdT<ImmType> to_immer(
        sem::SemId<SemType> const& id,
        ImmAstEditContext&         ctx) {
        return ctx.ctx->store->add(id.asOrg(), ctx).template as<ImmType>();
    }

    static sem::SemId<SemType> from_immer(
        org::ImmIdT<ImmType> const& id,
        ImmAstContext const&        ctx) {
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
        ImmVec<ImmType> base{};
        auto            tmp = base.transient();
        for (auto const& sub : value) {
            tmp.push_back(
                ImmSemSerde<SemType, ImmType>::to_immer(sub, ctx));
        }
        return tmp.persistent();
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
__same_type(sem::CmdArgumentValue);


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

sem::SemId<sem::Org> ImmAstContext::get(ImmId id) {
    return store->get(id, *this);
}

template <org::IsImmOrgValueType ImmType>
ImmId_t org::ImmAstKindStore<ImmType>::add(
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

template <org::IsImmOrgValueType T>
ImmId ImmAstKindStore<T>::add(const T& value, ImmAstEditContext& ctx) {
    auto  mask   = ImmId::combineMask(T::staticKind);
    ImmId result = values.add(value, mask);

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


template <org::IsImmOrgValueType T>
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
    template class org::ImmAstKindStore<org::Imm##__Kind>;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
