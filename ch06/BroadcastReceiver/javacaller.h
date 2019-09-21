#ifndef JAVACALLER_H
#define JAVACALLER_H

#include <QObject>

class JavaCaller : public QObject
{
    Q_OBJECT
public:
    explicit JavaCaller(QObject *root, QObject *parent = nullptr);
    void callSlotInt(int data);
    void callSlotString(const QString& message);

public slots:
    void sendBroadcastSlot();
    void updateQML(int data);
    void updateQML(const QString& message);

private:
    QObject *m_root;

};

#endif // JAVACALLER_H
