#ifndef MYACTIVITYRESULTRECEIVER_H
#define MYACTIVITYRESULTRECEIVER_H

#include <QAndroidActivityResultReceiver>
#include <QtQuick/QQuickItem>

class ActivityCalling;

class MyActivityResultReceiver : public QAndroidActivityResultReceiver
{
public:
    MyActivityResultReceiver();
public:
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data) override;

    void setActivityCalling(ActivityCalling* activity_calling);
private:
    ActivityCalling* m_activity_calling;
};

#endif // MYACTIVITYRESULTRECEIVER_H
