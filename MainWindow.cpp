#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h" // Thư viện QCustomPlot
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>
#include <chrono>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>

// Biến tạm để lưu giá trị id/iq
float id_tmp = 0;
float iq_tmp = 0;
float theta_ref_global = 0.0f;
float speed_ref_global = 0.0f;
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
    // ui->dothi->setTabText(0, "Graph Voltage");
    ui->dothi->setTabText(0, "Graph Current");
    ui->dothi->setTabText(1, "Graph Angle");
    ui->dothi->setTabText(2, "Graph Speed");
    ui->alltab->setTabText(0, "Graph and Controls");
    ui->alltab->setTabText(1, "PDO and SDO List");
    ui->alltab->setTabText(2, "Received and Sent Messages");



    // //////////////// đổi tên của sổ ////////////////////
    this->setWindowTitle("MOTOR_CONTROL_MONITOR");

    // Chế độ màu xen kẽ bảng PDO và SDO
    ui->tableWidget_2->setAlternatingRowColors(true);
    QPalette palette = ui->tableWidget_2->palette();
    palette.setColor(QPalette::Base, QColor("#E3F2FD"));
    palette.setColor(QPalette::AlternateBase, QColor("#F5F5F5"));
    ui->tableWidget_2->setPalette(palette);


    // Hiệu ứng khoảng cách và tự động dãn
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_2->setStyleSheet("QTableWidget::item { padding: 6px; }");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setStyleSheet("QTableWidget::item { padding: 6px; }");

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
    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::listAvailableSerialPorts);
    connect(ui->pushButton_okPort, &QPushButton::clicked, this, &MainWindow::on_pushButton_okPort_clicked);
    connect(Serial, &QSerialPort::readyRead, this, &MainWindow::readCanData);


    // 4. Khởi động luồng
    canThread->start();

    listAvailableSerialPorts();


    // ////////////////////ĐỒ THỊ ĐIỆN ÁP //////////////////////////////////////
    // customPlotVoltage = new QCustomPlot(ui->customPlotWidget1);
    // customPlotVoltage->setGeometry(ui->customPlotWidget1->rect());
    // customPlotVoltage->setOpenGl(true); // Bật Double Buffer với OpenGL

    // // Graph 0: ud (xanh)
    // customPlotVoltage->addGraph();
    // customPlotVoltage->graph(0)->setPen(QPen(Qt::blue));
    // customPlotVoltage->graph(0)->setName("ud");

    // // Graph 1: uq (cam)
    // customPlotVoltage->addGraph();
    // customPlotVoltage->graph(1)->setPen(QPen(Qt::darkYellow));
    // customPlotVoltage->graph(1)->setName("uq");

    // // Cấu hình trục
    // customPlotVoltage->xAxis->setLabel("Time (s)");
    // customPlotVoltage->yAxis->setLabel("Voltage (V)");
    // customPlotVoltage->xAxis->setRange(0, 10);
    // customPlotVoltage->yAxis->setRange(-10, 10);  // Điều chỉnh tùy hệ thống
    // customPlotVoltage->legend->setVisible(true);

    // // Bật zoom và kéo bằng chuột trên cả hai trục
    // customPlotVoltage->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    // // customPlotVoltage->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);  // Zoom cả trục X và Y
    // //////////////////// ĐỒ THỊ DÒNG ĐIỆN //////////////////////////////////////////////
    customPlotCurrent = new QCustomPlot(ui->customPlotWidget2);
    customPlotCurrent->setGeometry(ui->customPlotWidget2->rect());
    customPlotCurrent->setOpenGl(true); // Bật Double Buffer với OpenGL

    // Cỡ chữ 18
    QFont font18("Times New Roman", 18);
    customPlotCurrent->xAxis->setLabelFont(font18);
    customPlotCurrent->yAxis->setLabelFont(font18);
    customPlotCurrent->xAxis->setTickLabelFont(font18);
    customPlotCurrent->yAxis->setTickLabelFont(font18);
    customPlotCurrent->legend->setFont(font18);

    // tên đồ thị
    customPlotCurrent->plotLayout()->insertRow(0);
    customPlotCurrent->plotLayout()->addElement(0, 0, new QCPTextElement(customPlotCurrent, "Graph Current", font18));
    // Graph 0: id (xanh)
    customPlotCurrent->addGraph();
    customPlotCurrent->graph(0)->setPen(QPen(Qt::blue));
    customPlotCurrent->graph(0)->setName("id");

    // Graph 1: iq (cam)
    customPlotCurrent->addGraph();
    customPlotCurrent->graph(1)->setPen(QPen(Qt::darkYellow));
    customPlotCurrent->graph(1)->setName("iq");

    // Cấu hình trục
    customPlotCurrent->xAxis->setLabel("Time (s)");
    customPlotCurrent->yAxis->setLabel("Current (A)");
    customPlotCurrent->xAxis->setRange(0, 10);
    customPlotCurrent->yAxis->setRange(-1, 1);  // Điều chỉnh tùy hệ thống
    customPlotCurrent->legend->setVisible(true);
    customPlotCurrent->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // //////////////////////////////// ĐỒ THỊ THETA ////////////////////////////////
    // Khởi tạo QCustomPlot cho góc theta (gắn vào customPlotWidget3)
    customPlotTheta = new QCustomPlot(ui->customPlotWidget3);
    customPlotTheta->setGeometry(ui->customPlotWidget3->rect());
    customPlotTheta->setOpenGl(true);


    // Cỡ chữ 18
    customPlotTheta->xAxis->setLabelFont(font18);
    customPlotTheta->yAxis->setLabelFont(font18);
    customPlotTheta->xAxis->setTickLabelFont(font18);
    customPlotTheta->yAxis->setTickLabelFont(font18);
    customPlotTheta->legend->setFont(font18);

    // tên đồ thị
    customPlotTheta->plotLayout()->insertRow(0);
    customPlotTheta->plotLayout()->addElement(0, 0, new QCPTextElement(customPlotTheta, "Graph Angle", font18));

    // Thêm đồ thị
    customPlotTheta->addGraph();  // theta_now
    customPlotTheta->graph(0)->setPen(QPen(Qt::darkGreen));
    customPlotTheta->graph(0)->setName("theta_now");

    customPlotTheta->addGraph();  // theta_ref
    customPlotTheta->graph(1)->setPen(QPen(Qt::red, 1, Qt::DashLine));
    customPlotTheta->graph(1)->setName("theta_ref");

    // Cấu hình trục
    customPlotTheta->xAxis->setLabel("Time (s)");
    customPlotTheta->yAxis->setLabel("Angle (π)");
    customPlotTheta->xAxis->setRange(0, 10);
    customPlotTheta->yAxis->setRange(-10, 10);  // Điều chỉnh theo hệ thống của bạn
    customPlotTheta->legend->setVisible(true);
    customPlotTheta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // //////////////////////////////// ĐỒ THỊ SPEED khi điều khiển vị trí ////////////////////////////////
    customPlotSpeed = new QCustomPlot(ui->customPlotWidget4);
    customPlotSpeed->setGeometry(ui->customPlotWidget4->rect());
    customPlotSpeed->setOpenGl(true);

    // Cỡ chữ 18
    customPlotSpeed->xAxis->setLabelFont(font18);
    customPlotSpeed->yAxis->setLabelFont(font18);
    customPlotSpeed->xAxis->setTickLabelFont(font18);
    customPlotSpeed->yAxis->setTickLabelFont(font18);
    customPlotSpeed->legend->setFont(font18);

    // tên đồ thị
    customPlotSpeed->plotLayout()->insertRow(0);
    customPlotSpeed->plotLayout()->addElement(0, 0, new QCPTextElement(customPlotSpeed, "Graph Speed", font18));

    // Thêm đồ thị cho speed_now
    customPlotSpeed->addGraph();  // graph(0) - speed_now
    customPlotSpeed->graph(0)->setPen(QPen(Qt::blue));
    customPlotSpeed->graph(0)->setName("speed_now");

    // Cấu hình trục
    customPlotSpeed->xAxis->setLabel("Time (s)");
    customPlotSpeed->yAxis->setLabel("Speed(RPM)");
    customPlotSpeed->xAxis->setRange(0, 10);
    customPlotSpeed->yAxis->setRange(-10,10);  // điều chỉnh theo hệ thống
    customPlotSpeed->legend->setVisible(true);
    customPlotSpeed->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // //////////////////////////////// ĐỒ THỊ SPEED khi điều khiển tốc độ ////////////////////////////////
    customPlotSpeedGraph = new QCustomPlot(ui->customPlotWidget5);
    customPlotSpeedGraph->setGeometry(ui->customPlotWidget5->rect());
    customPlotSpeedGraph->setOpenGl(true);

    // Cỡ chữ 18
    customPlotSpeedGraph->xAxis->setLabelFont(font18);
    customPlotSpeedGraph->yAxis->setLabelFont(font18);
    customPlotSpeedGraph->xAxis->setTickLabelFont(font18);
    customPlotSpeedGraph->yAxis->setTickLabelFont(font18);
    customPlotSpeedGraph->legend->setFont(font18);

    // tên đồ thị
    customPlotSpeedGraph->plotLayout()->insertRow(0);
    customPlotSpeedGraph->plotLayout()->addElement(0, 0, new QCPTextElement(customPlotSpeedGraph, "Graph Speed", font18));

    customPlotSpeedGraph->addGraph();  // speed_now
    customPlotSpeedGraph->graph(0)->setPen(QPen(Qt::blue));
    customPlotSpeedGraph->graph(0)->setName("speed_now");

    customPlotSpeedGraph->addGraph();  // speed_ref
    customPlotSpeedGraph->graph(1)->setPen(QPen(Qt::darkRed, 1, Qt::DashLine));
    customPlotSpeedGraph->graph(1)->setName("speed_ref");

    customPlotSpeedGraph->xAxis->setLabel("Time (s)");
    customPlotSpeedGraph->yAxis->setLabel("Speed(RPM)");
    customPlotSpeedGraph->xAxis->setRange(0, 10);
    customPlotSpeedGraph->yAxis->setRange(-100, 100);  // Tuỳ hệ thống bạn
    customPlotSpeedGraph->legend->setVisible(true);
    customPlotSpeedGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ THETA /////////////////////////////////
    thetaPlotTimer = new QTimer(this);
    connect(thetaPlotTimer, &QTimer::timeout, this, &MainWindow::updateThetaPlot);
    thetaPlotTimer->start(20);

    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ DÒNG ĐIỆN /////////////////////////////////
    currentTimer = new QTimer(this);
    connect(currentTimer, &QTimer::timeout, this, &MainWindow::updateCurrentPlot);
    currentTimer->start(20); //
    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ ĐIỆN ÁP /////////////////////////////////
    // VoltageTimer = new QTimer(this);
    // connect(VoltageTimer, &QTimer::timeout, this, &MainWindow::updateVoltagePlot);
    // VoltageTimer->start(20); //
    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ SPEED ĐIỀU KHIỂN VỊ TRÍ /////////////////////////////////
    speedPlotTimer = new QTimer(this);
    connect(speedPlotTimer, &QTimer::timeout, this, &MainWindow::updateSpeedPlot);
    speedPlotTimer->start(20);

    // //////////////// TIMER CẬP NHẬT ĐỒ THỊ SPEED ĐIỀU KHIỂN TỐC ĐỘ /////////////////////////////////
    speedGraphElapsedTimer.start();
    speedGraphTimer = new QTimer(this);
    connect(speedGraphTimer, &QTimer::timeout, this, &MainWindow::updateSpeedGraphPlot);
    speedGraphTimer->start(20);

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
        double timestamp = thetaTimer.elapsed() / 1000.0;
        timeVector.append(timestamp);
        thetaRefVec.append(point.x());
        thetaNowVec.append(point.y());
    }

    totalTimeTheta += timeVector;
    totalThetaRef += thetaRefVec;
    totalThetaNow += thetaNowVec;

    while (totalTimeTheta.size() > 400) {
        totalTimeTheta.removeFirst();
        totalThetaRef.removeFirst();
        totalThetaNow.removeFirst();
    }

    if (!totalTimeTheta.isEmpty()) {
        double lastTime = totalTimeTheta.last();
        customPlotTheta->xAxis->setRange(qMax(0.0, lastTime - 40), lastTime);
    }

    customPlotTheta->graph(0)->setData(totalTimeTheta, totalThetaNow);
    customPlotTheta->graph(1)->setData(totalTimeTheta, totalThetaRef);
    customPlotTheta->replot();
}
// /////////////////////////////// SPEED ĐIỀU KHIỂN VỊ TRÍ  //////////////////////////////////////
void MainWindow::updateSpeedPlot()
{
    QVector<QPointF> plotData;

    speedBufferMutex.lock();
    useSpeedBufferA = !useSpeedBufferA;
    if (useSpeedBufferA) {
        plotData = speedBufferB;
        speedBufferB.clear();
    } else {
        plotData = speedBufferA;
        speedBufferA.clear();
    }
    speedBufferMutex.unlock();

    QVector<double> timeVec, speedNowVec;
    for (const QPointF &point : plotData) {
        timeVec.append(point.x());
        speedNowVec.append(point.y());
    }

    totalTimeSpeed += timeVec;
    totalSpeedNow += speedNowVec;

    while (totalTimeSpeed.size() > 400) {
        totalTimeSpeed.removeFirst();
        totalSpeedNow.removeFirst();
    }

    if (!totalTimeSpeed.isEmpty()) {
        double lastTime = totalTimeSpeed.last();
        customPlotSpeed->xAxis->setRange(qMax(0.0, lastTime - 40), lastTime);
    }

    customPlotSpeed->graph(0)->setData(totalTimeSpeed, totalSpeedNow);
    customPlotSpeed->replot();
}

