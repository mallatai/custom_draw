#include "graphnode.h"

#include <QGraphicsView>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QFont>

#include <QDebug>

GraphNode::GraphNode(int index, QGraphicsView *parent)
    : index_(index), graphView_(parent)
{
    setToolTip("fuck off");
    setFlag(QGraphicsItem::ItemIsSelectable);
}

int GraphNode::index() const
{
    return index_;
}

void GraphNode::setIndex(int index)
{
    index_ = index;
}

void GraphNode::addEdge(GraphEdge *edge)
{
    if (edge)
        edges_ << edge;
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    edges_.removeOne(edge);
}

QList<GraphEdge*> GraphNode::edges() const
{
    return edges_;
}

QRectF GraphNode::boundingRect() const
{
    return QRectF(-15,-15,30,30);
}

QPainterPath GraphNode::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-15,-15,30,30));
    return path;
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::blue, 3));
    painter->setBrush(Qt::transparent);
    painter->drawEllipse(-15,-15,30,30);

    QPainterPath indexNumberPath;
    indexNumberPath.addText(-5,2, QFont("Courier", 10), QString::number(index_));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawPath(indexNumberPath);
}

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphNode mousePressEvent";
//    setCursor(Qt::CrossCursor);
//    setSelected(true);
//    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    setCursor(Qt::ArrowCursor);
//    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant GraphNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {
        // TODO redraw edges when item is moved
    }

    return QGraphicsItem::itemChange(change, value);
}
