#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/Regex.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/ItaniumDemangle.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <unordered_map>
#include <boost/describe.hpp>
#include <llvm/ADT/Hashing.h>
#include <hstd/system/Formatter.hpp>
#include <algorithm>
#include <absl/hash/hash.h>
#include <fstream>
#include <hstd/system/aux_utils.hpp>
#include <execution>
#include <llvm/ADT/SmallBitVector.h>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Map.hpp>

#include <hstd/ext/perfetto_aux.hpp>

#ifdef ORG_USE_PERFETTO

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("llvm").SetDescription("LLVM code execution time"),
    perfetto::Category("sql").SetDescription("SQLite data insertion"),
    perfetto::Category("transform").SetDescription("Data transform time"),
    perfetto::Category("main").SetDescription("Top execution steps")
    //
);


#endif

#define NO_COVERAGE                                                       \
    __attribute__((no_sanitize("coverage", "address", "thread")))


#pragma clang diagnostic error "-Wswitch"

#include <hstd/ext/perfetto_aux_impl_template.hpp>

namespace fs = std::filesystem;
using namespace llvm::coverage;
using namespace llvm::itanium_demangle;
using namespace hstd;

enum class KindProxy
{
#define NODE(NodeKind) NodeKind,
#include <llvm/Demangle/ItaniumNodes.def>
};

BOOST_DESCRIBE_ENUM_BEGIN(KindProxy)
#define NODE(NodeKind) BOOST_DESCRIBE_ENUM_ENTRY(KindProxy, NodeKind)
#include <llvm/Demangle/ItaniumNodes.def>
BOOST_DESCRIBE_ENUM_END()

namespace llvm::coverage {
BOOST_DESCRIBE_STRUCT(
    CoverageSegment,
    (),
    (Line, Col, Count, HasCount, IsRegionEntry, IsGapRegion));
BOOST_DESCRIBE_STRUCT(ExpansionRecord, (), (FileID));
BOOST_DESCRIBE_STRUCT(
    FunctionRecord,
    (),
    (Name,
     Filenames,
     CountedRegions,
     CountedBranchRegions,
     MCDCRecords,
     ExecutionCount));

BOOST_DESCRIBE_STRUCT(
    CounterMappingRegion,
    (),
    (Count,
     FalseCount,
     MCDCParams,
     FileID,
     ExpandedFileID,
     LineStart,
     ColumnStart,
     LineEnd,
     ColumnEnd,
     Kind));

BOOST_DESCRIBE_STRUCT(
    CountedRegion,
    (CounterMappingRegion),
    (ExecutionCount, FalseExecutionCount, Folded));

BOOST_DESCRIBE_STRUCT(
    CounterMappingRegion::MCDCParameters,
    (),
    (BitmapIdx, NumConditions, ID, TrueID, FalseID));

BOOST_DESCRIBE_ENUM(
    CounterMappingRegion::RegionKind,
    CodeRegion,
    ExpansionRegion,
    SkippedRegion,
    GapRegion,
    BranchRegion,
    MCDCDecisionRegion,
    MCDCBranchRegion);


}


NO_COVERAGE std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

NO_COVERAGE void llvm_unreachable_f(std::string const& msg) {
    llvm_unreachable(msg.c_str());
}


NO_COVERAGE void CreateTables(SQLite::Database& db) {
    auto path = fs::path{__FILE__}.parent_path() / "profdata_merger.sql";
    std::string sql = read_file(path);
    db.exec(sql);
}

