#pragma once

#include <boost/describe.hpp>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/ItaniumDemangle.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MD5.h>

#include <haxdex_read_code_cpp_common/reflection_config.hpp>

struct BinarySymbolVisitContext {};


using namespace llvm::itanium_demangle;

#define NO_COVERAGE __attribute__((no_sanitize("coverage", "address", "thread")))

enum class KindProxy
{
#define NODE(NodeKind) NodeKind,
#include <llvm/Demangle/ItaniumNodes.def>
};

BOOST_DESCRIBE_ENUM_BEGIN(KindProxy)
#define NODE(NodeKind) BOOST_DESCRIBE_ENUM_ENTRY(KindProxy, NodeKind)
#include <llvm/Demangle/ItaniumNodes.def>
BOOST_DESCRIBE_ENUM_END(KindProxy)

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

BOOST_DESCRIBE_ENUM(llvm::itanium_demangle::TemplateParamKind, Type, NonType, Template);

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
    static constexpr size_t UsableAllocSize = AllocSize - sizeof(BlockMeta);

    alignas(long double) char InitialBuffer[AllocSize];
    BlockMeta* BlockList = nullptr;

    NO_COVERAGE void grow() {
        char* NewMeta = static_cast<char*>(std::malloc(AllocSize));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList = new (NewMeta) BlockMeta{BlockList, 0};
    }

    NO_COVERAGE void* allocateMassive(size_t NBytes) {
        NBytes += sizeof(BlockMeta);
        BlockMeta* NewMeta = reinterpret_cast<BlockMeta*>(std::malloc(NBytes));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList->Next = new (NewMeta) BlockMeta{BlockList->Next, 0};
        return static_cast<void*>(NewMeta + 1);
    }

  public:
    NO_COVERAGE BumpPointerAllocator()
        : BlockList(new (InitialBuffer) BlockMeta{nullptr, 0}) {}

    NO_COVERAGE void* allocate(size_t N) {
        N = (N + 15u) & ~15u;
        if (UsableAllocSize <= N + BlockList->Current) {
            if (N > UsableAllocSize) { return allocateMassive(N); }
            grow();
        }
        BlockList->Current += N;
        return static_cast<void*>(
            reinterpret_cast<char*>(BlockList + 1) + BlockList->Current - N);
    }

    NO_COVERAGE void reset() {
        while (BlockList) {
            BlockMeta* Tmp = BlockList;
            BlockList      = BlockList->Next;
            if (reinterpret_cast<char*>(Tmp) != InitialBuffer) { std::free(Tmp); }
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
        return new (Alloc.allocate(sizeof(T))) T(std::forward<Args>(args)...);
    }

    NO_COVERAGE void* allocateNodeArray(size_t sz) {
        return Alloc.allocate(sizeof(Node*) * sz);
    }
};
} // unnamed namespace

using Demangler = llvm::itanium_demangle::ManglingParser<DefaultAllocator>;

NO_COVERAGE llvm::MD5::MD5Result demangle_digest(Node const* node);


NO_COVERAGE llvm::json::Array& add_array_field(
    llvm::json::Object&      obj,
    std::string const&       field,
    llvm::json::Value const& value) {
    if (obj.getArray(field) == nullptr) { obj[field] = llvm::json::Array(); }
    obj.getArray(field)->push_back(value);
    return *obj.getArray(field);
}

NO_COVERAGE llvm::json::Object& add_obj_field(
    llvm::json::Object& obj,
    std::string const&  field) {
    if (obj.getObject(field) == nullptr) { obj[field] = llvm::json::Object(); }
    return *obj.getObject(field);
}


int findSymbolNamePosition(std::string const& input);


template <int N, typename T>
struct ForwardNth {
    T* target;
    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {
        *target = std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
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

#define K_CAST(Name)                                                                     \
    auto cast = const_cast<llvm::itanium_demangle::Name*>(                               \
        static_cast<llvm::itanium_demangle::Name const*>(node));

#define K_FIELD(Name, Idx, Type, ...)                                                    \
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


llvm::json::Value demangle_to_json(
    std::string const&        name,
    BinarySymbolVisitContext& ctx,
    int                       depth,
    int                       max_depth);

llvm::json::Value demangle_to_json(
    llvm::itanium_demangle::Node const* node,
    BinarySymbolVisitContext&           ctx,
    int                                 depth,
    int                                 max_depth);

std::string getClangResourceDir();


/// Filter out compilation options that were used in the compilation
/// database -- remove reflection plugin usage, precompiled headers, and
/// add provided toolchain include configuration.
clang::tooling::CommandLineArguments dropReflectionPlugin(
    clang::tooling::CommandLineArguments const& Args,
    llvm::StringRef                             Filename,
    ReflectionCLI const&                        cli);
