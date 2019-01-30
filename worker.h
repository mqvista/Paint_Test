#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include "DriverGC.h"
#include "utils/UPID.h"
#include "utils/UWindowFilter.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    void initSystem();
    Q_INVOKABLE void addPaint(double weight);

signals:
    void isRunning(bool flag);

public slots:
    void getScalesData(double value, QString unit, bool status);
    void timerRunner();

private:
    double m_scaleWeight;
    double m_targetWeight;
    QString m_scaleUnit;
    bool m_scaleStatus;
    UPID<double, int32_t> pid;
    int32_t m_targetSpeed;
    QDateTime m_startTime;
    bool runFlag;
    QTimer *pidTimer;
    int32_t m_fSpeed;

};

#endif // WORKER_H