// std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
//     return std::cerr << std::format("[profmerge:{}] {}\n", line, msg);
// }

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
        [&result](std::string const& field, ReferenceKind const& RK) {
            switch (RK) {
                case ReferenceKind::LValue:
                    result[field] = "LValue";
                    break;
                case ReferenceKind::RValue:
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
            K_FIELD(RK, 1, ReferenceKind);
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


template <>
struct JsonSerde<Counter> {
    NO_COVERAGE static json to_json(Counter const& cnt) { return json(); }
};

template <>
struct JsonSerde<CountedRegion::MCDCParameters> {
    NO_COVERAGE static json to_json(
        CountedRegion::MCDCParameters const& cnt) {
        return json();
    }
};

template <>
struct JsonSerde<llvm::json::Object> {
    NO_COVERAGE static json to_json(llvm::json::Object const& obj);
};


template <>
struct JsonSerde<llvm::json::Array> {
    NO_COVERAGE static json to_json(llvm::json::Array const& obj);
};

template <>
struct JsonSerde<llvm::json::Value> {
    NO_COVERAGE static json to_json(llvm::json::Value const& value) {
        using K = llvm::json::Value::Kind;
        switch (value.kind()) {
            case K::Null: return json();
            case K::Number: return value.getAsNumber().value();
            case K::String: return value.getAsString().value();
            case K::Boolean: return value.getAsBoolean().value();
            case K::Array:
                return JsonSerde<llvm::json::Array>::to_json(
                    *value.getAsArray());
            case K::Object:
                return JsonSerde<llvm::json::Object>::to_json(
                    *value.getAsObject());
        }
    }
};


NO_COVERAGE json
    JsonSerde<llvm::json::Array>::to_json(const llvm::json::Array& obj) {
    json result = json::array();
    for (auto const& it : obj) {
        result.push_back(JsonSerde<llvm::json::Value>::to_json(it));
    }
    return result;
}


NO_COVERAGE json
    JsonSerde<llvm::json::Object>::to_json(const llvm::json::Object& obj) {
    json result = json::object();
    for (auto const& field : obj) {
        result[field.first.str()] = JsonSerde<llvm::json::Value>::to_json(
            field.second);
    }
    return result;
}


template <>
struct JsonSerde<FunctionRecord> {
    static json to_json(FunctionRecord const& func) {
        json result = JsonSerdeDescribedRecordBase<
            FunctionRecord>::to_json(func);

        result["DemangledName"] = llvm::demangle(func.Name);

        Demangler Parser(
            func.Name.data(), func.Name.data() + func.Name.length());

        Node*             AST  = Parser.parse();
        llvm::json::Value repr = treeRepr(AST);
        result["ParsedName"] = JsonSerde<llvm::json::Value>::to_json(repr);

        return result;
    }

    // static FunctionRecord from_json(json const& func) {
    //     return JsonSerdeDescribedRecordBase<FunctionRecord>::from_json(
    //         func);
    // }
};

template <>
struct JsonSerde<MCDCRecord> {
    static json to_json(MCDCRecord const& cnt) { return json(); }
};


template <>
struct JsonSerde<CoverageMapping> {
    NO_COVERAGE static json to_json(CoverageMapping const& map) {
        json result = json::object();
        for (auto const& it : map.getCoveredFunctions()) {
            result["functions"].push_back(to_json_eval(it));
        }
        return result;
    }
};


NO_COVERAGE static void loadInput(
    std::string const&     Filename,
    std::string const&     ProfiledBinary,
    llvm::InstrProfWriter* Writer) {

    auto FS          = llvm::vfs::getRealFileSystem();
    auto ReaderOrErr = llvm::InstrProfReader::create(Filename, *FS);
    if (llvm::Error E = ReaderOrErr.takeError()) {
        auto [ErrCode, Msg] = llvm::InstrProfError::take(std::move(E));
        if (ErrCode != llvm::instrprof_error::empty_raw_profile) {
            assert(false);
        }
        return;
    }

    auto Reader = std::move(ReaderOrErr.get());
    for (auto& I : *Reader) {
        const llvm::StringRef FuncName = I.Name;
        bool                  Reported = false;
        Writer->addRecord(std::move(I), 1, [&](llvm::Error E) {
            LOG(INFO) << std::format("{}", toString(std::move(E)));
        });
    }

    if (Reader->hasTemporalProfile()) {
        auto& Traces = Reader->getTemporalProfTraces();
        if (!Traces.empty()) {
            Writer->addTemporalProfileTraces(
                Traces, Reader->getTemporalProfTraceStreamSize());
        }
    }

    if (Reader->hasError()) {
        if (llvm::Error E = Reader->getError()) {
            LOG(INFO) << std::format(
                "{} {}", toString(std::move(E)), Filename);
            return;
        }
    }

    std::vector<llvm::object::BuildID> BinaryIds;
    if (llvm::Error E = Reader->readBinaryIds(BinaryIds)) {
        LOG(INFO) << std::format(
            "{} {}", toString(std::move(E)), Filename);
        return;
    }

    Writer->addBinaryIds(BinaryIds);
}

struct CoverageMappingLyt {
    llvm::DenseMap<size_t, llvm::DenseSet<size_t>> RecordProvenance;
    std::vector<FunctionRecord>                    Functions;
    llvm::DenseMap<size_t, llvm::SmallVector<unsigned, 0>>
        FilenameHash2RecordIndices;
    std::vector<std::pair<std::string, uint64_t>> FuncHashMismatches;
};

static_assert(sizeof(CoverageMappingLyt) == sizeof(CoverageMapping));

CoverageMappingLyt const* toCoverageMappingLyt(
    CoverageMapping const* Mapping) {
    return reinterpret_cast<CoverageMappingLyt const*>(Mapping);
}

NO_COVERAGE llvm::ArrayRef<unsigned> getImpreciseRecordIndicesForFilename(
    CoverageMapping const& Mapping,
    llvm::StringRef        Filename) {
    size_t FilenameHash = hash_value(Filename);
    auto   RecordIt     = toCoverageMappingLyt(&Mapping)
                        ->FilenameHash2RecordIndices.find(FilenameHash);
    if (RecordIt
        == toCoverageMappingLyt(&Mapping)
               ->FilenameHash2RecordIndices.end()) {
        return {};
    }
    return RecordIt->second;
}

NO_COVERAGE static std::optional<unsigned> findMainViewFileID(
    const FunctionRecord& Function) {
    llvm::SmallBitVector IsNotExpandedFile(
        Function.Filenames.size(), true);
    for (const auto& CR : Function.CountedRegions) {
        if (CR.Kind == CounterMappingRegion::ExpansionRegion) {
            IsNotExpandedFile[CR.ExpandedFileID] = false;
        }
    }
    int I = IsNotExpandedFile.find_first();
    if (I == -1) { return std::nullopt; }
    return I;
}

NO_COVERAGE static std::optional<unsigned> findMainViewFileID(
    llvm::StringRef       SourceFile,
    const FunctionRecord& Function) {
    std::optional<unsigned> I = findMainViewFileID(Function);
    if (I && SourceFile == Function.Filenames[*I]) { return I; }
    return std::nullopt;
}

NO_COVERAGE static llvm::SmallBitVector gatherFileIDs(
    llvm::StringRef       SourceFile,
    const FunctionRecord& Function) {
    llvm::SmallBitVector FilenameEquivalence(
        Function.Filenames.size(), false);
    for (unsigned I = 0, E = Function.Filenames.size(); I < E; ++I) {
        if (SourceFile == Function.Filenames[I]) {
            FilenameEquivalence[I] = true;
        }
    }
    return FilenameEquivalence;
}

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

struct queries {
    SQLite::Statement file_region;
    SQLite::Statement context;
    SQLite::Statement func;
    SQLite::Statement file;

    queries(SQLite::Database& db)
        : // ---
        file_region(
            db,
            SqlInsert(
                "CovFileRegion",
                {
                    "Id",                  // 1
                    "Context",             // 2
                    "ExecutionCount",      // 3
                    "FalseExecutionCount", // 4
                    "Folded",              // 5
                    "LineStart",           // 6
                    "ColumnStart",         // 7
                    "LineEnd",             // 8
                    "ColumnEnd",           // 9
                    "RegionKind",          // 10
                    "File",                // 11
                    "Function",            // 12
                    "ExpandedFrom",        // 13
                }))
        ,
        // ---
        context(
            db,
            SqlInsert(
                "CovContext",
                {
                    "Id",      // 1
                    "Name",    // 2
                    "Parent",  // 3
                    "Profile", // 4
                    "Params",  // 5
                    "Binary",  // 6
                }))
        ,
        // ---
        func(
            db,
            SqlInsert(
                "CovFunction",
                {
                    "Id",        // 1
                    "Mangled",   // 2
                    "Demangled", // 3
                    "Parsed",    // 4
                }))
        ,
        // ---
        file(
            db,
            SqlInsert(
                "CovFile",
                {
                    "Id",   // 1
                    "Path", // 2
                })) {}
};

struct CountedRegionHasher {
    size_t operator()(const CounterMappingRegion& region) const {
        return llvm::hash_combine(
            std::hash<unsigned>()(region.FileID),
            std::hash<unsigned>()(region.ExpandedFileID),
            std::hash<unsigned>()(region.LineStart),
            std::hash<unsigned>()(region.ColumnStart),
            std::hash<unsigned>()(region.LineEnd),
            std::hash<unsigned>()(region.ColumnEnd),
            std::hash<int>()(static_cast<int>(region.Kind)));
    }
};


struct CountedRegionComparator {
    size_t operator()(
        const CounterMappingRegion& lhs,
        const CounterMappingRegion& rhs) const {
        return lhs.FileID == rhs.FileID
            && lhs.ExpandedFileID == rhs.ExpandedFileID
            && lhs.LineStart == rhs.LineStart
            && lhs.ColumnStart == rhs.ColumnStart
            && lhs.LineEnd == rhs.LineEnd && lhs.ColumnEnd == rhs.ColumnEnd
            && lhs.Kind == rhs.Kind;
    }
};


struct FileSpan {
    unsigned int LineStart{};
    unsigned int LineEnd{};
    unsigned int ColStart{};
    unsigned int ColEnd{};
};

struct FileSpanHasher {
    size_t operator()(const FileSpan& region) const {
        return llvm::hash_combine(
            region.LineStart,
            region.LineEnd,
            region.ColStart,
            region.ColEnd);
    }
};


struct FileSpanComparator {
    size_t operator()(const FileSpan& lhs, const FileSpan& rhs) const {
        return lhs.LineStart == rhs.LineStart //
            && lhs.ColStart == rhs.ColStart   //
            && lhs.LineEnd == rhs.LineEnd     //
            && lhs.ColEnd == rhs.ColEnd;
    }
};

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

struct db_build_ctx {
    /// \brief DB ID generator for individual coverage contexts from the
    /// coverage configuration file.
    int                                  context_id{};
    int                                  instantiation_id{};
    std::unordered_map<std::string, int> function_ids{};
    /// \brief Absolute file path to the file ID.
    ///
    /// LLVM coverage contains `FileID` and `ExpandedFileID` fields in the
    /// counted regions. These fields are local to individual function
    /// records and are used for both real files and for macro expansion
    /// IDs pointing to the same file. A function with macro expansion
    /// might have multiple duplicate file names with different IDs.
    ///
    /// DB build uses absolute path to the file as a unique identifier for
    /// the file and is not directly mapped to the LLVM coverage file ID.
    std::unordered_map<std::string, int> file_ids{};
    /// \brief DB ID generator for coverage file regions
    int region_counter{};

    /// \brief Cache for the JSON value demangling.
    std::unordered_map<std::string, llvm::json::Value>
        demangled_json_dumps{};

    /// \brief List of regexps to filter out from the input file coverage.
    /// Has secondary check order compared to blacklist. For a file to pass
    /// it must match the whitelist and then not fail on the blacklist.
    std::vector<llvm::Regex> file_blacklist;
    /// \brief List of regexps to allow for for the coverage extractor. Has
    /// first check order compared to blacklist.
    std::vector<llvm::Regex> file_whitelist;

    /// \brief Get JSON dump of the demangled function record name.
    NO_COVERAGE std::string getDemangledJson(FunctionRecord const& f) {
        if (demangled_json_dumps.contains(f.Name)) {
            return llvm::formatv("{0}", demangled_json_dumps.at(f.Name));
        } else {
            int         offset = findSymbolNamePosition(f.Name);
            std::string name   = f.Name.substr(offset);
            Demangler   Parser(name.data(), name.data() + name.length());

            Node* AST = Parser.parse();

            // In some cases LLVM fails to demangle itanium names for
            // lambdas and some other symbols, like
            // `SemOrgApi.cpp:_ZZNK3sem7Subtree14getTimePeriodsE6IntSetINS0_6Period4KindEEENK3$_0clINS0_8Property17ExportLatexHeaderEEEDaRKT_`
            // so this heuristics is used to give more information on the
            // failure -- `cxx-filt` also fails to process this, so it
            // seems to be a LLVM issue.
            if (AST == nullptr && name.contains("$_")
                && name.contains("cl") && name.contains('K')) {
                llvm::json::Object repr;
                repr["NodeKind"] = "LambdaDemangleFail";
                return llvm::formatv(
                    "{0}", llvm::json::Value{std::move(repr)});
            } else {
                llvm::json::Value repr = treeRepr(AST);
                demangled_json_dumps.insert({f.Name, repr});
                return llvm::formatv("{0}", repr);
            }
        }
    }


    /// \brief Check the file against provided white/black list of
    /// mappings.
    NO_COVERAGE bool file_matches(
        std::string const& path,
        std::string&       debug) const {
        bool result = false;
        if (file_whitelist.empty()) {
            throw std::logic_error(
                "file match whitelist cannot be empty -- specify at least "
                "`.*` as a pattern");
        }

        for (auto const& r : file_whitelist) {
            if (r.match(path)) {
                result = true;
                break;
            }
        }

        if (!result) {
            debug = "no matching whitelist";
            return false;
        }

        for (auto const& r : llvm::enumerate(file_blacklist)) {
            if (r.value().match(path)) {
                debug = std::format("blacklisted by #{}", r.index());
                return false;
            }
        }

        return result;
    }

    NO_COVERAGE int get_file_id(std::string const& path, queries& q) {
        if (!file_ids.contains(path)) {
            int id         = file_ids.size();
            file_ids[path] = id;

            q.file.bind(1, id);
            q.file.bind(2, path);
            q.file.exec();
            q.file.reset();
        }
        return file_ids.at(path);
    }
};

/// \brief Get an ID for the function from a database, insert a new entry
/// in DB if needed.
///
/// Functions are mapped based on their mangled names and are shared across
/// all execution contexts and all executed files.
NO_COVERAGE int get_function_id(
    FunctionRecord const& f,
    queries&              q,
    db_build_ctx&         ctx) {
    std::string readeable = llvm::demangle(f.Name);


    int function_id = -1;

    if (ctx.function_ids.contains(f.Name)) {
        function_id = ctx.function_ids.at(f.Name);
    } else {
        function_id              = ctx.function_ids.size();
        ctx.function_ids[f.Name] = function_id;

        q.func.bind(1, function_id);
        q.func.bind(2, f.Name); // mangled
        char const* demangled = llvm::itaniumDemangle(f.Name);
        if (demangled == nullptr) {
            q.func.bind(3, f.Name);
        } else {
            q.func.bind(3, demangled);
        }
        q.func.bind(4, ctx.getDemangledJson(f));
        q.func.exec();
        q.func.reset();
    }

    return function_id;
}


template <typename T, typename FormatContext>
NO_COVERAGE auto fmt_ctx_field(
    std::string const& field_name,
    T const&           field_value,
    FormatContext&     ctx) {
    fmt_ctx(" ", ctx);
    fmt_ctx(field_name, ctx);
    fmt_ctx(" = ", ctx);
    return fmt_ctx(field_value, ctx);
}

template <>
struct std::formatter<CountedRegion> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const CountedRegion& p, FormatContext& ctx) const {
        fmt_ctx("{", ctx);
        fmt_ctx_field("ExecutionCount", p.ExecutionCount, ctx);
        fmt_ctx_field("FalseExecutionCount", p.FalseExecutionCount, ctx);
        fmt_ctx_field(
            "Loc",
            fmt("[{}:{}..{}:{}]",
                p.LineStart,
                p.ColumnStart,
                p.LineEnd,
                p.ColumnEnd),
            ctx);
        fmt_ctx_field("FileId", p.FileID, ctx);
        fmt_ctx_field("ExpandedFileID", p.ExpandedFileID, ctx);
        fmt_ctx_field("Kind", p.Kind, ctx);
        return fmt_ctx("}", ctx);
    }
};

