#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h" // Thư viện QCustomPlot
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDebug>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>
#include <chrono>

// Biến tạm để lưu giá trị id/iq
float id_tmp = 0;
float iq_tmp = 0;
float theta_ref_global = 0.0f;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);


    loadJsonData(); // Load dữ liệu từ JSON khi khởi động
    // loadCANDefinitions();
    // Tạo đối tượng Serial
    Serial = new QSerialPort(this);
    // Kết nối tín hiệu với slot xử lý
    ui->dothi->setTabText(0, "Điện áp");
    ui->dothi->setTabText(1, "Dòng điện");
    ui->dothi->setTabText(2, "Góc quay");

    // connect(ui->pushButton_Send, &QPushButton::clicked, this, &MainWindow::sendCanData);

    // Cài đặt cổng COM
    setupSerialPort();

    // 1. Tạo thread và worker
    canThread = new QThread(this);
    canWorker = new CanWorker();
    canWorker->moveToThread(canThread);

    // 2. Truyền serial đang dùng
    canWorker->setSerial(Serial);

    // 3. Kết nối tín hiệu
    connect(canThread, &QThread::started, canWorker, &CanWorker::startListening);
    connect(this, &MainWindow::sendCANCommand, canWorker, &CanWorker::handleSendFrame);
    connect(canWorker, &CanWorker::logMessage, this, &MainWindow::updateTextBrowserSent);

    // 4. Khởi động luồng
    canThread->start();




    // //////////////////// ĐỒ THỊ DÒNG ĐIỆN //////////////////////////////////////////////
    customPlotCurrent = new QCustomPlot(ui->customPlotWidget2);
    customPlotCurrent->setGeometry(ui->customPlotWidget2->rect());
    customPlotCurrent->setOpenGl(true); // Bật Double Buffer với OpenGL

    // Graph 0: id (xanh)
    customPlotCurrent->addGraph();
    customPlotCurrent->graph(0)->setPen(QPen(Qt::blue));
    customPlotCurrent->graph(0)->setName("id");

    // Graph 1: iq (cam)
    customPlotCurrent->addGraph();
    customPlotCurrent->graph(1)->setPen(QPen(Qt::darkYellow));
    customPlotCurrent->graph(1)->setName("iq");

    // Cấu hình trục
    customPlotCurrent->xAxis->setLabel("Thời gian (s)");
    customPlotCurrent->yAxis->setLabel("Dòng điện (A)");
    customPlotCurrent->xAxis->setRange(0, 10);
    customPlotCurrent->yAxis->setRange(-1, 1);  // Điều chỉnh tùy hệ thống
    customPlotCurrent->legend->setVisible(true);
    customPlotCurrent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

 // //////////////////////////////// ĐỒ THỊ THETA ////////////////////////////////
    // Khởi tạo QCustomPlot cho góc theta (gắn vào customPlotWidget3)
    customPlotTheta = new QCustomPlot(ui->customPlotWidget3);
    customPlotTheta->setGeometry(ui->customPlotWidget3->rect());
    customPlotTheta->setOpenGl(true);

    // Thêm 2 đồ thị
    customPlotTheta->addGraph();  // theta_now
    customPlotTheta->graph(0)->setPen(QPen(Qt::darkGreen));
    customPlotTheta->graph(0)->setName("theta_now");

    customPlotTheta->addGraph();  // theta_ref
    customPlotTheta->graph(1)->setPen(QPen(Qt::red, 1, Qt::DashLine));
    customPlotTheta->graph(1)->setName("theta_ref");

    // Cấu hình trục
    customPlotTheta->xAxis->setLabel("Thoi gian (s)");
    customPlotTheta->yAxis->setLabel("Goc quay (rad)");
    customPlotTheta->xAxis->setRange(0, 10);
    customPlotTheta->yAxis->setRange(-10, 10);  // Điều chỉnh theo hệ thống của bạn
    customPlotTheta->legend->setVisible(true);
    customPlotTheta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ THETA /////////////////////////////////
    thetaPlotTimer = new QTimer(this);
    connect(thetaPlotTimer, &QTimer::timeout, this, &MainWindow::updateThetaPlot);
    thetaPlotTimer->start(50);

    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ DÒNG ĐIỆN /////////////////////////////////
    currentTimer = new QTimer(this);
    connect(currentTimer, &QTimer::timeout, this, &MainWindow::updateCurrentPlot);
    currentTimer->start(50); //
}
 // /////////////////////////////// THE TA //////////////////////////////////////
