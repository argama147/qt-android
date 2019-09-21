#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtAndroid>
#include "activitycalling.h"


int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Connect QML Signal to C++ Slot
    QObject *root = engine.rootObjects().first();
    ActivityCalling caller;
    caller.connectQml(root);

    return app.exec();
}
