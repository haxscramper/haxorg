#include <editor/editor_lib/document/org_document_render.hpp>
#include <editor/editor_lib/store/org_exporter_html.hpp>
#include <QLabel>
#include <QPainter>

SPtr<QWidget> make_label(Str const& node) {
    auto label = std::make_shared<QLabel>();
    label->setText(QString::fromStdString(node));
    label->setWordWrap(true);
    label->setStyleSheet("QLabel { background-color : white; }");
    return label;
}


SPtr<QWidget> make_label(sem::OrgArg node) {
    ExporterHtml exp;
    auto         html_tree = exp.evalTop(node);
    return make_label(exp.store.toString(html_tree));
}


QSize get_width_fit(QWidget* widget, int width) {
    Q_ASSERT(widget);
    widget->setFixedWidth(width);
    QSize size = widget->sizeHint();
    widget->deleteLater();
    return size;
}

QSize get_width_fit(QWidget* widget, const QObject* parent) {
    return get_width_fit(
        widget, qobject_cast<QWidget const*>(parent)->width());
}

void draw(
    QWidget*                    widget,
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) {
    widget->setGeometry(option.rect);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);
    painter->drawPixmap(option.rect.topLeft(), pixmap);
}
