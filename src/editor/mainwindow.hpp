#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <editor/org_document_edit.hpp>
#include <editor/org_document_model.hpp>
#include "org_document_outline.hpp"
#include "app_state.hpp"

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
