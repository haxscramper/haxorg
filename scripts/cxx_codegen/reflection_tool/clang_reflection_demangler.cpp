#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/Regex.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>
#include <boost/describe.hpp>
#include <llvm/ADT/Hashing.h>
#include <hstd/stdlib/Formatter.hpp>
#include <absl/hash/hash.h>
#include <hstd/system/aux_utils.hpp>
#include <llvm/ADT/SmallBitVector.h>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/ItaniumDemangle.h>

#include <hstd/ext/perfetto_aux.hpp>
#include <absl/log/log.h>

#include <hstd/stdlib/OptFormatter.hpp>
#include "reflection_defs.pb.h"

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


NO_COVERAGE llvm::json::Value treeRepr(Node const* node) {
    llvm::json::Object result;
    if (node == nullptr) { return nullptr; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["NodeKind"] = Kind;

    auto sub = hstd::overloaded{
        [&result](std::string const& field, llvm::json::Value value) {
            result[field] = value;
        },
        [&result](std::string const& field, std::string_view value) {
            result[field] = std::string{value.begin(), value.end()};
        },
        [&result](std::string const& field, std::string value) {
            result[field] = value;
        },
        [&result](std::string const& field, Node const* value) {
            result[field] = treeRepr(value);
        },
        [&result](std::string const& field, NodeArray const& value) {
            llvm::json::Array array;
            for (auto const& it : value) { array.push_back(treeRepr(it)); }
            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&result](std::string const& field, Qualifiers const& value) {
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
        [&result](std::string const& field, FunctionRefQual const& value) {
            switch (value) {
                case FunctionRefQual::FrefQualNone: break;
                case FunctionRefQual::FrefQualLValue:
                    result[field] = "FrefQualLValue";
                    break;
                case FunctionRefQual::FrefQualRValue:
                    result[field] = "FrefQualRValue";
                    break;
                default: llvm_unreachable("unreacahable default");
            }
        },
        // [&result](std::string const& field, ModuleName const& value) {

        // },
        [&result](
            std::string const& field, TemplateParamKind const& value) {
            switch (value) {
                case TemplateParamKind::Type:
                    result[field] = "Type";
                    break;
                case TemplateParamKind::NonType:
                    result[field] = "NonType";
                    break;
                case TemplateParamKind::Template:
                    result[field] = "Template";
                    break;
                default: llvm_unreachable("unreacahable default");
            }
        },
        [&result](std::string const& field, SpecialSubKind const& value) {
            switch (value) {
                case SpecialSubKind::allocator:
                    result[field] = "allocator";
                    break;
                case SpecialSubKind::basic_string:
                    result[field] = "basic_string";
                    break;
                case SpecialSubKind::string:
                    result[field] = "string";
                    break;
                case SpecialSubKind::istream:
                    result[field] = "istream";
                    break;
                case SpecialSubKind::ostream:
                    result[field] = "ostream";
                    break;
                case SpecialSubKind::iostream:
                    result[field] = "iostream";
                    break;
                default: llvm_unreachable("unreacahable default");
            }
        },
        [&result](
            std::string const&                           field,
            llvm::itanium_demangle::ReferenceKind const& RK) {
            switch (RK) {
                case llvm::itanium_demangle::ReferenceKind::LValue:
                    result[field] = "LValue";
                    break;
                case llvm::itanium_demangle::ReferenceKind::RValue:
                    result[field] = "RValue";
                    break;
                default: llvm_unreachable("unreacahable default");
            }
        },
    };

    using K = llvm::itanium_demangle::Node::Kind;

#define K_CAST(Name)                                                      \
    break;                                                                \
    }                                                                     \
    case K::K##Name: {                                                    \
        auto cast = const_cast<llvm::itanium_demangle::Name*>(            \
            static_cast<llvm::itanium_demangle::Name const*>(node));

#define K_DEFAULT()                                                       \
    break;                                                                \
    }                                                                     \
    default:


#define K_CASE_END()                                                      \
    break;                                                                \
    }

