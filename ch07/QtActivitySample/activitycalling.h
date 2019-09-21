#ifndef ACTIVITYCALLING_H
#define ACTIVITYCALLING_H

#include <QObject>
#include <QtQuick/QQuickItem>
#include "myactivityresultreceiver.h"

class ActivityCalling : public QObject
{
    Q_OBJECT
public:
    explicit ActivityCalling(QObject *parent = nullptr);
    void connectQml(QObject *root);
    void putExtra(const QString &key, const QByteArray &data, QAndroidJniObject handle);

public slots:
    void startActivitySlot();
    void updateQml(const QString &msg);
private:

    MyActivityResultReceiver m_result_receiver;
    QObject *m_root;

    QAndroidJniObject m_handle;
};

#endif // ACTIVITYCALLING_H
