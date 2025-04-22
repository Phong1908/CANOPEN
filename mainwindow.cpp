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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    loadJsonData(); // Load dữ liệu từ JSON khi khởi động
    // Tạo đối tượng Serial
    Serial = new QSerialPort(this);
    // Kết nối tín hiệu với slot xử lý


    connect(ui->pushButton_Send, &QPushButton::clicked, this, &MainWindow::sendCanData);

    // Cài đặt cổng COM
    setupSerialPort();
    // //////////////////// ĐỒ THỊ DÒNG ĐIỆN //////////////////////////////////////////////
    // Tạo đối tượng QCustomPlot và gắn nó vào widget customPlotWidget1
    QCustomPlot *customPlot = new QCustomPlot(ui->customPlotWidget1);
    customPlot->setGeometry(ui->customPlotWidget1->rect()); // Đặt kích thước khớp với widget



    // Khởi tạo QCustomPlot cho dòng điện (gắn vào customPlotWidget2)
    QCustomPlot *customPlotCurrent = new QCustomPlot(ui->customPlotWidget2);
    customPlotCurrent->setGeometry(ui->customPlotWidget2->rect());

    // Tạo 2 đồ thị cho i_d và i_q
    customPlotCurrent->addGraph();  // i_d
    customPlotCurrent->graph(0)->setPen(QPen(Qt::darkRed));
    customPlotCurrent->graph(0)->setName("i_d");

    customPlotCurrent->addGraph();  // i_q
    customPlotCurrent->graph(1)->setPen(QPen(Qt::darkBlue));
    customPlotCurrent->graph(1)->setName("i_q");

    // Cấu hình trục và chú thích
    customPlotCurrent->xAxis->setLabel("Thoi gian (s)");
    customPlotCurrent->yAxis->setLabel("Dong dien (A)");
    customPlotCurrent->xAxis->setRange(0, 10);  // Hiển thị 10 giây gần nhất
    customPlotCurrent->yAxis->setRange(-0.9, 0.9);
    customPlotCurrent->legend->setVisible(true);
    customPlotCurrent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Dữ liệu thời gian và dòng điện
    QVector<double> timeData, idData, iqData;
    double *elapsedTime = new double(0);  // Thời gian đã trôi qua

    // Tạo timer cập nhật đồ thị
    QTimer *plotTimer = new QTimer(this);
    connect(plotTimer, &QTimer::timeout, this, [=]() mutable {
        // Lấy giá trị từ label
        double id = ui->label_id->text().toDouble();
        double iq = ui->label_iq->text().toDouble();

        // Cập nhật thời gian
        *elapsedTime += 0.05;  // Giả sử 50ms mỗi lần cập nhật
        timeData.append(*elapsedTime);
        idData.append(id);
        iqData.append(iq);

        // Giới hạn tối đa 200 điểm để không quá tải
        if (timeData.size() > 200) {
            timeData.removeFirst();
            idData.removeFirst();
            iqData.removeFirst();
        }

        // Cập nhật dữ liệu lên đồ thị
        customPlotCurrent->graph(0)->setData(timeData, idData);
        customPlotCurrent->graph(1)->setData(timeData, iqData);

        // Cập nhật trục x để cuộn theo thời gian
        customPlotCurrent->xAxis->setRange(*elapsedTime - 10, *elapsedTime);
        customPlotCurrent->replot();
    });

    plotTimer->start(50);  // Cập nhật mỗi 50ms

    // //////////////////////////////// ĐỒ THỊ THETA ////////////////////////////////
    // Khởi tạo QCustomPlot cho góc theta (gắn vào customPlotWidget3)
    customPlotTheta = new QCustomPlot(ui->customPlotWidget3);
    customPlotTheta->setGeometry(ui->customPlotWidget3->rect());

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
    customPlotTheta->yAxis->setRange(-6.5, 6.5);  // Điều chỉnh theo hệ thống của bạn
    customPlotTheta->legend->setVisible(true);
    customPlotTheta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // === TIMER CẬP NHẬT ĐỒ THỊ ===
    thetaTimer = new QTimer(this);
    connect(thetaTimer, &QTimer::timeout, this, [=]() {
        // Lấy giá trị theta_now từ label
        double thetaNow = ui->label_angle->text().toDouble();

        elapsedTheta += 0.05;
        timeThetaData.append(elapsedTheta);
        thetaNowData.append(thetaNow);
        thetaRefData.append(thetaRef);  // Giữ nguyên đến khi có cập nhật mới

        // Giới hạn 200 điểm
        if (timeThetaData.size() > 200) {
            timeThetaData.removeFirst();
            thetaNowData.removeFirst();
            thetaRefData.removeFirst();
        }

        // Cập nhật đồ thị
        customPlotTheta->graph(0)->setData(timeThetaData, thetaNowData);
        customPlotTheta->graph(1)->setData(timeThetaData, thetaRefData);
        customPlotTheta->xAxis->setRange(elapsedTheta - 10, elapsedTheta);
        customPlotTheta->replot();
    });
    thetaTimer->start(50);

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
    // Lấy văn bản hiện tại từ textBrowser và thêm dữ liệu mới
    QString displayText = ui->textBrowser->toPlainText();
    displayText.append(data + "  |  " + QTime::currentTime().toString("hh:mm:ss") + "\n");

    // Cập nhật lại nội dung textBrowser
    ui->textBrowser->setPlainText(displayText);

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
// Gửi dữ liệu qua cổng com
void MainWindow::sendCanData()
{
    QString idHex = ui->lineEdit_CAN_ID->text();     // Lấy ID từ QLineEdit
    QString dataHex = ui->lineEdit_CAN_Data->text(); // Lấy Data từ QLineEdit

    QByteArray idData = hexStringToByteArray(idHex);  // Chuyển ID sang QByteArray
    QByteArray frameData = hexStringToByteArray(dataHex); // Chuyển Data sang QByteArray

    if (idData.size() != 4 || frameData.size() != 8) // Kiểm tra đúng kích thước
    {
        qDebug() << "Loi: ID phai có 4 byte và Data phai có 8 byte!";
        return;
    }

    QByteArray frame;
    frame.append((char)0xAA); // Start Mark 1
    frame.append((char)0xAA); // Start Mark 2
    frame.append(idData); // Thêm 4 byte ID vào Frame
    frame.append(frameData); // Thêm 8 byte Data vào Frame

    // **Thêm các trường bổ sung**
    frame.append((char)0x08); // Frame Data Length = 8 byte
    frame.append((char)0x00); // Message Type = 0x00 (CAN Message)
    frame.append((char)0x01); // CAN Frame Type = 0x01 (Extended)'
    frame.append((char)0x00); // CAN Request Type = 0x01 (Remote Request Frame)

    // **Tính toán CRC**
    QByteArray crcData = idData + frameData;
    crcData.append((char)0x08); // Thêm Frame Data Length vào CRC
    crcData.append((char)0x00); // Thêm Message Type vào CRC
    crcData.append((char)0x01); // Thêm CAN Frame Type vào CRC
    crcData.append((char)0x00); // Thêm CAN Request Type vào CRC

    QByteArray processedData;
    for (char byte : crcData)
    {
        if (byte == (char)0xA5 || byte == (char)0xAA || byte == (char)0x55)
        {
            processedData.append((char)0xA5); // Thêm FrameCtrl nếu gặp ký tự đặc biệt
        }
        processedData.append(byte);
    }

    uchar crc = 0;
    for (char byte : processedData)
    {
        crc += (uchar)byte; // Tổng đơn giản
    }
    crc &= 0xFF;

    if (crc == 0xA5 || crc == 0xAA || crc == 0x55)
    {
        frame.append((char)0xA5); // Chống trùng CRC với ký tự đặc biệt
    }
    frame.append(crc); // Thêm CRC vào Frame

    frame.append((char)0x55); // End
    frame.append((char)0x55); // End

    // **Gửi dữ liệu qua COM**
    Serial->write(frame);

    if (Serial->waitForBytesWritten(1000)) // Chờ gửi xong
    {
        QString sentData = frame.toHex(' ').toUpper();
        qDebug() << "Sent Data (HEX): " << frame.toHex(' ').toUpper();
        updateTextBrowserSent(sentData);
    }
    else
    {
        qDebug() << "Loi khi gui du lieu!";
    }
}

