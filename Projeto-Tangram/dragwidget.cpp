#include <QtWidgets>
#include "dragwidget.h"

#include <iostream>
using namespace std;

//! [0]
DragWidget::DragWidget(QString name, QWidget *parent)
    : QFrame(parent), _name(name)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    //Criando o vetor de peças
    addPiece(QString(":/image/Imagem1.png"), 120, QPoint(10,5), QPoint(1,0));
    addPiece(QString(":/image/Imagem2.png"), 120, QPoint(300,20), QPoint(119,179));
    addPiece(QString(":/image/Imagem3.png"), 120, QPoint(300,150), QPoint(60,180));
    addPiece(QString(":/image/Imagem4.png"), 180, QPoint(200,5), QPoint(60,61));
    addPiece(QString(":/image/Imagem5.png"), 170, QPoint(10,130), QPoint(119,130));
    addPiece(QString(":/image/Imagem6.png"), 120, QPoint(150,150), QPoint(119,10));
    addPiece(QString(":/image/Imagem7.png"), 120, QPoint(400,150), QPoint(1,60));
    //chooseShadow();

    if (_name == "Frame-Pieces")
    {
        setFixedSize(600,300);
        for (int i = 0; i < NumPieces; i++ )
            showPieces(i);
    }
    else if (_name == "Frame-Shadow"){
        setFixedSize(360,300);
        QPixmap bkgnd(":/image/sombra.png");
        bkgnd = bkgnd.scaledToHeight(300);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        setPalette(palette);
        setAutoFillBackground(true);
    }
}
//! [0]


void DragWidget::addPiece(QString name_image, int scale,  QPoint location, QPoint shadow_location)
{
    Piece new_piece;
    QPixmap pixmap;
    pixmap.load(name_image);
    pixmap = pixmap.scaledToHeight(scale);
    new_piece._pixmap = pixmap;
    new_piece._location = location;
    new_piece._shadow_location = shadow_location;

    _pieces.push_back(new_piece);
}

void DragWidget::showPieces(int i){
    QLabel *formas = new QLabel(this);
    formas->setPixmap(_pieces[i]._pixmap);
    formas->move(_pieces[i]._location);
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

        for(int i = 0; i < NumPieces; i++){
            if(newIcon->pixmap()->toImage() == _pieces[i]._pixmap.toImage()){
                _pieces[i]._location = newIcon->pos();
                if(_name == "Frame-Shadow" )
                    check_position(i);
                break;
            }
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
    //! [2]

    //! [3]
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
        else {
            child->show();
            child->setPixmap(pixmap);
        }
    }

    if(event->button() == Qt::RightButton){
        /*
         * QPixmap original;
// load original from your source or take it from somewhere
QImage srcImg = original.toImage();
QPoint center = srcImg.rect().center();
QMatrix matrix;
matrix.translate(center.x(), center.y());
matrix.rotate(90);
QImage dstImg = srcImage.transformed(matrix);
QPixmap dstPix = QPixmap::fromImage(dstImg); //New pixmap rotated
*/

        QPixmap tempPixmap = pixmap;
        QTransform t;
        t.rotate(45);

        //QMatrix matrix;
        //matrix.rotate(45);
        //tempPixmap = tempPixmap.transformed(matrix);
        tempPixmap = tempPixmap.transformed(t);

        //QPainter painter(&tempPixmap);
        //painter.rotate(45);
        //painter.end();

        //child->setPixmap(tempPixmap);
        //child->show();
        //QLabel *newIcon = new QLabel(this);
        child->setFrameRect(tempPixmap.rect());
        child->setPixmap(tempPixmap);
        child->show();
        child->setAttribute(Qt::WA_DeleteOnClose);


        //cout << child->height() << endl;



    }

}
void DragWidget::check_position(int i)
{
    if((_pieces[i]._location.y() > _pieces[i]._shadow_location.y() - 5) && (_pieces[i]._location.y() < _pieces[i]._shadow_location.y() + 5) && (_pieces[i]._location.x() > _pieces[i]._shadow_location.x() - 5) && (_pieces[i]._location.x() < _pieces[i]._shadow_location.x() + 5))
        _pieces[i].correct_position = true;
    else
        _pieces[i].correct_position = false;

    for (i=0; i < NumPieces; i++){
        if ( _pieces[i].correct_position == false)
            break;
        if ((i == 6) && (_pieces[i].correct_position == true) )
            emit puzzleCompleted();
    }
}


void DragWidget::chooseShadow(){
    int index_shadow = QRandomGenerator::global()->bounded(1,NumShadows);
    printf("\n\n%d\n", index_shadow);
}
