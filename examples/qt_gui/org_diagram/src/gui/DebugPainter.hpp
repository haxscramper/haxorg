#pragma once

#include <QPainter>
#include <QDebug>
#include <QPainterPath>
#include <hstd/system/aux_utils.hpp>
#include <QGlyphRun>
#include <QPicture>
#include <QStaticText>

#define CALL_LOC() __LINE__, __func__, __FILE__

struct DebugPainter {
    QPainter*               painter;
    QString                 context;
    hstd::finally_std       on_close;
    static thread_local int depth;
    bool                    TraceState = false;

    DebugPainter(
        QPainter*      p,
        bool           TraceState,
        const QString& ctx      = "",
        int            line     = __builtin_LINE(),
        char const*    function = __builtin_FUNCTION(),
        char const*    file     = __builtin_FILE())
        : painter{p}
        , context{ctx}
        , on_close{[]() { --DebugPainter::depth; }}
        , TraceState{TraceState} //
    {
        if (TraceState) {
            auto debug = qDebug().noquote();
            debug << prefix();

            if (context.isEmpty()) {
                debug << QString("paint at %1:%2").arg(function).arg(line);
            } else {
                debug << QString("start '%1' at %2:%3")
                             .arg(context)
                             .arg(function)
                             .arg(line);
            }
        }

        ++depth;
    }

    template <typename T>
    void debug_single(QDebug& debug, T const& item) {
        debug << item;
    }


    void debug_single(
        QDebug&                         debug,
        QPainter::PixmapFragment const& item) {
        debug << "QPixmapFragment";
    }

    void debug_single(QDebug& debug, QGlyphRun const& item) {
        debug << "QGlyphRun";
    }

    void debug_single(QDebug& debug, QPicture const& item) {
        debug << "QPicture";
    }

    void debug_single(QDebug& debug, QStaticText const& item) {
        debug << "QStaticText";
    }

    void debug_single(QDebug& debug, QTextOption const& item) {
        debug << "QTextOption";
    }


