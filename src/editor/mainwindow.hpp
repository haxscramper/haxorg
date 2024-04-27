#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <editor/org_document_edit.hpp>
#include <editor/org_document_model.hpp>
#include "app_state.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    OrgStore store;

    Vec<SPtr<OrgDocumentModel>> models;
    AppState                    state;

    SPtr<QTabWidget> tabs;

    void loadFiles();

    MainWindow(AppState const& state, QWidget* parent = nullptr)
        : QMainWindow(parent)
        , state(state)
        , tabs(new QTabWidget(this)) //
    {
        resize(1200, 1200);
        setCentralWidget(tabs.get());
    }
};
