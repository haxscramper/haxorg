#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <immer/vector_transient.hpp>
#include <immer/map_transient.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <boost/mp11.hpp>
#include <boost/preprocessor.hpp>
#include <haxorg/sem/ImmOrgHash.hpp>

const u64 org::ImmId::NodeIdxMask    = 0x000000FFFFFFFFFF; // >>0*0=0,
const u64 org::ImmId::NodeIdxOffset  = 0;
const u64 org::ImmId::NodeKindMask   = 0x000FFF0000000000; // >>10*4=40
const u64 org::ImmId::NodeKindOffset = 40;
const u64 org::ImmId::StoreIdxMask   = 0xFFF0000000000000; // >>13*4=52
const u64 org::ImmId::StoreIdxOffset = 52;

org::ImmId::IdType org::ImmId::combineMask(
    StoreIdxT  store,
    OrgSemKind kind) {
    auto res = (u64(kind) << NodeKindOffset) & NodeKindMask
             | (u64(store) << StoreIdxOffset) & StoreIdxMask;

    auto t = ImmId{ImmId::FromMaskedIdx(0, res >> ImmIdMaskOffset)};
    CHECK(t.getKind() == kind) << fmt(
        R"(
kind:    {0:016X} {0:064b} {1}
kind<<:  {2:016X} {2:064b}
mask:    {3:016X} {3:064b}
t.kind:  {4:016X} {4:064b}
t.kind<<:{5:016X} {5:064b}
t.value: {6:016X} {6:064b}
res:     {7:016X} {7:064b})",
        u64(kind),
        kind,
        u64(kind) << NodeKindOffset,
        NodeKindMask,
        u64(t.getKind()),
        u64(t.getKind()) << NodeKindOffset,
        t.value,
        res >> ImmIdMaskOffset);


    return res >> ImmIdMaskOffset;
}

org::ImmId::IdType org::ImmId::combineFullValue(
    StoreIdxT  store,
    OrgSemKind kind,
    NodeIdxT   node) {
    return (combineMask(store, kind) << ImmIdMaskOffset)
         | (u64(node) << NodeIdxOffset) & NodeIdxMask;
}

#define _define_static(__Kind)                                            \
    const OrgSemKind org::Imm##__Kind::staticKind = OrgSemKind::__Kind;

EACH_SEM_ORG_KIND(_define_static)
#undef _define_static

#define _eq_method(__QualType, _)                                         \
    bool org::Imm##__QualType::operator==(                                \
        org::Imm##__QualType const& other) const {                        \
        bool result = true;                                               \
        for_each_field_with_bases<org::Imm##__QualType>(                  \
            [&](auto const& field) {                                      \
                if (result) {                                             \
                    result &= this->*field.pointer                        \
                           == other.*field.pointer;                       \
                }                                                         \
            });                                                           \
        return result;                                                    \
    }

EACH_SEM_ORG_RECORD(_eq_method)
#undef _eq_method


using namespace org;


const ImmOrg* ImmAstStore::at(ImmId index) const {
    switch (index.getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        org::Imm##__Kind const* res = store##__Kind.at(index);            \
        logic_assertion_check(                                            \
            res->getKind() == index.getKind(),                            \
            "index kind {} does not match result node kind {}",           \
            index.getKind(),                                              \
            res->getKind());                                              \
        return res;                                                       \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }

    throw logic_unreachable_error::init(
        fmt("Cannot get node for index {}", index));
}

namespace {
void eachSubnodeRecImpl(
    CR<org::SubnodeVisitor> visitor,
    ImmId                   org,
    bool                    originalBase,
    org::ImmAstContext*     ctx);

template <typename T>
struct Visitor {};


#define placeholder_visitor(__Type)                                       \
    template <>                                                           \
    struct Visitor<__Type> {                                              \
        static void visitField(                                           \
            CR<org::SubnodeVisitor> visitor,                              \
            __Type const&           tmp,                                  \
            org::ImmAstContext*     ctx) {}                                   \
    };

placeholder_visitor(Str);
placeholder_visitor(int);
placeholder_visitor(bool);
placeholder_visitor(absl::Time);
placeholder_visitor(UserTime);
placeholder_visitor(std::string);
placeholder_visitor(sem::BigIdent);
placeholder_visitor(org::ImmIdT<sem::BigIdent>);
placeholder_visitor(Vec<sem::SemId<sem::Org>>);

#undef placeholder_visitor


template <IsEnum T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        T const&                tree,
        org::ImmAstContext*     ctx) {}
};

