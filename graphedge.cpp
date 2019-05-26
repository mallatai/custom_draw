#include "graphedge.h"

#include <QPainter>
#include <QtMath>

#include "graphnode.h"

#include <QDebug>

GraphEdge::GraphEdge(GraphNode* from, GraphNode* to)
    : fromNode_(from), toNode_(to),
      arrowSize_(10)
{
    init();
}

void GraphEdge::init()
{
    if (!fromNode_|| !toNode_)
        return;

    QLineF line(mapFromItem(fromNode_, 0, 0), mapFromItem(toNode_, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

auto GraphEdge::fromNode() const
{
    return fromNode_;
}

auto GraphEdge::toNode() const
{
    return toNode_;
}

QRectF GraphEdge::boundingRect() const
{
    if (!fromNode_ || !toNode_)
        return QRectF();

    qreal penWidth = 1;
    qreal extraWidth = (penWidth + arrowSize_) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extraWidth, -extraWidth, extraWidth, extraWidth);
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!fromNode_ || !toNode_)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    double angle = qAtan2(-line.dy(), line.dx());

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize_,
                                              cos(angle - M_PI / 3) * arrowSize_);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize_,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize_);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