#define K_SWITCH(Expr)                                                    \
    switch (Expr) {                                                       \
        {

#define K_FIELD(Name, Idx, Type) sub(#Name, match<Idx, Type>(cast));


    using NPtr = Node const*;

    K_SWITCH(node->getKind()) {
        K_CAST(NameType) { K_FIELD(Name, 0, std::string_view); }
        K_CAST(TypeTemplateParamDecl) { K_FIELD(Name, 0, NPtr); }
        K_CAST(TemplateParamPackDecl) { K_FIELD(Param, 0, NPtr); }
        K_CAST(LiteralOperator) { K_FIELD(OpName, 0, NPtr); }
        K_CAST(TemplateArgs) { K_FIELD(Params, 0, NodeArray); }
        K_CAST(PointerType) { K_FIELD(Pointee, 0, NPtr); }
        K_CAST(TemplateArgumentPack) { K_FIELD(Elements, 0, NodeArray); }
        K_CAST(ParameterPackExpansion) { K_FIELD(Child, 0, NPtr); }
        K_CAST(GlobalQualifiedName) { K_FIELD(Child, 0, NPtr); }
        K_CAST(ParameterPack) { K_FIELD(Data, 0, NodeArray); }
        K_CAST(ConversionOperatorType) { K_FIELD(Ty, 0, NPtr); }
        K_CAST(EnableIfAttr) { K_FIELD(Conditions, 0, NodeArray); }
        K_CAST(BoolExpr) { K_FIELD(Value, 0, bool); }
        K_CAST(FunctionParam) { K_FIELD(Number, 0, std::string_view); }
        K_CAST(NodeArrayNode) { K_FIELD(Array, 0, NodeArray); }
        K_CAST(NoexceptSpec) { K_FIELD(E, 0, NPtr); }
        K_CAST(DynamicExceptionSpec) { K_FIELD(Types, 0, NodeArray); }
        K_CAST(PixelVectorType) { K_FIELD(Dimension, 0, NPtr); }
        K_CAST(BinaryFPType) { K_FIELD(Dimension, 0, NPtr); }
        K_CAST(SpecialSubstitution) { K_FIELD(SSK, 0, SpecialSubKind); }
        K_CAST(DtorName) { K_FIELD(Base, 0, NPtr); }
        K_CAST(UnnamedTypeName) { K_FIELD(Count, 0, std::string_view); }
        K_CAST(StructuredBindingName) { K_FIELD(Bindings, 0, NodeArray); }
        K_CAST(SizeofParamPackExpr) { K_FIELD(Pack, 0, NPtr); }
        K_CAST(ThrowExpr) { K_FIELD(Op, 0, NPtr); }
        K_CAST(StringLiteral) { K_FIELD(Type, 0, NPtr); }
        K_CAST(LambdaExpr) { K_FIELD(Type, 0, NPtr); }
        K_CAST(FloatLiteral) { K_FIELD(Type, 0, std::string_view); }
        K_CAST(DoubleLiteral) { K_FIELD(Type, 0, std::string_view); }
        K_CAST(LongDoubleLiteral) { K_FIELD(Type, 0, std::string_view); }


        K_CAST(ExpandedSpecialSubstitution) {
            K_FIELD(SSK, 0, SpecialSubKind);
        }

        K_CAST(DeleteExpr) {
            K_FIELD(Op, 0, NPtr);
            K_FIELD(IsGlobal, 1, bool);
            K_FIELD(IsArray, 2, bool);
        }

        K_CAST(BracedRangeExpr) {
            K_FIELD(First, 0, NPtr);
            K_FIELD(Last, 1, NPtr);
            K_FIELD(Init, 2, NPtr);
        }

        K_CAST(BracedExpr) {
            K_FIELD(Elem, 0, NPtr);
            K_FIELD(Init, 1, NPtr);
            K_FIELD(IsArray, 2, bool);
        }


        K_CAST(PointerToMemberConversionExpr) {
            K_FIELD(Type, 0, NPtr);
            K_FIELD(SubExpr, 1, NPtr);
            K_FIELD(Offset, 2, std::string_view);
        }

        K_CAST(FoldExpr) {
            K_FIELD(IsLeftFold, 0, bool);
            K_FIELD(OperatorName, 1, std::string_view);
            K_FIELD(Pack, 2, NPtr);
            K_FIELD(Init, 3, NPtr);
        }


        K_CAST(NewExpr) {
            K_FIELD(ExprList, 0, NodeArray);
            K_FIELD(Type, 1, NPtr);
            K_FIELD(NodeArray, 2, NodeArray);
            K_FIELD(IsGlobal, 3, bool);
            K_FIELD(IsArray, 4, bool);
        }

        K_CAST(VectorType) {
            K_FIELD(BaseType, 0, NPtr);
            K_FIELD(Dimension, 1, NPtr);
        }

        K_CAST(ArraySubscriptExpr) {
            K_FIELD(Op1, 0, NPtr);
            K_FIELD(Op2, 1, NPtr);
        }

        K_CAST(ConditionalExpr) {
            K_FIELD(Cond, 0, NPtr);
            K_FIELD(Then, 1, NPtr);
            K_FIELD(Else, 2, NPtr);
        }

        K_CAST(SubobjectExpr) {
            K_FIELD(Type, 0, NPtr);
            K_FIELD(SubExpr, 1, NPtr);
            K_FIELD(Offset, 2, std::string_view);
            K_FIELD(UnionSelectors, 3, NodeArray);
            K_FIELD(OnePastTheEnd, 4, bool);
        }


        K_CAST(PostfixExpr) {
            K_FIELD(Child, 0, NPtr);
            K_FIELD(Operator, 1, std::string_view);
        }

        K_CAST(ForwardTemplateReference) {
            sub("Index", cast->Index);
            sub("Ref", cast->Ref);
        }

        K_CAST(SyntheticTemplateParamName) {
            K_FIELD(Kind, 0, TemplateParamKind);
            K_FIELD(Index, 1, unsigned);
        }


        K_CAST(SpecialName) {
            K_FIELD(Special, 0, std::string_view);
            K_FIELD(Child, 1, NPtr);
        }

        K_CAST(PrefixExpr) {
            K_FIELD(Prefix, 0, std::string_view);
            K_FIELD(Child, 1, NPtr);
        }

        K_CAST(ModuleName) {
            sub("Parent", cast->Parent);
            K_FIELD(Name, 1, NPtr);
            K_FIELD(IsPartition, 2, bool);
        }

        K_CAST(ModuleEntity) {
            sub("Module", cast->Module);
            K_FIELD(Name, 1, NPtr);
        }


        K_CAST(NonTypeTemplateParamDecl) {
            K_FIELD(Name, 0, NPtr);
            K_FIELD(Type, 1, NPtr);
        }

        K_CAST(TemplateTemplateParamDecl) {
            K_FIELD(Name, 0, NPtr);
            K_FIELD(Params, 1, NodeArray);
        }

        K_CAST(CtorVtableSpecialName) {
            K_FIELD(FirstType, 0, NPtr);
            K_FIELD(SecondType, 1, NPtr);
        }


        K_CAST(ObjCProtoName) {
            K_FIELD(Ty, 0, NPtr);
            K_FIELD(Protocol, 1, std::string_view);
        }


        K_CAST(PointerToMemberType) {
            K_FIELD(ClassType, 0, NPtr);
            K_FIELD(MemberType, 1, NPtr);
        }

        K_CAST(DotSuffix) {
            K_FIELD(Prefix, 0, NPtr);
            K_FIELD(SUffix, 1, std::string_view);
        }

        K_CAST(VendorExtQualType) {
            K_FIELD(Ty, 0, NPtr);
            K_FIELD(Ext, 1, std::string_view);
            K_FIELD(TA, 2, NPtr);
        }

        K_CAST(AbiTagAttr) {
            K_FIELD(Base, 0, NPtr);
            K_FIELD(Tag, 1, std::string_view);
        }

        K_CAST(BitIntType) {
            K_FIELD(Size, 0, NPtr);
            K_FIELD(Signed, 1, bool);
        }

        K_CAST(ConversionExpr) {
            K_FIELD(Type, 0, NPtr);
            K_FIELD(Expressions, 1, NodeArray);
        }

        K_CAST(EnumLiteral) {
            K_FIELD(Ty, 0, NPtr);
            K_FIELD(Integer, 1, std::string_view);
        }


        K_CAST(LocalName) {
            K_FIELD(Encoding, 0, NPtr);
            K_FIELD(Entity, 1, NPtr);
        }

        K_CAST(PostfixQualifiedType) {
            K_FIELD(Ty, 0, NPtr);
            K_FIELD(Postfix, 1, std::string_view);
        }

        K_CAST(EnclosingExpr) {
            K_FIELD(Prefix, 0, std::string_view);
            K_FIELD(Infix, 1, NPtr);
        }

        K_CAST(ClosureTypeName) {
            K_FIELD(TemplateParams, 0, NodeArray);
            K_FIELD(Requires1, 1, NPtr);
            K_FIELD(Params, 2, NodeArray);
            K_FIELD(Requires2, 3, NPtr);
            K_FIELD(Count, 4, std::string_view);
        }


        K_CAST(QualifiedName) {
            K_FIELD(Qualifier, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
        }

        K_CAST(CastExpr) {
            K_FIELD(CastKind, 0, std::string_view);
            K_FIELD(To, 1, NPtr);
            K_FIELD(From, 2, NPtr);
        }

        K_CAST(ArrayType) {
            K_FIELD(Base, 0, NPtr);
            K_FIELD(Dimension, 1, NPtr);
        }

        K_CAST(MemberExpr) {
            K_FIELD(LHS, 0, NPtr);
            K_FIELD(Kind, 1, std::string_view);
            K_FIELD(RHS, 2, NPtr);
        }

        K_CAST(BinaryExpr) {
            K_FIELD(LHS, 0, NPtr);
            K_FIELD(InfixOperator, 1, std::string_view);
            K_FIELD(RHS, 2, NPtr);
        }

        K_CAST(CallExpr) {
            K_FIELD(Callee, 0, NPtr);
            K_FIELD(Args, 1, NodeArray);
        }


        K_CAST(ElaboratedTypeSpefType) {
            K_FIELD(Kind, 0, std::string_view);
            K_FIELD(Child, 1, NPtr);
        }

        K_CAST(FunctionEncoding) {
            K_FIELD(Ret, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
            K_FIELD(Params, 2, NodeArray);
            K_FIELD(Attrs, 3, NPtr);
            K_FIELD(Requires, 4, NPtr);
            K_FIELD(CVQuals, 5, Qualifiers);
            K_FIELD(RefQual, 6, FunctionRefQual);
        }

        K_CAST(FunctionType) {
            K_FIELD(Ret, 0, NPtr);
            K_FIELD(Params, 1, NodeArray);
            K_FIELD(CVQuals, 2, Qualifiers);
            K_FIELD(RefQual, 3, FunctionRefQual);
            K_FIELD(ExpcetionSpec, 4, NPtr);
        }

        K_CAST(NestedName) {
            K_FIELD(Qual, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
        }

        K_CAST(QualType) {
            K_FIELD(Child, 0, NPtr);
            K_FIELD(Quals, 1, Qualifiers);
        }

        K_CAST(ReferenceType) {
            K_FIELD(Pointee, 0, NPtr);
            K_FIELD(RK, 1, llvm::itanium_demangle::ReferenceKind);
        }


        K_CAST(IntegerLiteral) {
            K_FIELD(Type, 0, std::string_view);
            K_FIELD(Value, 1, std::string_view);
        }

        K_CAST(NameWithTemplateArgs) {
            K_FIELD(Name, 0, NPtr);
            K_FIELD(TemplateArgs, 1, NPtr);
        }

        K_CAST(CtorDtorName) {
            K_FIELD(Basename, 0, NPtr);
            K_FIELD(IsDtor, 1, bool);
            K_FIELD(Variant, 2, int);
        }

        K_CAST(InitListExpr) {
            K_FIELD(Ty, 0, NPtr);
            K_FIELD(Inits, 1, NodeArray);
        }

        K_CAST(TemplateParamQualifiedArg) {
            K_FIELD(Param, 0, NPtr);
            K_FIELD(Arg, 1, NPtr);
        }

        K_CAST(ConstrainedTypeTemplateParamDecl) {
            K_FIELD(Constraint, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
        }


        K_CAST(ExplicitObjectParameter) { K_FIELD(Base, 0, NPtr); }
        K_CAST(NestedRequirement) { K_FIELD(Constraint, 0, NPtr); }
        K_CAST(TypeRequirement) { K_FIELD(Type, 0, NPtr); }
        K_CAST(MemberLikeFriendName) {
            K_FIELD(Qual, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
        }
        K_CAST(RequiresExpr) {
            K_FIELD(Parameters, 0, NodeArray);
            K_FIELD(Requirements, 1, NodeArray);
        }
        K_CAST(ExprRequirement) {
            K_FIELD(Expr, 0, NPtr);
            K_FIELD(IsNoexcept, 1, bool);
            K_FIELD(TypeConstraint, 2, NPtr);
        }

        K_CAST(TransformedType) {
            K_FIELD(Transform, 0, std::string_view);
            K_FIELD(BaseType, 1, NPtr);
        }

        K_CASE_END()
        // K_DEFAULT() {
        //     std::string msg = std::format("ERR:'{}'", Kind);
        //     llvm_unreachable(msg.c_str());
        //     break;
        // }
    }
}

return result;
}

ParsedBinaryName parseBinary(std::string const& name) {
    Demangler         Parser(name.data(), name.data() + name.size());
    Node*             AST  = Parser.parse();
    llvm::json::Value repr = treeRepr(AST);
}