void MainWindow::updateThetaPlot()
{
    QVector<QPointF> plotData;

    bufferMutex.lock();
    useBufferA = !useBufferA;
    if (useBufferA) {
        plotData = bufferB;
        bufferB.clear();
    } else {
        plotData = bufferA;
        bufferA.clear();
    }
    bufferMutex.unlock();

    QVector<double> timeVector, thetaRefVec, thetaNowVec;

    for (const QPointF &point : plotData) {
        elapsedTheta += 0.05;
        timeVector.append(elapsedTheta);
        thetaRefVec.append(point.x());
        thetaNowVec.append(point.y());
    }

    totalTimeTheta += timeVector;
    totalThetaRef += thetaRefVec;
    totalThetaNow += thetaNowVec;

    while (totalTimeTheta.size() > 200) {
        totalTimeTheta.removeFirst();
        totalThetaRef.removeFirst();
        totalThetaNow.removeFirst();
    }

    customPlotTheta->graph(0)->setData(totalTimeTheta, totalThetaNow);
    customPlotTheta->graph(1)->setData(totalTimeTheta, totalThetaRef);
    customPlotTheta->xAxis->setRange(qMax(0.0, elapsedTheta - 10), elapsedTheta);
    customPlotTheta->replot();
}
 // /////////////////////////////// DÒNG ĐIỆN //////////////////////////////////////
void MainWindow::updateCurrentPlot()
{
    // double id = ui->label_id->text().toDouble();
    // double iq = ui->label_iq->text().toDouble();

    // elapsedCurrent += 0.01;  // Thời gian thực (nên đồng bộ với timer 10ms)

    // timeCurrentData.append(elapsedCurrent);
    // idData.append(id);
    // iqData.append(iq);

    // if (timeCurrentData.size() > 200) {
    //     timeCurrentData.removeFirst();
    //     idData.removeFirst();
    //     iqData.removeFirst();
    // }

    // customPlotCurrent->graph(0)->setData(timeCurrentData, idData);
    // customPlotCurrent->graph(1)->setData(timeCurrentData, iqData);
    // customPlotCurrent->xAxis->setRange(elapsedCurrent - 10, elapsedCurrent);
    // customPlotCurrent->replot();
    QVector<QPointF> data;
    currentBufferMutex.lock();
    useCurrentBufferA = !useCurrentBufferA;
    if (useCurrentBufferA) {
        data = currentBufferB;
        currentBufferB.clear();
    } else {
        data = currentBufferA;
        currentBufferA.clear();
    }
    currentBufferMutex.unlock();

    QVector<double> idVec, iqVec, timeVec;
    for (const QPointF &point : data) {
        elapsedCurrent += 0.05;
        idVec.append(point.x());
        iqVec.append(point.y());
        timeVec.append(elapsedCurrent);
    }

    totalId += idVec;
    totalIq += iqVec;
    totalTimeCurrent += timeVec;

    while (totalTimeCurrent.size() > 200) {
        totalTimeCurrent.removeFirst();
        totalId.removeFirst();
        totalIq.removeFirst();
    }
customPlotTheta->xAxis->setRange(qMax(0.0, elapsedTheta - 10), elapsedTheta);
    customPlotCurrent->graph(0)->setData(totalTimeCurrent, totalId);
    customPlotCurrent->graph(1)->setData(totalTimeCurrent, totalIq);
    customPlotCurrent->xAxis->setRange(qMax(0.0, elapsedCurrent - 10), elapsedCurrent);
    customPlotCurrent->replot();

    // Xóa dữ liệu cũ để tránh quá tải bộ nhớ //giữ 1000 điểm gần nhất//
    int maxPoints = 1000;
    if (thetaTimeData.size() > maxPoints) {
        thetaTimeData.remove(0, thetaTimeData.size() - maxPoints);
        thetaNowData.remove(0, thetaNowData.size() - maxPoints);
        thetaRefData.remove(0, thetaRefData.size() - maxPoints);
}
}
void MainWindow::setupSerialPort()
{
    Serial->setPortName("COM3"); // Thay bằng cổng COM phù hợp
    Serial->setBaudRate(QSerialPort::Baud115200);
    Serial->setDataBits(QSerialPort::Data8);
    Serial->setParity(QSerialPort::NoParity);
    Serial->setStopBits(QSerialPort::OneStop);
    Serial->setFlowControl(QSerialPort::NoFlowControl);

    if (Serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened successfully!";
        connect(Serial, &QSerialPort::readyRead, this, &MainWindow::readCanData);
    } else {
        qDebug() << "Failed to open serial port: " << Serial->errorString();
        QMessageBox::critical(this, "Error", "Failed to open serial port!");

    }
}


