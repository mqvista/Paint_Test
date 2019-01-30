#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QThread>
#include <QMetaObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "control/scalesworker.h"
#include "usermodule.h"
#include "worker.h"

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QQmlApplicationEngine *appEng, QObject *parent = nullptr);
    ~Service();

signals:

public slots:

private:
    QQmlApplicationEngine *m_engine;
    QThread scalesWorkerThread;
    QThread motionWorkerThread;
    QThread workerThread;
    Worker m_worker;
    UserModule m_userModule;
    void driverGCDebugInfo(QString msg, QDateTime curTime);


};

#endif // SERVICE_H