template <>
struct std::formatter<CoverageSegment> : std::formatter<std::string> {
    template <typename FormatContext>
    NO_COVERAGE auto format(const CoverageSegment& p, FormatContext& ctx)
        const {
        fmt_ctx("{", ctx);
        fmt_ctx_field("Line", p.Line, ctx);
        fmt_ctx_field("Col", p.Col, ctx);
        fmt_ctx_field("Count", p.Count, ctx);
        fmt_ctx_field("HasCount", p.HasCount, ctx);
        fmt_ctx_field("IsRegionEntry", p.IsRegionEntry, ctx);
        fmt_ctx_field("IsGapRegion", p.IsGapRegion, ctx);
        return fmt_ctx(" }", ctx);
    }
};


NO_COVERAGE void add_file_regions(
    CoverageMapping const& Mapping,
    std::string const&     Filename,
    queries&               q,
    db_build_ctx&          ctx) {

    // Look up the function records in the given file. Due to hash
    // collisions on the filename, we may get back some records that are
    // not in the file.
    llvm::ArrayRef<unsigned>
        RecordIndices = getImpreciseRecordIndicesForFilename(
            Mapping, Filename);
    auto Access = toCoverageMappingLyt(&Mapping);
    for (unsigned RecordIndex : RecordIndices) {
        const FunctionRecord& Function = Access->Functions[RecordIndex];
        auto MainFileID = findMainViewFileID(Filename, Function);
        auto FileIDs    = gatherFileIDs(Filename, Function);
        // `ExpandedFileID` in the expansion regions points to the file ID
        // of the macro body region. This map retains information on which
        // segment index introduced a new expanded file ID.
        UnorderedMap<int, int> expanded_from;

        bool dbg = false && Function.Name.contains("parseSubtree")
                && !(Function.Name.contains("parseSubtreeLogbook")
                     || Function.Name.contains("parseSubtreeProperties")
                     || Function.Name.contains("parseSubtreeTodo")
                     || Function.Name.contains("parseSubtreeTitle")
                     || Function.Name.contains("parseSubtreeUrgency")
                     || Function.Name.contains("parseSubtreeDrawer")
                     || Function.Name.contains("parseSubtreeTags")
                     || Function.Name.contains("parseSubtreeTimes")
                     || Function.Name.contains("parseSubtreeCompletion"));

        auto reg = [&](int region_index) -> CountedRegion const& {
            return Function.CountedRegions.at(region_index);
        };

        for (const auto& it : llvm::enumerate(Function.CountedRegions)) {
            if (it.value().Kind
                == CounterMappingRegion::RegionKind::ExpansionRegion) {
                expanded_from[it.value().ExpandedFileID] = it.index();
            }
        }

        auto getOriginalIndex = [&](int region) -> Opt<int> {
            if (expanded_from.contains(reg(region).FileID)) {
                // while (expanded_from.contains(reg(region).FileID)) {
                region = expanded_from.at(reg(region).FileID);
                // }
                return region;
            } else {
                return std::nullopt;
            }
        };

        // Map region indices for the function to the generated IDs. Each
        // function has its own, separate set of counted regions, so this
        // mapping is local for each function processing.
        UnorderedMap<int, int> file_region_ids;

        std::function<int(int)> addRegion;
        addRegion = [&](int region_index) -> int {
            CountedRegion const& r = reg(region_index);

            ++ctx.region_counter;
            int region_id = ctx.region_counter;

            Opt<int> expanded_from_id = std::nullopt;
            // <<expanded_from>>
            if (expanded_from.contains(r.FileID)) {
                auto original_index = getOriginalIndex(region_index);
                if (original_index.has_value()) {
                    auto id = *original_index;
                    // Protection against segments arriving out of order
                    // due to macro expansion magicks. If the region
                    // already mapped, existing ID must be reused.
                    if (file_region_ids.contains(id)) {
                        expanded_from_id = file_region_ids.at(id);
                    } else {
                        if (dbg) {
                            LOG(INFO)
                                << fmt("recursively adding region {} {} "
                                       ".contains({}) -> {}",
                                       id,
                                       file_region_ids,
                                       id,
                                       file_region_ids.contains(id));
                        }

                        expanded_from_id = addRegion(id);
                    }
                }
            }

            // Passing LLVM information directly
            q.file_region.bind(1, region_id);
            q.file_region.bind(2, ctx.context_id);
            q.file_region.bind(3, static_cast<int>(r.ExecutionCount));
            q.file_region.bind(4, static_cast<int>(r.FalseExecutionCount));
            q.file_region.bind(5, r.Folded);
            q.file_region.bind(6, static_cast<int>(r.LineStart));
            q.file_region.bind(7, static_cast<int>(r.ColumnStart));
            q.file_region.bind(8, static_cast<int>(r.LineEnd));
            q.file_region.bind(9, static_cast<int>(r.ColumnEnd));
            q.file_region.bind(10, r.Kind);
            q.file_region.bind(
                11, ctx.get_file_id(Function.Filenames.at(r.FileID), q));
            // Addition to the LLVM info -- the function which contains the
            // segment
            q.file_region.bind(12, get_function_id(Function, q, ctx));
            // And optionally a location that was expanded to this segment
            // (for macro body).
            if (expanded_from_id) {
                q.file_region.bind(13, *expanded_from_id);
            }

            q.file_region.exec();
            q.file_region.reset();

            if (dbg) {
                LOG(INFO) << fmt(
                    "add region [{} -> {}] {} ",
                    region_index,
                    region_id,
                    r);
            }

            file_region_ids[region_index] = region_id;
            return region_id;
        };


        for (const auto& it : llvm::enumerate(Function.CountedRegions)) {
            if (FileIDs.test(it.value().FileID)) {
                addRegion(it.index());
            } else {
                if (dbg) {
                    LOG(INFO) << fmt(
                        "skip region [{}] {}", it.index(), it.value());
                }
            }
        }
    }
}

