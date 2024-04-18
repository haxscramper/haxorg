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


#include <boost/describe.hpp>


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
    if (node == nullptr) { return result; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["Kind"] = Kind;

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
            result[field] = std::move(array);
        },
        [&result](std::string const& field, Qualifiers const& value) {

        },
        [&result](std::string const& field, FunctionRefQual const& value) {

        },
        [&result](std::string const& field, ReferenceKind const& RK) {
            if (RK == ReferenceKind::LValue) {
                result[field] = "LValue";
            } else {
                result[field] = "RValue";
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

#define K_SWITCH(Expr)                                                    \
    switch (Expr) {                                                       \
        {

#define K_FIELD(Name, Idx, Type) sub(#Name, match<Idx, Type>(cast));

    using NPtr = Node const*;

    K_SWITCH(node->getKind()) {
        K_CAST(NameType) { K_FIELD(Name, 0, std::string_view); }
        K_CAST(LiteralOperator) { K_FIELD(OpName, 0, NPtr); }
        K_CAST(TemplateArgs) { K_FIELD(Params, 0, NodeArray); }
        K_CAST(PointerType) { K_FIELD(Pointee, 0, NPtr); }

        K_CAST(FunctionEncoding) {
            K_FIELD(Ret, 0, NPtr);
            K_FIELD(Name, 1, NPtr);
            K_FIELD(Params, 2, NodeArray);
            K_FIELD(Attrs, 3, NPtr);
            K_FIELD(CVQuals, 4, Qualifiers);
            K_FIELD(RefQual, 5, FunctionRefQual);
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


        K_DEFAULT() {
            LOG(std::format("ERR:'{}'", Kind));
            llvm::llvm_unreachable_internal();
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

std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


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

    Expected<json::Value> parsed = json::parse(json_parameters);

    if (!parsed) {
        LOG(std::format(
            "Failed to parse JSON: {}\n{}",
            toString(parsed.takeError()),
            json_parameters));
        return 1;
    }

    Expected<json::Value> summary = json::parse(
        read_file(parsed->getAsObject()->getString("coverage")->str()));

    auto FS = vfs::getRealFileSystem();
    for (auto const& run : *summary->getAsObject()->getArray("runs")) {
        std::string coverage_path = run.getAsObject()
                                        ->getString("test_profile")
                                        ->str();

        std::string binary_path = run.getAsObject()
                                      ->getString("test_binary")
                                      ->str();


        InstrProfWriter Writer;
        loadInput(coverage_path, binary_path, &Writer);
        LOG(std::format(
            "Loaded {} binary {}", coverage_path, binary_path));

        std::vector<StringRef> ObjectFilenames;
        ObjectFilenames.push_back(binary_path);

        std::string tmp_path = "/tmp/tmp.profdata";

        {
            std::error_code EC;
            raw_fd_ostream  Output(tmp_path, EC, sys::fs::OF_None);

            if (EC) {
                LOG(std::format(
                    "Error while creating output stream {}",
                    EC.message()));
                return 1;
            }

            if (Error E = Writer.write(Output)) {
                LOG(std::format(
                    "Failed write: {}", toString(std::move(E))));
                return 1;
            }
        }

        auto FS = vfs::getRealFileSystem();
        Expected<std::unique_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (Error E = mapping_or_err.takeError()) {
            LOG(std::format(
                "Failed to load profdata {}", toString(std::move(E))));
            return 1;
        }

        auto const& mapping = mapping_or_err.get();

        for (auto const& f : mapping->getCoveredFunctions()) {
            if (f.ExecutionCount == 0) { continue; }

            std::string readeable = demangle(f.Name);

            Demangler Parser(
                f.Name.data(), f.Name.data() + f.Name.length());

            Node*       AST  = Parser.parse();
            json::Value repr = treeRepr(AST);
            // LOG(formatv("{0:2}", repr));
        }
    }
}
