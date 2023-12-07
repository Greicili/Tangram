#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>

class Shadow : public QWidget
{
public:
    Shadow(QString path_image, int scaleShadow, QVector<QPoint> shadow_location, QVector<int> trueIndexRotation, QWidget *parent = nullptr);

    QPoint shadowLocation(int index){return _shadowLocationPieces[index];}
    int trueIndexRotation(int index){return _trueIndexRotation[index];}
    QPixmap shadowImage(){return _shadowImage;}


private:
    QPixmap _shadowImage;
    QVector<QPoint> _shadowLocationPieces;
    QVector<int> _trueIndexRotation;
};

#endif // SHADOW_H