// /////////////////////////////// SPEED ĐIỀU KHIỂN TỐC ĐỘ //////////////////////////////////////
void MainWindow::updateSpeedGraphPlot()
{
    QVector<QPointF> plotData;

    speedGraphBufferMutex.lock();
    useSpeedGraphBufferA = !useSpeedGraphBufferA;
    if (useSpeedGraphBufferA) {
        plotData = speedGraphBufferB;
        speedGraphBufferB.clear();
    } else {
        plotData = speedGraphBufferA;
        speedGraphBufferA.clear();
    }
    speedGraphBufferMutex.unlock();

    QVector<double> timeVec, speedNowVec, speedRefVec;

    for (const QPointF &point : plotData) {
        double timestamp = speedGraphElapsedTimer.elapsed() / 1000.0;
        timeVec.append(timestamp);
        speedRefVec.append(point.x());
        speedNowVec.append(point.y());
    }

    totalTimeSpeedGraph += timeVec;
    totalSpeedNowGraph += speedNowVec;
    totalSpeedRefGraph += speedRefVec;

    while (totalTimeSpeedGraph.size() > 400) {
        totalTimeSpeedGraph.removeFirst();
        totalSpeedNowGraph.removeFirst();
        totalSpeedRefGraph.removeFirst();
    }

    if (!totalTimeSpeedGraph.isEmpty()) {
        double lastTime = totalTimeSpeedGraph.last();
        customPlotSpeedGraph->xAxis->setRange(qMax(0.0, lastTime - 40), lastTime);
    }

    customPlotSpeedGraph->graph(0)->setData(totalTimeSpeedGraph, totalSpeedNowGraph);
    customPlotSpeedGraph->graph(1)->setData(totalTimeSpeedGraph, totalSpeedRefGraph);
    customPlotSpeedGraph->replot();
}

