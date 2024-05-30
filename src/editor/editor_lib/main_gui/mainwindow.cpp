#include <editor/editor_lib/main_gui/mainwindow.hpp>
#include <editor/editor_lib/document/org_document_outline.hpp>
#include <QSplitter>

void MainWindow::loadFiles() {
    for (auto const& file : state.opened_files) {
        SPtr<OrgDocumentModel> model = std::make_shared<OrgDocumentModel>(
            store.get());
        model->loadFile(file.path.toBase());
        models.emplace_back(model);
        qInfo(editor_files)
            << std::format("Loded initial document from {}", file.path);
    }

    for (auto const& [idx, model] : enumerate(models)) {
        OrgDocumentEdit* edit = new OrgDocumentEdit(
            store.get(), model.get(), this);
        edit->expandRecursively(edit->rootIndex());
        tabs->addTab(edit, "tab");
        edit->setObjectName(
            QString("MainWindow-OrgDocumentEdit-%1").arg(idx));
    }
}

MainWindow::MainWindow(const AppState& state, QWidget* parent)
    : QMainWindow(parent)
    , state(state)
    , tabs(new QTabWidget(this))
    , outline(std::make_shared<OrgDocumentOutline>(store.get(), this))
    , store(std::make_shared<OrgStore>())
//
{


    resize(1200, 1200);
    auto splitter = new QSplitter(this);
    setCentralWidget(splitter);
    splitter->addWidget(outline.get());
    splitter->addWidget(tabs.get());
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    outline->setObjectName("MainWindow-OrgDocumentOutline");
    tabs->setObjectName("MainWindow-CentralTabWidget");


    QObject::connect(
        tabs.get(), &QTabWidget::currentChanged, this, [&](int tab) {
            OrgDocumentEdit* edit = qobject_cast<OrgDocumentEdit*>(
                tabs->widget(tab));
            outline->setFilter(std::make_shared<OrgSubtreeSearchModel>(
                edit->docModel, this, store.get()));

            connect(
                outline.get(),
                &OrgDocumentOutline::outlineFocusRequested,
                edit,
                &OrgDocumentEdit::focusOn);
        });
}
