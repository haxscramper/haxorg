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
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>
#include <llvm/Demangle/Demangle.h>
#include <llvm/Demangle/ItaniumDemangle.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <unordered_map>
#include <boost/describe.hpp>
#include <llvm/ADT/Hashing.h>


#include <perfetto.h>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("llvm").SetDescription("LLVM code execution time"),
    perfetto::Category("sql").SetDescription("SQLite data insertion"),
    perfetto::Category("transform").SetDescription("Data transform time"),
    perfetto::Category("main").SetDescription("Top execution steps")
    //
);


#include <hstd/wrappers/perfetto_aux_impl_template.hpp>

namespace fs = std::filesystem;
using namespace llvm;
using namespace llvm::coverage;
using namespace itanium_demangle;

enum class KindProxy
{
#define NODE(NodeKind) NodeKind,
#include <llvm/Demangle/ItaniumNodes.def>
};

BOOST_DESCRIBE_ENUM_BEGIN(KindProxy)
#define NODE(NodeKind) BOOST_DESCRIBE_ENUM_ENTRY(KindProxy, NodeKind)
#include <llvm/Demangle/ItaniumNodes.def>
BOOST_DESCRIBE_ENUM_END()

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


template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
    return std::cerr << std::format("[profmerge:{}] {}\n", line, msg);
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