// /////////////////////////////// DÒNG ĐIỆN //////////////////////////////////////

void MainWindow::updateCurrentPlot()
{
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
        double timestamp = currentTimerElapsed.elapsed() / 1000.0;
        timeVec.append(timestamp);
        idVec.append(point.x());
        iqVec.append(point.y());
    }

    totalTimeCurrent += timeVec;
    totalId += idVec;
    totalIq += iqVec;

    while (totalTimeCurrent.size() > 400) {
        totalTimeCurrent.removeFirst();
        totalId.removeFirst();
        totalIq.removeFirst();
    }

    if (!totalTimeCurrent.isEmpty()) {
        double lastTime = totalTimeCurrent.last();
        customPlotCurrent->xAxis->setRange(qMax(0.0, lastTime - 20), lastTime);
    }

    customPlotCurrent->graph(0)->setData(totalTimeCurrent, totalId);
    customPlotCurrent->graph(1)->setData(totalTimeCurrent, totalIq);
    customPlotCurrent->replot();
}

void MainWindow::updateVoltagePlot(){
    // QVector<QPointF> data;

    // voltageBufferMutex.lock();
    // useVoltageBufferA = !useVoltageBufferA;
    // if (useVoltageBufferA) {
    //     data = voltageBufferB;
    //     voltageBufferB.clear();
    // } else {
    //     data = voltageBufferA;
    //     voltageBufferA.clear();
    // }
    // voltageBufferMutex.unlock();

    // QVector<double> udVec, uqVec, timeVec;

    // for (const QPointF &point : data) {
    //     double timestamp = voltageTimerElapsed.elapsed() / 1000.0;
    //     timeVec.append(timestamp);
    //     udVec.append(point.x());
    //     uqVec.append(point.y());
    // }

    // totalTimeVoltage += timeVec;
    // totalUd += udVec;
    // totalUq += uqVec;

    // while (totalTimeVoltage.size() > 400) {
    //     totalTimeVoltage.removeFirst();
    //     totalUd.removeFirst();
    //     totalUq.removeFirst();
    // }

    // if (!totalTimeVoltage.isEmpty()) {
    //     double lastTime = totalTimeVoltage.last();
    //     customPlotVoltage->xAxis->setRange(qMax(0.0, lastTime - 20), lastTime);
    // }

    // customPlotVoltage->graph(0)->setData(totalTimeVoltage, totalUd);
    // customPlotVoltage->graph(1)->setData(totalTimeVoltage, totalUq);
    // customPlotVoltage->replot();
}