template <typename T>
NO_COVERAGE std::string format_range(T begin, T end) {
    bool        isFirst = true;
    std::string result  = "[";
    while (begin != end) {
        if (isFirst) {
            isFirst = false;
        } else {
            result += ", ";
        }
        result += std::format("{}", *begin);
        ++begin;
    }

    result += "]";
    return result;
}

NO_COVERAGE void add_file(
    CoverageMapping const* mapping,
    llvm::StringRef        file,
    queries&               q,
    db_build_ctx&          ctx) {
    __perf_trace("sql", "File coverage data");
    int file_id = ctx.get_file_id(file.str(), q);

    add_file_regions(*mapping, file.str(), q, ctx);
}

struct ProfdataCookie {
    std::string                test_binary;
    std::string                test_name;
    std::optional<std::string> test_class = std::nullopt;
    std::string                test_profile;
    json                       test_params;

    DESC_FIELDS(
        ProfdataCookie,
        (test_binary, test_name, test_class, test_profile, test_params));
};

static_assert(DescribedRecord<ProfdataCookie>, "dbg");

NO_COVERAGE void add_context(
    ProfdataCookie const& run,
    queries&              q,
    db_build_ctx&         ctx) {
    ++ctx.context_id;

    q.context.bind(1, ctx.context_id);
    q.context.bind(2, run.test_name);
    if (run.test_class) {
        q.context.bind(3, run.test_class.value());
    } else {
        q.context.bind(3, nullptr);
    }
    q.context.bind(4, run.test_profile);
    q.context.bind(5, run.test_params.dump());
    q.context.bind(6, run.test_binary);

    q.context.exec();
    q.context.reset();
}

