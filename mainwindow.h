#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h" // Thêm thư viện QCustomPlot
#include <QSerialPort>
#include <QTimer>
#include <QElapsedTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void writeCanData(const QByteArray &data); //

    QMap<QPair<int, int>, QString> nameMap;
    QMap<QPair<int, int>, QString> typeMap;
    QMap<QPair<int, int>, int> rowMap; // Lưu vị trí của (index, subindex)

private slots:

    void on_pushButton_readData_clicked(); // Đọc dữ liệu
    void on_pushButton_clear_clicked();   // Xóa dữ liệu
    void readCanData();                    // Đọc dữ liệu từ Serial

    void on_pushButton_SPEED_clicked();
    void on_pushButton_ANGLE_clicked();
    void on_pushButton_clear_sent_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *Serial;                 // Serial port object
    QTimer *timer;                         // Đọc dữ liệu theo chu kỳ
    void setupSerialPort();             // Cài đặt cổng COM
    QLineEdit *lineEdit_value;
    void updateTextBrowser(const QString &data); // Hiển thị dữ liệu vào textBrowser
    void sendCanData();
    void sendCanFrame();
    QByteArray hexStringToByteArray(const QString &hex);
    void updateTextBrowserSent(const QString &data);
    void parseCanData(const QByteArray &data);
    void updateTableValue1(int index, int subindex, const QString &dataHex, const QString &valueDecimal);
    void loadJsonData();
    void sendCANFrame(quint16 index, quint16 subindex, float value);
    void processReceivedCANFrame(const QByteArray &frame);
    void parseDataByPattern(const QByteArray &data);

    // Biến dùng cho đồ thị dòng điện

    QVector<double> timeData, idData, iqData;
    QTimer *plotTimer;
    double elapsedTime;

    // Biến dùng cho đồ thị theta
    QCustomPlot *customPlotTheta;
    QVector<double> timeThetaData, thetaNowData, thetaRefData;
    double elapsedTheta = 0;
    double thetaRef = 0;
    QTimer *thetaTimer;
};
#endif // MAINWINDOW_H

