#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQuickView>
#include <QQmlContext>
#include "hcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    HController c;

    engine.rootContext()->setContextProperty("controller", &c);

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl){
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
