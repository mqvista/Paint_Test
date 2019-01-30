#include "service.h"

Service::Service(QQmlApplicationEngine *appEng, QObject *parent) : QObject(parent), m_userModule(&m_worker)
{

    m_engine = appEng;
    ScalesWorker::Instance()->moveToThread(&scalesWorkerThread);
    scalesWorkerThread.start();

    m_engine->rootContext()->setContextProperty("userModule", &m_userModule);
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesSmallDataChangedSig, &m_userModule, &UserModule::getScalesData);
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallOpen", Qt::QueuedConnection, Q_ARG(QString, "tty.usbserial"), Q_ARG(quint32, 9600));

    m_worker.moveToThread(&workerThread);
    workerThread.start();
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesSmallDataChangedSig, &m_worker, &Worker::getScalesData);
    QMetaObject::invokeMethod(&m_worker, &Worker::initSystem, Qt::QueuedConnection);

    connect(&m_worker, &Worker::isRunning, &m_userModule, &UserModule::getRunningSatus);
}

Service::~Service()
{
    workerThread.quit();
    workerThread.wait();

    scalesWorkerThread.quit();
    scalesWorkerThread.wait();
}

void Service::driverGCDebugInfo(QString msg, QDateTime curTime)
{
    qDebug()<<curTime.toString("hh:mm:ss.zzz")<<":"<< msg;
}
