#include "mainwindow.h"

#include "graphscene.h"
#include "graphnode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene_ = new GraphScene(this);
    scene_->setSceneRect(0,0,700,500);
    scene_->resize(750, 550);
    scene_->centerOn(0.0, 0.0);
    scene_->show();

//    view_ = new QGraphicsView(scene_, this);
//    view_->setScene(scene_);
//    view_->resize(750, 550);
//    view_->centerOn(0.0, 0.0);
//    view_->show();

//    static int graphIndex = 0;
//    auto item = new GraphNode(++graphIndex, view_);
//    scene_->addItem(item);
//    item->setPos(100, 100);
}

MainWindow::~MainWindow()
{

}
