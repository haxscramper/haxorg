
#include <llvm/ADT/Hashing.h>
#include <llvm/ADT/SmallBitVector.h>
#include <llvm/DebugInfo/DWARF/DWARFContext.h>
#include <llvm/DebugInfo/Symbolize/Symbolize.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/ItaniumDemangle.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Object/Archive.h>
#include <llvm/Object/Binary.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/Object/SymbolSize.h>
#include <llvm/Object/SymbolSize.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MD5.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Regex.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/VirtualFileSystem.h>

#include <absl/hash/hash.h>
#include <absl/log/log.h>
#include <boost/describe.hpp>

#include <hstd/ext/perfetto_aux.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/system/macros.hpp>

#include "clang_reflection_demangler.hpp"
#include "clang_reflection_perf.hpp"


using namespace llvm::itanium_demangle;

#define NO_COVERAGE                                                       \
    __attribute__((no_sanitize("coverage", "address", "thread")))

enum class KindProxy
{
#define NODE(NodeKind) NodeKind,
#include <llvm/Demangle/ItaniumNodes.def>
};

BOOST_DESCRIBE_ENUM_BEGIN(KindProxy)
#define NODE(NodeKind) BOOST_DESCRIBE_ENUM_ENTRY(KindProxy, NodeKind)
#include <llvm/Demangle/ItaniumNodes.def>
BOOST_DESCRIBE_ENUM_END()

BOOST_DESCRIBE_ENUM(
    llvm::itanium_demangle::Node::Prec,
    Primary,
    Postfix,
    Unary,
    Cast,
    PtrMem,
    Multiplicative,
    Additive,
    Shift,
    Spaceship,
    Relational,
    Equality,
    And,
    Xor,
    Ior,
    AndIf,
    OrIf,
    Conditional,
    Assign,
    Comma,
    Default);

BOOST_DESCRIBE_ENUM(
    llvm::itanium_demangle::TemplateParamKind,
    Type,
    NonType,
    Template);

BOOST_DESCRIBE_ENUM(
    llvm::itanium_demangle::FunctionRefQual,
    FrefQualNone,
    FrefQualLValue,
    FrefQualRValue);

BOOST_DESCRIBE_ENUM(
    llvm::itanium_demangle::Qualifiers,
    QualNone,
    QualConst,
    QualVolatile,
    QualRestrict);

BOOST_DESCRIBE_ENUM(
    llvm::itanium_demangle::SpecialSubKind,
    allocator,
    basic_string,
    string,
    istream,
    ostream,
    iostream);

BOOST_DESCRIBE_ENUM(llvm::itanium_demangle::ReferenceKind, LValue, RValue);


namespace {
class BumpPointerAllocator {
    struct BlockMeta {
        BlockMeta* Next;
        size_t     Current;
    };

    static constexpr size_t AllocSize       = 4096;
    static constexpr size_t UsableAllocSize = AllocSize
                                            - sizeof(BlockMeta);

    alignas(long double) char InitialBuffer[AllocSize];
    BlockMeta* BlockList = nullptr;

    NO_COVERAGE void grow() {
        char* NewMeta = static_cast<char*>(std::malloc(AllocSize));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList = new (NewMeta) BlockMeta{BlockList, 0};
    }

    NO_COVERAGE void* allocateMassive(size_t NBytes) {
        NBytes += sizeof(BlockMeta);
        BlockMeta* NewMeta = reinterpret_cast<BlockMeta*>(
            std::malloc(NBytes));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList->Next = new (NewMeta) BlockMeta{BlockList->Next, 0};
        return static_cast<void*>(NewMeta + 1);
    }

  public:
    NO_COVERAGE BumpPointerAllocator()
        : BlockList(new(InitialBuffer) BlockMeta{nullptr, 0}) {}

    NO_COVERAGE void* allocate(size_t N) {
        N = (N + 15u) & ~15u;
        if (N + BlockList->Current >= UsableAllocSize) {
            if (N > UsableAllocSize) { return allocateMassive(N); }
            grow();
        }
        BlockList->Current += N;
        return static_cast<void*>(
            reinterpret_cast<char*>(BlockList + 1) + BlockList->Current
            - N);
    }

    NO_COVERAGE void reset() {
        while (BlockList) {
            BlockMeta* Tmp = BlockList;
            BlockList      = BlockList->Next;
            if (reinterpret_cast<char*>(Tmp) != InitialBuffer) {
                std::free(Tmp);
            }
        }
        BlockList = new (InitialBuffer) BlockMeta{nullptr, 0};
    }

    NO_COVERAGE ~BumpPointerAllocator() { reset(); }
};

class DefaultAllocator {
    BumpPointerAllocator Alloc;

  public:
    NO_COVERAGE void reset() { Alloc.reset(); }

    template <typename T, typename... Args>
    NO_COVERAGE T* makeNode(Args&&... args) {
        return new (Alloc.allocate(sizeof(T)))
            T(std::forward<Args>(args)...);
    }

    NO_COVERAGE void* allocateNodeArray(size_t sz) {
        return Alloc.allocate(sizeof(Node*) * sz);
    }
};
} // unnamed namespace

using Demangler = llvm::itanium_demangle::ManglingParser<DefaultAllocator>;


NO_COVERAGE llvm::json::Array& add_array_field(
    llvm::json::Object&      obj,
    std::string const&       field,
    llvm::json::Value const& value) {
    if (obj.getArray(field) == nullptr) {
        obj[field] = llvm::json::Array();
    }
    obj.getArray(field)->push_back(value);
    return *obj.getArray(field);
}

NO_COVERAGE llvm::json::Object& add_obj_field(
    llvm::json::Object& obj,
    std::string const&  field) {
    if (obj.getObject(field) == nullptr) {
        obj[field] = llvm::json::Object();
    }
    return *obj.getObject(field);
}


template <int N, typename T>
struct ForwardNth {
    T* target;
    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {
        *target = std::get<N>(
            std::forward_as_tuple(std::forward<Args>(args)...));
    }
};

