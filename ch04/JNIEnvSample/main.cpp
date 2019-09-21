#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
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
    QAndroidJniObject *instance = new QAndroidJniObject(
                "com.eugo.example.jnienvsample.MyClass");

    instance->callMethod<void>(
                "method1");

    QAndroidJniEnvironment env;
    // JNIクラスオブジェクト
    jclass jniClassObject = env->GetObjectClass(instance->object());
    // JNIクラスメソッド
    jmethodID methodId1 = env->GetMethodID(jniClassObject, "method1", "()V");
    env->CallVoidMethod(instance->object(),
                        methodId1);

    //【2】
    {
        jint ret = instance->callMethod<jint>(
                    "method2");
        int retInt = ret;
        qDebug() << "method2() ret" << retInt << ret;

        jmethodID methodId2 = env->GetMethodID(jniClassObject, "method2", "()I");
        ret = env->CallIntMethod(instance->object(),
                                 methodId2);
        qDebug() << "method2() ret" << retInt << ret;
    }

    //【3】
    instance->callMethod<void>(
                "method3",
                "(I)V",
                100);
    jmethodID methodId3 = env->GetMethodID(jniClassObject, "method3", "(I)V");
    env->CallVoidMethod(instance->object(),
                        methodId3,
                        100);

    //【4】
    {
        jint ret = instance->callMethod<jint>(
                    "method4",
                    "(I)I",
                    100);
        qDebug() << "method4() ret" << ret;

        jmethodID methodId4 = env->GetMethodID(jniClassObject, "method4", "(I)I");
        ret = env->CallIntMethod(
                    instance->object(),
                    methodId4,
                    ret);
        qDebug() << "method4() ret" << ret;
    }

    //【5】
    {
        int data = 100;
        long data2 = 200;
        int ret = instance->callMethod<jint>(
                    "method5",
                    "(IJ)I",
                    data,
                    data2);
        qDebug() << "method5() ret" << ret;

        jmethodID methodId5 = env->GetMethodID(jniClassObject, "method5", "(IJ)I");
        ret = env->CallIntMethod(
                    instance->object(),
                    methodId5,
                    data + ret,
                    data2 + ret);
        qDebug() << "method5() ret" << ret;
    }

    //【6】
    {
        QString str = "Test";
        instance->callMethod<void>(
                    "method6",
                    "(Ljava/lang/String;)V",
                    QAndroidJniObject::fromString(str).object<jstring>());

        jmethodID methodId6 = env->GetMethodID(jniClassObject, "method6", "(Ljava/lang/String;)V");
        env->CallVoidMethod(
                    instance->object(),
                    methodId6,
                    QAndroidJniObject::fromString(str).object<jstring>());
    }

    //【6】-2
    {
        QString str = "Test";
        instance->callMethod<void>(
                    "method6",
                    "(Landroid/content/Context;Ljava/lang/String;)V",
                    QtAndroid::androidContext().object<jobject>(),
                    QAndroidJniObject::fromString(str).object<jstring>());

//        jmethodID methodId6 = env->GetMethodID(jniClassObject, "method6", "(Ljava/lang/String;)V");
//        env->CallVoidMethod(
//                    instance->object(),
//                    methodId6,
//                    QAndroidJniObject::fromString(str).object<jstring>());
    }

    //【7】
    {
        QAndroidJniObject ret = instance->callObjectMethod(
                    "method7",
                    "()Ljava/lang/String;");
        qDebug() << "method7" << ret.toString();

        jmethodID methodId7 = env->GetMethodID(jniClassObject, "method7", "()Ljava/lang/String;");
        jobject obj = env->CallObjectMethod(
                    instance->object(),
                    methodId7);
        QAndroidJniObject androidJniObj(obj);
        qDebug() << "method7" << androidJniObj.toString();
    }

    //【8】
    {
        QString str = "Test";
        QAndroidJniObject ret = instance->callObjectMethod(
                    "method8",
                    "(Ljava/lang/String;)Ljava/lang/String;",
                    QAndroidJniObject::fromString(str).object<jstring>());
        qDebug() << "method8" << ret.toString();

        jmethodID methodId8 = env->GetMethodID(jniClassObject,
                                               "method8",
                                               "(Ljava/lang/String;)Ljava/lang/String;");
        jobject obj = env->CallObjectMethod(
                    instance->object(),
                    methodId8,
                    QAndroidJniObject::fromString(str).object<jstring>());
        QAndroidJniObject androidJniObj(obj);
        qDebug() << "method8" << androidJniObj.toString();
    }

    //【9】
    {
        QString str1 = "RICK";
        QString str2 = "DIAS";
        QAndroidJniObject ret = instance->callObjectMethod(
                    "method9",
                    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                    QAndroidJniObject::fromString(str1).object<jstring>(),
                    QAndroidJniObject::fromString(str2).object<jstring>());
        qDebug() << "method9" << ret.toString();

        jmethodID methodId9 = env->GetMethodID(jniClassObject,
                                               "method9",
                                               "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
        jobject obj = env->CallObjectMethod(
                    instance->object(),
                    methodId9,
                    QAndroidJniObject::fromString(str1).object<jstring>(),
                    QAndroidJniObject::fromString(str2).object<jstring>());
        QAndroidJniObject androidJniObj(obj);
        qDebug() << "method9" << androidJniObj.toString();
    }
    delete instance;
    return app.exec();
}
