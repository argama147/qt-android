#include "myactivityresultreceiver.h"
#include <QDebug>
#include <QtAndroidExtras>
#include "activitycalling.h"

MyActivityResultReceiver::MyActivityResultReceiver()
{
}

void MyActivityResultReceiver::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{

    Q_UNUSED(resultCode);
    Q_UNUSED(data);
    qDebug() << __FUNCTION__ << "receiverRequestCode=" << receiverRequestCode;
    if (m_activity_calling != nullptr) {
        if (data.isValid()) {
            QAndroidJniObject extras = data.callObjectMethod("getExtras", "()Landroid/os/Bundle;");
            qDebug() << "extras" << extras.toString();
            QAndroidJniObject string1 = QAndroidJniObject::fromString("SubActivityData");
            QAndroidJniObject result= extras.callObjectMethod("getString", "(Ljava/lang/String;)Ljava/lang/String;", string1.object<jstring>());
            qDebug() << "result" << result.toString();
            QMetaObject::invokeMethod(m_activity_calling,
                                      "updateQml",
                                      Qt::QueuedConnection,
                                      Q_ARG(QString, result.toString()));
        } else {
            qDebug() << "data is inValid.";
        }
    } else {
        qDebug() << "m_activity_calling is null.";
    }
}

void MyActivityResultReceiver::setActivityCalling(ActivityCalling* activity_calling)
{
    m_activity_calling = activity_calling;
}

