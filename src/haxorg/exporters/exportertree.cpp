#include <haxorg/exporters/exportertree.hpp>
#include <filesystem>
#include <fstream>

#define __scope() ScopedField CONCAT(close, __COUNTER__){this};

#include <haxorg/exporters/Exporter.cpp>
template class org::algo::Exporter<ExporterTree, int>;

void ExporterTree::visitField(
    int&                 arg,
    const char*          name,
    sem::SemId<sem::Org> org) {

    __scope();
    indent();
    os << name << ":" << "\n";
    Base::visitField(arg, name, org);
}

void ExporterTree::visitField(
    int&                       i,
    const char*                name,
    CVec<sem::SemId<sem::Org>> org) {
    if (skipAsEmpty(org)) {
        writeSkip("empty");
        return;
    }
    if (skipAsTooNested()) {
        writeSkip(
            fmt("too nested stack:{} max:{}",
                stack.size(),
                conf.maxTreeDepth));
        return;
    }

    __scope();
    indent();
    os << name << ":\n";
    for (const auto& [idx, sub] : enumerate(org)) {
        __scope();
        indent();
        os << "[" << fmt1(idx) << "]:\n";
        visit(i, sub);
    }
}

ColText ExporterTree::treeRepr(sem::SemId<sem::Org> org) {
    ColStream    os{};
    ExporterTree exp{os};
    exp.evalTop(org);
    return os.getBuffer();
}

void ExporterTree::treeRepr(
    sem::SemId<sem::Org>         org,
    const std::filesystem::path& path) {
    std::ofstream file{path.native()};
    if (file.is_open()) {
        ColStream os{file};
        os.colored = false;
        ExporterTree(os).evalTop(org);
    } else {
        throw FilesystemError::init(std::format(
            "Could not open file {} for writing tree repr", path));
    }
}

ColText ExporterTree::treeRepr(
    sem::SemId<sem::Org> org,
    CR<TreeReprConf>     conf) {
    ColStream    os{};
    ExporterTree exporter{os};
    exporter.conf = conf;
    exporter.evalTop(org);
    return os.getBuffer();
}

void ExporterTree::init(sem::SemId<sem::Org> org) {
    auto ctx = stack.back();
    indent();
    os << os.green() << std::format("{}", org->getKind()) << os.end();

    if (conf.withSubnodeIdx && ctx.subnodeIdx != -1) {
        os << " [" << ctx.subnodeIdx << "]";
    }

    if (conf.withOriginalId) {
        os << " OID:" << fmt1(org->original.id.getUnmasked());
    }

    if (conf.withLineCol) {
        if (org->loc.has_value()) {
            auto& [line, col, pos] = org->loc.value();
            os << " " << os.cyan() << fmt1(line) << ":" << fmt1(col) << "("
               << fmt1(pos) << ")" << os.end();
        } else {
            os << " loc=none";
        }
    }
    os << "\n";
}

bool ExporterTree::skipAsTooNested() const {
    return conf.maxTreeDepth < stack.size();
}

void ExporterTree::writeSkip(
    CR<Str>     message,
    CR<Str>     trail,
    int         line,
    const char* function) {
    // indent();
    // os << fmt("{} in {}:{}{}", message, function, line, trail);
}


template <typename T>
void ExporterTree::visitField(int& arg, const char* name, CR<T> value) {
    if (skipAsEmpty(value)) {
        writeSkip(fmt("  empty field {}", name), "\n");
        return;
    }
    // Location is printed as a part of 'init'
    if (std::is_same_v<T, Opt<org::parse::LineCol>>) { return; }

    __scope();
    indent();
    os << name << " ";
    if (conf.withTypeAnnotations) {
        os << "(" << os.green() << hstd::value_metadata<T>::typeName()
           << os.end() << ")";
    }
    if constexpr (std::is_same_v<T, int>) {
        os << " = " << os.cyan() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_same_v<T, bool>) {
        os << " = " << os.blue() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_enum_v<T>) {
        os << " = " << os.green() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_same_v<T, Str>) {
        os << " = " << os.yellow() << escape_literal(value) << os.end()
           << "\n";
    } else if constexpr (std::is_same_v<T, UserTime>) {
        os << " = " << fmt("align:{} time:{}", value.align, value.format())
           << "\n";
    } else {
        os << "\n";
        visit(arg, value);
    }
}

template <typename T>
void ExporterTree::visitField(
    int&          arg,
    const char*   name,
    sem::SemId<T> org) {
    visitField(arg, name, org.asOrg());
}

template <typename T>
void ExporterTree::visit(int& arg, sem::SemId<T> org) {
    if (skipAsTooNested()) {
        writeSkip("too nested");
        return;
    }
    visit(arg, org.asOrg());
}

template <typename T>
void ExporterTree::visit(int& arg, CR<T> opt) {
    if (skipAsTooNested()) {
        writeSkip("too nested");
        return;
    }
    __scope();
    indent();
    if constexpr (std::is_enum<T>::value) {
        os << os.red() << std::format("{}", opt) << os.end() << "\n";
    } else if constexpr (std::is_same_v<T, Str>) {
        if (conf.withTypeAnnotations) {
            os << value_metadata<T>::typeName();
        }

        os << os.yellow() << " " << escape_literal(opt) << os.end()
           << "\n";
    } else {
        if (conf.withTypeAnnotations) {
            os << os.red() << value_metadata<T>::typeName() << os.end();
        }
        os << "\n";
    }
}

template <typename T>
void ExporterTree::visit(int& arg, CR<Opt<T>> opt) {
    if (opt) {
        visit(arg, *opt);
    } else {
        indent();
        os << os.cyan() << "<none>" << os.end() << "\n";
    }
}

template <typename T>
void ExporterTree::visit(int& arg, CR<Vec<T>> value) {
    if (skipAsTooNested()) {
        writeSkip("too nested");
        return;
    }
    __scope();
    if (value.empty()) {
        indent();
        os << os.cyan() << "<empty>" << os.end() << "\n";
    } else {
        int idx = 0;
        for (const auto& it : value) {
            indent();
            os << "@[" << fmt1(idx) << "]:\n";
            visit(arg, it);
            ++idx;
        }
    }
}

template <typename V>
void ExporterTree::visit(int& arg, CR<UnorderedMap<Str, V>> opt) {
    __scope();
    for (auto const& [key, value] : opt) {
        visitField(arg, key.c_str(), value);
    }
}