void MainWindow::listAvailableSerialPorts()
{
    ui->comboBox_serialPort->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        ui->comboBox_serialPort->addItem(port.portName(), port.portName());
    }

    if (ui->comboBox_serialPort->count() == 0)
        ui->comboBox_serialPort->addItem("No COM ports found");
}

void MainWindow::on_pushButton_refresh_clicked()
{
    listAvailableSerialPorts();
}

void MainWindow::on_pushButton_okPort_clicked()
{
    // QString selectedPort = ui->comboBox_serialPort->currentData().toString();
    // if (selectedPort.isEmpty() || selectedPort.contains("No COM ports")) {
    //     QMessageBox::warning(this, "Invalid Port", "Please select a valid COM port.");
    //     return;
    // }

    // // Đọc Baudrate từ comboBox_Baudrate
    // QString selectedBaud = ui->comboBox_Baudrate->currentText();

    // Serial->setPortName(selectedPort);
    // // Serial->setBaudRate(QSerialPort::Baud115200);
    // Serial->setBaudRate(selectedBaud.toInt());  // Thiết lập Baudrate
    // Serial->setDataBits(QSerialPort::Data8);
    // Serial->setParity(QSerialPort::NoParity);
    // Serial->setStopBits(QSerialPort::OneStop);
    // Serial->setFlowControl(QSerialPort::NoFlowControl);

    // if (Serial->open(QIODevice::ReadWrite)) {
    //     qDebug() << "Serial port opened: " << selectedPort;
    //     // connect(Serial, &QSerialPort::readyRead, this, &MainWindow::readCanData);
    //     QMessageBox::information(this, "Success", "Connected to " + selectedPort);
    //     ui->label_status->setText("Connected to " + selectedPort);
    // }
    // thetaTimer.start();
    // currentTimerElapsed.start();
    // voltageTimerElapsed.start();
    QString selectedPort = ui->comboBox_serialPort->currentData().toString();
    if (selectedPort.isEmpty() || selectedPort.contains("No COM ports")) {
        QMessageBox::warning(this, "Invalid Port", "Please select a valid COM port.");
        return;
    }

    // Đọc Baudrate từ comboBox_Baudrate
    QString selectedBaud = ui->comboBox_Baudrate->currentText();

    // Đóng cổng COM nếu đang mở
    if (Serial->isOpen()) {
        Serial->close();
        qDebug() << "Serial port closed before reconnecting.";
    }

    Serial->setPortName(selectedPort);
    Serial->setBaudRate(selectedBaud.toInt());
    Serial->setDataBits(QSerialPort::Data8);
    Serial->setParity(QSerialPort::NoParity);
    Serial->setStopBits(QSerialPort::OneStop);
    Serial->setFlowControl(QSerialPort::NoFlowControl);

    if (Serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened: " << selectedPort;
        // QMessageBox::information(this, "Success", "Connected to " + selectedPort);
        ui->label_status->setText("Connected to " + selectedPort);

        // Bắt đầu timer sau khi kết nối thành công
        thetaTimer.start();
        currentTimerElapsed.start();
        voltageTimerElapsed.start();
        speedGraphElapsedTimer.start();
    } else {
        QMessageBox::critical(this, "Error", "Failed to open " + selectedPort);
        ui->label_status->setText("Disconnected");
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


void MainWindow::updateTextBrowserSent(const QString &data)
{

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

QByteArray MainWindow::removeFrameCtrl(const QByteArray &rawData) {
    QByteArray cleaned;
    for (int i = 0; i < rawData.size(); ++i) {
        if ((uchar)rawData[i] == 0xA5) {
            // Nếu là FrameCtrl, bỏ qua nó, lấy byte kế tiếp nếu có
            if (i + 1 < rawData.size()) {
                cleaned.append(rawData[i + 1]);
                ++i; // Bỏ qua byte tiếp theo (vì đã xử lý)
            }
        } else {
            cleaned.append(rawData[i]);
        }
    }
    return cleaned;
}


bool MainWindow::parseCanHeader(const QByteArray &data, int &index, int &subindex, QByteArray &valueData) {
    // Giải mã FrameCtrl nếu có
    QByteArray cleaned = removeFrameCtrl(data);

    if (cleaned.size() < 20) return false;

    index = (uchar)cleaned[3] << 8 | (uchar)cleaned[2];
    subindex = (uchar)cleaned[5] << 8 | (uchar)cleaned[4];
    valueData = cleaned.mid(6, 8);  // bạn có thể thay 8 bằng Length thật từ byte 14 nếu cần
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

void MainWindow::handleSpecialValues(int index, int subindex, const QByteArray &valueData) {
    // static float prev_id = 0.0f;
    // static float prev_iq = 0.0f;
    // float valueFloat = convertToFloat(valueData);
    // if (valueFloat > -1500 && valueFloat < 1500 && (valueFloat < -0.0000001 || valueFloat > 0.0000001)) {
    //     if (index == 0x01A0 && subindex == 0x0000) {
    //         // Angle
    //         ui->label_angle->setText(QString::number(valueFloat/3.14159265359, 'f', 4));
    //         float theta_now = valueFloat/3.14159265359;
    //         float theta_ref = theta_ref_global;
    //         double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    //         thetaTimeData.append(timestamp);
    //         thetaNowData.append(theta_now);
    //         thetaRefData.append(theta_ref);

    //         QMutexLocker locker(&bufferMutex);
    //         if (useBufferA)
    //             bufferA.append(QPointF(theta_ref_global, theta_now));
    //         else
    //             bufferB.append(QPointF(theta_ref_global, theta_now));
    //     }

    //     else if (index == 0x02A0 && subindex == 0x0000 && valueData.size() >= 8) {
    //         // id và iq
    //         float id = convertToFloat(valueData.mid(0, 4));
    //         float iq = convertToFloat(valueData.mid(4, 4));

    //         if (id > -100 && id < 100 && (id < -0.00001 || id > 0.00001)) {
    //             if (qAbs(id - prev_id) <= 20.0f) {  // chỉ nhận nếu chênh lệch không quá 20
    //                 ui->label_id->setText(QString::number(id, 'f', 4));
    //                 id_tmp = id;
    //                 prev_id = id; // lưu giá trị để so sánh lần sau
    //             }
    //         }

    //         if (iq > -100 && iq < 100 && (iq < -0.00001 || iq > 0.00001)) {
    //             if (qAbs(iq - prev_iq) <= 20.0f) {
    //                 ui->label_iq->setText(QString::number(iq, 'f', 4));
    //                 iq_tmp = iq;
    //                 prev_iq = iq;

    //                 QMutexLocker locker(&currentBufferMutex);
    //                 if (useCurrentBufferA)
    //                     currentBufferA.append(QPointF(id_tmp, iq_tmp));
    //                 else
    //                     currentBufferB.append(QPointF(id_tmp, iq_tmp));
    //             }
    //         }
    //     }

    //     else if (index == 0x03A0 && subindex == 0x0000 && valueData.size() >= 8) {
    //         // vd và vq
    //         float vd = convertToFloat(valueData.mid(0, 4));
    //         // qDebug() << "Giá trị vd sau khi chuyển đổi:" << vd;
    //         // qDebug() << "Dữ liệu valueData (hex):" << valueData.toHex(' ').toUpper();
    //         float vq = convertToFloat(valueData.mid(4, 4));

    //         if (vd > -50 && vd < 50 && (vd < -0.01 || vd > 0.01))
    //             ui->label_vd->setText(QString::number(vd, 'f', 4));

    //         if (vq > -100 && vq < 100 && (vq < -0.01 || vq > 0.01))
    //             ui->label_vq->setText(QString::number(vq, 'f', 4));

    //         if ((qAbs(vd) > 0.0001 && qAbs(vd) < 50) &&
    //             (qAbs(vq) > 0.0001 && qAbs(vq) < 50)) {

    //             QMutexLocker locker(&voltageBufferMutex);
    //             if (useVoltageBufferA)
    //                 voltageBufferA.append(QPointF(vd, vq));
    //             else
    //                 voltageBufferB.append(QPointF(vd, vq));
    //         }
    //     }
    // }
    float valueFloat = convertToFloat(valueData);
    if (index == 0x01A0 && subindex == 0x0000) {
        // Angle
        ui->label_angle->setText(QString::number(valueFloat / 3.14159265359, 'f', 4));
        float theta_now = valueFloat / 3.14159265359;
        float theta_ref = theta_ref_global;
        double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
        thetaTimeData.append(timestamp);
        thetaNowData.append(theta_now);
        thetaRefData.append(theta_ref);

        QMutexLocker locker(&bufferMutex);
        if (useBufferA)
            bufferA.append(QPointF(theta_ref, theta_now));
        else
            bufferB.append(QPointF(theta_ref, theta_now));


        // speed khi điều khiển vị trí
        float speed_now = convertToFloat(valueData.mid(4, 4));
        float speed_ref = speed_ref_global;
        ui->label_speed->setText(QString::number(speed_now, 'f', 4));

        double timestamp1 = thetaTimer.elapsed() / 1000.0;

        totalTimeSpeed.append(timestamp1);
        totalSpeedNow.append(speed_now);

        QMutexLocker locker2(&speedBufferMutex);
        if (useSpeedBufferA)
            speedBufferA.append(QPointF(timestamp1, speed_now));
        else
            speedBufferB.append(QPointF(timestamp1, speed_now));

        QMutexLocker locker3(&speedGraphBufferMutex);
        if (useSpeedGraphBufferA)
            speedGraphBufferA.append(QPointF(speed_ref, speed_now));
        else
            speedGraphBufferB.append(QPointF(speed_ref, speed_now));
    }

    else if (index == 0x02A0 && subindex == 0x0000 && valueData.size() >= 8) {
        // id và iq
        float id = convertToFloat(valueData.mid(0, 4));
        float iq = convertToFloat(valueData.mid(4, 4));

        ui->label_id->setText(QString::number(id, 'f', 4));
        ui->label_iq->setText(QString::number(iq, 'f', 4));
        id_tmp = id;
        iq_tmp = iq;

        QMutexLocker locker(&currentBufferMutex);
        if (useCurrentBufferA)
            currentBufferA.append(QPointF(id_tmp, iq_tmp));
        else
            currentBufferB.append(QPointF(id_tmp, iq_tmp));


    }

    // else if (index == 0x03A0 && subindex == 0x0000 && valueData.size() >= 8) {
    //     // vd và vq
    //     float vd = convertToFloat(valueData.mid(0, 4));
    //     float vq = convertToFloat(valueData.mid(4, 4));

    //     ui->label_vd->setText(QString::number(vd, 'f', 4));
    //     ui->label_vq->setText(QString::number(vq, 'f', 4));

    //     QMutexLocker locker(&voltageBufferMutex);
    //     if (useVoltageBufferA)
    //         voltageBufferA.append(QPointF(vd, vq));
    //     else
    //         voltageBufferB.append(QPointF(vd, vq));
    // }
    if (index == 0x03A0 && subindex == 0x0000 && valueData.size() >= 6) {
        if (autoUpdatePID) {
        // Đọc raw 2 byte theo little endian
        quint16 kp_raw = static_cast<quint16>(static_cast<quint8>(valueData[0]) | (static_cast<quint8>(valueData[1]) << 8));
        quint16 ki_raw = static_cast<quint16>(static_cast<quint8>(valueData[2]) | (static_cast<quint8>(valueData[3]) << 8));
        quint16 kd_raw = static_cast<quint16>(static_cast<quint8>(valueData[4]) | (static_cast<quint8>(valueData[5]) << 8));




        // Chuyển về float với scale (ví dụ: x100 → chia 100.0f)
        float kp = kp_raw/ 100.0f;
        float ki = ki_raw/ 100.0f;
        float kd = kd_raw/ 100.0f;

        // Hiển thị lên giao diện
        ui->kp_speed->setText(QString::number(kp, 'f', 2));
        ui->ki_speed->setText(QString::number(ki, 'f', 2));
        ui->kd_speed->setText(QString::number(kd, 'f', 2));

        }
    }

    if (index == 0x04A0 && subindex == 0x0000 && valueData.size() >= 6) {
        if (autoUpdatePID) {
        // Đọc raw 2 byte theo Little Endian
        quint16 kp_raw = static_cast<quint8>(valueData[0]) | (static_cast<quint8>(valueData[1]) << 8);
        quint16 ki_raw = static_cast<quint8>(valueData[2]) | (static_cast<quint8>(valueData[3]) << 8);
        quint16 kd_raw = static_cast<quint8>(valueData[4]) | (static_cast<quint8>(valueData[5]) << 8);

        // Chuyển về float với scale (ví dụ: x100 → chia 100.0f)
        float kp = kp_raw / 100.0f;
        float ki = ki_raw / 100.0f;
        float kd = kd_raw / 100.0f;

        // Hiển thị lên giao diện
        ui->kp_pos->setText(QString::number(kp, 'f', 2));
        ui->ki_pos->setText(QString::number(ki, 'f', 2));
        ui->kd_pos->setText(QString::number(kd, 'f', 2));
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

    // Gọi hàm mới dùng QByteArray thay vì float
    appendToTableWidget(index, subindex, valueData);

    handleSpecialValues(index, subindex, valueData);
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
    float value = ui->lineEdit_value_speed->text().toFloat(&ok);
    if (!ok) {
        qDebug() << "Lỗi: Giá trị không hợp lệ!";
        return;
    }

    emit sendCANCommand(0x0184, 0x0000, value);

    // Chuyển float thành QByteArray (8 byte)
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));

    appendToTableWidget(0x0184, 0x0000, valueData);
    speed_ref_global= value;

}

// nút nhấn gửi angle
void MainWindow::on_pushButton_ANGLE_clicked()
{
    bool ok;
    float value = ui->lineEdit_value_angle->text().toFloat(&ok);
    if (!ok) {
        qDebug() << "Lỗi: Giá trị không hợp lệ!";
        return;
    }

    value *= 3.14159265359;
    qDebug().nospace() << "value = " << QString::number(value, 'f', 10);

    emit sendCANCommand(0x0180, 0x0000, value);

    // Chuyển float thành QByteArray (8 byte)
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));

    appendToTableWidget(0x0180, 0x0000, valueData);

    theta_ref_global = value / 3.14159265359;
}

// nút nhấn gửi mode speed
void MainWindow::on_pushButton_Mode_Speed_clicked()
{
    float value = 1.0f;
    emit sendCANCommand(0x0183, 0x0000, value);  // Gửi float

    // Tạo 8 byte để hiển thị lên bảng
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));
    //hiển thi lên bảng
    appendToTableWidget(0x0183, 0x0000, valueData);

}


