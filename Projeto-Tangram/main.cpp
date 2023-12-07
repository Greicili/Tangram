#include <QApplication>
#include <tangram.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);

    QApplication app(argc, argv);
    Tangram game;
    QObject::connect(&game, SIGNAL(quit()), &app, SLOT(quit()));
    game.show();
    return app.exec();
}
