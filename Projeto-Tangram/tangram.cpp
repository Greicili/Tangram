#include "tangram.h"
#include "dragwidget.h"
#include "QWidget"
#include <iostream>

using namespace std;

Tangram::Tangram(QWidget *parent)
    : QDialog (parent)
{
    addShadow();
    addPieces();
    QPushButton *novoJogo = new QPushButton("NOVO JOGO");
    connect(novoJogo, SIGNAL(clicked()), this, SLOT(newGame()));
    novoJogo->setFixedWidth(600);

    QPushButton *quit = new QPushButton("SAIR");
    connect(quit, SIGNAL(clicked()), this, SIGNAL(quit()));
    quit->setFixedWidth(360);


    mainLayout = new QGridLayout;
    mainLayout->addWidget(novoJogo, 0, 0);
    mainLayout->addWidget(quit, 0, 1);



    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setFixedSize(1000,380);
    setStyleSheet("font-size: 15px;");
    setWindowTitle(tr("Jogo - Tangram"));

    connect(this, SIGNAL(tangramCompleted()), this, SLOT(setCompleted()));

    game_window();
}

void Tangram::game_window(){

    _frame0 = new DragWidget(600,360, _pieces, this);
    _frame1 = new DragWidget(360,360, _pieces, this);
    mainLayout->addWidget(_frame0, 1, 0);
    mainLayout->addWidget(_frame1, 1, 1);

   for (int i = 0; i < NumPieces; i++ )
       _frame0->showPieces(i);

   _indexShadow = chooseShadow();
   QPalette palette;
   palette.setBrush(QPalette::Window, _shadows[_indexShadow]->shadowImage());
   _frame1->setPalette(palette);
   _frame1->setAutoFillBackground(true);

   connect(_frame1, SIGNAL(changeInPiece()), this, SLOT(checkPieces()));
   setLayout(mainLayout);
}

int Tangram::chooseShadow(){
    int index = QRandomGenerator::global()->bounded(0,NumShadows);
    cout << "\n\n\n Sombra index: " << index << endl;
   return index;
}
void Tangram::setCompleted(){
   QMessageBox::information(this, tr("*** TANGRAM ESTÁ COMPLETO ***"),
                            tr("Parabéns! Você completou o Tangram!\n"
                               "Clique no OK para jogar uma nova partida."),
                            QMessageBox::Ok);
   newGame();
}

void Tangram::newGame(){
   _frame0->close();
   _frame1->close();
   _pieces.clear();
   addPieces();
   game_window();
}