// nút nhấn gửi mode angle
void MainWindow::on_pushButton_Mode_Position_clicked()
{
    float value = 0.0f;
    emit sendCANCommand(0x0183, 0x0000, value);  // Gửi float

    // Tạo 8 byte để hiển thị lên bảng
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));
    //hiển thi lên bảng
    appendToTableWidget(0x0183, 0x0000, valueData);
}

// nút nhấn gửi PID
void MainWindow::on_pushButton_send_PID_clicked() {
    // Đọc PID speed từ UI
    float kp_speed = ui->kp_speed->text().toFloat();
    float ki_speed = ui->ki_speed->text().toFloat();
    float kd_speed = ui->kd_speed->text().toFloat();

    // Đọc PID position từ UI
    float kp_pos = ui->kp_pos->text().toFloat();
    float ki_pos = ui->ki_pos->text().toFloat();
    float kd_pos = ui->kd_pos->text().toFloat();

    if (canWorker) {
        // Gửi PID speed với index 181
        canWorker->sendPIDFrame(0x0181, kp_speed, ki_speed, kd_speed);
        // Hiển thị PID speed lên bảng
        QByteArray speedData(6, 0);
        qint16 kp_raw = static_cast<qint16>(kp_speed * 100);
        qint16 ki_raw = static_cast<qint16>(ki_speed * 100);
        qint16 kd_raw = static_cast<qint16>(kd_speed * 100);
        speedData[0] = kp_raw & 0xFF;
        speedData[1] = (kp_raw >> 8) & 0xFF;
        speedData[2] = ki_raw & 0xFF;
        speedData[3] = (ki_raw >> 8) & 0xFF;
        speedData[4] = kd_raw & 0xFF;
        speedData[5] = (kd_raw >> 8) & 0xFF;
        appendToTableWidget(0x0181, 0x0000, speedData);

        // Gửi PID position với index 182 (0x00B6)
        canWorker->sendPIDFrame(0x0182, kp_pos, ki_pos, kd_pos);
    }
}

