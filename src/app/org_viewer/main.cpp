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
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <hstd/ext/logger.hpp>

struct MainArgs {
    std::string infile;
    std::string graph_path   = "/tmp/immutable_graph_dump.bin";
    std::string context_path = "/tmp/immutable_ast_dump.bin";
    std::string epoch_path   = "/tmp/immutable_epoch_dump.bin";
    std::string cache_file = "/tmp/file_agenda_cache.org_files_cache.json";
    std::optional<std::string> log_path  = "/tmp/org_viewer.log";
    bool                       use_cache = true;

    DESC_FIELDS(
        MainArgs,
        (infile,
         graph_path,
         context_path,
         epoch_path,
         cache_file,
         use_cache));
};

int main(int argc, char* argv[]) {
    auto config = hstd::parse_json_argc<MainArgs>(argc, argv);

    if (config.log_path) {
        hstd::log::push_sink(
            hstd::log::init_file_sink(config.log_path.value()));
    }

    auto parse_context = org::parse::ParseContext::shared();

    HSLOG_INFO("Started org_viewer");

    auto node = loadCachedImmNode(
        config.infile,
        config.graph_path,
        config.context_path,
        config.epoch_path,
        config.cache_file,
        parse_context,
        config.use_cache);

    QApplication a(argc, argv);
    MainWindow   w;
    w.resize(1400, 600);
    auto tree   = buildAgendaTree(node);
    auto agenda = AgendaWidget(tree.get(), &w);
    w.setCentralWidget(&agenda);
    w.show();
    return a.exec();
}
