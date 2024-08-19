#pragma once

/// \file org_graph_layout.hpp
///
/// \brief Intermediate representation for interfacing with specific graph
/// layout backends: graphviz and adaptagrams/cola.

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <hstd/wrappers/hstd_extra/graphviz.hpp>
#include <QRect>
#include <QPolygonF>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <editor/editor_lib/common/app_utils.hpp>
#include <QPainterPath>
#include <hstd/wrappers/adaptagrams_wrap/adaptagrams_ir.hpp>

DECL_QDEBUG_FORMATTER(QPainterPath);

Q_DECLARE_REFL_METATYPE(GraphLayoutIR::Edge);

QPainterPath toQPainterPath(GraphPath const& path);
QPoint       toQPoint(GraphPoint const& point);
QRect        toQRect(GraphRect const& rect);
