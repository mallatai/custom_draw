#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsItem>
#include <QList>

class QGraphicsView;
class GraphEdge;

class GraphNode : public QGraphicsItem
{
public:
    GraphNode(int index, QGraphicsView *parent = nullptr);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    int index() const;
    void setIndex(int index);

    void addEdge(GraphEdge *edge);
    void removeEdge(GraphEdge *edge);
    QList<GraphEdge*> edges() const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    int index_;
    QGraphicsView* graphView_;
    QList<GraphEdge*> edges_;
};

#endif // GRAPHNODE_H
