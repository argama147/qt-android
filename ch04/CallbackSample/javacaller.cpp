#include "javacaller.h"
#include <QQuickItem>

#include <QMetaObject>

std::function<void(int data)> gCallbackInt;
std::function<void(const QString& message)> gCallbackString;

JavaCaller::JavaCaller(QObject *root, QObject *parent) : QObject(parent)
{
    QQuickItem *button = root->findChild<QQuickItem *>("callJavaButton");
    connect(button, SIGNAL(clicked()),
            this, SLOT(callJava()));

    registerNativeMethods();
    gCallbackInt = std::bind(&JavaCaller::receiveFromJavaInt, this, std::placeholders::_1);
    gCallbackString = std::bind(&JavaCaller::receiveFromJavaString, this, std::placeholders::_1);
}

void JavaCaller::receiveFromJavaInt(int data)
{
    qDebug() << __FUNCTION__ << data;
}

void JavaCaller::receiveFromJavaString(const QString& message)
{
    qDebug() << __FUNCTION__ << message;
}

void JavaCaller::fromJavaInt(JNIEnv *env, jobject thiz, jint x)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    gCallbackInt(x);
}

void JavaCaller::fromJavaString(JNIEnv *env, jobject thiz, jstring str)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    QAndroidJniObject obj(str);
    gCallbackString(obj.toString());

}

void JavaCaller::callJava()
{
    callJavaMethod();
}

void JavaCaller::registerNativeMethods() {
    JNINativeMethod methods[] {
        {"callNativeInt", "(I)V", reinterpret_cast<void *>(fromJavaInt)},
        {"callNativeString", "(Ljava/lang/String;)V", reinterpret_cast<void *>(fromJavaString)}};

    QAndroidJniObject javaClass("com/eugo/example/callbacksample/MyClass");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void JavaCaller::callJavaMethod()
{
    QAndroidJniObject::callStaticMethod<void>("com/eugo/example/callbacksample/MyClass",
                                              "method1",
                                              "(I)V",
                                              10);
    QString str = "Test";
    QAndroidJniObject::callStaticMethod<void>("com/eugo/example/callbacksample/MyClass",
                                              "method2",
                                              "(Ljava/lang/String;)V",
                                              QAndroidJniObject::fromString(str).object<jstring>());
}



