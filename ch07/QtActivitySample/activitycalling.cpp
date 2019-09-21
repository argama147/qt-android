#include "activitycalling.h"

#include <QtAndroidExtras>
#include <QString>
#include <QException>

ActivityCalling::ActivityCalling(QObject *parent)
    : QObject(parent), m_handle("android/content/Intent", "()V")
{
    m_result_receiver.setActivityCalling(this);
}

void ActivityCalling::connectQml(QObject *root)
{
    m_root = root;

    QQuickItem *startButton = root->findChild<QQuickItem *>("startActivityButton");
    connect(startButton, SIGNAL(clicked()),
            this, SLOT(startActivitySlot()));
}

void ActivityCalling::putExtra(const QString &key, const QByteArray &data, QAndroidJniObject handle)
{
    QAndroidJniExceptionCleaner cleaner;
    QAndroidJniEnvironment env;
    jbyteArray array = env->NewByteArray(data.size());
    env->SetByteArrayRegion(array, 0, data.length(), reinterpret_cast<const jbyte*>(data.constData()));
    handle.callObjectMethod("putExtra", "(Ljava/lang/String;[B)Landroid/content/Intent;",
                              QAndroidJniObject::fromString(key).object(), array);
    env->DeleteLocalRef(array);
}

void ActivityCalling::startActivitySlot()
{
    auto intent = QAndroidIntent(QtAndroid::androidActivity().object(),
                                 "com.eugo.example.qtactivitysample.SubActivity");
    QString key = "MainActivityData";
    QString strData = "MainActivityData";
    QVariant variantData(strData);

//    intent.putExtra(key, strData.toUtf8());
    putExtra(key, strData.toUtf8(), intent.handle());

    QtAndroid::startActivity(intent, 1, &m_result_receiver);
}

void ActivityCalling::updateQml(const QString &msg)
{
    QObject *resultText = m_root->findChild<QObject*>("resultText");
    resultText->setProperty("text", msg);
}
