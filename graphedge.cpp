#include "graphedge.h"

#include "graphnode.h"

GraphEdge::GraphEdge(QSharedPointer<GraphNode> from, QSharedPointer<GraphNode> to)
    : fromNode_(from), toNode_(to),
      arrowSize_(10)
{

}

GraphEdge::~GraphEdge()
{

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
    if (fromNode_.isNull() || toNode_.isNull())
        return QRectF();

    qreal penWidth = 1;
    qreal extraWidth = (penWidth + arrowSize_) / 2.0;

    return QRectF();
//    return QRectF(fromNode_->);
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
