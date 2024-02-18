#include <exporters/exportertree.hpp>
#include <filesystem>
#include <fstream>

#define __scope() ScopedField CONCAT(close, __COUNTER__){this};

#include <exporters/Exporter.cpp>
template class Exporter<ExporterTree, int>;

void ExporterTree::visitField(
    int&                 arg,
    const char*          name,
    sem::SemId<sem::Org> org) {

    __scope();
    indent();
    os << name << ":"
       << "\n";
    Base::visitField(arg, name, org);
}

void ExporterTree::visitField(
    int&                       i,
    const char*                name,
    CVec<sem::SemId<sem::Org>> org) {
    if (skipAsEmpty(org)) { return; }

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

void ExporterTree::treeRepr(sem::SemId<sem::Org> org) {
    ColStream os{std::cout};
    ExporterTree(os).evalTop(org);
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
        LOG(ERROR) << "Could not open file" << path
                   << "for writing tree repr";
    }
}

void ExporterTree::treeRepr(
    sem::SemId<sem::Org> org,
    CR<TreeReprConf>     conf) {
    ColStream    os{std::cout};
    ExporterTree exporter{os};
    exporter.conf = conf;
    exporter.evalTop(org);
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

    if (conf.withLineCol && org->loc.has_value()) {
        auto& [line, col, pos] = org->loc.value();
        os << " " << os.cyan() << line << ":" << fmt1(col) << "("
           << fmt1(pos) << ")" << os.end();
    }
    os << "\n";
}

template <typename T>
void ExporterTree::visitField(int& arg, const char* name, CR<T> value) {
    if (skipAsEmpty(value)) { return; }

    __scope();
    indent();
    os << name << " (" << os.green() << TypeName<T>::get() << os.end()
       << ")";
    if constexpr (std::is_same_v<T, int>) {
        os << " = " << os.cyan() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_same_v<T, bool>) {
        os << " = " << os.blue() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_enum_v<T>) {
        os << " = " << os.green() << fmt1(value) << os.end() << "\n";
    } else if constexpr (std::is_same_v<T, Str>) {
        os << " = " << os.yellow() << escape_literal(value) << os.end()
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
    visit(arg, org.asOrg());
}

template <typename T>
void ExporterTree::visit(int& arg, CR<T> opt) {
    if constexpr (std::is_enum<T>::value) {
        __scope();
        indent();
        os << os.red() << std::format("{}", opt) << os.end() << "\n";
    } else {
        __scope();
        indent();
        os << os.red() << TypeName<T>::get() << os.end() << "\n";
    }
}

template <typename T>
void ExporterTree::visit(int& arg, CR<Opt<T>> opt) {
    __scope();
    if (opt) {
        visit(arg, *opt);
    } else {
        indent();
        os << os.cyan() << "<none>" << os.end() << "\n";
    }
}

template <typename T>
void ExporterTree::visit(int& arg, CR<Vec<T>> value) {
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
