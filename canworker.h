#ifndef CANWORKER_H
#define CANWORKER_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>

class CanWorker : public QObject
{
    Q_OBJECT
public:
    explicit CanWorker(QObject *parent = nullptr);
    void setSerial(QSerialPort *serial); // Dùng chung Serial đã khởi tạo

signals:
    void canDataReceived(QByteArray data); // Gửi dữ liệu đã nhận
    void logMessage(QString msg);          // Gửi log ra UI

public slots:
    void handleSendFrame(quint16 index, quint16 subindex, float value);
    void startListening();


private:
    QSerialPort *serial;
};

#endif // CANWORKER_H
