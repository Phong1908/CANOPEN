/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_RUN;
    QLabel *label_DK;
    QPushButton *pushButton_STOP;
    QPushButton *pushButton_STOP_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *pushButton_STOP_3;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_5;
    QGroupBox *groupBox_6;
    QTextBrowser *textBrowser_sent;
    QLineEdit *lineEdit_CAN_Data;
    QPushButton *pushButton_Send;
    QLineEdit *lineEdit_CAN_ID;
    QLabel *label_6;
    QLabel *label_7;
    QGroupBox *groupBox_5;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_readData;
    QPushButton *pushButton_clear;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *customPlotWidget;
    QWidget *tab_2;
    QWidget *tab_4;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1300, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 0, 1271, 561));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 631, 531));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setItalic(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        groupBox->setFont(font);
        groupBox->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 310, 301, 211));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        pushButton_RUN = new QPushButton(groupBox_2);
        pushButton_RUN->setObjectName(QString::fromUtf8("pushButton_RUN"));
        pushButton_RUN->setGeometry(QRect(10, 70, 111, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        pushButton_RUN->setFont(font2);
        pushButton_RUN->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(85, 255, 127);"));
        label_DK = new QLabel(groupBox_2);
        label_DK->setObjectName(QString::fromUtf8("label_DK"));
        label_DK->setGeometry(QRect(60, 30, 151, 31));
        label_DK->setFont(font2);
        label_DK->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        pushButton_STOP = new QPushButton(groupBox_2);
        pushButton_STOP->setObjectName(QString::fromUtf8("pushButton_STOP"));
        pushButton_STOP->setGeometry(QRect(140, 70, 111, 31));
        pushButton_STOP->setFont(font2);
        pushButton_STOP->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"color: rgb(0, 0, 0);"));
        pushButton_STOP_2 = new QPushButton(groupBox_2);
        pushButton_STOP_2->setObjectName(QString::fromUtf8("pushButton_STOP_2"));
        pushButton_STOP_2->setGeometry(QRect(10, 160, 111, 31));
        pushButton_STOP_2->setFont(font2);
        pushButton_STOP_2->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(120, 110, 113, 31));
        lineEdit->setFont(font2);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 120, 91, 16));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_STOP_3 = new QPushButton(groupBox_2);
        pushButton_STOP_3->setObjectName(QString::fromUtf8("pushButton_STOP_3"));
        pushButton_STOP_3->setGeometry(QRect(140, 160, 111, 31));
        pushButton_STOP_3->setFont(font2);
        pushButton_STOP_3->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(310, 310, 311, 211));
        groupBox_3->setFont(font1);
        groupBox_3->setTabletTracking(false);
        groupBox_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 40, 111, 31));
        label->setFont(font2);
        label->setMouseTracking(false);
        label->setAcceptDrops(false);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 50, 111, 16));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 100, 111, 31));
        label_2->setFont(font2);
        label_2->setMouseTracking(false);
        label_2->setAcceptDrops(false);
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 110, 111, 16));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(310, 70, 311, 231));
        groupBox_6->setFont(font1);
        groupBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser_sent = new QTextBrowser(groupBox_6);
        textBrowser_sent->setObjectName(QString::fromUtf8("textBrowser_sent"));
        textBrowser_sent->setGeometry(QRect(10, 20, 291, 131));
        textBrowser_sent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_CAN_Data = new QLineEdit(groupBox_6);
        lineEdit_CAN_Data->setObjectName(QString::fromUtf8("lineEdit_CAN_Data"));
        lineEdit_CAN_Data->setGeometry(QRect(10, 190, 151, 31));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        lineEdit_CAN_Data->setFont(font3);
        lineEdit_CAN_Data->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        pushButton_Send = new QPushButton(groupBox_6);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));
        pushButton_Send->setGeometry(QRect(220, 180, 75, 24));
        lineEdit_CAN_ID = new QLineEdit(groupBox_6);
        lineEdit_CAN_ID->setObjectName(QString::fromUtf8("lineEdit_CAN_ID"));
        lineEdit_CAN_ID->setGeometry(QRect(10, 160, 151, 31));
        lineEdit_CAN_ID->setFont(font3);
        lineEdit_CAN_ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 170, 51, 16));
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(170, 200, 51, 16));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 70, 301, 231));
        groupBox_5->setFont(font1);
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser = new QTextBrowser(groupBox_5);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 20, 281, 131));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_readData = new QPushButton(groupBox_5);
        pushButton_readData->setObjectName(QString::fromUtf8("pushButton_readData"));
        pushButton_readData->setGeometry(QRect(10, 200, 75, 24));
        pushButton_clear = new QPushButton(groupBox_5);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(210, 200, 75, 24));
        tabWidget = new QTabWidget(tab_3);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(630, 0, 581, 541));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        customPlotWidget = new QWidget(tab);
        customPlotWidget->setObjectName(QString::fromUtf8("customPlotWidget"));
        customPlotWidget->setGeometry(QRect(10, 10, 661, 481));
        customPlotWidget->setMouseTracking(false);
        customPlotWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tableWidget = new QTableWidget(tab_4);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 8)
            tableWidget->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem14);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QBrush brush1(QColor(255, 255, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setBackground(brush1);
        __qtablewidgetitem15->setForeground(brush);
        tableWidget->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(5, 2, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(6, 2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(7, 2, __qtablewidgetitem33);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 330, 571, 201));
        tableWidget_2 = new QTableWidget(tab_4);
        if (tableWidget_2->columnCount() < 6)
            tableWidget_2->setColumnCount(6);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Times New Roman"));
        font4.setPointSize(10);
        font4.setBold(true);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        __qtablewidgetitem34->setFont(font4);
        __qtablewidgetitem34->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setFont(font4);
        __qtablewidgetitem35->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setFont(font4);
        __qtablewidgetitem36->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setFont(font4);
        __qtablewidgetitem37->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        __qtablewidgetitem38->setFont(font4);
        __qtablewidgetitem38->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem38);
        QFont font5;
        font5.setFamily(QString::fromUtf8("Times New Roman"));
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setUnderline(false);
        font5.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setFont(font5);
        __qtablewidgetitem39->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem39);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 0, 1131, 271));
        tabWidget_2->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1300, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\304\220I\341\273\200U KHI\341\273\202N ", nullptr));
        pushButton_RUN->setText(QCoreApplication::translate("MainWindow", "RUN", nullptr));
        label_DK->setText(QString());
        pushButton_STOP->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        pushButton_STOP_2->setText(QCoreApplication::translate("MainWindow", "ANGLE", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SETPOINT:", nullptr));
        pushButton_STOP_3->setText(QCoreApplication::translate("MainWindow", "SPEED", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U TH\341\273\260C T\341\272\276", nullptr));
        label->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "REAL SPEED:", nullptr));
        label_2->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "REAL ANGLE:", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U G\341\273\254I", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "SEND", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "DATA", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U NH\341\272\254N", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton_readData->setText(QCoreApplication::translate("MainWindow", "Read Data", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "index", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "sub-index", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "value", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "digital_inputs", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "digital_outputs", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "following_error_time_out", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "velocity_sensor_actual_value", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "velocity_demand_value", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "0446", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "0000", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(0, 2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(1, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "60FE", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "0x00", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(1, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "0x01", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(3, 1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "0x02", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(3, 2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(4, 1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "0x03", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(4, 2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(5, 0);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "6066", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(5, 1);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "0x00", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(5, 2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(6, 0);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "6069", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(6, 1);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "0x00", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(6, 2);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(7, 0);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "606B", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(7, 1);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "0x00", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->item(7, 2);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "UINT16", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Index", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Subindex", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
