#include "canworker.h"
#include <QTime>

CanWorker::CanWorker(QObject *parent) : QObject(parent), serial(nullptr) {}

void CanWorker::setSerial(QSerialPort *serialPort) {
    serial = serialPort;
}

void CanWorker::startListening() {
    if (!serial) return;
    connect(serial, &QSerialPort::readyRead, [this]() {
        QByteArray data = serial->readAll();
        emit canDataReceived(data);  // gửi sang MainWindow
    });
}
// //////////////hàm gửi dữ liệu /////////////////////////////////////////////////
void CanWorker::handleSendFrame(quint16 index, quint16 subindex, float value) {
    if (!serial) return;

    QByteArray frame;

    // Start Mark
    frame.append((char)0xAA);
    frame.append((char)0xAA);

    // Ghép Index và SubIndex thành 4 byte ID
    frame.append((char)(index & 0xFF));        // Byte thấp của index
    frame.append((char)((index >> 8) & 0xFF)); // Byte cao của index
    frame.append((char)(subindex & 0xFF));     // Byte thấp của subindex
    frame.append((char)((subindex >> 8) & 0xFF)); // Byte cao của subindex

    // Tạo frameData (Dữ liệu chính 8 byte)
    QByteArray frameData;

    // Chuyển đổi giá trị float thành 4 byte (IEEE 754)
    QByteArray valueBytes(reinterpret_cast<const char*>(&value), sizeof(float));

    // Thêm dữ liệu giá trị vào frameData
    frameData.append(valueBytes);

    // Đảm bảo frameData có đúng 8 byte
    while (frameData.size() < 8) {
        frameData.append((char)0x00);
    }

    // Ghép frameData vào Frame chính
    frame.append(frameData);

    // Các trường bổ sung
    frame.append((char)0x08); // Frame Data Length = 8 byte
    frame.append((char)0x00); // Message Type = 0x00 (CAN Message)
    frame.append((char)0x00); // CAN Frame Type = 0x01
    frame.append((char)0x00); // CAN Request Type = 0x00 (Data Frame)

    // Tính toán CRC
    QByteArray crcData = frame.mid(2, 16); // Lấy dữ liệu cần tính CRC (bỏ 2 byte Start Mark)

    uchar crc = 0;
    for (char byte : crcData) {
        crc += (uchar)byte; // Tính tổng
    }
    crc &= 0xFF;

    // Chống trùng với ký tự đặc biệt
    if (crc == 0xA5 || crc == 0xAA || crc == 0x55) {
        frame.append((char)0xA5);
    }
    frame.append(crc);

    // End Mark
    frame.append((char)0x55);
    frame.append((char)0x55);

    // **Gửi dữ liệu qua COM**
    serial->write(frame);

    if (serial->waitForBytesWritten(1000)) // Chờ gửi xong
    {
        QString sentData = frame.toHex(' ').toUpper();
        qDebug() << "Sent Data (HEX): " << frame.toHex(' ').toUpper();

    }
    else
    {
        qDebug() << "Loi khi gui du lieu!";
    }

    serial->write(frame);
    emit logMessage("Sent: " + frame.toHex(' ').toUpper());
}