NO_COVERAGE llvm::MD5::MD5Result getMD5Digest(
    const std::string& str1,
    const std::string& str2) {
    llvm::MD5 hash;
    hash.update(llvm::ArrayRef<uint8_t>(
        reinterpret_cast<const uint8_t*>(str1.data()), str1.size()));
    hash.update(llvm::ArrayRef<uint8_t>(
        reinterpret_cast<const uint8_t*>(str2.data()), str2.size()));
    llvm::MD5::MD5Result result;
    hash.final(result);
    return result;
}

NO_COVERAGE std::shared_ptr<CoverageMapping> get_coverage_mapping(
    std::string const& coverage_path,
    std::string const& binary_path) {
    __perf_trace(
        "llvm",
        "Profraw to coverage mapping",
        "coverage_path",
        coverage_path,
        "binary_path",
        binary_path);

    llvm::InstrProfWriter Writer;
    {
        __perf_trace("llvm", "Load raw profile coverage");
        loadInput(coverage_path, binary_path, &Writer);
        LOG(INFO) << std::format(
            "Loaded {} binary {}", coverage_path, binary_path);
    }

    std::string tmp_path = std::format(
        "/tmp/{}.profdata",
        getMD5Digest(coverage_path, binary_path).digest().str().str());

    std::vector<llvm::StringRef> ObjectFilenames;
    ObjectFilenames.push_back(binary_path);
    {
        __perf_trace("llvm", "Write converted profile data");
        std::error_code      EC;
        llvm::raw_fd_ostream Output(tmp_path, EC, llvm::sys::fs::OF_None);

        if (EC) {
            throw std::domain_error(std::format(
                "Error while creating output stream {}", EC.message()));
        }

        if (llvm::Error E = Writer.write(Output)) {
            throw std::domain_error(
                std::format("Failed write: {}", toString(std::move(E))));
        }
    }

    LOGIC_ASSERTION_CHECK(fs::exists(tmp_path), "{}", tmp_path);

    {
        __perf_trace("llvm", "Load coverage profile data");
        auto FS = llvm::vfs::getRealFileSystem();
        llvm::Expected<std::shared_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (llvm::Error E = mapping_or_err.takeError()) {
            throw std::domain_error(std::format(
                "Failed to load profdata {} from {}",
                toString(std::move(E)),
                tmp_path));
        }

        fs::remove(tmp_path);

        return std::move(mapping_or_err.get());
    }
}