// nút nhấn gửi mode change PID
    void MainWindow::on_pushButton_change_PID_clicked()
{
    float value = 1.0f;
    autoUpdatePID = false; // Tắt cập nhật tự động
    emit sendCANCommand(0x0185, 0x0000, value);  // Gửi float

    // Tạo 8 byte để hiển thị lên bảng
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));
    //hiển thi lên bảng
    appendToTableWidget(0x0185, 0x0000, valueData);

}


// nút nhấn refresh PID
void MainWindow::on_pushButton_refresh_PID_clicked()
{
    float value = 0.0f;
    autoUpdatePID = true;  // Bật lại cập nhật
    emit sendCANCommand(0x0185, 0x0000, value);  // Gửi float

    // Tạo 8 byte để hiển thị lên bảng
    QByteArray valueData(8, 0);
    memcpy(valueData.data(), &value, sizeof(float));
    //hiển thi lên bảng
    appendToTableWidget(0x0185, 0x0000, valueData);

}
// // nút nhấn gửi pid speed
// void MainWindow::on_pushButton_sent_speed_clicked() {
//     float kp = ui->kp_speed->text().toFloat();
//     float ki = ui->ki_speed->text().toFloat();
//     float kd = ui->kd_speed->text().toFloat();

//     // Gửi PID Speed với index = 0x03A0
//     if (canWorker) {
//         canWorker->sendPIDFrame(0x03A0, kp, ki, kd);
//     }
// }

