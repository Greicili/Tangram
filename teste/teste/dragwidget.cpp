#include <QtWidgets>

#include "dragwidget.h"
#include "pieces.h"
#include <iostream>

using namespace std;

//! [0]
DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setFixedSize(600,300);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);


    for (int i = 0; i < 7; i++ ){
        showPieces(i);
    }



    /*

    QLabel *imagem1 = new QLabel(this);
    imagem1->setPixmap(QPixmap(":/images/Imagem1.png").scaledToHeight(120));
    imagem1->move(10, 5);
    imagem1->show();
    imagem1->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem2 = new QLabel(this);
    imagem2->setPixmap(QPixmap(":/images/Imagem2.png").scaledToHeight(120));
    imagem2->move(300, 20);
    imagem2->show();
    imagem2->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem3 = new QLabel(this);
    imagem3->setPixmap(QPixmap(":/images/Imagem3.png").scaledToHeight(120));
    imagem3->move(300, 150);
    imagem3->show();
    imagem3->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem4 = new QLabel(this);
    imagem4->setPixmap(QPixmap(":/images/Imagem4.png").scaledToHeight(180));
    imagem4->move(200, 5);
    imagem4->show();
    imagem4->setAttribute(Qt::WA_DeleteOnClose);


    QLabel *imagem5 = new QLabel(this);
    imagem5->setPixmap(QPixmap(":/images/Imagem5.png").scaledToHeight(170));
    imagem5->move(10, 130);
    imagem5->show();
    imagem5->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem6 = new QLabel(this);
    imagem6->setPixmap(QPixmap(":/images/Imagem6.png").scaledToHeight(120));
    imagem6->move(150, 150);
    imagem6->show();
    imagem6->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *imagem7 = new QLabel(this);
    imagem7->setPixmap(QPixmap(":/images/Imagem7.png").scaledToHeight(120));
    imagem7->move(400, 150);
    imagem7->show();
    imagem7->setAttribute(Qt::WA_DeleteOnClose);
*/
}
//! [0]
void DragWidget::showPieces(int index){
    Pieces *formas = new Pieces(this);
    formas->setPixmap(formas->_pieces[index]._pixmap);
    formas->move(formas->_pieces[index]._location);
    formas->show();
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

         //essa parte move os objetos dentro do frame1
        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);


        if((newIcon->x() < 0) && (newIcon->y() < 0))
            newIcon->move(0,0);
        else if (newIcon->x() < 0)
            newIcon->move(0,newIcon->y());
        else if (newIcon->y() < 0)
            newIcon->move(newIcon->x(),0);

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }
}

//! [1]
void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
    //! [1]

    //! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    //! [2]

    //! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
    //! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