template <typename T>
struct Visitor<ImmIdT<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmIdT<T>               tree,
        org::ImmAstContext*     ctx) {

        if (tree.isNil()) { return; }
        visitor(ImmAdapter{tree.toId(), ctx});

        for_each_field_with_bases<T>([&](auto const& field) {
            Visitor<std::remove_cvref_t<
                decltype(ctx->at(tree)->*field.pointer)>>::
                visitField(visitor, ctx->at(tree)->*field.pointer, ctx);
        });
    }
};

template <DescribedRecord T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        T const&                obj,
        org::ImmAstContext*     ctx) {
        for_each_field_with_bases<T>([&](auto const& field) {
            Visitor<std::remove_cvref_t<decltype(obj.*field.pointer)>>::
                visitField(visitor, obj.*field.pointer, ctx);
        });
    }
};


template <>
struct Visitor<ImmId> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmId                   org,
        org::ImmAstContext*     ctx) {
        switch (ctx->at(org)->getKind()) {


#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        Visitor<org::ImmIdT<org::Imm##__Kind>>::visitField(               \
            visitor, org.as<org::Imm##__Kind>(), ctx);                    \
        break;                                                            \
    }
            EACH_SEM_ORG_KIND(__case)
#undef __case
        }
    }
};


template <sem::IsOrg T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<T>                   node,
        org::ImmAstContext*     ctx) {
        Visitor<ImmId>::visitField(visitor, node.asOrg(), ctx);
    }
};

template <IsVariant T>
struct Visitor<T> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<T>                   node,
        org::ImmAstContext*     ctx) {
        std::visit(
            [&](auto const& it) {
                Visitor<std::remove_cvref_t<decltype(it)>>::visitField(
                    visitor, it, ctx);
            },
            node);
    }
};


template <typename T>
struct Visitor<ImmVec<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmVec<T> const&        value,
        org::ImmAstContext*     ctx) {
        for (const auto& it : value) {
            Visitor<T>::visitField(visitor, it, ctx);
        }
    }
};

template <typename K, typename V>
struct Visitor<ImmMap<K, V>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        ImmMap<K, V> const&     value,
        org::ImmAstContext*     ctx) {
        for (const auto& [key, value] : value) {
            Visitor<V>::visitField(visitor, value, ctx);
        }
    }
};


template <typename T>
struct Visitor<ImmBox<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<ImmBox<T>>           value,
        org::ImmAstContext*     ctx) {
        Visitor<T>::visitField(visitor, value.get(), ctx);
    }
};

template <typename T>
struct Visitor<Opt<T>> {
    static void visitField(
        CR<org::SubnodeVisitor> visitor,
        CR<Opt<T>>              value,
        org::ImmAstContext*     ctx) {
        if (value) { Visitor<T>::visitField(visitor, *value, ctx); }
    }
};

} // namespace


void org::eachSubnodeRec(ImmAdapter id, SubnodeVisitor cb) {
    Visitor<ImmId>::visitField(cb, id.id, id.ctx);
}


#define DEFINE_VISITOR_BASE_STRUCT(                                       \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType)                                                  \
                                                                          \
    template <BOOST_PP_TUPLE_REM() __VisitorTemplateArgs>                 \
    struct __VisitorTypename<BOOST_PP_TUPLE_REM()                         \
                                 __VisitorTypeSpecification> {            \
        static BOOST_PP_TUPLE_REM() __VisitorResultType visit(            \
            BOOST_PP_TUPLE_REM() __VisitorTypeSpecification const& arg,   \
            BOOST_PP_TUPLE_REM() __VisitorSharedArgs);                    \
    };

#define IS_EMPTY_TUPLE(tuple)                                             \
    BOOST_PP_IS_EMPTY(BOOST_PP_TUPLE_ELEM(0, tuple))

