#include <QApplication>
#include <tangram.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);

    QApplication app(argc, argv);
    Tangram game;
    game.show();
    return app.exec();
}
