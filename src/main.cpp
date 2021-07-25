#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"
#include "process.h"
#include "mpv.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<Process>("Process", 1, 0, "Process");
    qmlRegisterType<Mpv>("Mpv", 1, 0, "Mpv");

    QQmlApplicationEngine engine;
    BackEnd backend;
    engine.rootContext()->setContextProperty("BackEnd", &backend);
    engine.load(QUrl(QStringLiteral("qrc://⁄src/main.qml")));
    return app.exec();
}
