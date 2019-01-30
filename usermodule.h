#ifndef USERMODULE_H
#define USERMODULE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include "worker.h"

class UserModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString weight READ weight NOTIFY weightChanged)
    Q_PROPERTY(bool status READ status NOTIFY statusChanged)
public:
    explicit UserModule(Worker *worker, QObject *parent = nullptr);
    QString weight();
    bool status();
    Q_INVOKABLE void addPaint(QString weight);

signals:
    void weightChanged();
    void statusChanged();

public slots:
    void getScalesData(double value, QString unit, bool status);
    void getRunningSatus(bool flag);

private:
    Worker *m_worker;
    QString m_weight;
    bool m_status;
};

#endif // USERMODULE_H