struct ProfdataCLIConfig {
    std::string                coverage;
    std::string                coverage_db;
    std::optional<std::string> perf_trace     = std::nullopt;
    std::vector<std::string>   file_whitelist = {".*"};
    std::vector<std::string>   file_blacklist;
    std::optional<std::string> debug_file            = std::nullopt;
    std::optional<std::string> coverage_mapping_dump = std::nullopt;
    int                        run_group_batch_size  = 8;

    DESC_FIELDS(
        ProfdataCLIConfig,
        (coverage,
         coverage_db,
         perf_trace,
         file_whitelist,
         file_blacklist,
         debug_file,
         coverage_mapping_dump));
};

struct ProfdataFullProfile {
    std::vector<ProfdataCookie> runs;
    DESC_FIELDS(ProfdataFullProfile, (runs));
};

struct ProfdataRun {
    int            index;
    ProfdataCookie run;
    DESC_FIELDS(ProfdataRun, (index, run));
};


const char* __asan_default_options() { return "detect_leaks=0"; }

void process_runs(
    Vec<ProfdataRun> const&  runs,
    ProfdataCLIConfig const& config,
    int                      full_run_size,
    std::function<void()>    flush_debug,
    db_build_ctx&            ctx,
    queries&                 q,
    json&                    debug,
    SQLite::Database&        db) {

    UnorderedMap<
        std::pair<std::string, std::string>,
        std::shared_ptr<CoverageMapping>,
        llvm::pair_hash<std::string, std::string>>
        coverage_map;

    {
        __perf_trace("llvm", "Parallel convert of coverage data");
        std::vector<std::pair<std::string, std::string>> paths{};

        for (auto const& run : runs) {
            paths.push_back({run.run.test_profile, run.run.test_binary});
        }

        std::mutex coverage_mutex;

        std::for_each(
            std::execution::par,
            paths.begin(),
            paths.end(),
            [&](const std::pair<std::string, std::string>& p) {
                __perf_trace("llvm", "Get coverage mapping task");
                auto coverage = get_coverage_mapping(p.first, p.second);
                std::scoped_lock lock{coverage_mutex};
                coverage_map.emplace(p, std::move(coverage));
            });
    }


    if (config.coverage_mapping_dump) {
        LOG(INFO) << fmt(
            "Coverage mapping dump to {}",
            config.coverage_mapping_dump.value());
    }

    for (auto const& run : runs) {
        __perf_trace("main", "Insert run data");
        finally{flush_debug};
        LOG(INFO) << fmt(
            "[{}/{}] Insert run data profile={} binary={}",
            run.index,
            full_run_size,
            run.run.test_profile,
            run.run.test_binary);

        add_context(run.run, q, ctx);

        std::shared_ptr<CoverageMapping> mapping = coverage_map.at(
            {run.run.test_profile, run.run.test_binary});


        if (mapping.get() == nullptr) {
            throw std::logic_error(
                fmt("Failed to load coverage mapping profile={} binary={}",
                    run.run.test_profile,
                    run.run.test_binary));
        }

        if (config.coverage_mapping_dump) {
            auto j = to_json_eval(*mapping);
            auto path //
                = fs::path{*config.coverage_mapping_dump}
                / fmt("coverage_mapping_{}.json", run.index);

            LOG(INFO) << fmt("coverage-mapping-dump={}", path);
            writeFile(path, j.dump(2));
        }

        json j_run = json::object();
        {
            __perf_trace("sql", "Full coverage run info");
            SQLite::Transaction transaction{db};
            {
                __perf_trace("sql", "Covered files");
                json j_files = json::object();
                for (auto const& file : mapping->getUniqueSourceFiles()) {
                    std::string debug;
                    if (!ctx.file_matches(file.str(), debug)) {
                        j_files["skipped"].push_back(json::object({
                            {"file", file.str()},
                            {"reason", debug},
                        }));
                        continue;
                    }
                    __perf_trace("sql", "Add file", "File", file.str());
                    add_file(mapping.get(), file, q, ctx);
                }

                j_run["covered_files"] = j_files;
            }

            transaction.commit();
        }


        debug["runs"].push_back(j_run);
    }
}