QByteArray MainWindow::hexStringToByteArray(const QString &hex)
{
    QByteArray byteArray;
    QStringList hexList = hex.split(' ', Qt::SkipEmptyParts); // Tách từng byte
    for (const QString &byte : hexList)
    {
        bool ok;
        byteArray.append(static_cast<char>(byte.toInt(&ok, 16))); // Chuyển từ HEX sang Byte
        if (!ok)
        {
            qDebug() << "Loi chuyen đoi du lieu HEX!";
            return QByteArray(); // Trả về rỗng nếu có lỗi
        }
    }
    return byteArray;
}

void MainWindow::updateTextBrowserSent(const QString &data)
{
    QString displayText = ui->textBrowser_sent->toPlainText();
    displayText.append(data + "  |  " + QTime::currentTime().toString("hh:mm:ss") + "\n");
    ui->textBrowser_sent->setPlainText(displayText);

    // **Tự động cuộn xuống cuối**
    QTextCursor cursor = ui->textBrowser_sent->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser_sent->setTextCursor(cursor);
}


void MainWindow::parseCanData(const QByteArray &data) {
    if (data.size() < 20) { // Kiểm tra độ dài hợp lệ
        qDebug() << "Dữ liệu nhận được không hợp lệ!";
        return;
    }

    // Bỏ qua 2 byte đầu (AA AA)
    int index = (uchar)data[3] << 8 | (uchar)data[2]; // ID (Little Endian)
    int subindex = (uchar)data[5] << 8 | (uchar)data[4]; // Subindex (Byte thứ 6)

    // Lấy dữ liệu 8 byte tiếp theo
    QByteArray valueData = data.mid(6, 8);
    QString dataHex = valueData.toHex(' ').toUpper(); // Chuyển thành chuỗi HEX

    // Chuyển dữ liệu sang số nguyên (Big Endian)
    qint64 valueDecimal = 0;
    for (int i = 0; i < 4; i++) {
        valueDecimal = (valueDecimal << 8) | (uchar)valueData[i];
    }

    // Cập nhật vào bảng QTableWidget
    updateTableValue1(index, subindex, dataHex, QString::number(valueDecimal));
    ui->tableWidget_3->resizeColumnsToContents();

    // ---- CÁCH CHUYỂN 4 BYTE ĐẦU THÀNH FLOAT ----
    float valueFloat = 0.0f;
    QByteArray floatData;
    if (valueData.size() >= 4) {
        QByteArray floatData = valueData.left(8); // Lấy 8 byte đầu
        // Đảo thứ tự byte vì dữ liệu gốc là Big Endian
        // std::reverse(floatData.begin(), floatData.end());
        memcpy(&valueFloat, floatData.data(), sizeof(float)); // Chuyển đổi dữ liệu
    }

    // Kiểm tra nếu dữ liệu là Speed hoặc Angle

    if (index == 0x01A0 && subindex == 0x0000) { // Angle (thay bằng Index thực tế)
        ui->label_angle->setText(QString::number(valueFloat, 'f', 0));
    }
    else if (index == 0x02A0 && subindex == 0x0000) {
        ui->label_id->setText(QString::number(valueFloat, 'f', 4));
    }
    else if (index == 0x03A0 && subindex == 0x0000) {
        ui->label_iq->setText(QString::number(valueFloat, 'f', 4));
    }


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
        ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(type)); // Cập nhật Type
        ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(dataHex));   // Cập nhật cột "Data"
        ui->tableWidget_3->setItem(row, 5, new QTableWidgetItem(valueDecimal)); //Cập nhật cột "Value"
    } else {
        // Thêm dòng mới
        int newRow = ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow(newRow);

        // Gán giá trị vào từng cột
        ui->tableWidget_3->setItem(newRow, 0, new QTableWidgetItem(name));  // Name
        ui->tableWidget_3->setItem(newRow, 1, new QTableWidgetItem(indexStr)); // Index
        ui->tableWidget_3->setItem(newRow, 2, new QTableWidgetItem(subindexStr)); // Subindex
        ui->tableWidget_3->setItem(newRow, 3, new QTableWidgetItem(type));  // Type
        ui->tableWidget_3->setItem(newRow, 4, new QTableWidgetItem(dataHex));  // data
        ui->tableWidget_3->setItem(newRow, 5, new QTableWidgetItem(valueDecimal));   // Cột "Value"

        // Lưu vị trí vào map để cập nhật nhanh hơn
        rowMap[key] = newRow;
    }
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

}


// Gửi dữ liệu tốc độ và góc quay
void MainWindow::sendCANFrame(quint16 index, quint16 subindex, float value) {
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
    Serial->write(frame);

    if (Serial->waitForBytesWritten(1000)) // Chờ gửi xong
    {
        QString sentData = frame.toHex(' ').toUpper();
        qDebug() << "Sent Data (HEX): " << frame.toHex(' ').toUpper();
        updateTextBrowserSent(sentData);
    }
    else
    {
        qDebug() << "Loi khi gui du lieu!";
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

    quint16 index = 0x0183;   // Đặt Index cố định
    quint16 subindex = 0x0000; // Đặt SubIndex cố định

    sendCANFrame(index, subindex, value);
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

    quint16 index = 0x0182;   // Giữ nguyên Index cố định
    quint16 subindex = 0x0000; // SubIndex cho ANGLE

    sendCANFrame(index, subindex, value);
    thetaRef = ui->lineEdit_value->text().toDouble();
}




MainWindow::~MainWindow()
{
    delete ui;
}




