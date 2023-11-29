#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QString>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DragWidget(QString name, QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void puzzleCompleted();

private:
    enum {NumShadows = 4, NumPieces = 7};

    struct Piece {
        QPixmap _pixmap;
        QPoint _location;
        QPoint _shadow_location;
        bool correct_position;
        int rotate;
    };

    void addPiece(QString name_image, int scale,  QPoint location, QPoint shadow_location);
    void showPieces(int i);
    void chooseShadow();
    void check_position(int i);

    QString _name;
    QVector<Piece> _pieces;
    QVector<QPixmap> _shadows;
};
//! [0]

#endif // DRAGWIDGET_H