    template <typename T, typename... Args>
    void send_debug(
        QDebug&            debug,
        QStringList const& names,
        int                arg_index,
        T const*           items,
        int                size,
        Args&&... args) {
        for (int i = 0; i << size; ++i) {
            debug << names[arg_index].trimmed() << "=";
            debug_single(debug, items[i]);
        }
        send_debug(
            debug, names, arg_index + 2, std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    void send_debug(
        QDebug&            debug,
        QStringList const& names,
        int                arg_index,
        T const&           item,
        Args&&... args) {
        debug << names[arg_index].trimmed() << "=";
        debug_single(debug, item);
        send_debug(
            debug, names, arg_index + 1, std::forward<Args>(args)...);
    }

    template <typename T>
    void send_debug(
        QDebug&            debug,
        QStringList const& names,
        int                arg_index,
        T const&           item) {
        debug << names[arg_index].trimmed() << "=";
        debug_single(debug, item);
    }

    void send_debug(
        QDebug&            debug,
        QStringList const& names,
        int                arg_index) {}

    template <typename... Args>
    void qdebug_painter_args(
        const QString& context,
        const QString& method,
        int            line,
        const char*    function,
        const char*    file,
        const QString& arg_names,
        Args&&... args) {
        QDebug debug = qDebug().noquote();
        debug << prefix() << QString{"%1:"}.arg(method);

        QStringList names = arg_names.split(',');
        int         i     = 0;

        send_debug(debug, names, 0, args...);

        debug << QString{"at %1:%2"}.arg(function).arg(line);
    }

#define DEBUG_PAINTER_ARGUMENTS(method, line, function, file, ...)        \
    qdebug_painter_args(                                                  \
        context,                                                          \
        #method,                                                          \
        line,                                                             \
        function,                                                         \
        file,                                                             \
        #__VA_ARGS__,                                                     \
        __VA_ARGS__)

#define DEBUG_PAINTER_IMPL(method, line, function, file, ...)             \
    if (this->TraceState) {                                               \
        DEBUG_PAINTER_ARGUMENTS(                                          \
            method, line, function, file, __VA_ARGS__);                   \
    }                                                                     \
    painter->method(__VA_ARGS__);


    QString prefix() const { return QString("  ").repeated(depth); }

    // clang-format off
    void 	drawArc(const QRectF &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawArc, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawArc(const QRect &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawArc, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawArc(int x, int y, int width, int height, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawArc, line, function, file, x, y, width, height, startAngle, spanAngle); }
    void 	drawChord(const QRectF &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawChord, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawChord(const QRect &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawChord, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawChord(int x, int y, int width, int height, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawChord, line, function, file, x, y, width, height, startAngle, spanAngle); }
    void 	drawConvexPolygon(const QPointF *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawConvexPolygon, line, function, file, points, pointCount); }
    void 	drawConvexPolygon(const QPolygon &polygon, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawConvexPolygon, line, function, file, polygon); }
    void 	drawConvexPolygon(const QPolygonF &polygon, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawConvexPolygon, line, function, file, polygon); }
    void 	drawConvexPolygon(const QPoint *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawConvexPolygon, line, function, file, points, pointCount); }
    void 	drawEllipse(const QRectF &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawEllipse, line, function, file, rectangle); }
    void 	drawEllipse(const QRect &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawEllipse, line, function, file, rectangle); }
    void 	drawEllipse(const QPoint &center, int rx, int ry, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawEllipse, line, function, file, center, rx, ry); }
    void 	drawEllipse(const QPointF &center, qreal rx, qreal ry, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawEllipse, line, function, file, center, rx, ry); }
    void 	drawEllipse(int x, int y, int width, int height, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawEllipse, line, function, file, x, y, width, height); }
    void 	drawGlyphRun(const QPointF &position, const QGlyphRun &glyphs, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawGlyphRun, line, function, file, position, glyphs); }
    void 	drawImage(const QRectF &target, const QImage &image, const QRectF &source, Qt::ImageConversionFlags flags = Qt::AutoColor, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, target, image); }
    void 	drawImage(const QPoint &point, const QImage &image, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, point, image); }
    void 	drawImage(const QPointF &point, const QImage &image, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, point, image); }
    void 	drawImage(const QRect &rectangle, const QImage &image, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, rectangle, image); }
    void 	drawImage(const QRectF &rectangle, const QImage &image, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, rectangle, image); }
    void 	drawImage(const QPoint &point, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags = Qt::AutoColor, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, point, image, source, flags); }
    void 	drawImage(const QPointF &point, const QImage &image, const QRectF &source, Qt::ImageConversionFlags flags = Qt::AutoColor, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, point, image, source, flags); }
    void 	drawImage(const QRect &target, const QImage &image, const QRect &source, Qt::ImageConversionFlags flags = Qt::AutoColor, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, target, image, source, flags); }
    void 	drawImage(int x, int y, const QImage &image, int sx = 0, int sy = 0, int sw = -1, int sh = -1, Qt::ImageConversionFlags flags = Qt::AutoColor, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawImage, line, function, file, x, y, image, sx, sy, sw, sh); }
    void 	drawLine(const QLineF &line, int code_line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLine, code_line, function, file, line); }
    void 	drawLine(const QLine &line, int code_line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLine, code_line, function, file, line); }
    void 	drawLine(const QPoint &p1, const QPoint &p2, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLine, line, function, file, p1, p2); }
    void 	drawLine(const QPointF &p1, const QPointF &p2, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLine, line, function, file, p1, p2); }
    void 	drawLine(int x1, int y1, int x2, int y2, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLine, line, function, file, x1, y1, x2, y2); }
    void 	drawLines(const QLineF *lines, int lineCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, lines, lineCount); }
    void 	drawLines(const QList<QLine> &lines, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, lines); }
    void 	drawLines(const QList<QLineF> &lines, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, lines); }
    void 	drawLines(const QList<QPoint> &pointPairs, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, pointPairs); }
    void 	drawLines(const QList<QPointF> &pointPairs, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, pointPairs); }
    void 	drawLines(const QLine *lines, int lineCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, lines, lineCount); }
    void 	drawLines(const QPoint *pointPairs, int lineCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, pointPairs, lineCount); }
    void 	drawLines(const QPointF *pointPairs, int lineCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawLines, line, function, file, pointPairs, lineCount); }
    void 	drawPath(const QPainterPath &path, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPath, line, function, file, path); }
    void 	drawPicture(const QPointF &point, const QPicture &picture, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPicture, line, function, file, point, picture); }
    void 	drawPicture(const QPoint &point, const QPicture &picture, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPicture, line, function, file, point, picture); }
    void 	drawPicture(int x, int y, const QPicture &picture, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPicture, line, function, file, x, y, picture); }
    void 	drawPie(const QRectF &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPie, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawPie(const QRect &rectangle, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPie, line, function, file, rectangle, startAngle, spanAngle); }
    void 	drawPie(int x, int y, int width, int height, int startAngle, int spanAngle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPie, line, function, file, x, y, width, height, startAngle, spanAngle); }
    void 	drawPixmap(const QRectF &target, const QPixmap &pixmap, const QRectF &source, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, target, pixmap, source); }
    void 	drawPixmap(const QPoint &point, const QPixmap &pixmap, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, point, pixmap); }
    void 	drawPixmap(const QPointF &point, const QPixmap &pixmap, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, point, pixmap); }
    void 	drawPixmap(const QRect &rectangle, const QPixmap &pixmap, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, rectangle, pixmap); }
    void 	drawPixmap(const QPoint &point, const QPixmap &pixmap, const QRect &source, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, point, pixmap); }
    void 	drawPixmap(const QPointF &point, const QPixmap &pixmap, const QRectF &source, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, point, pixmap); }
    void 	drawPixmap(const QRect &target, const QPixmap &pixmap, const QRect &source, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, target, pixmap); }
    void 	drawPixmap(int x, int y, const QPixmap &pixmap, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, x, y, pixmap); }
    void 	drawPixmap(int x, int y, int width, int height, const QPixmap &pixmap, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, x, y, width, height, pixmap); }
    void 	drawPixmap(int x, int y, const QPixmap &pixmap, int sx, int sy, int sw, int sh, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, x, y, pixmap, sx, sy, sw, sh); }
    void 	drawPixmap(int x, int y, int w, int h, const QPixmap &pixmap, int sx, int sy, int sw, int sh, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmap, line, function, file, x, y, w, h, pixmap, sx, sy, sw, sh); }
    void 	drawPixmapFragments(const QPainter::PixmapFragment *fragments, int fragmentCount, const QPixmap &pixmap, QPainter::PixmapFragmentHints hints = QPainter::PixmapFragmentHints(), int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPixmapFragments, line, function, file, fragments, fragmentCount, pixmap, hints); }
    void 	drawPoint(const QPointF &position, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoint, line, function, file, position); }
    void 	drawPoint(const QPoint &position, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoint, line, function, file, position); }
    void 	drawPoint(int x, int y, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoint, line, function, file, x, y); }
    void 	drawPoints(const QPointF *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoints, line, function, file, points, pointCount); }
    void 	drawPoints(const QPolygon &points, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoints, line, function, file, points); }
    void 	drawPoints(const QPolygonF &points, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoints, line, function, file, points); }
    void 	drawPoints(const QPoint *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPoints, line, function, file, points, pointCount); }
    void 	drawPolygon(const QPointF *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolygon, line, function, file, points, pointCount, fillRule); }
    void 	drawPolygon(const QPolygon &points, Qt::FillRule fillRule = Qt::OddEvenFill, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolygon, line, function, file, points, fillRule); }
    void 	drawPolygon(const QPolygonF &points, Qt::FillRule fillRule = Qt::OddEvenFill, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolygon, line, function, file, points, fillRule); }
    void 	drawPolygon(const QPoint *points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolygon, line, function, file, points, pointCount, fillRule); }
    void 	drawPolyline(const QPointF *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolyline, line, function, file, points, pointCount); }
    void 	drawPolyline(const QPolygon &points, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolyline, line, function, file, points); }
    void 	drawPolyline(const QPolygonF &points, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolyline, line, function, file, points); }
    void 	drawPolyline(const QPoint *points, int pointCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawPolyline, line, function, file, points, pointCount); }
    void 	drawRect(const QRectF &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRect, line, function, file, rectangle); }
    void 	drawRect(const QRect &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRect, line, function, file, rectangle); }
    void 	drawRect(int x, int y, int width, int height, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRect, line, function, file, x, y, width, height); }
    void 	drawRects(const QRectF *rectangles, int rectCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRects, line, function, file, rectangles, rectCount); }
    void 	drawRects(const QList<QRect> &rectangles, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRects, line, function, file, rectangles); }
    void 	drawRects(const QList<QRectF> &rectangles, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRects, line, function, file, rectangles); }
    void 	drawRects(const QRect *rectangles, int rectCount, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRects, line, function, file, rectangles, rectCount); }
    void 	drawRoundedRect(const QRectF &rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRoundedRect, line, function, file, rect, xRadius, yRadius, mode); }
    void 	drawRoundedRect(const QRect &rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRoundedRect, line, function, file, rect, xRadius, yRadius, mode); }
    void 	drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawRoundedRect, line, function, file, x, y, w, h, xRadius, yRadius, mode); }
    void 	drawStaticText(const QPointF &topLeftPosition, const QStaticText &staticText, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawStaticText, line, function, file, topLeftPosition, staticText); }
    void 	drawStaticText(const QPoint &topLeftPosition, const QStaticText &staticText, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawStaticText, line, function, file, topLeftPosition, staticText); }
    void 	drawStaticText(int left, int top, const QStaticText &staticText, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawStaticText, line, function, file, left, top, staticText); }
    void 	drawText(const QPointF &position, const QString &text, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, position, text); }
    void 	drawText(const QPoint &position, const QString &text, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, position, text); }
    void 	drawText(const QRectF &rectangle, const QString &text, const QTextOption &option = QTextOption(), int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, rectangle, text, option); }
    void 	drawText(int x, int y, const QString &text, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, x, y, text); }
    void 	drawText(const QRect &rectangle, int flags, const QString &text, QRect *boundingRect = nullptr, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, rectangle, flags, text, boundingRect); }
    void 	drawText(const QRectF &rectangle, int flags, const QString &text, QRectF *boundingRect = nullptr, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, rectangle, flags, text, boundingRect); }
    void 	drawText(int x, int y, int width, int height, int flags, const QString &text, QRect *boundingRect = nullptr, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawText, line, function, file, x, y, width, height, flags, text, boundingRect); }
    void 	drawTiledPixmap(const QRectF &rectangle, const QPixmap &pixmap, const QPointF &position = QPointF(), int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawTiledPixmap, line, function, file, rectangle, pixmap, position); }
    void 	drawTiledPixmap(const QRect &rectangle, const QPixmap &pixmap, const QPoint &position = QPoint(), int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawTiledPixmap, line, function, file, rectangle, pixmap, position); }
    void 	drawTiledPixmap(int x, int y, int width, int height, const QPixmap &pixmap, int sx = 0, int sy = 0, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(drawTiledPixmap, line, function, file, x, y, width, height, pixmap, sx, sy); }
    void 	eraseRect(const QRectF &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(eraseRect, line, function, file, rectangle); }
    void 	eraseRect(const QRect &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(eraseRect, line, function, file, rectangle); }
    void 	eraseRect(int x, int y, int width, int height, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(eraseRect, line, function, file, x, y, width, height); }
    void 	fillPath(const QPainterPath &path, const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillPath, line, function, file, path, brush); }
    void 	fillRect(const QRectF &rectangle, const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, brush); }
    void 	fillRect(const QRect &rectangle, QGradient::Preset preset, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, preset); }
    void 	fillRect(const QRect &rectangle, Qt::BrushStyle style, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, style); }
    void 	fillRect(const QRect &rectangle, Qt::GlobalColor color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, color); }
    void 	fillRect(const QRect &rectangle, const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, brush); }
    void 	fillRect(const QRect &rectangle, const QColor &color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, color); }
    void 	fillRect(const QRectF &rectangle, QGradient::Preset preset, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, preset); }
    void 	fillRect(const QRectF &rectangle, Qt::BrushStyle style, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, style); }
    void 	fillRect(const QRectF &rectangle, Qt::GlobalColor color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, color); }
    void 	fillRect(const QRectF &rectangle, const QColor &color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, rectangle, color); }
    void 	fillRect(int x, int y, int width, int height, QGradient::Preset preset, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, x, y, width, height, preset); }
    void 	fillRect(int x, int y, int width, int height, Qt::BrushStyle style, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, x, y, width, height, style); }
    void 	fillRect(int x, int y, int width, int height, Qt::GlobalColor color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, x, y, width, height, color); }
    void 	fillRect(int x, int y, int width, int height, const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, x, y, width, height, brush); }
    void 	fillRect(int x, int y, int width, int height, const QColor &color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(fillRect, line, function, file, x, y, width, height, color); }
    void 	scale(qreal sx, qreal sy, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(scale, line, function, file, sx, sy); }
    void 	setBackground(const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBackground, line, function, file, brush); }
    void 	setBackgroundMode(Qt::BGMode mode, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBackgroundMode, line, function, file, mode); }
    void 	setBrush(const QBrush &brush, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrush, line, function, file, brush); }
    void 	setBrush(QColor color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrush, line, function, file, color); }
    void 	setBrush(Qt::BrushStyle style, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrush, line, function, file, style); }
    void 	setBrush(Qt::GlobalColor color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrush, line, function, file, color); }
    void 	setBrushOrigin(const QPointF &position, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrushOrigin, line, function, file, position); }
    void 	setBrushOrigin(const QPoint &position, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrushOrigin, line, function, file, position); }
    void 	setBrushOrigin(int x, int y, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setBrushOrigin, line, function, file, x, y); }
    void 	setClipPath(const QPainterPath &path, Qt::ClipOperation operation = Qt::ReplaceClip, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipPath, line, function, file, path, operation); }
    void 	setClipRect(const QRectF &rectangle, Qt::ClipOperation operation = Qt::ReplaceClip, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipRect, line, function, file, rectangle, operation); }
    void 	setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation = Qt::ReplaceClip, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipRect, line, function, file, x, y, width, height, operation); }
    void 	setClipRect(const QRect &rectangle, Qt::ClipOperation operation = Qt::ReplaceClip, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipRect, line, function, file, rectangle, operation); }
    void 	setClipRegion(const QRegion &region, Qt::ClipOperation operation = Qt::ReplaceClip, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipRegion, line, function, file, region, operation); }
    void 	setClipping(bool enable, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setClipping, line, function, file, enable); }
    void 	setCompositionMode(QPainter::CompositionMode mode, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setCompositionMode, line, function, file, mode); }
    void 	setFont(const QFont &font, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setFont, line, function, file, font); }
    void 	setLayoutDirection(Qt::LayoutDirection direction, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setLayoutDirection, line, function, file, direction); }
    void 	setOpacity(qreal opacity, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setOpacity, line, function, file, opacity); }
    void 	setPen(const QPen &pen, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setPen, line, function, file, pen); }
    void 	setPen(Qt::PenStyle style, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setPen, line, function, file, style); }
    void 	setPen(const QColor &color, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setPen, line, function, file, color); }
    void 	setRenderHint(QPainter::RenderHint hint, bool on = true, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setRenderHint, line, function, file, hint, on); }
    void 	setRenderHints(QPainter::RenderHints hints, bool on = true, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setRenderHints, line, function, file, hints, on); }
    void 	setTransform(const QTransform &transform, bool combine = false, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setTransform, line, function, file, transform, combine); }
    void 	setViewTransformEnabled(bool enable, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setViewTransformEnabled, line, function, file, enable); }
    void 	setViewport(const QRect &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setViewport, line, function, file, rectangle); }
    void 	setViewport(int x, int y, int width, int height, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setViewport, line, function, file, x, y, width, height); }
    void 	setWindow(const QRect &rectangle, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setWindow, line, function, file, rectangle); }
    void 	setWindow(int x, int y, int width, int height, int line = __builtin_LINE(), const char *function = __builtin_FUNCTION(), const char *file = __builtin_FILE()) { DEBUG_PAINTER_IMPL(setWindow, line, function, file, x, y, width, height); }
    // clang-format on
};
