#ifndef TANGRAM_H
#define TANGRAM_H
#include <QWidget>
#include <QPixmap>
#include <QVector>

#include "dragwidget.h"

class Tangram : public QWidget
{
    Q_OBJECT
public:
    explicit Tangram(QWidget *parent = nullptr);


public slots:
//void setupPuzzle();
    void game_window();
    //void win_window();
    void inicial_window();


private slots:
    void setCompleted();


private:
    //void chooseShadow();
    //void create_vector_shadow();
    enum {NumShadows = 4, NumPieces = 7};

    struct Piece {
        QPixmap _pixmap;
        QPoint _location;
        QPoint _shadow_location;
        bool correct_position;
        int rotate;
    };

    DragWidget *_frame1 = new DragWidget("Frame-Shadow");
    DragWidget *_frame0 = new DragWidget("Frame-Pieces");

};

#endif // TANGRAM_H