json::Value treeRepr(Node const* node) {
    json::Object result;
    if (node == nullptr) { return nullptr; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["NodeKind"] = Kind;

    auto sub = overloaded{
        [&result](std::string const& field, json::Value value) {
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
            json::Array array;
            for (auto const& it : value) { array.push_back(treeRepr(it)); }
            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&result](std::string const& field, Qualifiers const& value) {
            json::Array array;
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

    using K = itanium_demangle::Node::Kind;

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
            K_FIELD(Params, 1, NodeArray);
            K_FIELD(Count, 2, std::string_view);
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
            K_FIELD(CVQuals, 4, Qualifiers);
            K_FIELD(RefQual, 5, FunctionRefQual);
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

        K_DEFAULT() {
            std::string msg = std::format("ERR:'{}'", Kind);
            llvm_unreachable(msg.c_str());
            break;
        }
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

using Demangler = itanium_demangle::ManglingParser<DefaultAllocator>;


static void loadInput(
    std::string const& Filename,
    std::string const& ProfiledBinary,
    InstrProfWriter*   Writer) {

    auto FS          = vfs::getRealFileSystem();
    auto ReaderOrErr = InstrProfReader::create(Filename, *FS);
    if (Error E = ReaderOrErr.takeError()) {
        auto [ErrCode, Msg] = InstrProfError::take(std::move(E));
        if (ErrCode != instrprof_error::empty_raw_profile) {
            assert(false);
        }
        return;
    }

    auto Reader = std::move(ReaderOrErr.get());
    for (auto& I : *Reader) {
        const StringRef FuncName = I.Name;
        bool            Reported = false;
        Writer->addRecord(std::move(I), 1, [&](Error E) {
            LOG(std::format("{}", toString(std::move(E))));
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
        if (Error E = Reader->getError()) {
            LOG(std::format("{} {}", toString(std::move(E)), Filename));
            return;
        }
    }

    std::vector<object::BuildID> BinaryIds;
    if (Error E = Reader->readBinaryIds(BinaryIds)) {
        LOG(std::format("{} {}", toString(std::move(E)), Filename));
        return;
    }

    Writer->addBinaryIds(BinaryIds);
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
    SQLite::Statement file_branch;
    SQLite::Statement context;
    SQLite::Statement func;
    SQLite::Statement file;
    SQLite::Statement segment;
    SQLite::Statement instantiation_group;
    SQLite::Statement function_instantiation;
    SQLite::Statement expansion;

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
        expansion(
            db,
            SqlInsert(
                "CovExpansionRegion",
                {
                    "FileId",
                    "Region",
                    "Function",
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
        segment(
            db,
            SqlInsert(
                "CovSegment",
                {
                    "Line",          // 1
                    "Col",           // 2
                    "Count",         // 3
                    "HasCount",      // 4
                    "IsRegionEntry", // 5
                    "IsGapRegion",   // 6
                    "File",          // 7
                    "Context",       // 8
                    "SegmentIndex",  // 9
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
        , file_branch(
              db,
              SqlInsert(
                  "CovFileBranch",
                  {
                      "Context",             // 1
                      "ExecutionCount",      // 2
                      "FalseExecutionCount", // 3
                      "Folded",              // 4
                      "LineStart",           // 5
                      "ColumnStart",         // 6
                      "LineEnd",             // 7
                      "ColumnEnd",           // 8
                      "RegionKind",          // 9
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
                    "Path" // 1
                })) {}
};

struct CountedRegionHasher {
    size_t operator()(const CounterMappingRegion& region) const {
        return hash_combine(
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

struct db_build_ctx {
    int                                  context_id{};
    int                                  instantiation_id{};
    std::unordered_map<std::string, int> function_ids{};
    std::unordered_map<std::string, int> file_ids{};
    int                                  function_region_counter{};

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

            q.file.bind(1, path);
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
    std::string readeable = demangle(f.Name);

    Demangler Parser(f.Name.data(), f.Name.data() + f.Name.length());

    Node*       AST  = Parser.parse();
    json::Value repr = treeRepr(AST);


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

void add_file(CoverageData const& file, queries& q, db_build_ctx& ctx) {
    TRACE_EVENT("sql", "File coverage data");
    int file_id = ctx.get_file_id(file.getFilename().str(), q);


    for (auto it : enumerate(file)) {
        CoverageSegment const& s = it.value();
        q.segment.bind(1, s.Line);
        q.segment.bind(2, s.Col);
        q.segment.bind(3, (int64_t)s.Count);
        q.segment.bind(4, s.HasCount);
        q.segment.bind(5, s.IsRegionEntry);
        q.segment.bind(6, s.IsGapRegion);
        q.segment.bind(7, file_id);
        q.segment.bind(8, ctx.context_id);
        q.segment.bind(9, (int)it.index());
        q.segment.exec();
        q.segment.reset();
    }

    for (auto it : enumerate(file.getBranches())) {
        CountedRegion const& r = it.value();
        q.file_branch.bind(1, ctx.context_id);
        q.file_branch.bind(2, (int64_t)r.ExecutionCount);
        q.file_branch.bind(3, (int64_t)r.FalseExecutionCount);
        q.file_branch.bind(4, r.Folded);
        q.file_branch.bind(5, (int64_t)r.LineStart);
        q.file_branch.bind(6, (int64_t)r.ColumnStart);
        q.file_branch.bind(7, (int64_t)r.LineEnd);
        q.file_branch.bind(8, (int64_t)r.ColumnEnd);
        q.func_region.bind(9, r.Kind);
        q.file_branch.exec();
        q.file_branch.reset();
    }

    for (ExpansionRecord const& e : file.getExpansions()) {
        int function_id = get_function_id(e.Function, q, ctx);
        q.expansion.bind(1, e.FileID);
        q.expansion.bind(
            2,
            get_region_id(
                e.Function, e.Region, false, q, function_id, ctx));
        q.expansion.bind(3, function_id);
        q.expansion.exec();
        q.expansion.reset();
    }
}


void add_instantiations(
    std::unique_ptr<CoverageMapping> const& mapping,
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


void add_context(json::Object const* run, queries& q, db_build_ctx& ctx) {
    ++ctx.context_id;

    q.context.bind(1, ctx.context_id);
    q.context.bind(2, run->getString("test_name")->str());
    q.context.bind(3, run->getString("test_class")->str());
    q.context.bind(4, run->getString("test_profile")->str());
    q.context.bind(5, llvm::formatv("{0}", *run->get("test_params")));
    q.context.bind(6, run->getString("test_binary")->str());

    q.context.exec();
    q.context.reset();
}

std::unique_ptr<CoverageMapping> get_coverage_mapping(
    std::string const& coverage_path,
    std::string const& binary_path) {
    TRACE_EVENT("llvm", "Profraw to coverage mapping");

    InstrProfWriter Writer;
    {
        TRACE_EVENT("llvm", "Load raw profile coverage");
        loadInput(coverage_path, binary_path, &Writer);
        LOG(std::format(
            "Loaded {} binary {}", coverage_path, binary_path));
    }

    std::string            tmp_path = "/tmp/tmp.profdata";
    std::vector<StringRef> ObjectFilenames;
    ObjectFilenames.push_back(binary_path);
    {
        TRACE_EVENT("llvm", "Write converted profile data");
        std::error_code EC;
        raw_fd_ostream  Output(tmp_path, EC, sys::fs::OF_None);

        if (EC) {
            LOG(std::format(
                "Error while creating output stream {}", EC.message()));
            return nullptr;
        }

        if (Error E = Writer.write(Output)) {
            LOG(std::format("Failed write: {}", toString(std::move(E))));
            return nullptr;
        }
    }


    {
        TRACE_EVENT("llvm", "Load coverage profile data");
        auto FS = vfs::getRealFileSystem();
        Expected<std::unique_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (Error E = mapping_or_err.takeError()) {
            LOG(std::format(
                "Failed to load profdata {}", toString(std::move(E))));
            return nullptr;
        }

        return std::move(mapping_or_err.get());
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        LOG("Expected single positional argument -- JSON literal "
            "with parameters or absolute path to the JSON "
            "configuration file.");
        return 1;
    }

    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        json_parameters = read_file(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    Expected<json::Value> config_value = json::parse(json_parameters);

    if (!config_value) {
        LOG(std::format(
            "Failed to parse JSON: {}\n{}",
            toString(config_value.takeError()),
            json_parameters));
        return 1;
    }

    auto config = config_value->getAsObject();

    Expected<json::Value> summary = json::parse(
        read_file(config->getString("coverage")->str()));

    fs::path db_file{config->getString("coverage_db")->str()};

    std::unique_ptr<perfetto::TracingSession> perfetto_session;
    if (config->getString("perf_trace")) {
        perfetto_session = StartProcessTracing("profdata_merger");
    }


    if (fs::exists(db_file)) { fs::remove(db_file); }

    SQLite::Database db(
        db_file.native(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    CreateTables(db);
    queries q{db};

    db_build_ctx ctx;
    auto         FS = vfs::getRealFileSystem();


    for (auto const& run_value :
         *summary->getAsObject()->getArray("runs")) {
        TRACE_EVENT("main", "Insert run data");

        auto        run           = run_value.getAsObject();
        std::string coverage_path = run->getString("test_profile")->str();
        std::string binary_path   = run->getString("test_binary")->str();
        ctx.function_region_ids.clear();

        add_context(run, q, ctx);

        std::unique_ptr<CoverageMapping> mapping = get_coverage_mapping(
            coverage_path, binary_path);


        if (mapping.get() == nullptr) { return 1; }

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
                for (auto const& file : mapping->getUniqueSourceFiles()) {
                    if (file.contains("base_lexer_gen.cpp")
                        || file.contains("thirdparty")) {
                        continue;
                    }
                    TRACE_EVENT("sql", "Add file", "File", file.str());
                    TRACE_EVENT_BEGIN("llvm", "Get coverage for file");
                    CoverageData cover = mapping->getCoverageForFile(file);
                    TRACE_EVENT_END("llvm");
                    add_file(cover, q, ctx);
                    add_instantiations(mapping, file.str(), q, ctx);
                }
            }

            db.exec("COMMIT");
        }
    }

    if (config->getString("perf_trace")) {
        fs::path out_path{config->getString("perf_trace")->str()};
        StopTracing(std::move(perfetto_session), out_path);
    }
}
