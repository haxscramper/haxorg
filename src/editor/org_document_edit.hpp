#pragma once

#include <QTreeView>
#include <editor/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QTextEdit>
#include <sem/SemBaseApi.hpp>

class QVBoxLayout;
class KDescendantsProxyModel;

class OrgDocumentEdit : public QWidget {
    Q_OBJECT
  public:
    SPtr<KDescendantsProxyModel> flatProxy;
    SPtr<QVBoxLayout>            layout;
    QAbstractItemModel*          baseModel;

    QAbstractItemModel* model();

    OrgDocumentEdit(
        OrgStore*           store,
        QAbstractItemModel* model,
        QWidget*            parent);

    int getNestingLevel(const QModelIndex& index) const {
        int         level   = 0;
        QModelIndex current = index;
        while (current.parent().isValid()) {
            level++;
            current = current.parent();
        }
        return level;
    }

    QWidget* getWidget(CR<QModelIndex> index);

  private slots:
    void populateList();
    void onRowsInserted(const QModelIndex& parent, int first, int last);
    void onRowsRemoved(const QModelIndex& parent, int first, int last);
};
