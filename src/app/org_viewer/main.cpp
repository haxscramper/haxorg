#include "mainwindow.hpp"

#include <QApplication>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Json.hpp>
#include "shared_org_logic.hpp"
#include "file_agenda_table.hpp"
#include <hstd/stdlib/JsonSerde.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

struct MainArgs {
    std::string infile;
    std::string graph_path   = "/tmp/immutable_graph_dump.bin";
    std::string context_path = "/tmp/immutable_ast_dump.bin";
    std::string epoch_path   = "/tmp/immutable_epoch_dump.bin";
    std::string cache_file = "/tmp/file_agenda_cache.org_files_cache.json";

    DESC_FIELDS(MainArgs, (infile));
};

int main(int argc, char* argv[]) {
    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        json_parameters = hstd::readFile(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    auto config = hstd::JsonSerde<MainArgs>::from_json(
        json::parse(json_parameters));

    auto node = loadCachedImmNode(
        config.infile,
        config.graph_path,
        config.context_path,
        config.epoch_path,
        config.cache_file);

    QApplication a(argc, argv);
    MainWindow   w;
    w.resize(1400, 600);
    auto tree   = buildAgendaTree(node);
    auto agenda = AgendaWidget(tree.get(), &w);
    w.setCentralWidget(&agenda);
    w.show();
    return a.exec();
}
