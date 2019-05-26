#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsItem>
#include <QSharedPointer>

class GraphNode;

class GraphEdge : public QGraphicsItem
{
public:
    GraphEdge(QSharedPointer<GraphNode> from, QSharedPointer<GraphNode> to);
    ~GraphEdge() override;

    auto fromNode() const;
    auto toNode() const;

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QSharedPointer<GraphNode> fromNode_, toNode_;
    qreal arrowSize_;
};

#endif // GRAPHEDGE_H
