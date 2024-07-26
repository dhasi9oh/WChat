#include "msgrectangle.h"

const int MsgRectangle::MSGRECTANGLE_RADIUS = 4;
const int MsgRectangle::MSGRECTANGLE_DISTANCE = 8;
const int MsgRectangle::MSGRECTANGLE_TRIANGLE_WIDTH = 6;
const int MsgRectangle::MSGRECTANGLE_TRIANGLE_HEIGHT = 4;

MsgRectangle::MsgRectangle(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    _isLeft = true;
    _color = QColor(255, 255, 255);
}

void MsgRectangle::paint(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF rect = boundingRect();
    painter->setPen(Qt::NoPen);
    painter->setBrush(_color);
    painter->drawRoundedRect(rect, MSGRECTANGLE_RADIUS, MSGRECTANGLE_RADIUS);

    painter->setBrush(Qt::transparent);
    painter->setCompositionMode(QPainter::CompositionMode_Clear);

    int w = rect.width();
    int h = rect.height();
    QPainterPath clear_path;

    if (_isLeft) {
        clear_path.moveTo(QPointF(0, 0));
        clear_path.lineTo(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT + MSGRECTANGLE_RADIUS, 0));
        clear_path.arcTo(
            QRectF(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT, 0),
                   QSize(MSGRECTANGLE_RADIUS * 2, MSGRECTANGLE_RADIUS * 2))
            , 90, 90);
        clear_path.lineTo(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT, MSGRECTANGLE_DISTANCE));
        clear_path.lineTo(QPointF(0, MSGRECTANGLE_DISTANCE + MSGRECTANGLE_TRIANGLE_WIDTH / 2));
        clear_path.lineTo(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT, MSGRECTANGLE_DISTANCE + MSGRECTANGLE_TRIANGLE_WIDTH));
        clear_path.lineTo(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT, h - MSGRECTANGLE_RADIUS));
        clear_path.arcTo(
            QRectF(QPointF(MSGRECTANGLE_TRIANGLE_HEIGHT, h - 2 * MSGRECTANGLE_RADIUS),
                   QSize(MSGRECTANGLE_RADIUS * 2, MSGRECTANGLE_RADIUS * 2))
            , 180, 90);
        clear_path.lineTo(QPointF(0, h));
        clear_path.lineTo(QPointF(0, 0));
    }
    else {
        clear_path.moveTo(QPointF(w, 0));
        clear_path.lineTo(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT - MSGRECTANGLE_RADIUS, 0));
        clear_path.arcTo(
            QRectF(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT - MSGRECTANGLE_RADIUS * 2, 0),
                   QSize(MSGRECTANGLE_RADIUS * 2, MSGRECTANGLE_RADIUS * 2))
            , 90, -90);
        clear_path.lineTo(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT, MSGRECTANGLE_DISTANCE));
        clear_path.lineTo(QPointF(w, MSGRECTANGLE_DISTANCE + MSGRECTANGLE_TRIANGLE_WIDTH / 2));
        clear_path.lineTo(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT, MSGRECTANGLE_DISTANCE + MSGRECTANGLE_TRIANGLE_WIDTH));
        clear_path.lineTo(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT, h - MSGRECTANGLE_RADIUS));
        clear_path.arcTo(
            QRectF(QPointF(w - MSGRECTANGLE_TRIANGLE_HEIGHT - MSGRECTANGLE_RADIUS * 2, h - MSGRECTANGLE_RADIUS * 2),
                   QSize(MSGRECTANGLE_RADIUS * 2, MSGRECTANGLE_RADIUS * 2))
            , 0, -90);
        clear_path.lineTo(QPointF(w, h));
        clear_path.lineTo(QPointF(w, 0));
    }

    painter->drawPath(clear_path);
    painter->restore();
}