// clang-format off
#define DEFINE_VISITOR_BASE_METHOD_SIGNATURE(                             \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType)                                                  \
                                                                          \
    BOOST_PP_IF(                                                          \
        IS_EMPTY_TUPLE(__VisitorTemplateArgs),                            \
        BOOST_PP_EMPTY(),                                                   \
        template <BOOST_PP_TUPLE_REM() __VisitorTemplateArgs>)            \
    BOOST_PP_TUPLE_REM() __VisitorResultType                                                   \
        __VisitorTypename<BOOST_PP_TUPLE_REM() __VisitorTypeSpecification>::visit(             \
            BOOST_PP_TUPLE_REM() __VisitorTypeSpecification const& arg,                        \
            BOOST_PP_TUPLE_REM() __VisitorSharedArgs)
// clang-format on

#define DEFINE_VISITOR_BASE_ALL(                                          \
    __VisitorTypename,                                                    \
    __VisitorTemplateArgs,                                                \
    __VisitorSharedArgs,                                                  \
    __VisitorTypeSpecification,                                           \
    __VisitorResultType)                                                  \
                                                                          \
    DEFINE_VISITOR_BASE_STRUCT(                                           \
        __VisitorTypename,                                                \
        __VisitorTemplateArgs,                                            \
        __VisitorSharedArgs,                                              \
        __VisitorTypeSpecification,                                       \
        __VisitorResultType)                                              \
                                                                          \
    DEFINE_VISITOR_BASE_METHOD_SIGNATURE(                                 \
        __VisitorTypename,                                                \
        __VisitorTemplateArgs,                                            \
        __VisitorSharedArgs,                                              \
        __VisitorTypeSpecification,                                       \
        __VisitorResultType)


template <typename T>
struct __DescFieldTypeHelper {};

#define DESC_FIELD_TYPE(__field)                                          \
    __DescFieldTypeHelper<decltype(__field.pointer)>::Type

template <typename StructType, typename FieldType>
struct __DescFieldTypeHelper<FieldType StructType::*> {
    using Type = std::remove_cvref_t<FieldType>;
};

template <typename StructType, typename FieldType>
struct __DescFieldTypeHelper<FieldType StructType::*const> {
    using Type = std::remove_cvref_t<FieldType>;
};

namespace {
struct ImmTreeReprContext {
    int                           level;
    Vec<int>                      path;
    org::ImmAdapter::TreeReprConf conf;
    ImmAstContext*                ctx;

    ImmTreeReprContext addPath(int diff) const {
        ImmTreeReprContext result = *this;
        result.path.push_back(diff);
        return result;
    }

    ImmTreeReprContext addLevel(int diff) const {
        ImmTreeReprContext result = *this;
        result.level += diff;
        return result;
    }
};

template <typename T>
struct ImmTreeReprVisitor {};


template <typename T>
struct ImmTreeReprVisitor<org::ImmAdapterT<T>> {
    static void visit(
        org::ImmAdapterT<T>       id,
        ColStream&                os,
        ImmTreeReprContext const& ctx);
};

#define IMM_TREE_REPR_IMPL(__TemplateArgs, __VisitorTypeSpecification)    \
    DEFINE_VISITOR_BASE_ALL(                                              \
        /*Typename=*/ImmTreeReprVisitor,                                  \
        /*TemplateArgs=*/__TemplateArgs,                                  \
        /*SharedArgs=*/(ColStream & os, ImmTreeReprContext const& ctx),   \
        /*TypeSpecification=*/__VisitorTypeSpecification,                 \
        /*ResultType=*/(void))

IMM_TREE_REPR_IMPL((typename T), (ImmBox<T>)) {
    ImmTreeReprVisitor<T>::visit(arg.get(), os, ctx);
}

IMM_TREE_REPR_IMPL((typename T), (Opt<T>)) {
    if (arg) { ImmTreeReprVisitor<T>::visit(arg.value(), os, ctx); }
}

IMM_TREE_REPR_IMPL((typename T), (ImmVec<T>)) {
    int subIdx = 0;
    for (auto const& sub : arg) {
        os << "\n";
        ImmTreeReprVisitor<T>::visit(sub, os, ctx.addLevel(1));
    }
}

IMM_TREE_REPR_IMPL((), (org::ImmAdapter)) {
    switch (arg->getKind()) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        auto id_t = arg.as<org::Imm##__Kind>();                           \
        ImmTreeReprVisitor<org::ImmAdapterT<org::Imm##__Kind>>::visit(    \
            id_t, os, ctx);                                               \
        break;                                                            \
    }
        EACH_SEM_ORG_KIND(__case)