void Tangram::addShadow(){

   QVector<QPoint> shadow_location;
   QVector<int> trueIndexRotation;
   int scaleShadow = 360;

   QString path_images = ":/image/sombra.png";
   shadow_location.push_back(QPoint(2,23));
   shadow_location.push_back(QPoint(118,159));
   shadow_location.push_back(QPoint(35,202));
   shadow_location.push_back(QPoint(-3,83));
   shadow_location.push_back(QPoint(85,114));
   shadow_location.push_back(QPoint(94,13));
   shadow_location.push_back(QPoint(-36,84));
   trueIndexRotation.push_back(1);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(4);
   trueIndexRotation.push_back(2);
   trueIndexRotation.push_back(1);
   trueIndexRotation.push_back(4);
   trueIndexRotation.push_back(6);

   _shadows.push_back(new Shadow(path_images, scaleShadow, shadow_location, trueIndexRotation));
   shadow_location.clear();
   trueIndexRotation.clear();


   path_images = ":/image/sombra1.png";
   shadow_location.push_back(QPoint(181,209));
   shadow_location.push_back(QPoint(-6,31));
   shadow_location.push_back(QPoint(136,150));
   shadow_location.push_back(QPoint(61,210));
   shadow_location.push_back(QPoint(129,31));
   shadow_location.push_back(QPoint(35,130));
   shadow_location.push_back(QPoint(121,47));
   trueIndexRotation.push_back(1);
   trueIndexRotation.push_back(2);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(4);
   trueIndexRotation.push_back(0);

   _shadows.push_back(new Shadow(path_images, scaleShadow, shadow_location, trueIndexRotation));
   shadow_location.clear();
   trueIndexRotation.clear();


   path_images = ":/image/sombra2.png";
   shadow_location.push_back(QPoint(62,150));
   shadow_location.push_back(QPoint(60,166));
   shadow_location.push_back(QPoint(197,151));
   shadow_location.push_back(QPoint(3,-27));
   shadow_location.push_back(QPoint(70,30));
   shadow_location.push_back(QPoint(215,2));
   shadow_location.push_back(QPoint(62,49));
   trueIndexRotation.push_back(1);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);

   _shadows.push_back(new Shadow(path_images, scaleShadow, shadow_location, trueIndexRotation));
   shadow_location.clear();
   trueIndexRotation.clear();


   path_images = ":/image/sombra3.png";
   shadow_location.push_back(QPoint(71,239));
   shadow_location.push_back(QPoint(70,16));
   shadow_location.push_back(QPoint(85,0));
   shadow_location.push_back(QPoint(186,180));
   shadow_location.push_back(QPoint(70,117));
   shadow_location.push_back(QPoint(104,219));
   shadow_location.push_back(QPoint(176,-1));
   trueIndexRotation.push_back(1);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(0);
   trueIndexRotation.push_back(2);
   trueIndexRotation.push_back(6);
   trueIndexRotation.push_back(4);
   trueIndexRotation.push_back(2);

   _shadows.push_back(new Shadow(path_images, scaleShadow, shadow_location, trueIndexRotation));
   shadow_location.clear();
   trueIndexRotation.clear();

}
void Tangram::addPieces(){
QVector<QString> path_images;
path_images.push_back(":/image/Imagem1.png");
path_images.push_back(":/image/Imagem1-1.png");
_pieces.push_back(new Piece(path_images, 2, 120,  QPoint(10,5)));

path_images.clear();
path_images.push_back(":/image/Imagem2.png");
path_images.push_back(":/image/Imagem2-1.png");
path_images.push_back(":/image/Imagem2-2.png");
path_images.push_back(":/image/Imagem2-3.png");
path_images.push_back(":/image/Imagem2-4.png");
path_images.push_back(":/image/Imagem2-5.png");
path_images.push_back(":/image/Imagem2-6.png");
path_images.push_back(":/image/Imagem2-7.png");
_pieces.push_back(new Piece(path_images, 8, 240,  QPoint(337,-32)));

path_images.clear();
path_images.push_back(":/image/Imagem3.png");
path_images.push_back(":/image/Imagem3-1.png");
path_images.push_back(":/image/Imagem3-2.png");
path_images.push_back(":/image/Imagem3-3.png");
path_images.push_back(":/image/Imagem3-4.png");
path_images.push_back(":/image/Imagem3-5.png");
path_images.push_back(":/image/Imagem3-6.png");
path_images.push_back(":/image/Imagem3-7.png");
_pieces.push_back(new Piece(path_images, 8, 120,  QPoint(299,202)));

path_images.clear();
path_images.push_back(":/image/Imagem4.png");
path_images.push_back(":/image/Imagem4-1.png");
path_images.push_back(":/image/Imagem4-2.png");
path_images.push_back(":/image/Imagem4-3.png");
_pieces.push_back(new Piece(path_images, 4, 180,  QPoint(141,-26)));

path_images.clear();
path_images.push_back(":/image/Imagem5.png");
path_images.push_back(":/image/Imagem5-1.png");
path_images.push_back(":/image/Imagem5-2.png");
path_images.push_back(":/image/Imagem5-3.png");
path_images.push_back(":/image/Imagem5-4.png");
path_images.push_back(":/image/Imagem5-5.png");
path_images.push_back(":/image/Imagem5-6.png");
path_images.push_back(":/image/Imagem5-7.png");
_pieces.push_back(new Piece(path_images, 8, 240,  QPoint(-45,110)));

path_images.clear();
path_images.push_back(":/image/Imagem6.png");
path_images.push_back(":/image/Imagem6-1.png");
path_images.push_back(":/image/Imagem6-2.png");
path_images.push_back(":/image/Imagem6-3.png");
path_images.push_back(":/image/Imagem6-4.png");
path_images.push_back(":/image/Imagem6-5.png");
path_images.push_back(":/image/Imagem6-6.png");
path_images.push_back(":/image/Imagem6-7.png");
_pieces.push_back(new Piece(path_images, 8, 170,  QPoint(150, 150)));

path_images.clear();
path_images.push_back(":/image/Imagem7.png");
path_images.push_back(":/image/Imagem7-1.png");
path_images.push_back(":/image/Imagem7-2.png");
path_images.push_back(":/image/Imagem7-3.png");
path_images.push_back(":/image/Imagem7-4.png");
path_images.push_back(":/image/Imagem7-5.png");
path_images.push_back(":/image/Imagem7-6.png");
path_images.push_back(":/image/Imagem7-7.png");
_pieces.push_back(new Piece(path_images, 8, 120,  QPoint(445,185)));
path_images.clear();
}


void Tangram::checkPieces(){
int i = _frame1->showIndex();
if ((_pieces[i]->getLocation().x() > _shadows[_indexShadow]->shadowLocation(i).x() - 5) && (_pieces[i]->getLocation().x() < _shadows[_indexShadow]->shadowLocation(i).x() + 5) && (_pieces[i]->getLocation().y() > _shadows[_indexShadow]->shadowLocation(i).y() - 5) && (_pieces[i]->getLocation().y() < _shadows[_indexShadow]->shadowLocation(i).y() + 5) && (_pieces[i]->indexPieceRotation() == _shadows[_indexShadow]->trueIndexRotation(i)))
       _pieces[i]->correctPosition(true);
else
       _pieces[i]->correctPosition(false);

int soma  = 0;
for(int i = 0;(i < NumPieces) && (_pieces[i]->correctPosition() == true); i++)
       soma +=1;

if (soma == 7)
       emit tangramCompleted();
}
