#include "Piece.h"
#include <QGraphicsScene>
#include <QDebug>
#include  "mainwindow.h"

extern MainWindow *mainwindow;
Piece::Piece(QString team,QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    side =team;

}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("pressok");
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
//        .length() < QApplication::startDragDistance()) {
//        return;
//    }
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    drag->setHotSpot(pix.rect().center());
    drag->setPixmap(pix);

    setAcceptDrops(true);

     update();
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<"mouseReleaseEvent"<<endl;
}

void Piece::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    qDebug()<<"dragEnterEvent"<<endl;
    update();
}

void Piece::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"dragLeaveEvent"<<endl;
    update();
}

void Piece::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"dropEvent"<<endl;
    scene()->removeItem(this);

    delete this;
    event->accept();

    update();
}
