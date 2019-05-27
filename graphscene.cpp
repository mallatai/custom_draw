#include "graphscene.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>

#include "graphnode.h"
#include "graphedge.h"

#include <QDebug>

int GraphScene::graphIndex_ = 0;

GraphScene::GraphScene(QWidget* parent)
    : QGraphicsView(parent)
{
    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    setRenderHint(QPainter::Antialiasing);
    setWindowTitle("Custom draw");

    drawingState_ = NotDrawing;

    pressReleaseEventDiffTime_.setSingleShot(true);
    connect(&pressReleaseEventDiffTime_, &QTimer::timeout, [this] () {
        drawingState_ = InDrawing;
    });
}

void GraphScene::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::RightButton:
    {
        auto itemAtPos = itemAt(event->pos());
        if (itemAtPos) {
            pressReleaseEventDiffTime_.start(400);
            sourceNode_ = dynamic_cast<GraphNode*>(itemAtPos);
        }

        QGraphicsView::mousePressEvent(event);
    }
        break;
    case Qt::LeftButton:
    {
        if (itemAt(event->pos())) {
            break;
        }

        auto item = new GraphNode(-1, this);
        item->setPos(event->x() - 23, event->y() - 23);
        scene_->addItem(item);
        if (item->collidingItems().size()) {
            scene_->removeItem(item);
            break;
        }
        item->setIndex(++graphIndex_);
    }
        break;
    default:
        QGraphicsView::mousePressEvent(event);
        break;
    }
}

void GraphScene::mouseReleaseEvent(QMouseEvent *event)
{
    pressReleaseEventDiffTime_.stop();

    if (event->button() != Qt::RightButton) {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }

    qDebug() << "Mouse release" << (drawingState_ == InDrawing) << sourceNode_;

    switch (drawingState_) {
    case NotDrawing:
    {
        if (event->button() == Qt::RightButton) {
            qDebug() << "GraphScene mouseReleaseEvent";
            for (auto item : items(event->pos())) {
                if (GraphNode *graphNode = qgraphicsitem_cast<GraphNode*>(item)) {
                    for (auto edge : graphNode->edges()) {
                        scene_->removeItem(edge);
                        delete edge;
                    }
                    scene_->removeItem(graphNode);
                }
            }
        }
    }
        break;
    case InDrawing:
    {
        qDebug() << "InDrawing" << sourceNode_;
        if (!sourceNode_)
            break;

        auto itemAtPos = dynamic_cast<GraphNode*>(itemAt(event->pos()));
        if (itemAtPos && sourceNode_) {
            auto graphEdge = new GraphEdge(sourceNode_, itemAtPos);

            qDebug() << "Adding graphEdge" << graphEdge;

            sourceNode_->addEdge(graphEdge);
            itemAtPos->addEdge(graphEdge);

            scene_->addItem(graphEdge);
        }
    }
        break;
    }

    QGraphicsView::mouseReleaseEvent(event);

    sourceNode_ = nullptr;

    drawingState_ = NotDrawing;
}