void MainWindow::readCanData()
{
    QByteArray data = Serial->readAll(); // Đọc dữ liệu từ Serial
    QString receivedData = data.toHex(' ').toUpper(); // Chuyển thành chuỗi HEX

    qDebug() << "Received Data: " << receivedData;

    // Tách dữ liệu từ byte đầu AA AA và byte cuối 55 55
    parseDataByPattern(data);
}

void MainWindow::parseDataByPattern(const QByteArray &data)
{
    QByteArray startPattern = QByteArray::fromHex("AA AA"); // Dấu hiệu bắt đầu
    QByteArray endPattern = QByteArray::fromHex("55 55");   // Dấu hiệu kết thúc

    int startIndex = 0;
    int endIndex = 0;

    // Tìm tất cả các phần dữ liệu bắt đầu với AA AA và kết thúc với 55 55
    while ((startIndex = data.indexOf(startPattern, startIndex)) != -1) {
        endIndex = data.indexOf(endPattern, startIndex);
        if (endIndex == -1) {
            qWarning() << "Không tìm thấy dấu kết thúc (55 55)!";
            break;
        }

        // Tách phần dữ liệu từ startIndex đến endIndex (bao gồm cả 55 55)
        QByteArray part = data.mid(startIndex, endIndex + endPattern.size() - startIndex);

        // Chuyển phần dữ liệu đã tách thành chuỗi HEX
        QString partHex = part.toHex(' ').toUpper();

        // Hiển thị phần dữ liệu đã tách vào textBrowser
        updateTextBrowser(partHex);

        // Gọi hàm parseCanData để xử lý dữ liệu đã tách
        parseCanData(part);

        // Tiếp tục tìm kiếm phần tiếp theo
        startIndex = endIndex + endPattern.size();
    }
}

void MainWindow::updateTextBrowser(const QString &data)
{
    // Lấy văn bản hiện tại từ textBrowser
    QString displayText = ui->textBrowser->toPlainText();

    // Lấy thời gian hiện tại với độ phân giải micro giây
    auto now = std::chrono::system_clock::now();
    auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto duration = now_us.time_since_epoch();
    qint64 total_us = duration.count();

    // Giờ hiện tại
    QTime time = QTime::currentTime();
    QString timeStr = time.toString("hh:mm:ss");

    // Lấy phần micro giây (sau mili giây)
    int micro = total_us % 1000000;  // micro giây (6 chữ số)
    QString microStr = QString(".%1").arg(micro, 6, 10, QChar('0'));

    // Gộp chuỗi thời gian hoàn chỉnh
    QString fullTime = timeStr + microStr;

    // Thêm dữ liệu và thời gian vào text
    ui->textBrowser->append(data + "  |  " + fullTime);

    // Tự động cuộn xuống cuối
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cursor);

}



