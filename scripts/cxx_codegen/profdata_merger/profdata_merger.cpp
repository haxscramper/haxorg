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

#include <perfetto.h>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("llvm").SetDescription("LLVM code execution time"),
    perfetto::Category("sql").SetDescription("SQLite data insertion"),
    perfetto::Category("transform").SetDescription("Data transform time"),
    perfetto::Category("main").SetDescription("Top execution steps")
    //
);


#pragma clang diagnostic error "-Wswitch"

#include <hstd/wrappers/perfetto_aux_impl_template.hpp>

namespace fs = std::filesystem;
using namespace llvm::coverage;
using namespace llvm::itanium_demangle;

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


std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void llvm_unreachable_f(std::string const& msg) {
    llvm_unreachable(msg.c_str());
}


void CreateTables(SQLite::Database& db) {
    auto path = fs::path{__FILE__}.parent_path() / "profdata_merger.sql";
    std::string sql = read_file(path);
    db.exec(sql);
}

// std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
//     return std::cerr << std::format("[profmerge:{}] {}\n", line, msg);
// }

llvm::json::Array& add_array_field(
    llvm::json::Object&      obj,
    std::string const&       field,
    llvm::json::Value const& value) {
    if (obj.getArray(field) == nullptr) {
        obj[field] = llvm::json::Array();
    }
    obj.getArray(field)->push_back(value);
    return *obj.getArray(field);
}

