#ifndef JAVACALLER_H
#define JAVACALLER_H

#include <QObject>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>

class JavaCaller : public QObject
{
    Q_OBJECT
public:
    explicit JavaCaller(QObject *root, QObject *parent = nullptr);
    void receiveFromJavaInt(int data);
    void receiveFromJavaString(const QString& message);
    static void fromJavaInt(JNIEnv *env, jobject thiz, jint x);
    static void fromJavaString(JNIEnv *env, jobject thiz, jstring str);

public slots:
    void callJava();

private:
    void registerNativeMethods();
    void callJavaMethod();
};
#endif // JAVACALLER_H