#undef __case
        default: {
            os.indent(ctx.level * 2);
            os << fmt(
                "ERR Invalid kind value {0:064b} {0:064X}",
                arg.id.getValue());
        }
    }
}

IMM_TREE_REPR_IMPL((), (Vec<sem::SemId<sem::Org>>)) {}
IMM_TREE_REPR_IMPL((typename T), (ImmMap<Str, T>)) {}
IMM_TREE_REPR_IMPL((), (absl::Time)) {}
IMM_TREE_REPR_IMPL((), (absl::TimeZone)) {}

IMM_TREE_REPR_IMPL((), (std::string)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", escape_literal(arg));
}

IMM_TREE_REPR_IMPL((), (Str)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", escape_literal(arg));
}

IMM_TREE_REPR_IMPL((), (bool)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", arg);
}

IMM_TREE_REPR_IMPL((), (int)) {
    os << os.indent(ctx.level * 2) << fmt(" {}", arg);
}

IMM_TREE_REPR_IMPL((IsEnum E), (E)) {}

IMM_TREE_REPR_IMPL((DescribedRecord R), (R)) {
    for_each_field_with_bases<R>([&](auto const& f) {
        using F = DESC_FIELD_TYPE(f);
        ImmTreeReprVisitor<F>::visit(arg.*f.pointer, os, ctx);
    });
}

IMM_TREE_REPR_IMPL((IsVariant T), (T)) {
    std::visit(
        [&]<typename V>(V const& var) {
            ImmTreeReprVisitor<V>::visit(var, os, ctx);
        },
        arg);
}


IMM_TREE_REPR_IMPL((), (org::ImmId)) {
    ImmTreeReprVisitor<org::ImmAdapter>::visit(
        org::ImmAdapter{arg, ctx.ctx}, os, ctx);
}


IMM_TREE_REPR_IMPL((typename T), (org::ImmIdT<T>)) {
    ImmTreeReprVisitor<org::ImmAdapterT<T>>::visit(
        org::ImmAdapter{arg, ctx.ctx}.as<T>(), os, ctx);
}

template <typename T>
void ImmTreeReprVisitor<org::ImmAdapterT<T>>::visit(
    org::ImmAdapterT<T>       id,
    ColStream&                os,
    ImmTreeReprContext const& ctx) {
    os.indent(ctx.level * 2);
    os << fmt(
        "{} {} PATH:{}", id->getKind(), id.id.getReadableId(), ctx.path);

    for_each_field_with_bases<T>([&](auto const& f) {
        auto const& fieldValue = id.get()->*f.pointer;
        using FieldType        = std::remove_cvref_t<decltype(fieldValue)>;
        auto subctx            = ctx.addLevel(1);
        if (f.name == "subnodes"_ss) {
            if constexpr (std::is_same_v<ImmVec<org::ImmId>, FieldType>) {
                for (int i = 0; i < fieldValue.size(); ++i) {
                    os << "\n";
                    ImmTreeReprVisitor<typename FieldType::value_type>::
                        visit(fieldValue.at(i), os, subctx.addPath(i));
                }
            } else {
                throw logic_unreachable_error::init(
                    "subnodes field is a vector of imm ID");
            }
        } else if (ctx.conf.withAuxFields) {
            os << "\n";
            os.indent((ctx.level + 1) * 2);
            os << f.name;
            os << "\n";
            ImmTreeReprVisitor<FieldType>::visit(
                fieldValue, os, subctx.addLevel(1));
        }
    });
}


} // namespace

void ImmAdapter::treeRepr(ColStream& os, const TreeReprConf& conf) const {
    ImmTreeReprVisitor<org::ImmAdapter>::visit(
        *this,
        os,
        ImmTreeReprContext{
            .conf  = conf,
            .level = 0,
            .ctx   = this->ctx,
        });
}
