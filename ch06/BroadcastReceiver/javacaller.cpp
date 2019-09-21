#include "javacaller.h"
#include <QQuickItem>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QMetaObject>

std::function<void(int data)> gCallbackInt;
std::function<void(const QString& message)> gCallbackString;

JavaCaller::JavaCaller(QObject *root, QObject *parent) : QObject(parent)
{
    m_root = root;

    QtAndroid::androidActivity().callMethod<void>("registerBroadcastReceiver", "()V");

    gCallbackInt = std::bind(&JavaCaller::callSlotInt, this, std::placeholders::_1);
    gCallbackString = std::bind(&JavaCaller::callSlotString, this, std::placeholders::_1);

    QQuickItem *button = root->findChild<QQuickItem *>("sendBroadcastButton");
    connect(button, SIGNAL(clicked()),
            this, SLOT(sendBroadcastSlot()));
}

void JavaCaller::callSlotInt(int data)
{
    QMetaObject::invokeMethod(this,
                              "updateQML",
                              Qt::QueuedConnection,
                              Q_ARG(int, data));
}

void JavaCaller::callSlotString(const QString& message)
{
    QMetaObject::invokeMethod(this,
                              "updateQML",
                              Qt::QueuedConnection,
                              Q_ARG(QString, message));
}

void JavaCaller::sendBroadcastSlot()
{
    QtAndroid::androidActivity().callMethod<void>("sendBroadcast", "()V");
}

void JavaCaller::updateQML(int data)
{
    QObject *resultText = m_root->findChild<QObject*>("resultText");
    resultText->setProperty("text", data);
}

void JavaCaller::updateQML(const QString &message)
{
    QObject *resultText = m_root->findChild<QObject*>("resultText2");
    resultText->setProperty("text", message);
}

static void onReceiveSample(JNIEnv * /*env*/, jobject /*obj*/, jint data)
{
    gCallbackInt(data);
}

static void onReceiveSample2(JNIEnv * /*env*/, jobject /*obj*/, jstring message)
{
    QAndroidJniObject jniMessage(message);
    gCallbackString(jniMessage.toString());
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    static JNINativeMethod methods[] = {
        {"onReceiveNativeSample1", "(I)V", (void *)onReceiveSample},
        {"onReceiveNativeSample2", "(Ljava/lang/String;)V", (void *)onReceiveSample2}
    };

    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
      return JNI_ERR;

    jclass javaClass = env->FindClass("com/eugo/example/broadcastreceiver/NativeFunctions");
    if (!javaClass)
      return JNI_ERR;

    if (env->RegisterNatives(javaClass, methods,
                          sizeof(methods) / sizeof(methods[0])) < 0) {
      return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

