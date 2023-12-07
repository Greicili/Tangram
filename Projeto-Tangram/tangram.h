#ifndef TANGRAM_H
#define TANGRAM_H
#include <QWidget>
#include <QPixmap>
#include <QVector>

#include "dragwidget.h"
#include "piece.h"
#include "shadow.h"

class Tangram : public QDialog
{
    Q_OBJECT
public:
    explicit Tangram(QWidget *parent = nullptr);

private slots:
    void checkPieces();
    void setCompleted();
    void newGame();
signals:
    void tangramCompleted();
    void quit();

private:
    enum {NumShadows = 4, NumPieces = 7};
    int chooseShadow();
    void addShadow();
    void addPieces();
    void game_window();

    int _indexShadow;
    DragWidget *_frame0;
    DragWidget *_frame1;
    QVector<Piece*> _pieces;
    QVector<Shadow*> _shadows;
    QGridLayout *mainLayout;
};

#endif // TANGRAM_H
