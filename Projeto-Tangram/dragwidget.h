#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QString>
#include <piece.h>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DragWidget(int width, int height, QVector<Piece *> pieces, QWidget *parent = nullptr);
    void showPieces(int i);
    int showIndex(){return _index;}

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void changeInPiece();

private:
    enum {NumPieces = 7};
    int _width;
    int _height;
    QVector<Piece *> _pieces;
    int _index;
};
//! [0]

#endif // DRAGWIDGET_H