llvm::json::Object& add_obj_field(
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
T match(TNode const* node) {
    T result;
    node->match(ForwardNth<N, T>{&result});
    return result;
}


llvm::json::Value treeRepr(Node const* node) {
    llvm::json::Object result;
    if (node == nullptr) { return nullptr; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["NodeKind"] = Kind;

    auto sub = overloaded{
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

    void grow() {
        char* NewMeta = static_cast<char*>(std::malloc(AllocSize));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList = new (NewMeta) BlockMeta{BlockList, 0};
    }

    void* allocateMassive(size_t NBytes) {
        NBytes += sizeof(BlockMeta);
        BlockMeta* NewMeta = reinterpret_cast<BlockMeta*>(
            std::malloc(NBytes));
        if (NewMeta == nullptr) { std::terminate(); }
        BlockList->Next = new (NewMeta) BlockMeta{BlockList->Next, 0};
        return static_cast<void*>(NewMeta + 1);
    }

  public:
    BumpPointerAllocator()
        : BlockList(new(InitialBuffer) BlockMeta{nullptr, 0}) {}

    void* allocate(size_t N) {
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

    void reset() {
        while (BlockList) {
            BlockMeta* Tmp = BlockList;
            BlockList      = BlockList->Next;
            if (reinterpret_cast<char*>(Tmp) != InitialBuffer) {
                std::free(Tmp);
            }
        }
        BlockList = new (InitialBuffer) BlockMeta{nullptr, 0};
    }

    ~BumpPointerAllocator() { reset(); }
};

class DefaultAllocator {
    BumpPointerAllocator Alloc;

  public:
    void reset() { Alloc.reset(); }

    template <typename T, typename... Args>
    T* makeNode(Args&&... args) {
        return new (Alloc.allocate(sizeof(T)))
            T(std::forward<Args>(args)...);
    }

    void* allocateNodeArray(size_t sz) {
        return Alloc.allocate(sizeof(Node*) * sz);
    }
};
} // unnamed namespace

using Demangler = llvm::itanium_demangle::ManglingParser<DefaultAllocator>;


static void loadInput(
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

llvm::ArrayRef<unsigned> getImpreciseRecordIndicesForFilename(
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

static std::optional<unsigned> findMainViewFileID(
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

static std::optional<unsigned> findMainViewFileID(
    llvm::StringRef       SourceFile,
    const FunctionRecord& Function) {
    std::optional<unsigned> I = findMainViewFileID(Function);
    if (I && SourceFile == Function.Filenames[*I]) { return I; }
    return std::nullopt;
}

static llvm::SmallBitVector gatherFileIDs(
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


std::vector<CountedRegion> getRegionsForFile(
    CoverageMapping const& Mapping,
    std::string const&     Filename) {
    std::vector<CountedRegion> Regions;

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
        for (const auto& CR : Function.CountedRegions) {
            if (FileIDs.test(CR.FileID)) {
                Regions.push_back(CR);
                // TODO Integrate expansion regions
                // if (MainFileID && isExpansion(CR, *MainFileID)) {
                //     FileCoverage.Expansions.emplace_back(CR, Function);
                // }
            }
        }
        // Capture branch regions specific to the function (excluding
        // expansions).
        for (const auto& CR : Function.CountedBranchRegions) {
            // TODO integrate branch regions
            // if (FileIDs.test(CR.FileID)
            //     && (CR.FileID == CR.ExpandedFileID)) {
            //     FileCoverage.BranchRegions.push_back(CR);
            // }
        }
    }

    return Regions;
}

std::string SqlInsert(
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
    SQLite::Statement func_region;
    SQLite::Statement file_region;
    SQLite::Statement context;
    SQLite::Statement func;
    SQLite::Statement file;
    SQLite::Statement instantiation_group;
    SQLite::Statement function_instantiation;

    queries(SQLite::Database& db)
        : // ---
        function_instantiation(
            db,
            SqlInsert(
                "CovFunctionInstantiation",
                {
                    "Instantiation", // 1
                    "Function",      // 2
                }))
        ,
        // ---
        instantiation_group(
            db,
            SqlInsert(
                "CovInstantiationGroup",
                {
                    "Id",   // 1
                    "Line", // 2
                    "Col",  // 3
                }))
        ,
        // ---
        func_region(
            db,
            SqlInsert(
                "CovFunctionRegion",
                {
                    "Id",                  // 1
                    "Function",            // 2
                    "Context",             // 3
                    "IsBranch",            // 4
                    "ExecutionCount",      // 5
                    "FalseExecutionCount", // 6
                    "Folded",              // 7
                    "FileId",              // 8
                    "ExpandedFileId",      // 9
                    "LineStart",           // 10
                    "ColumnStart",         // 11
                    "LineEnd",             // 12
                    "ColumnEnd",           // 13
                    "RegionKind",          // 14
                }))
        ,
        // ---
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


struct db_build_ctx {
    int                                  context_id{};
    int                                  instantiation_id{};
    std::unordered_map<std::string, int> function_ids{};
    std::unordered_map<std::string, int> file_ids{};
    int                                  region_counter{};
    int                                  function_region_counter{};

    std::vector<llvm::Regex> file_blacklist;
    std::vector<llvm::Regex> file_whitelist;

    bool file_matches(std::string const& path, std::string& debug) const {
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

    std::unordered_map<
        CountedRegion,
        int,
        CountedRegionHasher,
        CountedRegionComparator>
        function_region_ids{};


    int get_file_id(std::string const& path, queries& q) {
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

int get_function_id(
    FunctionRecord const& f,
    queries&              q,
    db_build_ctx&         ctx) {
    std::string readeable = llvm::demangle(f.Name);

    Demangler Parser(f.Name.data(), f.Name.data() + f.Name.length());

    Node*             AST  = Parser.parse();
    llvm::json::Value repr = treeRepr(AST);


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
        q.func.bind(4, llvm::formatv("{0}", repr));
        q.func.exec();
        q.func.reset();
    }

    return function_id;
}

int get_region_id(
    FunctionRecord const& f,
    CountedRegion const&  r,
    bool                  IsBranch,
    queries&              q,
    int                   function_id,
    db_build_ctx&         ctx) {
    if (!ctx.function_region_ids.contains(r)) {
        auto get_file_id = [&](int in_function_id) {
            std::string const& full_path = f.Filenames.at(in_function_id);
            return ctx.get_file_id(full_path, q);
        };

        int id                     = ++ctx.function_region_counter;
        ctx.function_region_ids[r] = id;

        q.func_region.bind(1, id);
        q.func_region.bind(2, function_id);
        q.func_region.bind(3, ctx.context_id);
        q.func_region.bind(4, IsBranch);
        q.func_region.bind(5, (int64_t)r.ExecutionCount);
        q.func_region.bind(6, (int64_t)r.FalseExecutionCount);
        q.func_region.bind(7, r.Folded);
        q.func_region.bind(8, get_file_id(r.FileID));
        q.func_region.bind(9, get_file_id(r.ExpandedFileID));
        q.func_region.bind(10, r.LineStart);
        q.func_region.bind(11, r.ColumnStart);
        q.func_region.bind(12, r.LineEnd);
        q.func_region.bind(13, r.ColumnEnd);
        q.func_region.bind(14, r.Kind);
        q.func_region.exec();
        q.func_region.reset();
    }


    return ctx.function_region_ids.at(r);
}


template <typename T, typename FormatContext>
auto fmt_ctx_field(
    std::string const& field_name,
    T const&           field_value,
    FormatContext&     ctx) {
    fmt_ctx(" ", ctx);
    fmt_ctx(field_name, ctx);
    fmt_ctx(" = ", ctx);
    return fmt_ctx(field_value, ctx);
}

template <>
struct std::formatter<CoverageSegment> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const CoverageSegment& p, FormatContext& ctx) const {
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

template <typename T>
std::string format_range(T begin, T end) {
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

void add_file(
    CoverageMapping const* mapping,
    llvm::StringRef        file,
    queries&               q,
    db_build_ctx&          ctx) {
    TRACE_EVENT("sql", "File coverage data");
    int file_id = ctx.get_file_id(file.str(), q);

    auto regions = getRegionsForFile(*mapping, file.str());
    for (auto const& it : llvm::enumerate(regions)) {
        ++ctx.region_counter;
        CountedRegion const& r = it.value();
        q.file_region.bind(1, ctx.region_counter);
        q.file_region.bind(2, ctx.context_id);
        q.file_region.bind(3, (int64_t)r.ExecutionCount);
        q.file_region.bind(4, (int64_t)r.FalseExecutionCount);
        q.file_region.bind(5, r.Folded);
        q.file_region.bind(6, (int64_t)r.LineStart);
        q.file_region.bind(7, (int64_t)r.ColumnStart);
        q.file_region.bind(8, (int64_t)r.LineEnd);
        q.file_region.bind(9, (int64_t)r.ColumnEnd);
        q.file_region.bind(10, r.Kind);
        q.file_region.bind(11, file_id);
        q.file_region.exec();
        q.file_region.reset();
    }
}


void add_instantiations(
    std::shared_ptr<CoverageMapping> const& mapping,
    std::string const&                      file,
    queries&                                q,
    db_build_ctx&                           ctx) {
    TRACE_EVENT("sql", "Add instantiations");
    for (InstantiationGroup const& group :
         mapping->getInstantiationGroups(file)) {
        if (group.getTotalExecutionCount() == 0) { continue; }
        int inst_id = ++ctx.instantiation_id;
        q.instantiation_group.bind(1, inst_id);
        q.instantiation_group.bind(2, group.getLine());
        q.instantiation_group.bind(3, group.getColumn());
        q.instantiation_group.exec();
        q.instantiation_group.reset();

        for (FunctionRecord const* func : group.getInstantiations()) {
            int func_id = get_function_id(*func, q, ctx);
            q.function_instantiation.bind(1, inst_id);
            q.function_instantiation.bind(2, func_id);
            q.function_instantiation.exec();
            q.function_instantiation.reset();
        }
    }
}


void add_regions(
    FunctionRecord const& f,
    queries&              q,
    int                   function_id,
    db_build_ctx&         ctx) {
    TRACE_EVENT("sql", "Function record", "Mangled", f.Name);


    auto add_region = [&](CountedRegion const& r, bool IsBranch) {
        if (0 < r.ExecutionCount || 0 < r.FalseExecutionCount) {
            get_region_id(f, r, IsBranch, q, function_id, ctx);
        }
    };

    for (auto const& r : f.CountedRegions) { add_region(r, false); }
    for (auto const& r : f.CountedBranchRegions) { add_region(r, true); }
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

void add_context(
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

llvm::MD5::MD5Result getMD5Digest(
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

std::shared_ptr<CoverageMapping> get_coverage_mapping(
    std::string const& coverage_path,
    std::string const& binary_path) {
    TRACE_EVENT(
        "llvm",
        "Profraw to coverage mapping",
        "coverage_path",
        coverage_path,
        "binary_path",
        binary_path);

    llvm::InstrProfWriter Writer;
    {
        TRACE_EVENT("llvm", "Load raw profile coverage");
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
        TRACE_EVENT("llvm", "Write converted profile data");
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


    {
        TRACE_EVENT("llvm", "Load coverage profile data");
        auto FS = llvm::vfs::getRealFileSystem();
        llvm::Expected<std::shared_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (llvm::Error E = mapping_or_err.takeError()) {
            throw std::domain_error(std::format(
                "Failed to load profdata {}", toString(std::move(E))));
        }

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

    DESC_FIELDS(
        ProfdataCLIConfig,
        (coverage,
         coverage_db,
         perf_trace,
         file_whitelist,
         file_blacklist,
         debug_file));
};

struct ProfdataFullProfile {
    std::vector<ProfdataCookie> runs;
    DESC_FIELDS(ProfdataFullProfile, (runs));
};

template <>
struct JsonSerde<Counter> {
    static json to_json(Counter const& cnt) { return json(); }
};

template <>
struct JsonSerde<CountedRegion::MCDCParameters> {
    static json to_json(CountedRegion::MCDCParameters const& cnt) {
        return json();
    }
};


template <>
struct JsonSerde<MCDCRecord> {
    static json to_json(MCDCRecord const& cnt) { return json(); }
};

template <>
struct JsonSerde<CoverageMapping> {
    static json to_json(CoverageMapping const& map) {
        json result = json::object();
        for (auto const& it : map.getCoveredFunctions()) {
            result["functions"].push_back(to_json_eval(it));
        }
        return result;
    }
};

const char* __asan_default_options() { return "detect_leaks=0"; }

int main(int argc, char** argv) {
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

    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (config.perf_trace) {
        perfetto_session = StartProcessTracing("profdata_merger");
    }


    if (fs::exists(db_file)) { fs::remove(db_file); }

    SQLite::Database db(
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
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


    std::unordered_map<
        std::pair<std::string, std::string>,
        std::shared_ptr<CoverageMapping>,
        llvm::pair_hash<std::string, std::string>>
        coverage_map;

    {
        TRACE_EVENT("llvm", "Parallel convert of coverage data");
        std::vector<std::pair<std::string, std::string>> paths{};

        for (auto const& run : summary.runs) {
            paths.push_back({run.test_profile, run.test_binary});
        }

        std::mutex coverage_mutex;

        std::for_each(
            std::execution::par,
            paths.begin(),
            paths.end(),
            [&](const std::pair<std::string, std::string>& p) {
                auto coverage = get_coverage_mapping(p.first, p.second);
                std::scoped_lock lock{coverage_mutex};
                coverage_map.emplace(p, std::move(coverage));
            });
    }

    for (auto const& run : summary.runs) {
        TRACE_EVENT("main", "Insert run data");
        finally{flush_debug};

        ctx.function_region_ids.clear();

        add_context(run, q, ctx);

        std::shared_ptr<CoverageMapping> mapping = coverage_map.at(
            {run.test_profile, run.test_binary});


        if (mapping.get() == nullptr) {
            throw std::logic_error(
                fmt("Failed to load coverage mapping profile={} binary={}",
                    run.test_profile,
                    run.test_binary));
        }

        if (config.coverage_mapping_dump) {
            auto j    = to_json_eval(*mapping);
            auto path = fs::path{*config.coverage_mapping_dump}
                      / getMD5Digest(run.test_profile, run.test_binary)
                            .digest()
                            .str()
                            .str();

            LOG(INFO) << fmt(
                "profile={} binary={} coverage-mapping-dump={}",
                run.test_profile,
                run.test_binary,
                path);
            writeFile(path, j.dump(2));
        }

        json j_run = json::object();
        {
            TRACE_EVENT("sql", "Full coverage run info");
            db.exec("BEGIN");
            {
                TRACE_EVENT("sql", "Covered functions");
                for (auto const& f : mapping->getCoveredFunctions()) {
                    if (f.ExecutionCount == 0) { continue; }
                    int function_id = get_function_id(f, q, ctx);
                    add_regions(f, q, function_id, ctx);
                }
            }

            {
                TRACE_EVENT("sql", "Covered files");
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
                    TRACE_EVENT("sql", "Add file", "File", file.str());
                    add_file(mapping.get(), file, q, ctx);
                    add_instantiations(mapping, file.str(), q, ctx);
                }

                j_run["covered_files"] = j_files;
            }

            db.exec("COMMIT");
        }


        debug["runs"].push_back(j_run);
    }

    if (config.perf_trace) {
        fs::path out_path{config.perf_trace.value()};
        StopTracing(std::move(perfetto_session), out_path);
    }
}
