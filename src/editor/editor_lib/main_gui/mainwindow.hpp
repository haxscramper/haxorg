#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <editor/editor_lib/document/org_document_edit.hpp>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <editor/editor_lib/document/org_document_outline.hpp>
#include <editor/editor_lib/common/app_state.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    AppState                    state;
    SPtr<OrgStore>              store;
    Vec<SPtr<OrgDocumentModel>> models;
    SPtr<QTabWidget>            tabs;
    SPtr<OrgDocumentOutline>    outline;

    void loadFiles();

    MainWindow(AppState const& state, QWidget* parent = nullptr);
};
