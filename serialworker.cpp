#include "serialworker.h"
#include <QDebug>

SerialWorker::SerialWorker(QSerialPort *serial, QObject *parent)
    : QObject(parent), serial(serial) {}

void SerialWorker::readSerialData()
{
    if (serial->bytesAvailable()) {
        QByteArray data = serial->readAll();
        emit dataReceived(data); // Phát tín hiệu cho MainWindow xử lý tiếp
    }
}