// // nút nhấn gửi pid pos
// void MainWindow::on_pushButton_send_pos_clicked() {
//     float kp = ui->kp_pos->text().toFloat();
//     float ki = ui->ki_pos->text().toFloat();
//     float kd = ui->kd_pos->text().toFloat();

//     // Gửi PID Position với index = 0x04A0
//     if (canWorker) {
//         canWorker->sendPIDFrame(0x04A0, kp, ki, kd);
//     }
// }


void MainWindow::on_save_plot_speed_clicked(){
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Lưu đồ thị tốc độ",
        "",
        "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)"
        );

    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
            customPlotSpeedGraph->savePdf(fileName);
        } else if (fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
            customPlotSpeedGraph->saveJpg(fileName, 1200, 800);
        } else if (fileName.endsWith(".png", Qt::CaseInsensitive)) {
            customPlotSpeedGraph->savePng(fileName, 1200, 800);
        } else {
            // Nếu người dùng không nhập đuôi hoặc đuôi khác thì mặc định thêm .png
            customPlotSpeedGraph->savePng(fileName + ".png", 1200, 800);
        }
    }
}
void MainWindow::on_save_plot_current_clicked(){
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Lưu đồ thị tốc độ",
        "",
        "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)"
        );

    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
            customPlotCurrent->savePdf(fileName);
        } else if (fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
            customPlotCurrent->saveJpg(fileName, 1200, 800);
        } else if (fileName.endsWith(".png", Qt::CaseInsensitive)) {
            customPlotCurrent->savePng(fileName, 1200, 800);
        } else {
            // Nếu người dùng không nhập đuôi hoặc đuôi khác thì mặc định thêm .png
            customPlotCurrent->savePng(fileName + ".png", 1200, 800);
        }
    }
}

// void MainWindow::on_save_plot_angle_clicked() {
//     QString fileName = QFileDialog::getSaveFileName(
//         this,
//         "Lưu đồ thị tốc độ + góc",
//         "",
//         "PNG Files (*.png);;JPEG Files (*.jpg)"
//         );

//     if (fileName.isEmpty())
//         return;

//     // Kích thước mỗi đồ thị
//     QSize plotSize(1200, 400);  // mỗi đồ thị cao 400px
//     QSize totalSize(plotSize.width(), plotSize.height() * 2);  // tổng cộng 2 đồ thị

//     QPixmap finalPixmap(totalSize);
//     finalPixmap.fill(Qt::white); // Nền trắng

//     QPainter painter(&finalPixmap);
//     customPlotTheta->resize(plotSize);
//     customPlotTheta->replot(); // Đảm bảo đã vẽ xong
//     customPlotTheta->render(&painter, QPoint(0, 0), QRegion(), QWidget::DrawChildren);

//     customPlotSpeed->resize(plotSize);
//     customPlotSpeed->replot(); // Đảm bảo đã vẽ xong
//     customPlotSpeed->render(&painter, QPoint(0, plotSize.height()), QRegion(), QWidget::DrawChildren);

//     painter.end();

//     bool success = false;

//     if (fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
//         success = finalPixmap.save(fileName, "JPG");
//     } else if (fileName.endsWith(".png", Qt::CaseInsensitive)) {
//         success = finalPixmap.save(fileName, "PNG");
//     } else {
//         // Mặc định PNG nếu không rõ đuôi
//         success = finalPixmap.save(fileName + ".png", "PNG");
//     }

