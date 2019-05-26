#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsView>

class QGraphicsScene;
class GraphNode;

class GraphScene : public QGraphicsView
{
    Q_OBJECT

public:
    GraphScene(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    static int graphIndex_;
    QGraphicsScene* scene_;
};

#endif // GRAPHSCENE_H
