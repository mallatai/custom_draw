#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsView>
#include <QTimer>

class QGraphicsScene;
class GraphNode;

class GraphScene : public QGraphicsView
{
    Q_OBJECT

public:
    GraphScene(QWidget* parent = nullptr);

    enum ArrowDrawingState { NotDrawing, InDrawing };

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    static int graphIndex_;
    QGraphicsScene* scene_;

    GraphNode *sourceNode_;
    ArrowDrawingState drawingState_;
    QTimer pressReleaseEventDiffTime_;
};

#endif // GRAPHSCENE_H