//     if (success) {
//         QMessageBox::information(this, "Thành công", "Đã lưu 2 đồ thị vào file:\n" + fileName);
//     } else {
//         QMessageBox::critical(this, "Lỗi", "Không thể lưu file.");
//     }
// }

void MainWindow::on_save_plot_angle_clicked() {
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Lưu đồ thị góc và tốc độ",
        "",
        "PNG Files (*.png);;JPEG Files (*.jpg)"
        );

    if (fileName.isEmpty())
        return;

    // Kích thước mỗi đồ thị
    int width = 1200;
    int height = 400;

    // Vẽ mỗi đồ thị thành QPixmap riêng (không resize widget thật)
    QPixmap thetaPixmap = customPlotTheta->toPixmap(width, height);
    QPixmap speedPixmap = customPlotSpeed->toPixmap(width, height);

    // Tạo ảnh kết hợp
    QPixmap finalPixmap(width, height * 2);
    finalPixmap.fill(Qt::white);

    QPainter painter(&finalPixmap);
    painter.drawPixmap(0, 0, thetaPixmap);
    painter.drawPixmap(0, height, speedPixmap);
    painter.end();

    bool success = false;

    if (fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) {
        success = finalPixmap.save(fileName, "JPG");
    } else if (fileName.endsWith(".png", Qt::CaseInsensitive)) {
        success = finalPixmap.save(fileName, "PNG");
    } else {
        success = finalPixmap.save(fileName + ".png", "PNG");
    }
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
// void MainWindow::appendToTableWidget(quint16 index, quint8 subindex, double data)
// {
//     QString name = "Unknown";
//     QString type = "Unknown";

//     // Tìm trong danh sách đã load từ JSON
//     for (const QJsonObject &obj : canDefinitions) {
//         bool ok;
//         if (obj["index"].toString().toUShort(&ok, 16) == index &&
//             obj["subindex"].toString().toUShort(&ok, 16) == subindex) {
//             name = obj["name"].toString();
//             type = obj["type"].toString();
//             break;
//         }
//     }

//     QString indexStr = QString("%1").arg(index, 4, 16, QLatin1Char('0')).toUpper();
//     QString subindexStr = QString("%1").arg(subindex, 4, 16, QLatin1Char('0')).toUpper();

//     // ❗ Chuyển `double data` sang float (4 byte) giống bảng 2
//     float floatData = static_cast<float>(data);
//     QByteArray byteArray(reinterpret_cast<const char*>(&floatData), sizeof(float));
//     QString hexData;
//     for (int i = 0; i < byteArray.size(); ++i) {
//         hexData += QString("%1 ").arg(static_cast<quint8>(byteArray[i]), 2, 16, QLatin1Char('0')).toUpper();
//     }
//     hexData = hexData.trimmed(); // Bỏ khoảng trắng cuối

//     // Kiểm tra nếu đã có dòng trùng index + subindex
//     int rowCount = ui->tableWidget->rowCount();
//     for (int i = 0; i < rowCount; ++i) {
//         QString existingIndex = ui->tableWidget->item(i, 1)->text();
//         QString existingSubindex = ui->tableWidget->item(i, 2)->text();
//         if (existingIndex == indexStr && existingSubindex == subindexStr) {
//             // Cập nhật dòng
//             ui->tableWidget->item(i, 0)->setText(name);
//             ui->tableWidget->item(i, 3)->setText(type);
//             ui->tableWidget->item(i, 4)->setText(hexData);

//             // Tô màu dòng theo index
//             QColor rowColor = QColor(255, 255, 255); // mặc định trắng
//             if (index >= 0x01A0 && index <= 0x04A0) {
//                 rowColor = QColor(255, 200, 200); // Output – đỏ nhạt
//             } else if (index >= 0x0180 && index <= 0x0190) {
//                 rowColor = QColor(200, 255, 200); // Input – xanh lá nhạt
//             }

//             for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
//                 ui->tableWidget->item(i, col)->setBackground(rowColor);
//             }

//             return;
//         }
//     }

//     // Nếu không trùng, thêm dòng mới
//     int row = ui->tableWidget->rowCount();
//     ui->tableWidget->insertRow(row);
//     ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
//     ui->tableWidget->setItem(row, 1, new QTableWidgetItem(indexStr));
//     ui->tableWidget->setItem(row, 2, new QTableWidgetItem(subindexStr));
//     ui->tableWidget->setItem(row, 3, new QTableWidgetItem(type));
//     ui->tableWidget->setItem(row, 4, new QTableWidgetItem(hexData));

//     // Tô màu dòng mới theo index
//     QColor rowColor = QColor(255, 255, 255); // mặc định trắng
//     if ((index >= 0x01A0 && index <= 0x04A0) || (index == 0x0720)) {
//         rowColor = QColor(255, 200, 200); // Output – đỏ nhạt
//     } else if (index >= 0x0180 && index <= 0x0190) {
//         rowColor = QColor(200, 255, 200); // Input – xanh lá nhạt
//     }

//     for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
//         ui->tableWidget->item(row, col)->setBackground(rowColor);
//     }
// }
void MainWindow::appendToTableWidget(quint16 index, quint8 subindex, const QByteArray &valueData)
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

    // Chuyển valueData thành chuỗi hex
    QString hexData;
    for (int i = 0; i < valueData.size(); ++i) {
        hexData += QString("%1 ").arg(static_cast<quint8>(valueData[i]), 2, 16, QLatin1Char('0')).toUpper();
    }
    hexData = hexData.trimmed();

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
            if ((index >= 0x01A0 && index <= 0x04A0) || (index == 0x0720)) {
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
    if ((index >= 0x01A0 && index <= 0x04A0) || (index == 0x0720)) {
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




