#include <exporters/exportertree.hpp>
#include <QFileInfo>

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

template class Exporter<ExporterTree, int>;
