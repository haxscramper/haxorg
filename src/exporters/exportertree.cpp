#include <exporters/exportertree.hpp>
#include <QFileInfo>

#define __scope() ScopedField CONCAT(close, __COUNTER__){this};


void ExporterTree::visitField(int& arg, const char* name, sem::SemId org) {

    __scope();
    indent();
    os << name << ":"
       << "\n";
    Base::visitField(arg, name, org);
}

void ExporterTree::visitField(
    int&             i,
    const char*      name,
    CVec<sem::SemId> org) {
    if (skipAsEmpty(org)) {
        return;
    }

    __scope();
    indent();
    os << name << ":\n";
    for (const auto& [idx, sub] : enumerate(org)) {
        __scope();
        indent();
        os << "[" << idx << "]:\n";
        visit(i, sub);
    }
}

void ExporterTree::treeRepr(sem::SemId org) {
    ColStream os{qcout};
    ExporterTree(os).visitTop(org);
}

void ExporterTree::treeRepr(sem::SemId org, const QFileInfo& path) {
    QFile file{path.absoluteFilePath()};
    if (file.open(QIODevice::ReadWrite | QFile::Truncate)) {
        QTextStream stream{&file};
        ColStream   os{stream};
        os.colored = false;
        ExporterTree(os).visitTop(org);
    } else {
        qWarning() << "Could not open file" << path
                   << "for writing tree repr";
    }
}

void ExporterTree::treeRepr(sem::SemId org, CR<TreeReprConf> conf) {
    ColStream    os{qcout};
    ExporterTree exporter{os};
    exporter.conf = conf;
    exporter.visitTop(org);
}

void ExporterTree::init(sem::SemId org) {
    auto ctx = stack.back();
    indent();
    os << os.green() << to_string(org->getKind()) << os.end();

    if (conf.withSubnodeIdx && ctx.subnodeIdx != -1) {
        os << " [" << ctx.subnodeIdx << "]";
    }

    if (conf.withOriginalId) {
        os << " ID:" << org->original.id.getUnmasked();
    }

    if (conf.withLineCol && org->loc.has_value()) {
        auto& [line, col, pos] = org->loc.value();
        os << " " << os.cyan() << line << ":" << col << "(" << pos << ")"
           << os.end();
    }
    os << "\n";
}

template <typename T>
void ExporterTree::visitField(int& arg, const char* name, CR<T> value) {
    if (skipAsEmpty(value)) {
        return;
    }

    __scope();
    indent();
    os << name << " (" << os.green() << typeName<T>() << os.end() << ")";
    if constexpr (std::is_same_v<T, int>) {
        os << " = " << os.cyan() << value << os.end() << "\n";
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
    int&           arg,
    const char*    name,
    sem::SemIdT<T> org) {
    visitField(arg, name, org.toId());
}

template <typename T>
void ExporterTree::visit(int& arg, sem::SemIdT<T> org) {
    visit(arg, org.toId());
}

template <typename T>
void ExporterTree::visit(int& arg, CR<T> opt) {
    if constexpr (std::is_enum<T>::value) {
        __scope();
        indent();
        os << os.red() << to_string(opt) << os.end() << "\n";
    } else {
        __scope();
        indent();
        os << os.red() << typeName<T>() << os.end() << "\n";
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
            os << "@[" << idx << "]:\n";
            visit(arg, it);
            ++idx;
        }
    }
}


template class Exporter<ExporterTree, int>;
