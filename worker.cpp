#include "worker.h"

Worker::Worker(QObject* parent)
    : QObject(parent)
    , pid(m_scaleWeight, m_targetWeight, m_targetSpeed, 0, 30000, 10000, 0, 0, 0.1f, UPID<double, int32_t>::Mode_Normal, UPID<double, int32_t>::Dir_Postive)
{
    runFlag = false;
    pidTimer = new QTimer(this);
    connect(pidTimer, &QTimer::timeout, this, &Worker::timerRunner);
}

Worker::~Worker()
{
    DriverGC::Instance()->Special_Reset(1);
    DriverGC::Instance()->Close();
    pidTimer->stop();
}

void Worker::initSystem()
{
    if (!DriverGC::Instance()->Open("tty.SLAB_USBtoUART", 2000000)) {
        qDebug() << "openFailed1";
    }
    DriverGC::Instance()->Special_Reset(1);
    if (!DriverGC::Instance()->Special_Init(1)) {
        qDebug() << "openFailed2";
    }
}

void Worker::addPaint(double weight)
{
    qDebug() << weight;
    m_targetWeight = m_scaleWeight + weight;
    pid.Clear();
    m_fSpeed=0;
    runFlag = true;
    emit isRunning(runFlag);
    pidTimer->start(100);
}

void Worker::getScalesData(double value, QString unit, bool status)
{
    m_startTime = QDateTime::currentDateTime();
    m_scaleWeight = value;
    m_scaleUnit = unit;
    m_scaleStatus = status;
}

void Worker::timerRunner()
{
    if (runFlag)
    {
        pid.Compute();
        m_fSpeed=m_targetSpeed-int32_t(0.95*((m_targetSpeed-m_fSpeed)>=3000?(m_targetSpeed-m_fSpeed):0));


        if (m_targetSpeed == 0)
        {
            pidTimer->stop();
            runFlag = false;
            DriverGC::Instance()->Setting_SM_Speed(1, 3, 5000, 10000);
            DriverGC::Instance()->AutoControl_SM_By_Step(1, 3, -2000);
            emit isRunning(runFlag);
            return;
        }
        qDebug() << "tsb" << m_targetSpeed << "tsb" << m_fSpeed;
        DriverGC::Instance()->Control_SM_Run_Speed(1, 3, m_fSpeed);
    }
}
