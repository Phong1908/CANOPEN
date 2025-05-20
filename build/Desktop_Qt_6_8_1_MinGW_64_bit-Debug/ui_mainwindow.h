/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *alltab;
    QWidget *tab_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_3;
    QLabel *label_angle;
    QLabel *label_5;
    QLabel *label_id;
    QLabel *label_iq;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_speed;
    QGroupBox *groupBox_6;
    QTextBrowser *textBrowser_sent;
    QPushButton *pushButton_clear_sent;
    QGroupBox *groupBox_5;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_clear;
    QGroupBox *groupBox_4;
    QComboBox *comboBox_serialPort;
    QComboBox *comboBox_Baudrate;
    QLabel *label_status;
    QSplitter *splitter;
    QPushButton *pushButton_okPort;
    QPushButton *pushButton_refresh;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_ANGLE;
    QLineEdit *lineEdit_value_angle;
    QLabel *label_3;
    QPushButton *pushButton_SPEED;
    QLineEdit *lineEdit_value_speed;
    QGroupBox *groupBox_7;
    QLineEdit *kp_speed;
    QLineEdit *kd_speed;
    QLineEdit *kp_pos;
    QLineEdit *ki_speed;
    QLineEdit *ki_pos;
    QLineEdit *kd_pos;
    QPushButton *pushButton_sent_speed;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *pushButton_Mode_Speed;
    QPushButton *pushButton_Mode_Position;
    QPushButton *pushButton_send_pos;
    QTabWidget *dothi;
    QWidget *dongdien;
    QCustomPlot *customPlotWidget2;
    QWidget *sosanh_theta;
    QWidget *customPlotWidget3;
    QWidget *tab_4;
    QTableWidget *tableWidget_2;
    QWidget *tab;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1332, 672);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        alltab = new QTabWidget(centralwidget);
        alltab->setObjectName("alltab");
        alltab->setGeometry(QRect(0, 0, 1321, 631));
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 631, 601));
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
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(300, 360, 311, 231));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        groupBox_3->setFont(font1);
        groupBox_3->setTabletTracking(false);
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 235, 255);\n"
""));
        label_angle = new QLabel(groupBox_3);
        label_angle->setObjectName("label_angle");
        label_angle->setGeometry(QRect(140, 30, 141, 31));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        label_angle->setFont(font2);
        label_angle->setMouseTracking(false);
        label_angle->setAcceptDrops(false);
        label_angle->setAutoFillBackground(false);
        label_angle->setStyleSheet(QString::fromUtf8("border: 1px solid #000000;\n"
"color: rgb(0, 0, 0);"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 25, 91, 31));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_id = new QLabel(groupBox_3);
        label_id->setObjectName("label_id");
        label_id->setGeometry(QRect(140, 110, 141, 31));
        label_id->setFont(font2);
        label_id->setMouseTracking(false);
        label_id->setAcceptDrops(false);
        label_id->setAutoFillBackground(false);
        label_id->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border: 1px solid #000000;"));
        label_iq = new QLabel(groupBox_3);
        label_iq->setObjectName("label_iq");
        label_iq->setGeometry(QRect(140, 150, 141, 31));
        label_iq->setFont(font2);
        label_iq->setMouseTracking(false);
        label_iq->setAcceptDrops(false);
        label_iq->setAutoFillBackground(false);
        label_iq->setStyleSheet(QString::fromUtf8("border: 1px solid #000000;\n"
"color: rgb(0, 0, 0);"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 110, 51, 21));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 150, 61, 21));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 65, 101, 31));
        label_12->setFont(font1);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_speed = new QLabel(groupBox_3);
        label_speed->setObjectName("label_speed");
        label_speed->setGeometry(QRect(140, 70, 141, 31));
        label_speed->setFont(font2);
        label_speed->setMouseTracking(false);
        label_speed->setAcceptDrops(false);
        label_speed->setAutoFillBackground(false);
        label_speed->setStyleSheet(QString::fromUtf8("border: 1px solid #000000;\n"
"color: rgb(0, 0, 0);"));
        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(300, 0, 311, 211));
        groupBox_6->setFont(font1);
        groupBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 235, 255);"));
        textBrowser_sent = new QTextBrowser(groupBox_6);
        textBrowser_sent->setObjectName("textBrowser_sent");
        textBrowser_sent->setGeometry(QRect(10, 20, 291, 141));
        textBrowser_sent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_clear_sent = new QPushButton(groupBox_6);
        pushButton_clear_sent->setObjectName("pushButton_clear_sent");
        pushButton_clear_sent->setGeometry(QRect(220, 170, 75, 24));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(0, 0, 301, 211));
        groupBox_5->setFont(font1);
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);\n"
"background-color: rgb(229, 235, 255);"));
        textBrowser = new QTextBrowser(groupBox_5);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 20, 281, 141));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_clear = new QPushButton(groupBox_5);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(210, 170, 75, 24));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(0, 210, 301, 151));
        groupBox_4->setFont(font1);
        groupBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 235, 255);"));
        comboBox_serialPort = new QComboBox(groupBox_4);
        comboBox_serialPort->setObjectName("comboBox_serialPort");
        comboBox_serialPort->setGeometry(QRect(30, 30, 121, 31));
        comboBox_Baudrate = new QComboBox(groupBox_4);
        comboBox_Baudrate->addItem(QString());
        comboBox_Baudrate->addItem(QString());
        comboBox_Baudrate->addItem(QString());
        comboBox_Baudrate->addItem(QString());
        comboBox_Baudrate->addItem(QString());
        comboBox_Baudrate->setObjectName("comboBox_Baudrate");
        comboBox_Baudrate->setGeometry(QRect(30, 70, 121, 31));
        label_status = new QLabel(groupBox_4);
        label_status->setObjectName("label_status");
        label_status->setGeometry(QRect(30, 110, 121, 31));
        QFont font3;
        font3.setBold(true);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setStrikeOut(false);
        label_status->setFont(font3);
        label_status->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_status->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        splitter = new QSplitter(groupBox_4);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(180, 40, 111, 53));
        splitter->setOrientation(Qt::Orientation::Vertical);
        pushButton_okPort = new QPushButton(splitter);
        pushButton_okPort->setObjectName("pushButton_okPort");
        splitter->addWidget(pushButton_okPort);
        pushButton_refresh = new QPushButton(splitter);
        pushButton_refresh->setObjectName("pushButton_refresh");
        splitter->addWidget(pushButton_refresh);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(300, 210, 311, 151));
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 235, 255);"));
        pushButton_ANGLE = new QPushButton(groupBox_2);
        pushButton_ANGLE->setObjectName("pushButton_ANGLE");
        pushButton_ANGLE->setGeometry(QRect(20, 90, 111, 31));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        pushButton_ANGLE->setFont(font4);
        pushButton_ANGLE->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit_value_angle = new QLineEdit(groupBox_2);
        lineEdit_value_angle->setObjectName("lineEdit_value_angle");
        lineEdit_value_angle->setGeometry(QRect(20, 40, 113, 31));
        QFont font5;
        font5.setPointSize(16);
        font5.setBold(true);
        lineEdit_value_angle->setFont(font5);
        lineEdit_value_angle->setStyleSheet(QString::fromUtf8("border: 1px solid #000000;\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 20, 91, 16));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_SPEED = new QPushButton(groupBox_2);
        pushButton_SPEED->setObjectName("pushButton_SPEED");
        pushButton_SPEED->setGeometry(QRect(170, 90, 111, 31));
        pushButton_SPEED->setFont(font4);
        pushButton_SPEED->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);\n"
""));
        lineEdit_value_speed = new QLineEdit(groupBox_2);
        lineEdit_value_speed->setObjectName("lineEdit_value_speed");
        lineEdit_value_speed->setGeometry(QRect(170, 40, 113, 31));
        lineEdit_value_speed->setFont(font5);
        lineEdit_value_speed->setStyleSheet(QString::fromUtf8("border: 1px solid #000000;\n"
"color: rgb(0, 0, 0);"));
        groupBox_7 = new QGroupBox(groupBox);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(0, 360, 301, 231));
        groupBox_7->setFont(font1);
        groupBox_7->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 235, 255);"));
        kp_speed = new QLineEdit(groupBox_7);
        kp_speed->setObjectName("kp_speed");
        kp_speed->setGeometry(QRect(110, 50, 61, 31));
        kd_speed = new QLineEdit(groupBox_7);
        kd_speed->setObjectName("kd_speed");
        kd_speed->setGeometry(QRect(230, 50, 61, 31));
        kp_pos = new QLineEdit(groupBox_7);
        kp_pos->setObjectName("kp_pos");
        kp_pos->setGeometry(QRect(110, 100, 61, 31));
        ki_speed = new QLineEdit(groupBox_7);
        ki_speed->setObjectName("ki_speed");
        ki_speed->setGeometry(QRect(170, 50, 61, 31));
        ki_pos = new QLineEdit(groupBox_7);
        ki_pos->setObjectName("ki_pos");
        ki_pos->setGeometry(QRect(170, 100, 61, 31));
        kd_pos = new QLineEdit(groupBox_7);
        kd_pos->setObjectName("kd_pos");
        kd_pos->setGeometry(QRect(230, 100, 61, 31));
        pushButton_sent_speed = new QPushButton(groupBox_7);
        pushButton_sent_speed->setObjectName("pushButton_sent_speed");
        pushButton_sent_speed->setGeometry(QRect(40, 190, 91, 24));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 60, 61, 16));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 110, 91, 16));
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 21, 31, 20));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(190, 20, 31, 20));
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(250, 20, 31, 20));
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_Mode_Speed = new QPushButton(groupBox_7);
        pushButton_Mode_Speed->setObjectName("pushButton_Mode_Speed");
        pushButton_Mode_Speed->setGeometry(QRect(34, 150, 101, 24));
        pushButton_Mode_Position = new QPushButton(groupBox_7);
        pushButton_Mode_Position->setObjectName("pushButton_Mode_Position");
        pushButton_Mode_Position->setGeometry(QRect(160, 150, 101, 24));
        pushButton_send_pos = new QPushButton(groupBox_7);
        pushButton_send_pos->setObjectName("pushButton_send_pos");
        pushButton_send_pos->setGeometry(QRect(170, 190, 91, 24));
        dothi = new QTabWidget(tab_3);
        dothi->setObjectName("dothi");
        dothi->setGeometry(QRect(630, 0, 681, 601));
        dongdien = new QWidget();
        dongdien->setObjectName("dongdien");
        customPlotWidget2 = new QCustomPlot(dongdien);
        customPlotWidget2->setObjectName("customPlotWidget2");
        customPlotWidget2->setGeometry(QRect(10, 10, 661, 561));
        customPlotWidget2->setMouseTracking(false);
        customPlotWidget2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi->addTab(dongdien, QString());
        sosanh_theta = new QWidget();
        sosanh_theta->setObjectName("sosanh_theta");
        customPlotWidget3 = new QWidget(sosanh_theta);
        customPlotWidget3->setObjectName("customPlotWidget3");
        customPlotWidget3->setGeometry(QRect(10, 10, 661, 561));
        customPlotWidget3->setMouseTracking(false);
        customPlotWidget3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi->addTab(sosanh_theta, QString());
        alltab->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableWidget_2 = new QTableWidget(tab_4);
        if (tableWidget_2->columnCount() < 6)
            tableWidget_2->setColumnCount(6);
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Times New Roman")});
        font6.setPointSize(13);
        font6.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font6);
        __qtablewidgetitem->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font6);
        __qtablewidgetitem1->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font6);
        __qtablewidgetitem2->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font6);
        __qtablewidgetitem3->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font6);
        __qtablewidgetitem4->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Times New Roman")});
        font7.setPointSize(13);
        font7.setBold(true);
        font7.setItalic(false);
        font7.setUnderline(false);
        font7.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font7);
        __qtablewidgetitem5->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(0, 0, 781, 511));
        alltab->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font6);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font6);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font6);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font6);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font6);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 801, 511));
        alltab->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1332, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        alltab->setCurrentIndex(0);
        dothi->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "ACTUAL DATA", nullptr));
        label_angle->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "ANGLE(\317\200):", nullptr));
        label_id->setText(QString());
        label_iq->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "I_d(A):", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "I_q(A):", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "SPEED(rpm):", nullptr));
        label_speed->setText(QString());
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "DATA SENT TO STM32", nullptr));
        pushButton_clear_sent->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "DATA RECEIVED FROM STM32", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "SET COM", nullptr));
        comboBox_Baudrate->setItemText(0, QCoreApplication::translate("MainWindow", "115200", nullptr));
        comboBox_Baudrate->setItemText(1, QCoreApplication::translate("MainWindow", "57600", nullptr));
        comboBox_Baudrate->setItemText(2, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBox_Baudrate->setItemText(3, QCoreApplication::translate("MainWindow", "19200", nullptr));
        comboBox_Baudrate->setItemText(4, QCoreApplication::translate("MainWindow", "9600", nullptr));

        label_status->setText(QCoreApplication::translate("MainWindow", "Not connected", nullptr));
        pushButton_okPort->setText(QCoreApplication::translate("MainWindow", "CONNECTED", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "CONTROL", nullptr));
        pushButton_ANGLE->setText(QCoreApplication::translate("MainWindow", "ANGLE(\317\200)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SETPOINT:", nullptr));
        pushButton_SPEED->setText(QCoreApplication::translate("MainWindow", "SPEED(rpm)", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "PID", nullptr));
        pushButton_sent_speed->setText(QCoreApplication::translate("MainWindow", "Send PID", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "SPEED:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "POSITION:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Kp", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Ki", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Kd", nullptr));
        pushButton_Mode_Speed->setText(QCoreApplication::translate("MainWindow", "Mode_Speed", nullptr));
        pushButton_Mode_Position->setText(QCoreApplication::translate("MainWindow", "Mode_Position", nullptr));
        pushButton_send_pos->setText(QCoreApplication::translate("MainWindow", "Send PID", nullptr));
        dothi->setTabText(dothi->indexOf(dongdien), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        dothi->setTabText(dothi->indexOf(sosanh_theta), QCoreApplication::translate("MainWindow", "Page", nullptr));
        alltab->setTabText(alltab->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Index", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Subindex", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        alltab->setTabText(alltab->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Index", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Subindex", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        alltab->setTabText(alltab->indexOf(tab), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
