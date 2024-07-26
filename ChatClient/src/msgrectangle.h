#ifndef MSGRECTANGLE_H
#define MSGRECTANGLE_H

#include <QPainter>
#include <QQuickItem>
#include <QPainterPath>
#include <QQuickPaintedItem>

#ifndef Q_PROPERTY_AUTO
#define Q_PROPERTY_AUTO(TYPE, M)                                                                   \
Q_PROPERTY(TYPE M MEMBER _##M NOTIFY M##Changed)                                               \
    public:                                                                                            \
    Q_SIGNAL void M##Changed();                                                                    \
    void M(const TYPE &in_##M) {                                                                   \
        _##M = in_##M;                                                                             \
        Q_EMIT M##Changed();                                                                       \
}                                                                                              \
    TYPE M() {                                                                                     \
        return _##M;                                                                               \
}                                                                                              \
                                                                                                   \
    private:                                                                                           \
    TYPE _##M;
#endif

class MsgRectangle : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY_AUTO(bool, isLeft)
    Q_PROPERTY_AUTO(QColor, color)

    Q_SIGNAL void colorChange();
    Q_SIGNAL void isLeftChange();

public:

    explicit MsgRectangle(QQuickItem* parent = nullptr);

    void paint(QPainter *painter) override;

private:

    static const int MSGRECTANGLE_RADIUS;
    static const int MSGRECTANGLE_DISTANCE;
    static const int MSGRECTANGLE_TRIANGLE_WIDTH;
    static const int MSGRECTANGLE_TRIANGLE_HEIGHT;

};

#endif // MSGRECTANGLE_H
