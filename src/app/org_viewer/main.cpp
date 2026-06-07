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
    std::string                infile;
    std::optional<std::string> log_path = "/tmp/org_viewer.log";

    DESC_FIELDS(MainArgs, (infile));
};

int main(int argc, char* argv[]) {
    auto config = hstd::parse_json_argc<MainArgs>(argc, argv);

    if (config.log_path) {
        hstd::log::push_sink(
            hstd::log::init_file_sink(config.log_path.value()));
    }

    auto parse_context = org::parse::ParseContext::shared();

    HSLOG_INFO("Started org_viewer");

    auto node = loadCachedImmNode(config.infile, parse_context);

    QApplication a(argc, argv);
    MainWindow   w;
    w.resize(1400, 600);
    auto tree   = buildAgendaTree(node);
    auto agenda = AgendaWidget(tree.get(), &w);
    w.setCentralWidget(&agenda);
    w.show();
    return a.exec();
}
