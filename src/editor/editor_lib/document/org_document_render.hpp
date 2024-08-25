#pragma once

#include <QWidget>
#include <hstd/stdlib/Str.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <QStyleOption>

SPtr<QWidget> make_label(Str const& node);
SPtr<QWidget> make_label(sem::OrgArg node);
QSize         get_width_fit(QWidget* widget, int width);
QSize         get_width_fit(QWidget* widget, QObject const* parent);
void          draw(
             QWidget*                    widget,
             QPainter*                   painter,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index);
