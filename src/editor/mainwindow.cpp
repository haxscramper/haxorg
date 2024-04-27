#include "mainwindow.hpp"


void MainWindow::loadFiles() {
    for (auto const& file : state.opened_files) {
        SPtr<OrgDocumentModel> model = std::make_shared<OrgDocumentModel>(
            &store);
        model->loadFile(file.path.toBase());
        models.emplace_back(model);
        qInfo() << std::format(
            "Loded initial document from {}", file.path);
    }

    for (auto const& model : models) {
        auto filter = new OrgDocumentSearchFilter(model.get(), this);
        filter->acceptNode = [this](OrgBoxId id) -> bool {
            return store.node(id)->getKind() != OrgSemKind::Newline;
        };
        OrgDocumentEdit* edit = new OrgDocumentEdit(&store, filter, this);
        edit->expandRecursively(edit->rootIndex());
        tabs->addTab(edit, "tab");
    }
}
