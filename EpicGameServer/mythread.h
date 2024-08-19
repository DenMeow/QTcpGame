#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    int count;
    bool is_exit = false;
protected:
    void run() override;
signals:
    void progress(int value);
    void finish();
};

#endif // MYTHREAD_H
