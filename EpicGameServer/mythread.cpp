#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
}

void MyThread::run() {
    is_exit = false;
    for(int i = 0; i < count; ++i) {
        emit progress(i);
        QThread::msleep(100);
        if(is_exit)
            break;
    }
    emit finish();
}

