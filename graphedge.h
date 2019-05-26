#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsItem>

class GraphNode;

class GraphEdge : public QGraphicsItem
{
public:
    GraphEdge(GraphNode* from, GraphNode* to);

    auto fromNode() const;
    auto toNode() const;

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    void init();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    GraphNode *fromNode_, *toNode_;
    QPointF sourcePoint, destPoint;
    qreal arrowSize_;
};

#endif // GRAPHEDGE_H