void MainWindow::on_pushButton_readData_clicked()
{
    if (Serial->isOpen()) {
        QByteArray data = Serial->readAll(); // Đọc dữ liệu từ Serial
        QString receivedData = data.toHex(' ').toUpper(); // Chuyển thành chuỗi HEX

        // Hiển thị dữ liệu vào textBrowser
        updateTextBrowser(receivedData);

        qDebug() << "Received Data: " << receivedData;
    } else {
        QMessageBox::warning(this, "Serial Port", "Please open the connection first!");
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textBrowser->clear(); // Xóa toàn bộ dữ liệu
    qDebug() << "TextBrowser cleared!";
}


void MainWindow::on_pushButton_clear_sent_clicked()
{
    ui->textBrowser_sent->clear(); // Xóa toàn bộ dữ liệu
    qDebug() << " cleared!";
}
//     // Gửi dữ liệu qua cổng com
// void MainWindow::sendCanData()
// {
//     QString idHex = ui->lineEdit_CAN_ID->text();     // Lấy ID từ QLineEdit
//     QString dataHex = ui->lineEdit_CAN_Data->text(); // Lấy Data từ QLineEdit

//     QByteArray idData = hexStringToByteArray(idHex);  // Chuyển ID sang QByteArray
//     QByteArray frameData = hexStringToByteArray(dataHex); // Chuyển Data sang QByteArray

//     if (idData.size() != 4 || frameData.size() != 8) // Kiểm tra đúng kích thước
//     {
//         qDebug() << "Loi: ID phai có 4 byte và Data phai có 8 byte!";
//         return;
//     }

//     QByteArray frame;
//     frame.append((char)0xAA); // Start Mark 1
//     frame.append((char)0xAA); // Start Mark 2
//     frame.append(idData); // Thêm 4 byte ID vào Frame
//     frame.append(frameData); // Thêm 8 byte Data vào Frame

//     // **Thêm các trường bổ sung**
//     frame.append((char)0x08); // Frame Data Length = 8 byte
//     frame.append((char)0x00); // Message Type = 0x00 (CAN Message)
//     frame.append((char)0x01); // CAN Frame Type = 0x01 (Extended)'
//     frame.append((char)0x00); // CAN Request Type = 0x01 (Remote Request Frame)

//     // **Tính toán CRC**
//     QByteArray crcData = idData + frameData;
//     crcData.append((char)0x08); // Thêm Frame Data Length vào CRC
//     crcData.append((char)0x00); // Thêm Message Type vào CRC
//     crcData.append((char)0x01); // Thêm CAN Frame Type vào CRC
//     crcData.append((char)0x00); // Thêm CAN Request Type vào CRC

//     QByteArray processedData;
//     for (char byte : crcData)
//     {
//         if (byte == (char)0xA5 || byte == (char)0xAA || byte == (char)0x55)
//         {
//             processedData.append((char)0xA5); // Thêm FrameCtrl nếu gặp ký tự đặc biệt
//         }
//         processedData.append(byte);
//     }

//     uchar crc = 0;
//     for (char byte : processedData)
//     {
//         crc += (uchar)byte; // Tổng đơn giản
//     }
//     crc &= 0xFF;

//     if (crc == 0xA5 || crc == 0xAA || crc == 0x55)
//     {
//         frame.append((char)0xA5); // Chống trùng CRC với ký tự đặc biệt
//     }
//     frame.append(crc); // Thêm CRC vào Frame

//     frame.append((char)0x55); // End
//     frame.append((char)0x55); // End

//     // **Gửi dữ liệu qua COM**
//     Serial->write(frame);

//     if (Serial->waitForBytesWritten(1000)) // Chờ gửi xong
//     {
//         QString sentData = frame.toHex(' ').toUpper();
//         qDebug() << "Sent Data (HEX): " << frame.toHex(' ').toUpper();
//         updateTextBrowserSent(sentData);
//     }
//     else
//     {
//         qDebug() << "Loi khi gui du lieu!";
//     }
//     }

// QByteArray MainWindow::hexStringToByteArray(const QString &hex)
// {
//     QByteArray byteArray;
//     QStringList hexList = hex.split(' ', Qt::SkipEmptyParts); // Tách từng byte
//     for (const QString &byte : hexList)
//     {
//         bool ok;
//         byteArray.append(static_cast<char>(byte.toInt(&ok, 16))); // Chuyển từ HEX sang Byte
//         if (!ok)
//         {
//             qDebug() << "Loi chuyen đoi du lieu HEX!";
//             return QByteArray(); // Trả về rỗng nếu có lỗi
//         }
//     }
//     return byteArray;
// }

void MainWindow::updateTextBrowserSent(const QString &data)
{
    // QString displayText = ui->textBrowser_sent->toPlainText();
    // displayText.append(data + "  |  " + QTime::currentTime().toString("hh:mm:ss") + "\n");
    // ui->textBrowser_sent->setPlainText(displayText);

    // // **Tự động cuộn xuống cuối**
    // QTextCursor cursor = ui->textBrowser_sent->textCursor();
    // cursor.movePosition(QTextCursor::End);
    // ui->textBrowser_sent->setTextCursor(cursor);
        // QString displayText = ui->textBrowser_sent->toPlainText();

        // // Lấy thời gian hiện tại với micro giây
        // qint64 timestamp = QDateTime::currentMSecsSinceEpoch() * 1000;  // Lấy micro giây (tính từ Epoch)
        // QString timestampStr = QString::number(timestamp);

        // displayText.append(data + "  |  " + timestampStr + "\n");
        // ui->textBrowser_sent->setPlainText(displayText);

        // // **Tự động cuộn xuống cuối**
        // QTextCursor cursor = ui->textBrowser_sent->textCursor();
        // cursor.movePosition(QTextCursor::End);
        // ui->textBrowser_sent->setTextCursor(cursor);
    QString displayText = ui->textBrowser_sent->toPlainText();

    auto now = std::chrono::system_clock::now();
    auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

    QTime time = QTime::currentTime();
    QString timeStr = time.toString("hh:mm:ss") + QString(".%1").arg(now_us % 1000000, 6, 10, QChar('0'));

    QString line = data + "  |  " + timeStr;
    ui->textBrowser_sent->append(line);

    QTextCursor cursor = ui->textBrowser_sent->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser_sent->setTextCursor(cursor);

}


// void MainWindow::parseCanData(const QByteArray &data) {
//     if (data.size() < 20) { // Kiểm tra độ dài hợp lệ
//         qDebug() << "Dữ liệu nhận được không hợp lệ!";
//         return;
//     }

//     // Bỏ qua 2 byte đầu (AA AA)
//     int index = (uchar)data[3] << 8 | (uchar)data[2]; // ID (Little Endian)
//     int subindex = (uchar)data[5] << 8 | (uchar)data[4]; // Subindex (Byte thứ 6)

//     // Lấy dữ liệu 8 byte tiếp theo
//     QByteArray valueData = data.mid(6, 8);
//     QString dataHex = valueData.toHex(' ').toUpper(); // Chuyển thành chuỗi HEX

//     // Chuyển dữ liệu sang số nguyên (Big Endian)
//     qint64 valueDecimal = 0;
//     for (int i = 0; i < 4; i++) {
//         valueDecimal = (valueDecimal << 8) | (uchar)valueData[i];
//     }

//     // Cập nhật vào bảng QTableWidget
//     updateTableValue1(index, subindex, dataHex, QString::number(valueDecimal));
//     // ///
//     float value = 0;
//     memcpy(&value, valueData.constData(), sizeof(float)); // Chuyển byte array thành float
//     appendToTableWidget(index, subindex, value);
//     ui->tableWidget_2->resizeColumnsToContents();

//     // ---- CÁCH CHUYỂN 4 BYTE ĐẦU THÀNH FLOAT ----
//     float valueFloat = 0.0f;
//     QByteArray floatData;
//     if (valueData.size() >= 4) {
//         QByteArray floatData = valueData.left(4); // Lấy 8 byte đầu
//         // Đảo thứ tự byte vì dữ liệu gốc là Big Endian
//         // std::reverse(floatData.begin(), floatData.end());
//          memcpy(&valueFloat, floatData.data(), sizeof(float)); // Chuyển đổi dữ liệu
//     }

//     // Kiểm tra nếu dữ liệu là Speed hoặc Angle
//     if (valueFloat > -1000 && valueFloat < 1000 && (valueFloat < -0.001 || valueFloat > 0.001))
//     {
//      if (index == 0x01A0 && subindex == 0x0000) { // Angle (thay bằng Index thực tế)
//         ui->label_angle->setText(QString::number(valueFloat, 'f', 4));

//         float theta_now = valueFloat;
//         float theta_ref =theta_ref_global;
//         double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
//         thetaTimeData.append(timestamp);
//         thetaNowData.append(theta_now);
//         thetaRefData.append(theta_ref);
//         QMutexLocker locker(&bufferMutex);
//         if (useBufferA)
//             bufferA.append(QPointF(theta_ref_global, theta_now));
//         else
//             bufferB.append(QPointF(theta_ref_global, theta_now));
//      }

//     else if (index == 0x02A0 && subindex == 0x0000) {
//         ui->label_id->setText(QString::number(valueFloat, 'f', 4));
//         id_tmp = valueFloat;
//     }
//     else if (index == 0x03A0 && subindex == 0x0000) {
//         ui->label_iq->setText(QString::number(valueFloat, 'f', 4));
//         iq_tmp = valueFloat;

//         // Khi có cả id và iq thì ghi vào buffer
//         QMutexLocker locker(&currentBufferMutex);
//         if (useCurrentBufferA)
//             currentBufferA.append(QPointF(id_tmp, iq_tmp));
//         else
//             currentBufferB.append(QPointF(id_tmp, iq_tmp));
//     }
//     }

// }

bool MainWindow::parseCanHeader(const QByteArray &data, int &index, int &subindex, QByteArray &valueData) {
    if (data.size() < 20) return false;

    index = (uchar)data[3] << 8 | (uchar)data[2];
    subindex = (uchar)data[5] << 8 | (uchar)data[4];
    valueData = data.mid(6, 8);
    return true;
}

qint64 MainWindow::convertToDecimal(const QByteArray &valueData) {
    qint64 valueDecimal = 0;
    for (int i = 0; i < 4; i++) {
        valueDecimal = (valueDecimal << 8) | (uchar)valueData[i];
    }
    return valueDecimal;
}

float MainWindow::convertToFloat(const QByteArray &valueData) {
    float value = 0;
    if (valueData.size() >= 4) {
        memcpy(&value, valueData.constData(), sizeof(float));
    }
    return value;
}

void MainWindow::handleSpecialValues(int index, int subindex, float valueFloat) {
    if (valueFloat > -1000 && valueFloat < 1000 && (valueFloat < -0.001 || valueFloat > 0.001)) {
        if (index == 0x01A0 && subindex == 0x0000) {
            // Angle
            ui->label_angle->setText(QString::number(valueFloat, 'f', 4));
            float theta_now = valueFloat;
            float theta_ref = theta_ref_global;
            double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
            thetaTimeData.append(timestamp);
            thetaNowData.append(theta_now);
            thetaRefData.append(theta_ref);

            QMutexLocker locker(&bufferMutex);
            if (useBufferA)
                bufferA.append(QPointF(theta_ref_global, theta_now));
            else
                bufferB.append(QPointF(theta_ref_global, theta_now));
        } else if (index == 0x02A0 && subindex == 0x0000) {
            // id
            ui->label_id->setText(QString::number(valueFloat, 'f', 4));
            id_tmp = valueFloat;
        } else if (index == 0x03A0 && subindex == 0x0000) {
            // iq
            ui->label_iq->setText(QString::number(valueFloat, 'f', 4));
            iq_tmp = valueFloat;

            QMutexLocker locker(&currentBufferMutex);
            if (useCurrentBufferA)
                currentBufferA.append(QPointF(id_tmp, iq_tmp));
            else
                currentBufferB.append(QPointF(id_tmp, iq_tmp));
        }
    }
}

void MainWindow::parseCanData(const QByteArray &data) {
    int index, subindex;
    QByteArray valueData;

    if (!parseCanHeader(data, index, subindex, valueData)) {
        qDebug() << "Dữ liệu nhận được không hợp lệ!";
        return;
    }

    QString dataHex = valueData.toHex(' ').toUpper();
    qint64 valueDecimal = convertToDecimal(valueData);

    updateTableValue1(index, subindex, dataHex, QString::number(valueDecimal));

    float valueFloat = convertToFloat(valueData);
    appendToTableWidget(index, subindex, valueFloat);

    handleSpecialValues(index, subindex, valueFloat);
    ui->tableWidget_2->resizeColumnsToContents();
}


    // QMap<QPair<int, int>, int> rowMap;

    // Hàm cập nhật giá trị vào bảng `QTableWidget_2`
void MainWindow::updateTableValue1(int index, int subindex, const QString &dataHex, const QString &valueDecimal) {
    QPair<int, int> key = qMakePair(index, subindex);
    QString name = nameMap.contains(key) ? nameMap[key] : "Unknown";
    QString type = typeMap.contains(key) ? typeMap[key] : "Unknown";

    // Chuyển index và subindex thành chuỗi với 4 chữ số (thêm số 0 vào trước nếu cần)
    QString indexStr = QString::number(index, 16).toUpper().rightJustified(4, '0');
    QString subindexStr = QString::number(subindex, 16).toUpper().rightJustified(4, '0');
    // Kiểm tra nếu ID đã tồn tại trong bảng
    if (rowMap.contains(key)) {
        int row = rowMap[key];
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(type)); // Cập nhật Type
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(dataHex));   // Cập nhật cột "Data"
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(valueDecimal)); //Cập nhật cột "Value"
    } else {
    // Thêm dòng mới
    int newRow = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(newRow);

    // Gán giá trị vào từng cột
    ui->tableWidget_2->setItem(newRow, 0, new QTableWidgetItem(name));  // Name
    ui->tableWidget_2->setItem(newRow, 1, new QTableWidgetItem(indexStr)); // Index
    ui->tableWidget_2->setItem(newRow, 2, new QTableWidgetItem(subindexStr)); // Subindex
    ui->tableWidget_2->setItem(newRow, 3, new QTableWidgetItem(type));  // Type
    ui->tableWidget_2->setItem(newRow, 4, new QTableWidgetItem(dataHex));  // data
    ui->tableWidget_2->setItem(newRow, 5, new QTableWidgetItem(valueDecimal));   // Cột "Value"

    // Lưu vị trí vào map để cập nhật nhanh hơn
    rowMap[key] = newRow;
    }
    // Chế độ màu xen kẽ
    ui->tableWidget_2->setAlternatingRowColors(true);
    QPalette palette = ui->tableWidget_2->palette();
    palette.setColor(QPalette::Base, QColor("#E3F2FD"));
    palette.setColor(QPalette::AlternateBase, QColor("#F5F5F5"));
    ui->tableWidget_2->setPalette(palette);


    // Hiệu ứng khoảng cách và tự động dãn
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_2->setStyleSheet("QTableWidget::item { padding: 6px; }");

}

    // Hàm đọc file JSON và lưu vào QMap