NO_COVERAGE int main(int argc, char** argv) {
    json debug = json::object();

    if (argc != 2) {
        throw std::logic_error(
            "Expected single positional argument -- JSON literal "
            "with parameters or absolute path to the JSON "
            "configuration file.");
    }

    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        json_parameters = read_file(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    auto config = JsonSerde<ProfdataCLIConfig>::from_json(
        json::parse(json_parameters));


    auto flush_debug = [&]() {
        if (config.debug_file) {
            fs::path      out_path{config.debug_file.value()};
            std::ofstream os{out_path};
            os << debug.dump();
        }
    };

    finally{flush_debug};


    LOG(INFO) << std::format(
        "Using test summary file {}", config.coverage);

    if (config.debug_file) {
        LOG(INFO) << std::format(
            "Debug file enabled {}", config.debug_file);
    }

    auto summary = JsonSerde<ProfdataFullProfile>::from_json(
        json::parse(read_file(config.coverage)));

    fs::path db_file{config.coverage_db};

#ifdef ORG_USE_PERFETTO
    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (config.perf_trace) {
        perfetto_session = StartProcessTracing("profdata_merger");
    }
#endif

    if (fs::exists(db_file)) { fs::remove(db_file); }

    SQLite::Database db{
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
    CreateTables(db);
    queries q{db};

    db_build_ctx ctx;
    auto         FS = llvm::vfs::getRealFileSystem();


    auto get_regex_list = [](std::vector<std::string> const& list)
        -> std::vector<llvm::Regex> {
        std::vector<llvm::Regex> result;

        for (auto const& filter : list) {
            llvm::Regex r{filter};
            std::string error;
            if (r.isValid(error)) {
                result.push_back(std::move(r));
            } else {
                throw std::domain_error(
                    "Failed to compile regex for " + filter + ": "
                    + error);
            }
        }

        return result;
    };

    ctx.file_blacklist = get_regex_list(config.file_blacklist);
    ctx.file_whitelist = get_regex_list(config.file_whitelist);

    Vec<Vec<ProfdataRun>> runGroups;
    for (auto const& [run_idx, run] : enumerate(summary.runs)) {
        if (run_idx % config.run_group_batch_size == 0) {
            runGroups.push_back({});
        }

        runGroups.back().push_back(ProfdataRun{
            .index = run_idx,
            .run   = run,
        });
    }

    for (auto const& group : runGroups) {
        process_runs(
            group,
            config,
            summary.runs.size(),
            flush_debug,
            ctx,
            q,
            debug,
            db);
    }

    if (config.perf_trace) {
        fs::path out_path{config.perf_trace.value()};
#ifdef ORG_USE_PERFETTO
        StopTracing(std::move(perfetto_session), out_path);
#endif
    }
}
