#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QAndroidJniObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //【1】
    QAndroidJniObject::callStaticMethod<void>(
                "com.eugo.example.staticsample/MyClass",
                "method1");

    //【2】
    {
        jint ret = QAndroidJniObject::callStaticMethod<jint>(
                    "com.eugo.example.staticsample/MyClass",
                    "method2");
        int retInt = ret;
        qDebug() << "method2() ret" << retInt << ret;
    }

    //【3】
    QAndroidJniObject::callStaticMethod<void>(
                "com.eugo.example.staticsample/MyClass",
                "method3",
                "(I)V",
                100);

    //【4】
    {
        jint ret = QAndroidJniObject::callStaticMethod<jint>(
                    "com.eugo.example.staticsample/MyClass",
                    "method4",
                    "(I)I",
                    100);
        qDebug() << "method4() ret" << ret;
    }

    //【5】
    {
        int data = 100;
        long data2 = 200;
        int ret = QAndroidJniObject::callStaticMethod<jint>(
                    "com.eugo.example.staticsample/MyClass",
                    "method5",
                    "(IJ)I",
                    data,
                    data2);
        qDebug() << "method5() ret" << ret;
    }

    //【6】
    {
        QString str = "Test";
        QAndroidJniObject::callStaticMethod<void>(
                    "com.eugo.example.staticsample/MyClass",
                    "method6",
                    "(Ljava/lang/String;)V",
                    QAndroidJniObject::fromString(str).object<jstring>());

//NG
//        QAndroidJniObject::callStaticObjectMethod(
//                    "com.eugo.example.staticsample/MyClass",
//                    "method6",
//                    "(Ljava/lang/String;)V",
//                    QAndroidJniObject::fromString(str).object<jstring>());
    }

    //【7】
    {
        QAndroidJniObject ret = QAndroidJniObject::callStaticObjectMethod(
                    "com.eugo.example.staticsample/MyClass",
                    "method7",
                    "()Ljava/lang/String;");
        qDebug() << "method7" << ret.toString();

    }

    //【8】
    {
        QString str = "Test";
        QAndroidJniObject ret = QAndroidJniObject::callStaticObjectMethod(
                    "com.eugo.example.staticsample/MyClass",
                    "method8",
                    "(Ljava/lang/String;)Ljava/lang/String;",
                    QAndroidJniObject::fromString(str).object<jstring>());
        qDebug() << "method8" << ret.toString();

    }

    //【9】
    {
        QString str1 = "RICK";
        QString str2 = "DIAS";
        QAndroidJniObject ret = QAndroidJniObject::callStaticObjectMethod(
                    "com.eugo.example.staticsample/MyClass",
                    "method9",
                    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                    QAndroidJniObject::fromString(str1).object<jstring>(),
                    QAndroidJniObject::fromString(str2).object<jstring>());
        qDebug() << "method9" << ret.toString();
    }
    return app.exec();
}
