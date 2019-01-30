#include "usermodule.h"

UserModule::UserModule(Worker *worker, QObject *parent) : QObject(parent)
{
    m_worker = worker;
    m_status = false;
}

QString UserModule::weight()
{
    return  m_weight;
}

bool UserModule::status()
{
    return  m_status;
}

void UserModule::addPaint(QString weight)
{
    double wet = weight.toDouble();
    QMetaObject::invokeMethod(m_worker, "addPaint", Qt::QueuedConnection, Q_ARG(double, wet));
}

void UserModule::getScalesData(double value, QString unit, bool status)
{
    m_weight = QString::number(value, 'f', 2);
    m_status = status;
    emit weightChanged();
}

void UserModule::getRunningSatus(bool flag)
{
    m_status = flag;
    qDebug()<< m_status;
    emit statusChanged();
}
