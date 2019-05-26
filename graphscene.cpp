#include "graphscene.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>

#include "graphnode.h"

#include <QDebug>

int GraphScene::graphIndex_ = 0;

GraphScene::GraphScene(QWidget* parent)
    : QGraphicsView(parent)
{
    scene_ = new QGraphicsScene(this);
    setScene(scene_);

    setRenderHint(QPainter::Antialiasing);
    setWindowTitle("Custom draw");
}

void GraphScene::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::RightButton:
    {
        for (auto item : items(event->pos())) {
            scene_->removeItem(item);
        }
    }
        break;
    case Qt::LeftButton:
    {
        if (QGraphicsItem* item = itemAt(event->pos())) {
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