void MainWindow::loadJsonData() {
    QFile file("data.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở file JSON!";
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray dataArray = doc.array();

    for (const QJsonValue &value : dataArray) {
        QJsonObject obj = value.toObject();
        int index = obj["index"].toString().toInt(nullptr, 16);
        int subindex = obj["subindex"].toString().toInt(nullptr, 16);
        QString name = obj["name"].toString();
        QString type = obj["type"].toString();
        QString dataHex = obj["data"].toString(); // Lấy dữ liệu "data" (nếu có)
        QString valueDecimal = obj["value"].toString(); // Lấy giá trị "value" (nếu có)

        QPair<int, int> key = qMakePair(index, subindex);
        nameMap[key] = name;
        typeMap[key] = type;

        updateTableValue1(index, subindex, dataHex, valueDecimal);
    }

    QJsonArray array = doc.array();
    for (const QJsonValue &val : array) {
        if (val.isObject()) {
            canDefinitions.append(val.toObject());
        }
    }
}

// nút nhấn gửi speed
void MainWindow::on_pushButton_SPEED_clicked()
{
    bool ok;
    float value = ui->lineEdit_value->text().toFloat(&ok);
    if (!ok) {
        qDebug() << "Lỗi: Giá trị không hợp lệ!";
        return;
    }
    emit sendCANCommand(0x0183, 0x0000, value);
    appendToTableWidget(0x0183, 0000, value);
}

// nút nhấn gửi angle

void MainWindow::on_pushButton_ANGLE_clicked()
{
    bool ok;
    float value = ui->lineEdit_value->text().toFloat(&ok);
    if (!ok) {
        qDebug() << "Lỗi: Giá trị không hợp lệ!";
        return;
    }


    emit sendCANCommand(0x0182, 0x0000, value);
    appendToTableWidget(0x0182, 0000, value);
    theta_ref_global = value;
}


// void MainWindow::loadCANDefinitions()
// {
//     QFile file("data1.json");
//     if (!file.open(QIODevice::ReadOnly)) {
//         qDebug() << "Không thể mở file JSON";
//         return;
//     }

//     QByteArray jsonData = file.readAll();
//     QJsonDocument doc = QJsonDocument::fromJson(jsonData);
//     if (!doc.isArray()) {
//         qDebug() << "Dữ liệu JSON không phải mảng!";
//         return;
//     }

//     QJsonArray array = doc.array();
//     for (const QJsonValue &val : array) {
//         if (val.isObject()) {
//             canDefinitions.append(val.toObject());
//         }
//     }
// }
// /////////// HÀM HIỂN THỊ DỮ LIỆU LÊN TABLETABWIGET input output //////////////////
void MainWindow::appendToTableWidget(quint16 index, quint8 subindex, float data)
{
    QString name = "Unknown";
    QString type = "Unknown";

    // Tìm trong danh sách đã load từ JSON
    for (const QJsonObject &obj : canDefinitions) {
        bool ok;
        if (obj["index"].toString().toUShort(&ok, 16) == index &&
            obj["subindex"].toString().toUShort(&ok, 16) == subindex) {
            name = obj["name"].toString();
            type = obj["type"].toString();
            break;
        }
    }

    QString indexStr = QString("%1").arg(index, 4, 16, QLatin1Char('0')).toUpper();
    QString subindexStr = QString("%1").arg(subindex, 4, 16, QLatin1Char('0')).toUpper();

    // Data dạng hex
    QByteArray byteArray(reinterpret_cast<const char*>(&data), sizeof(float));
    QString hexData = byteArray.toHex(' ').toUpper();

    // Kiểm tra nếu đã có dòng trùng index + subindex
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QString existingIndex = ui->tableWidget->item(i, 1)->text();
        QString existingSubindex = ui->tableWidget->item(i, 2)->text();
        if (existingIndex == indexStr && existingSubindex == subindexStr) {
            // Cập nhật dòng
            ui->tableWidget->item(i, 0)->setText(name);
            ui->tableWidget->item(i, 3)->setText(type);
            ui->tableWidget->item(i, 4)->setText(hexData);

            // Tô màu dòng theo index
            QColor rowColor = QColor(255, 255, 255); // mặc định trắng
            if (  (index >= 0x01A0 && index <= 0x04A0)) {
                rowColor = QColor(255, 200, 200); // Output – đỏ nhạt
            } else if (index >= 0x0180 && index <= 0x0190) {
                rowColor = QColor(200, 255, 200); // Input – xanh lá nhạt
            }

            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                ui->tableWidget->item(i, col)->setBackground(rowColor);
            }

            return;
        }
    }

    // Nếu không trùng, thêm dòng mới
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(indexStr));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(subindexStr));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(type));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(hexData));


    // Tô màu dòng mới theo index
    QColor rowColor = QColor(255, 255, 255); // mặc định trắng
    if ( (index >= 0x01A0 && index <= 0x04A0)) {
        rowColor = QColor(255, 200, 200); // Output – đỏ nhạt
    } else if (index >= 0x0180 && index <= 0x0190) {
        rowColor = QColor(200, 255, 200); // Input – xanh lá nhạt
    }

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->item(row, col)->setBackground(rowColor);
    }

}

MainWindow::~MainWindow()
{
    canThread->quit();
    canThread->wait();
    delete canWorker;
    delete ui;
}