template <int N, typename T, typename TNode>
NO_COVERAGE T match(TNode const* node) {
    T result;
    node->match(ForwardNth<N, T>{&result});
    return result;
}

struct visit_meta {
    bool               head_node  = false;
    std::optional<int> head_depth = std::nullopt;

    visit_meta with_depth(int depth) const {
        auto tmp       = *this;
        tmp.head_depth = depth;
        return tmp;
    }
};

template <typename Func>
NO_COVERAGE void visit_node_fields(Node const* node, Func const& sub) {
    if (node == nullptr) { return; }

    using K = llvm::itanium_demangle::Node::Kind;

#define K_CAST(Name)                                                      \
    auto cast = const_cast<llvm::itanium_demangle::Name*>(                \
        static_cast<llvm::itanium_demangle::Name const*>(node));

#define K_FIELD(Name, Idx, Type, ...)                                     \
    sub(#Name, match<Idx, Type>(cast) __VA_OPT__(, ) __VA_ARGS__);

    visit_meta head_attached_rec{
        .head_node = true,
    };

    using NPtr = Node const*;

    switch (node->getKind()) {
            // clang-format off
        case K::KNameType: { K_CAST(NameType); K_FIELD(Name, 0, std::string_view); break; }
        case K::KTypeTemplateParamDecl: { K_CAST(TypeTemplateParamDecl); K_FIELD(Name, 0, NPtr); break; }
        case K::KTemplateParamPackDecl: { K_CAST(TemplateParamPackDecl); K_FIELD(Param, 0, NPtr); break; }
        case K::KLiteralOperator: { K_CAST(LiteralOperator); K_FIELD(OpName, 0, NPtr); break; }
        case K::KTemplateArgs: { K_CAST(TemplateArgs); K_FIELD(Params, 0, NodeArray); break; }
        case K::KPointerType: { K_CAST(PointerType); K_FIELD(Pointee, 0, NPtr); break; }
        case K::KTemplateArgumentPack: { K_CAST(TemplateArgumentPack); K_FIELD(Elements, 0, NodeArray); break; }
        case K::KParameterPackExpansion: { K_CAST(ParameterPackExpansion); K_FIELD(Child, 0, NPtr); break; }
        case K::KGlobalQualifiedName: { K_CAST(GlobalQualifiedName); K_FIELD(Child, 0, NPtr); break; }
        case K::KParameterPack: { K_CAST(ParameterPack); K_FIELD(Data, 0, NodeArray); break; }
        case K::KConversionOperatorType: { K_CAST(ConversionOperatorType); K_FIELD(Ty, 0, NPtr); break; }
        case K::KEnableIfAttr: { K_CAST(EnableIfAttr); K_FIELD(Conditions, 0, NodeArray); break; }
        case K::KBoolExpr: { K_CAST(BoolExpr); K_FIELD(Value, 0, bool); break; }
        case K::KFunctionParam: { K_CAST(FunctionParam); K_FIELD(Number, 0, std::string_view); break; }
        case K::KNodeArrayNode: { K_CAST(NodeArrayNode); K_FIELD(Array, 0, NodeArray); break; }
        case K::KNoexceptSpec: { K_CAST(NoexceptSpec); K_FIELD(E, 0, NPtr); break; }
        case K::KDynamicExceptionSpec: { K_CAST(DynamicExceptionSpec); K_FIELD(Types, 0, NodeArray); break; }
        case K::KPixelVectorType: { K_CAST(PixelVectorType); K_FIELD(Dimension, 0, NPtr); break; }
        case K::KBinaryFPType: { K_CAST(BinaryFPType); K_FIELD(Dimension, 0, NPtr); break; }
        case K::KSpecialSubstitution: { K_CAST(SpecialSubstitution); K_FIELD(SSK, 0, SpecialSubKind); break; }
        case K::KDtorName: { K_CAST(DtorName); K_FIELD(Base, 0, NPtr); break; }
        case K::KUnnamedTypeName: { K_CAST(UnnamedTypeName); K_FIELD(Count, 0, std::string_view); break; }
        case K::KStructuredBindingName: { K_CAST(StructuredBindingName); K_FIELD(Bindings, 0, NodeArray); break; }
        case K::KCastExpr: { K_CAST(CastExpr); K_FIELD(CastKind, 0, std::string_view); K_FIELD(To, 1, NPtr); K_FIELD(From, 2, NPtr); K_FIELD(Precedence, 3, Node::Prec); break; }
        case K::KSizeofParamPackExpr: { K_CAST(SizeofParamPackExpr); K_FIELD(Pack, 0, NPtr); break; }
        case K::KThrowExpr: { K_CAST(ThrowExpr); K_FIELD(Op, 0, NPtr); break; }
        case K::KStringLiteral: { K_CAST(StringLiteral); K_FIELD(Type, 0, NPtr); break; }
        case K::KLambdaExpr: { K_CAST(LambdaExpr); K_FIELD(Type, 0, NPtr); break; }
        case K::KFloatLiteral: { K_CAST(FloatLiteral); K_FIELD(Type, 0, std::string_view); break; }
        case K::KDoubleLiteral: { K_CAST(DoubleLiteral); K_FIELD(Type, 0, std::string_view); break; }
        case K::KLongDoubleLiteral: { K_CAST(LongDoubleLiteral); K_FIELD(Type, 0, std::string_view); break; }
        case K::KExpandedSpecialSubstitution: { K_CAST(ExpandedSpecialSubstitution); K_FIELD(SSK, 0, SpecialSubKind); break; }
        case K::KDeleteExpr: { K_CAST(DeleteExpr); K_FIELD(Op, 0, NPtr); K_FIELD(IsGlobal, 1, bool); K_FIELD(IsArray, 2, bool); break; }
        case K::KBracedRangeExpr: { K_CAST(BracedRangeExpr); K_FIELD(First, 0, NPtr); K_FIELD(Last, 1, NPtr); K_FIELD(Init, 2, NPtr); break; }
        case K::KBracedExpr: { K_CAST(BracedExpr); K_FIELD(Elem, 0, NPtr); K_FIELD(Init, 1, NPtr); K_FIELD(IsArray, 2, bool); break; }
        case K::KPointerToMemberConversionExpr: { K_CAST(PointerToMemberConversionExpr); K_FIELD(Type, 0, NPtr); K_FIELD(SubExpr, 1, NPtr); K_FIELD(Offset, 2, std::string_view); break; }
        case K::KFoldExpr: { K_CAST(FoldExpr); K_FIELD(IsLeftFold, 0, bool); K_FIELD(OperatorName, 1, std::string_view); K_FIELD(Pack, 2, NPtr); K_FIELD(Init, 3, NPtr); break; }
        case K::KNewExpr: { K_CAST(NewExpr); K_FIELD(ExprList, 0, NodeArray); K_FIELD(Type, 1, NPtr); K_FIELD(NodeArray, 2, NodeArray); K_FIELD(IsGlobal, 3, bool); K_FIELD(IsArray, 4, bool); break; }
        case K::KVectorType: { K_CAST(VectorType); K_FIELD(BaseType, 0, NPtr); K_FIELD(Dimension, 1, NPtr); break; }
        case K::KArraySubscriptExpr: { K_CAST(ArraySubscriptExpr); K_FIELD(Op1, 0, NPtr); K_FIELD(Op2, 1, NPtr); break; }
        case K::KConditionalExpr: { K_CAST(ConditionalExpr); K_FIELD(Cond, 0, NPtr); K_FIELD(Then, 1, NPtr); K_FIELD(Else, 2, NPtr); break; }
        case K::KSubobjectExpr: { K_CAST(SubobjectExpr); K_FIELD(Type, 0, NPtr); K_FIELD(SubExpr, 1, NPtr); K_FIELD(Offset, 2, std::string_view); K_FIELD(UnionSelectors, 3, NodeArray); K_FIELD(OnePastTheEnd, 4, bool); break; }
        case K::KPostfixExpr: { K_CAST(PostfixExpr); K_FIELD(Child, 0, NPtr); K_FIELD(Operator, 1, std::string_view); break; }
        case K::KForwardTemplateReference: { K_CAST(ForwardTemplateReference); sub("Index", cast->Index); sub("Ref", cast->Ref); break; }
        case K::KSyntheticTemplateParamName: { K_CAST(SyntheticTemplateParamName); K_FIELD(Kind, 0, TemplateParamKind); K_FIELD(Index, 1, unsigned); break; }
        case K::KSpecialName: { K_CAST(SpecialName); K_FIELD(Special, 0, std::string_view); K_FIELD(Child, 1, NPtr); break; }
        case K::KPrefixExpr: { K_CAST(PrefixExpr); K_FIELD(Prefix, 0, std::string_view); K_FIELD(Child, 1, NPtr); break; }
        case K::KModuleName: { K_CAST(ModuleName); sub("Parent", cast->Parent); K_FIELD(Name, 1, NPtr); K_FIELD(IsPartition, 2, bool); break; }
        case K::KModuleEntity: { K_CAST(ModuleEntity); sub("Module", cast->Module); K_FIELD(Name, 1, NPtr); break; }
        case K::KNonTypeTemplateParamDecl: { K_CAST(NonTypeTemplateParamDecl); K_FIELD(Name, 0, NPtr); K_FIELD(Type, 1, NPtr); break; }
        case K::KTemplateTemplateParamDecl: { K_CAST(TemplateTemplateParamDecl); K_FIELD(Name, 0, NPtr); K_FIELD(Params, 1, NodeArray); break; }
        case K::KCtorVtableSpecialName: { K_CAST(CtorVtableSpecialName); K_FIELD(FirstType, 0, NPtr); K_FIELD(SecondType, 1, NPtr); break; }
        case K::KObjCProtoName: { K_CAST(ObjCProtoName); K_FIELD(Ty, 0, NPtr); K_FIELD(Protocol, 1, std::string_view); break; }
        case K::KPointerToMemberType: { K_CAST(PointerToMemberType); K_FIELD(ClassType, 0, NPtr); K_FIELD(MemberType, 1, NPtr); break; }
        case K::KDotSuffix: { K_CAST(DotSuffix); K_FIELD(Prefix, 0, NPtr); K_FIELD(SUffix, 1, std::string_view); break; }
        case K::KVendorExtQualType: { K_CAST(VendorExtQualType); K_FIELD(Ty, 0, NPtr); K_FIELD(Ext, 1, std::string_view); K_FIELD(TA, 2, NPtr); break; }
        case K::KAbiTagAttr: { K_CAST(AbiTagAttr); K_FIELD(Base, 0, NPtr); K_FIELD(Tag, 1, std::string_view); break; }
        case K::KBitIntType: { K_CAST(BitIntType); K_FIELD(Size, 0, NPtr); K_FIELD(Signed, 1, bool); break; }
        case K::KConversionExpr: { K_CAST(ConversionExpr); K_FIELD(Type, 0, NPtr); K_FIELD(Expressions, 1, NodeArray); break; }
        case K::KEnumLiteral: { K_CAST(EnumLiteral); K_FIELD(Ty, 0, NPtr); K_FIELD(Integer, 1, std::string_view); break; }
        case K::KLocalName: { K_CAST(LocalName); K_FIELD(Encoding, 0, NPtr); K_FIELD(Entity, 1, NPtr); break; }
        case K::KPostfixQualifiedType: { K_CAST(PostfixQualifiedType); K_FIELD(Ty, 0, NPtr); K_FIELD(Postfix, 1, std::string_view); break; }
        case K::KEnclosingExpr: { K_CAST(EnclosingExpr); K_FIELD(Prefix, 0, std::string_view); K_FIELD(Infix, 1, NPtr); break; }
        case K::KClosureTypeName: { K_CAST(ClosureTypeName); K_FIELD(TemplateParams, 0, NodeArray); K_FIELD(Requires1, 1, NPtr); K_FIELD(Params, 2, NodeArray); K_FIELD(Requires2, 3, NPtr); K_FIELD(Count, 4, std::string_view); break; }
        case K::KQualifiedName: { K_CAST(QualifiedName); K_FIELD(Qualifier, 0, NPtr); K_FIELD(Name, 1, NPtr); break; }
        case K::KArrayType: { K_CAST(ArrayType); K_FIELD(Base, 0, NPtr); K_FIELD(Dimension, 1, NPtr); break; }
        case K::KMemberExpr: { K_CAST(MemberExpr); K_FIELD(LHS, 0, NPtr); K_FIELD(Kind, 1, std::string_view); K_FIELD(RHS, 2, NPtr); break; }
        case K::KBinaryExpr: { K_CAST(BinaryExpr); K_FIELD(LHS, 0, NPtr); K_FIELD(InfixOperator, 1, std::string_view); K_FIELD(RHS, 2, NPtr); break; }
        case K::KCallExpr: { K_CAST(CallExpr); K_FIELD(Callee, 0, NPtr); K_FIELD(Args, 1, NodeArray); break; }
        case K::KElaboratedTypeSpefType: { K_CAST(ElaboratedTypeSpefType); K_FIELD(Kind, 0, std::string_view); K_FIELD(Child, 1, NPtr); break; }
        case K::KFunctionType: { K_CAST(FunctionType); K_FIELD(Ret, 0, NPtr); K_FIELD(Params, 1, NodeArray); K_FIELD(CVQuals, 2, Qualifiers); K_FIELD(RefQual, 3, FunctionRefQual); K_FIELD(ExpcetionSpec, 4, NPtr); break; }
        case K::KQualType: { K_CAST(QualType); K_FIELD(Child, 0, NPtr); K_FIELD(Quals, 1, Qualifiers); break; }
        case K::KReferenceType: { K_CAST(ReferenceType); K_FIELD(Pointee, 0, NPtr); K_FIELD(RK, 1, llvm::itanium_demangle::ReferenceKind); break; }
        case K::KIntegerLiteral: { K_CAST(IntegerLiteral); K_FIELD(Type, 0, std::string_view); K_FIELD(Value, 1, std::string_view); break; }
        case K::KCtorDtorName: { K_CAST(CtorDtorName); K_FIELD(Basename, 0, NPtr); K_FIELD(IsDtor, 1, bool); K_FIELD(Variant, 2, int); break; }
        case K::KInitListExpr: { K_CAST(InitListExpr); K_FIELD(Ty, 0, NPtr); K_FIELD(Inits, 1, NodeArray); break; }
        case K::KTemplateParamQualifiedArg: { K_CAST(TemplateParamQualifiedArg); K_FIELD(Param, 0, NPtr); K_FIELD(Arg, 1, NPtr); break; }
        case K::KConstrainedTypeTemplateParamDecl: { K_CAST(ConstrainedTypeTemplateParamDecl); K_FIELD(Constraint, 0, NPtr); K_FIELD(Name, 1, NPtr); break; }
        case K::KExplicitObjectParameter: { K_CAST(ExplicitObjectParameter); K_FIELD(Base, 0, NPtr); break; }
        case K::KNestedRequirement: { K_CAST(NestedRequirement); K_FIELD(Constraint, 0, NPtr); break; }
        case K::KTypeRequirement: { K_CAST(TypeRequirement); K_FIELD(Type, 0, NPtr); break; }
        case K::KMemberLikeFriendName: { K_CAST(MemberLikeFriendName); K_FIELD(Qual, 0, NPtr); K_FIELD(Name, 1, NPtr); break; }
        case K::KRequiresExpr: { K_CAST(RequiresExpr); K_FIELD(Parameters, 0, NodeArray); K_FIELD(Requirements, 1, NodeArray); break; }
        case K::KExprRequirement: { K_CAST(ExprRequirement); K_FIELD(Expr, 0, NPtr); K_FIELD(IsNoexcept, 1, bool); K_FIELD(TypeConstraint, 2, NPtr); break; }
        case K::KTransformedType: { K_CAST(TransformedType); K_FIELD(Transform, 0, std::string_view); K_FIELD(BaseType, 1, NPtr); break; }
            // clang-format on
        case K::KNameWithTemplateArgs: {
            K_CAST(NameWithTemplateArgs);
            K_FIELD(Name, 0, NPtr, head_attached_rec.with_depth(2));
            K_FIELD(TemplateArgs, 1, NPtr);
            break;
        }
        case K::KFunctionEncoding: {
            K_CAST(FunctionEncoding);
            K_FIELD(Ret, 0, NPtr);
            K_FIELD(Name, 1, NPtr, head_attached_rec.with_depth(2));
            K_FIELD(Params, 2, NodeArray);
            K_FIELD(Attrs, 3, NPtr);
            K_FIELD(Requires, 4, NPtr);
            K_FIELD(CVQuals, 5, Qualifiers);
            K_FIELD(RefQual, 6, FunctionRefQual);
            break;
        }
        case K::KNestedName: {
            K_CAST(NestedName);
            K_FIELD(Qual, 0, NPtr, head_attached_rec.with_depth(2));
            K_FIELD(Name, 1, NPtr, head_attached_rec.with_depth(2));
            break;
        }
    }
}

NO_COVERAGE llvm::MD5::MD5Result demangle_digest(Node const* node) {
    llvm::MD5 result;

    auto visit_field = hstd::overloaded{
        // clang-format off
        [&result](std::string_view value) { result.update(value); },
        [&result](std::string value) { result.update(value); },
        [&result](bool const& value) { result.update(value); },
        [&result](Qualifiers const& value) { result.update(value); },
        [&result](FunctionRefQual const& value) { result.update(value); },
        [&result](Node const* value) { result.update(demangle_digest(value)); },
        [&result](Node::Prec const& value) { result.update(static_cast<int>(value)); },
        [&result](TemplateParamKind const& value) { result.update(static_cast<int>(value)); },
        [&result](SpecialSubKind const& value) { result.update(static_cast<int>(value)); },
        [&result](llvm::itanium_demangle::ReferenceKind const& RK) { result.update(static_cast<int>(RK)); },
        // clang-format on
        [&result](NodeArray const& value) {
            for (auto const& it : value) {
                result.update(demangle_digest(it));
            }
        },
    };

    auto sub = [&](std::string const&               field,
                   auto const&                      value,
                   std::optional<visit_meta> const& meta = std::nullopt) {
        result.update(field);
        visit_field(value);
    };

    visit_node_fields(node, sub);

    return result.result();
}

NO_COVERAGE llvm::json::Value demangle_to_json(
    Node const*               node,
    BinarySymbolVisitContext& ctx,
    int                       depth,
    int                       max_depth) {
    llvm::json::Object result;
    if (node == nullptr) { return nullptr; }
    if (max_depth < depth) { return nullptr; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["NodeKind"] = Kind;

    auto should_skip = hstd::overloaded{
        [](std::string const& view) { return view.empty(); },
        [](std::string_view view) { return view.empty(); },
        [](llvm::json::Value const& value) {
            switch (value.kind()) {
                case llvm::json::Value::Kind::Array:
                    value.getAsArray()->empty();
                case llvm::json::Value::Kind::Null: return true;
                default: return false;
            }
        },
        [](auto const&) { return false; },
    };

    auto sub = hstd::overloaded{
        [&](std::string const& field, llvm::json::Value const& value) {
            if (!should_skip(value)) { result[field] = value; }
        },
        [&](std::string const& field, std::string_view value) {
            if (!should_skip(value)) {
                result[field] = std::string{value.begin(), value.end()};
            }
        },
        [&](std::string const& field, std::string value) {
            if (!should_skip(value)) { result[field] = value; }
        },
        [&](std::string const& field, Node const* value) {
            auto tmp = demangle_to_json(value, ctx, depth + 1, max_depth);
            if (!should_skip(tmp)) { result[field] = std::move(tmp); }
        },
        [&](std::string const& field, NodeArray const& value) {
            llvm::json::Array array;
            for (auto const& it : value) {
                auto tmp = demangle_to_json(it, ctx, depth + 1, max_depth);
                if (!should_skip(tmp)) { array.push_back(std::move(tmp)); }
            }
            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&](std::string const& field, Qualifiers const& value) {
            llvm::json::Array array;
            if (value & Qualifiers::QualConst) {
                array.push_back("QualConst");
            }

            if (value & Qualifiers::QualVolatile) {
                array.push_back("QualVolatile");
            }

            if (value & Qualifiers::QualRestrict) {
                array.push_back("QualRestrict");
            }

            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&](std::string const& field, FunctionRefQual const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, Node::Prec const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, TemplateParamKind const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, SpecialSubKind const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const&                           field,
            llvm::itanium_demangle::ReferenceKind const& value) {
            result[field] = hstd::fmt1(value);
        },
    };

    auto sub_proxy =
        [&](std::string const&               field,
            auto const&                      value,
            std::optional<visit_meta> const& meta = std::nullopt) {
            sub(field, value);
        };

    visit_node_fields(node, sub_proxy);

    return result;
}

BinarySymComponentId demangle_to_db(
    Node const*               node,
    BinarySymbolVisitContext& ctx,
    BinaryFileDB&             db) {
    if (node == nullptr) { return BinarySymComponentId::Nil(); }

    BinarySymComponent comp;
    comp.binary_sym_kind = static_cast<int>(node->getKind());
    hstd::Vec<BinarySymComponentId> nested;

    using BSF = BinarySymField;
    using Res = std::optional<BinarySymField>;
    using Met = std::optional<visit_meta>;

    auto visit_value = hstd::overloaded{
        [&](std::string_view value, Met const& meta) -> Res {
            return BSF{std::string{value.begin(), value.end()}};
        },
        [&](std::string value, Met const& meta) -> Res {
            return BSF{value};
        },
        [&](bool const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](Node const* value, Met const& meta) -> Res {
            nested.push_back(demangle_to_db(value, ctx, db));
            if (meta && meta->head_node) {
                return BSF{demangle_to_json(
                    value, ctx, 0, meta->head_depth.value_or(1))};
            } else {
                return std::nullopt;
            }
        },
        [&](NodeArray const& value, Met const& meta) -> Res {
            for (auto const& it : value) {
                nested.push_back(demangle_to_db(it, ctx, db));
            }
            return std::nullopt;
        },
        [&](Qualifiers const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](FunctionRefQual const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](Node::Prec const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](TemplateParamKind const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](SpecialSubKind const& value, Met const& meta) -> Res {
            return BSF{hstd::fmt1(value)};
        },
        [&](llvm::itanium_demangle::ReferenceKind const& value,
            Met const& meta) -> Res { return BSF{hstd::fmt1(value)}; },
    };

    auto sub = [&](std::string const&               field,
                   auto const&                      value,
                   std::optional<visit_meta> const& meta = std::nullopt) {
        auto info = visit_value(value, meta);
        if (info) {
            comp.head_direct_fields.insert_or_assign(field, info.value());
        }
    };

    comp.head_direct_fields["Kind"] = BSF{
        std::string{boost::describe::enum_to_string(
            static_cast<KindProxy>(node->getKind()), "<none>")}};

    visit_node_fields(node, sub);
    auto res = db.symbol_components.add(comp);
    if (!nested.empty()) {
        db.nested_symbols.insert_or_assign(res, nested);
    }
    return res;
}

static std::vector<std::string> CompiledFileExtensions = {
    ".cpp",
    ".h",
    ".hpp",
    ".cc",
    ".cxx",
    ".c",
    ".C",
    ".java",
    ".js",
    ".ts",
    ".go",
    ".py",
    ".rs",
    ".swift",
    ".m",
    ".mm",
};

int findSymbolNamePosition(const std::string& input) {
    int pos = input.find(':');
    while (pos != std::string::npos) {
        for (const auto& ext : CompiledFileExtensions) {
            int extPos = input.rfind(ext, pos);
            if (extPos != std::string::npos
                && extPos + ext.length() == pos) {
                return pos + 1;
            }
        }
        pos = input.find(':', pos + 1);
    }

    return 0;
}

llvm::json::Value demangle_to_json(
    const std::string&        name,
    BinarySymbolVisitContext& ctx,
    int                       depth,
    int                       max_depth) {
    int         offset = findSymbolNamePosition(name);
    std::string name2  = name.substr(offset);
    Demangler   Parser(name2.data(), name2.data() + name2.length());
    Node*       AST = Parser.parse();
    return demangle_to_json(AST, ctx, depth, max_depth);
}


BinarySymComponentId parseBinarySymbolName(
    std::string const&        name,
    BinaryFileDB&             db,
    BinarySymbolVisitContext& ctx) {
    Demangler Parser(name.data(), name.data() + name.size());
    Node*     AST = Parser.parse();
    __perf_trace("sym", "Parse binary symbol");
    BinarySymComponentId res = BinarySymComponentId::Nil();
    {
        __perf_trace("sym", "Demangle to JSON", "name", name);
        res = demangle_to_db(AST, ctx, db);
    }

    // In some cases LLVM fails to demangle itanium names for
    // lambdas and some other symbols, like
    // `SemOrgApi.cpp:_ZZNK3sem7Subtree14getTimePeriodsE6IntSetINS0_6Period4KindEEENK3$_0clINS0_8Property17ExportLatexHeaderEEEDaRKT_`
    // so this heuristics is used to give more information on the
    // failure -- `cxx-filt` also fails to process this, so it
    // seems to be a LLVM issue.
    if (AST == nullptr && name.contains("$_") && name.contains("cl")
        && name.contains('K')) {
        // pass
    } else if (AST == nullptr) {
        // pass
    }

    return res;
}

std::size_t hash_json_value(const llvm::json::Value& value) {
    std::size_t result = 0;

    switch (value.kind()) {
        case llvm::json::Value::Null:
            hstd::hax_hash_combine(result, 0);
            break;

        case llvm::json::Value::Boolean:
            hstd::hax_hash_combine(result, value.getAsBoolean().value());
            break;

        case llvm::json::Value::Number:
            hstd::hax_hash_combine(result, value.getAsNumber().value());
            break;

        case llvm::json::Value::String:
            hstd::hax_hash_combine(
                result, llvm::hash_value(value.getAsString().value()));
            break;

        case llvm::json::Value::Array: {
            const auto& array = *value.getAsArray();
            hstd::hax_hash_combine(result, array.size());
            for (const auto& element : array) {
                hstd::hax_hash_combine(result, hash_json_value(element));
            }
            break;
        }

        case llvm::json::Value::Object: {
            const auto& object = *value.getAsObject();
            std::vector<std::pair<std::string, const llvm::json::Value*>>
                sorted_fields;

            for (const auto& pair : object) {
                sorted_fields.emplace_back(pair.first.str(), &pair.second);
            }

            std::sort(
                sorted_fields.begin(),
                sorted_fields.end(),
                [](const auto& a, const auto& b) {
                    return a.first < b.first;
                });

            hstd::hax_hash_combine(result, sorted_fields.size());
            for (const auto& field : sorted_fields) {
                hstd::hax_hash_combine(result, field.first);
                hstd::hax_hash_combine(
                    result, hash_json_value(*field.second));
            }
            break;
        }
    }

    return result;
}

bool json_values_equal(
    const llvm::json::Value& lhs,
    const llvm::json::Value& rhs) {
    if (lhs.kind() != rhs.kind()) { return false; }

    switch (lhs.kind()) {
        case llvm::json::Value::Null: return true;

        case llvm::json::Value::Boolean:
            return lhs.getAsBoolean().value()
                == rhs.getAsBoolean().value();

        case llvm::json::Value::Number:
            return lhs.getAsNumber().value() == rhs.getAsNumber().value();

        case llvm::json::Value::String:
            return lhs.getAsString().value() == rhs.getAsString().value();

        case llvm::json::Value::Array: {
            const auto& lhs_array = *lhs.getAsArray();
            const auto& rhs_array = *rhs.getAsArray();

            if (lhs_array.size() != rhs_array.size()) { return false; }

            for (int i = 0; i < lhs_array.size(); ++i) {
                if (!json_values_equal(lhs_array[i], rhs_array[i])) {
                    return false;
                }
            }
            return true;
        }

        case llvm::json::Value::Object: {
            const auto& lhs_object = *lhs.getAsObject();
            const auto& rhs_object = *rhs.getAsObject();

            if (lhs_object.size() != rhs_object.size()) { return false; }

            for (const auto& pair : lhs_object) {
                auto rhs_it = rhs_object.find(pair.first);
                if (rhs_it == rhs_object.end()) { return false; }
                if (!json_values_equal(pair.second, rhs_it->second)) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}

std::size_t std::hash<BinarySymComponent>::operator()(
    const BinarySymComponent& it) const noexcept {
    std::size_t result = 0;
    hstd::hax_hash_combine(result, it.binary_sym_kind);

    std::vector<std::string> sorted_keys;
    for (auto const& [key, value] : it.head_direct_fields) {
        sorted_keys.emplace_back(key);
    }
    std::sort(sorted_keys.begin(), sorted_keys.end());

    for (auto const& key : sorted_keys) {
        hstd::hax_hash_combine(result, key);
        hstd::hax_hash_combine(result, it.head_direct_fields.at(key));
    }

    return result;
}


std::size_t std::hash<BinarySymField>::operator()(
    const BinarySymField& it) const noexcept {
    return std::visit(
        hstd::overloaded{
            [](llvm::json::Value const& value) {
                return hash_json_value(value);
            },
            [](auto const& val) {
                return std::hash<std::decay_t<decltype(val)>>{}(val);
            },
        },
        it.value);
}

bool BinarySymComponent::operator==(
    const BinarySymComponent& other) const noexcept {
    if (binary_sym_kind != other.binary_sym_kind) { return false; }

    if (head_direct_fields.size() != other.head_direct_fields.size()) {
        return false;
    }

    std::vector<std::string> lhs_keys;
    for (auto const& [key, value] : head_direct_fields) {
        lhs_keys.emplace_back(key);
    }
    std::sort(lhs_keys.begin(), lhs_keys.end());

    std::vector<std::string> rhs_keys;
    for (auto const& [key, value] : other.head_direct_fields) {
        rhs_keys.emplace_back(key);
    }
    std::sort(rhs_keys.begin(), rhs_keys.end());

    for (int i = 0; i < static_cast<int>(lhs_keys.size()); ++i) {
        if (lhs_keys.at(i) != rhs_keys.at(i)) { return false; }
        if (head_direct_fields.at(lhs_keys.at(i))
            != other.head_direct_fields.at(rhs_keys.at(i))) {
            return false;
        }
    }

    return true;
}

namespace {

struct BinaryFileCtx {
    int counter     = 0;
    int min_counter = 0;
    int max_counter = INT_MAX;
    // Aggregate sections across all processed object files (including
    // archive members)
    std::map<std::string, std::vector<BinarySymbolInfoId>> sectionSymbols;
    BinaryFileDB                                           db;
    BinarySymbolVisitContext                               ctx;
};

void processObjectFile(
    llvm::object::ObjectFile&         obj,
    const std::optional<std::string>& objectLabel,
    BinaryFileCtx&                    ctx) {
    // Create DWARF context once per object file (cheap enough, and
    // avoids per-symbol reparse)
    std::unique_ptr<llvm::DWARFContext> dwarf = llvm::DWARFContext::create(
        obj);

    llvm::DILineInfoSpecifier spec;
    spec.FNKind = llvm::DILineInfoSpecifier::FunctionNameKind::LinkageName;
    spec.FLIKind = llvm::DILineInfoSpecifier::FileLineInfoKind::
        AbsoluteFilePath;

    for (const auto& symAndSize : llvm::object::computeSymbolSizes(obj)) {
        __perf_trace("sym", "Process symbol");
        ++ctx.counter;
        if (ctx.counter < ctx.min_counter) { continue; }
        if (ctx.max_counter < ctx.counter) { break; }

        const llvm::object::SymbolRef& symbol = symAndSize.first;
        uint64_t                       size   = symAndSize.second;
        if (size == 0) { continue; }

        auto nameOrErr = symbol.getName();
        if (!nameOrErr) {
            consumeError(nameOrErr.takeError());
            continue;
        }
        std::string name = nameOrErr->str();

        auto addressOrErr = symbol.getAddress();
        if (!addressOrErr) {
            consumeError(addressOrErr.takeError());
            continue;
        }
        uint64_t address = *addressOrErr;

        // Section name (optional)
        std::string sectionName;
        auto        sectionOrErr = symbol.getSection();
        if (sectionOrErr) {
            llvm::object::section_iterator section = *sectionOrErr;
            if (section != obj.section_end()) {
                if (auto sectionNameOrErr = section->getName()) {
                    sectionName = sectionNameOrErr->str();
                } else {
                    consumeError(sectionNameOrErr.takeError());
                }
            }
        } else {
            consumeError(sectionOrErr.takeError());
        }

        std::string demangled = llvm::demangle(name);

        BinarySymbolInfo info{
            .name      = name,
            .demangled = demangled,
            .head      = parseBinarySymbolName(name, ctx.db, ctx.ctx),
            .size      = size,
            .address   = address,
        };


        // Debug location (DWARF): best-effort. Mostly meaningful
        // for code symbols. Skip undefined symbols or zero
        // addresses to avoid junk lookups.
        bool isUndef = false;
        if (auto flagsOrErr = symbol.getFlags()) {
            isUndef = ((*flagsOrErr)
                       & llvm::object::SymbolRef::SF_Undefined)
                   != 0;

        } else {
            consumeError(flagsOrErr.takeError());
        }


        if (!isUndef && address != 0) {
            llvm::object::SectionedAddress sa;
            sa.Address = address;


            std::optional<llvm::DILineInfo> li = dwarf->getLineInfoForAddress(sa, spec);
            if (li && li->Line != 0 && !li->FileName.empty()) {
                BinarySymbolDebugLocation loc;
                loc.file     = li->FileName;
                loc.line     = li->Line;
                loc.column   = li->Column;
                loc.function = li->FunctionName;
                info.debug   = std::move(loc);
            }
        }

        ctx.sectionSymbols[sectionName].push_back(
            ctx.db.symbols.add(info));
    }
}
} // namespace

BinaryFileDB getSymbolsInBinary(const std::string& path) {
    __perf_trace("sym", "Get symbols in binary");
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetDisassembler();

    auto binaryOrErr = llvm::object::createBinary(path);
    if (!binaryOrErr) {
        auto errorMsg = llvm::toString(binaryOrErr.takeError());
        throw hstd::runtime_error::init(
            std::format("Binary loading error: {}", errorMsg));
    }

    llvm::object::OwningBinary<llvm::object::Binary> binary = std::move(
        *binaryOrErr);
    llvm::object::Binary* bin = binary.getBinary();

    BinaryFileCtx ctx{};

    if (auto sym_min = std::getenv("REFLECTION_TOOL_SYM_MIN")) {
        ctx.min_counter = std::atoi(sym_min);
    }
    if (auto sym_max = std::getenv("REFLECTION_TOOL_SYM_MAX")) {
        ctx.max_counter = std::atoi(sym_max);
    }

    // Dispatch based on binary kind
    if (auto* obj = llvm::dyn_cast<llvm::object::ObjectFile>(bin)) {
        processObjectFile(*obj, /*objectLabel=*/path, ctx);
    } else if (auto* arch = llvm::dyn_cast<llvm::object::Archive>(bin)) {
        llvm::Error err = llvm::Error::success();
        for (auto const& child : arch->children(err)) {
            std::optional<std::string> memberLabel;

            if (auto nameOrErr = child.getName()) {
                // Label like: "libfoo.a(member.o)"
                memberLabel = path + "(" + nameOrErr->str() + ")";
            } else {
                consumeError(nameOrErr.takeError());
                memberLabel = path + "(<unknown-member>)";
            }

            auto childBinOrErr = child.getAsBinary();
            if (!childBinOrErr) {
                consumeError(childBinOrErr.takeError());
                continue;
            }

            llvm::object::Binary* childBin = childBinOrErr->get();
            if (auto* childObj = llvm::dyn_cast<llvm::object::ObjectFile>(
                    childBin)) {
                processObjectFile(*childObj, memberLabel, ctx);
            } else {
                // else: skip non-object members
            }
        }
        if (err) { consumeError(std::move(err)); }
    } else {
        throw hstd::invalid_argument::init(
            "Unsupported binary type (not ObjectFile or Archive)");
    }

    // Build db.sections from accumulated map
    for (const auto& [sectionName, symbols] : ctx.sectionSymbols) {
        ctx.db.sections.push_back({sectionName, symbols});
    }

    return ctx.db;
}

NO_COVERAGE void CreateTables(SQLite::Database& db) {
    auto path = hstd::fs::path{__FILE__}.parent_path()
              / "reflection_demangler.sql";
    std::string sql = hstd::readFile(path);
    db.exec(sql);
}

namespace {
/// \brief Create a text for a `INSERT` statement with a given list of
/// column names and identical number of coverage instantiation
NO_COVERAGE std::string SqlInsert(
    std::string const&              Table,
    std::vector<std::string> const& Columns) {
    std::string result = std::format("INSERT INTO {} (", Table);
    for (auto it : llvm::enumerate(Columns)) {
        if (it.index() != 0) { result += ", "; }
        result += it.value();
    }

    result += ") VALUES (";

    for (auto it : llvm::enumerate(Columns)) {
        if (it.index() != 0) { result += ", "; }
        result += "?";
    }

    result += ")";
    return result;
}
} // namespace

struct queries {
    SQLite::Statement demangled_head;
    SQLite::Statement demangled_nested;
    SQLite::Statement binary_sections;
    SQLite::Statement binary_symbol;

    queries(SQLite::Database& db)
        : // ---
        demangled_head(
            db,
            SqlInsert(
                "DemangledHead",
                {
                    "Id",     // 1
                    "Kind",   // 2
                    "Fields", // 3
                }))
        ,
        // ---
        demangled_nested(
            db,
            SqlInsert(
                "DemangledNested",
                {
                    "ComponentIndex", // 1
                    "Parent",         // 2
                    "Self",           // 3
                }))
        ,
        // ---
        binary_sections(
            db,
            SqlInsert(
                "BinarySection",
                {
                    "Id",   // 1
                    "Name", // 2
                }))
        ,
        // ---
        binary_symbol(
            db,
            SqlInsert(
                "BinarySymbol",
                {
                    "Id",              // 1
                    "Name",            // 2
                    "Demangled",       // 3
                    "DemangledHeadId", // 4
                    "Size",            // 5
                    "Address",         // 6
                    "Section",         // 7
                    "File",            // 8
                    "Line",            // 9
                    "Column",          // 10
                    "Function",        // 11
                }))
    //
    {};
};

NO_COVERAGE void BinaryFileDB::writeToFile(const std::string& path) {
    hstd::fs::path db_file{path};

    if (hstd::fs::exists(db_file)) { hstd::fs::remove(db_file); }

    SQLite::Database db{
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
    CreateTables(db);
    queries q{db};

    __perf_trace_begin("sym", "Insert symbol components");
    for (auto const& [id, cp_value] : symbol_components.pairs()) {
        auto value = const_cast<BinarySymComponent*>(cp_value);
        q.demangled_head.bind(1, static_cast<int64_t>(id.getValue()));
        q.demangled_head.bind(2, static_cast<int>(value->binary_sym_kind));
        llvm::json::Object j_object;
        for (auto& [field_name, field_value] : value->head_direct_fields) {
            std::visit(
                hstd::overloaded{
                    [&](llvm::json::Value& value) {
                        j_object[field_name] = std::move(value);
                    },
                    [&](int const& value) {
                        j_object[field_name] = value;
                    },
                    [&](std::string const& value) {
                        j_object[field_name] = value;
                    },
                },
                field_value.value);
        }

        auto j_format = llvm::formatv(
            "{0}", llvm::json::Value(std::move(j_object)));

        q.demangled_head.bind(3, j_format);

        q.demangled_head.exec();
        q.demangled_head.reset();
    }
    __perf_trace_end("sym");


    __perf_trace_begin("sym", "Insert sections");
    for (auto const& it : hstd::enumerator(sections)) {
        q.binary_sections.bind(1, it.index());
        q.binary_sections.bind(2, it.value().name);
        q.binary_sections.exec();
        q.binary_sections.reset();

        for (auto const& sym_id : it.value().symbols) {
            q.binary_symbol.bind(
                1, static_cast<int64_t>(sym_id.getValue()));
            auto const& sym = symbols.at(sym_id);
            q.binary_symbol.bind(2, sym.name);
            q.binary_symbol.bind(3, sym.demangled);
            q.binary_symbol.bind(
                4, static_cast<int64_t>(sym.head.getValue()));
            q.binary_symbol.bind(5, static_cast<int>(sym.size));
            q.binary_symbol.bind(6, static_cast<int>(sym.address));
            q.binary_symbol.bind(7, static_cast<int>(it.index()));
            if (sym.debug) {
                auto const& d = sym.debug.value();
                q.binary_symbol.bind(8, d.file);
                q.binary_symbol.bind(9, static_cast<int>(d.line));
                q.binary_symbol.bind(10, static_cast<int>(d.column));
                if (!d.function.empty()) {
                    q.binary_symbol.bind(11, d.function);
                }
            }
            q.binary_symbol.exec();
            q.binary_symbol.reset();
        }
    }
    __perf_trace_end("sym");

    __perf_trace_begin("sym", "Insert nested symbols");
    for (auto const& id : hstd::sorted(nested_symbols.keys())) {
        for (auto const& it : hstd::enumerator(nested_symbols.at(id))) {
            q.demangled_nested.bind(1, static_cast<int>(it.index()));
            q.demangled_nested.bind(
                2, static_cast<int64_t>(id.getValue()));
            if (!it.value().isNil()) {
                q.demangled_nested.bind(
                    3, static_cast<int64_t>(it.value().getIndex()));
            }
            q.demangled_nested.exec();
            q.demangled_nested.reset();
        }
    }
    __perf_trace_end("sym");
}
