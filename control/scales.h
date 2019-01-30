#ifndef SCALES_H
#define SCALES_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

class Scales : public QObject
{
    Q_OBJECT
public:
    explicit Scales(QObject *parent = nullptr);
    ~Scales();
    bool open(QString port, quint32 baud);
    bool openUseSN(const QString &serialNumber, const quint32 &baud);
    void close(void);
    bool isScalesOpen();
    void goToThread(QThread *thread);
    bool getSerialPortBySerialNumber(QString serialNumber,QString* portName);

protected:
    QString p_receivedata;
    double p_scalesValue;
    QString p_scalesStatus;
    QString p_scalesUnit;

    QByteArray p_allData;

    virtual void serialStrConver2Data() = 0;     //must rewrite


signals:
    void receiveDataPush(double value, QString unit, QString status);

public slots:
    void serialErrorSlot(QSerialPort::SerialPortError error);
    void rawSerialReceiveSlot();
    void scalesOpenSlot(QString port, quint32 baud);
    void scalesCloseSlot();
    void scalesOpenUseSNSlot(QString serialNumber, quint32 baud);

private:
    QSerialPort m_serialPort;
    QString m_receivedata;
};

#endif // SCALES_H
