#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QByteArray>

#include <QObject>
#include <QByteArray>
#include <QSerialPort>

class SerialWorker : public QObject
{
    Q_OBJECT

public:
    SerialWorker(QSerialPort *serial, QObject *parent = nullptr);
    void start();

signals:
    void dataReceived(const QByteArray &data);

public slots:
    void readSerialData();

private:
    QSerialPort *serial;
};

#endif // SERIALWORKER_H
