#include <QtWidgets>
#include "dragwidget.h"

#include <iostream>

using namespace std;

DragWidget::DragWidget(int width, int height, QVector<Piece *> pieces,  QWidget *parent)
    : QFrame(parent)
{
    _pieces = pieces;
    setFixedSize(width,height);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
}

void DragWidget::showPieces(int i){
    QLabel *piece = new QLabel(this);
    piece->setPixmap(_pieces[i]->pieceImage(0));
    piece->move(_pieces[i]->getLocation());
    piece->show();
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
        bool found = false;
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

       cout << "x = " << newIcon->x() << " y = " << newIcon->y() << endl;


        for(int i = 0; i < NumPieces; i++){
            for (int j = 0; j < _pieces[i]->numRotation(); j++){
                if(newIcon->pixmap(Qt::ReturnByValue).toImage() == _pieces[i]->pieceImage(j).toImage()){
                    _pieces[i]->setLocation(newIcon->pos());
                    _index = i;
                    emit changeInPiece();
                    found = true;
                    break;
                }
            }
            if(found)
                break;
        }
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

    // Movimentar as peças
    if(event->button() == Qt::LeftButton){
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
        }
    }

    //Rotacionar as peças
    if(event->button() == Qt::RightButton){
        bool found = false;

        for(int i = 0; i < NumPieces; i++){
            for (int j = 0; j < _pieces[i]->numRotation(); j++){
                if (child->pixmap(Qt::ReturnByValue).toImage() == _pieces[i]->pieceImage(j).toImage())
                {
                    if(j+1 == _pieces[i]->numRotation())
                        _pieces[i]->indexPieceRotation(0);
                    else
                        _pieces[i]->indexPieceRotation(j+1);

                    child->setPixmap(_pieces[i]->pieceImage(_pieces[i]->indexPieceRotation()));
                    _index = i;
                    cout << "index change " << _index <<  endl;
                    emit changeInPiece();
                    found = true;
                    break;
                }
            }
            if(found)
                break;
        }
    }
}

