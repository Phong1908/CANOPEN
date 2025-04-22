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
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget_1;
    QWidget *tab_3;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_7;
    QPushButton *pushButton_ANGLE;
    QLineEdit *lineEdit_value;
    QLabel *label_4;
    QPushButton *pushButton_SPEED;
    QGroupBox *groupBox_8;
    QLabel *label_angle;
    QLabel *label_10;
    QLabel *label_id;
    QLabel *label_iq;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *groupBox_9;
    QTextBrowser *textBrowser_sent;
    QLineEdit *lineEdit_CAN_Data;
    QPushButton *pushButton_Send;
    QLineEdit *lineEdit_CAN_ID;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButton_clear_sent;
    QGroupBox *groupBox_10;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_readData;
    QPushButton *pushButton_clear;
    QTabWidget *dothi_2;
    QWidget *dienap_2;
    QWidget *customPlotWidget1;
    QWidget *dongdien_2;
    QCustomPlot *customPlotWidget2;
    QWidget *sosanh_theta_2;
    QWidget *customPlotWidget3;
    QWidget *tab_6;
    QTableWidget *tableWidget_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1300, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget_1 = new QTabWidget(centralwidget);
        tabWidget_1->setObjectName(QString::fromUtf8("tabWidget_1"));
        tabWidget_1->setGeometry(QRect(0, 0, 1291, 561));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 631, 531));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setItalic(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        groupBox_4->setFont(font);
        groupBox_4->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        groupBox_4->setAutoFillBackground(false);
        groupBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        groupBox_7 = new QGroupBox(groupBox_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 310, 301, 211));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        groupBox_7->setFont(font1);
        groupBox_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        pushButton_ANGLE = new QPushButton(groupBox_7);
        pushButton_ANGLE->setObjectName(QString::fromUtf8("pushButton_ANGLE"));
        pushButton_ANGLE->setGeometry(QRect(10, 110, 111, 31));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        pushButton_ANGLE->setFont(font2);
        pushButton_ANGLE->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit_value = new QLineEdit(groupBox_7);
        lineEdit_value->setObjectName(QString::fromUtf8("lineEdit_value"));
        lineEdit_value->setGeometry(QRect(120, 50, 113, 31));
        lineEdit_value->setFont(font2);
        lineEdit_value->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 60, 91, 16));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_SPEED = new QPushButton(groupBox_7);
        pushButton_SPEED->setObjectName(QString::fromUtf8("pushButton_SPEED"));
        pushButton_SPEED->setGeometry(QRect(140, 110, 111, 31));
        pushButton_SPEED->setFont(font2);
        pushButton_SPEED->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"border-top-color: rgb(255, 85, 127);\n"
"alternate-background-color: rgb(85, 85, 0);\n"
"background-color: rgb(255, 170, 0);\n"
"color: rgb(255, 0, 0);\n"
"gridline-color: rgb(255, 0, 0);\n"
"selection-color: rgb(255, 0, 0);"));
        groupBox_8 = new QGroupBox(groupBox_4);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(310, 310, 311, 211));
        groupBox_8->setFont(font1);
        groupBox_8->setTabletTracking(false);
        groupBox_8->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);"));
        label_angle = new QLabel(groupBox_8);
        label_angle->setObjectName(QString::fromUtf8("label_angle"));
        label_angle->setGeometry(QRect(140, 80, 161, 31));
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(true);
        label_angle->setFont(font3);
        label_angle->setMouseTracking(false);
        label_angle->setAcceptDrops(false);
        label_angle->setAutoFillBackground(false);
        label_angle->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 80, 111, 16));
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_id = new QLabel(groupBox_8);
        label_id->setObjectName(QString::fromUtf8("label_id"));
        label_id->setGeometry(QRect(140, 120, 161, 31));
        label_id->setFont(font3);
        label_id->setMouseTracking(false);
        label_id->setAcceptDrops(false);
        label_id->setAutoFillBackground(false);
        label_id->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_iq = new QLabel(groupBox_8);
        label_iq->setObjectName(QString::fromUtf8("label_iq"));
        label_iq->setGeometry(QRect(140, 160, 161, 31));
        label_iq->setFont(font3);
        label_iq->setMouseTracking(false);
        label_iq->setAcceptDrops(false);
        label_iq->setAutoFillBackground(false);
        label_iq->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 130, 111, 21));
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 165, 111, 21));
        label_12->setFont(font1);
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        groupBox_9 = new QGroupBox(groupBox_4);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(310, 70, 311, 231));
        groupBox_9->setFont(font1);
        groupBox_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser_sent = new QTextBrowser(groupBox_9);
        textBrowser_sent->setObjectName(QString::fromUtf8("textBrowser_sent"));
        textBrowser_sent->setGeometry(QRect(10, 20, 291, 131));
        textBrowser_sent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_CAN_Data = new QLineEdit(groupBox_9);
        lineEdit_CAN_Data->setObjectName(QString::fromUtf8("lineEdit_CAN_Data"));
        lineEdit_CAN_Data->setGeometry(QRect(10, 190, 151, 31));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        lineEdit_CAN_Data->setFont(font4);
        lineEdit_CAN_Data->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        pushButton_Send = new QPushButton(groupBox_9);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));
        pushButton_Send->setGeometry(QRect(220, 200, 75, 24));
        lineEdit_CAN_ID = new QLineEdit(groupBox_9);
        lineEdit_CAN_ID->setObjectName(QString::fromUtf8("lineEdit_CAN_ID"));
        lineEdit_CAN_ID->setGeometry(QRect(10, 160, 151, 31));
        lineEdit_CAN_ID->setFont(font4);
        lineEdit_CAN_ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        label_13 = new QLabel(groupBox_9);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(170, 170, 51, 16));
        label_13->setFont(font1);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_14 = new QLabel(groupBox_9);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(170, 200, 51, 16));
        label_14->setFont(font1);
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_clear_sent = new QPushButton(groupBox_9);
        pushButton_clear_sent->setObjectName(QString::fromUtf8("pushButton_clear_sent"));
        pushButton_clear_sent->setGeometry(QRect(220, 170, 75, 24));
        groupBox_10 = new QGroupBox(groupBox_4);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(10, 70, 301, 231));
        groupBox_10->setFont(font1);
        groupBox_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser = new QTextBrowser(groupBox_10);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 20, 281, 131));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_readData = new QPushButton(groupBox_10);
        pushButton_readData->setObjectName(QString::fromUtf8("pushButton_readData"));
        pushButton_readData->setGeometry(QRect(10, 200, 75, 24));
        pushButton_clear = new QPushButton(groupBox_10);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(210, 200, 75, 24));
        dothi_2 = new QTabWidget(tab_3);
        dothi_2->setObjectName(QString::fromUtf8("dothi_2"));
        dothi_2->setGeometry(QRect(630, 0, 641, 541));
        dienap_2 = new QWidget();
        dienap_2->setObjectName(QString::fromUtf8("dienap_2"));
        customPlotWidget1 = new QWidget(dienap_2);
        customPlotWidget1->setObjectName(QString::fromUtf8("customPlotWidget1"));
        customPlotWidget1->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget1->setMouseTracking(false);
        customPlotWidget1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi_2->addTab(dienap_2, QString());
        dongdien_2 = new QWidget();
        dongdien_2->setObjectName(QString::fromUtf8("dongdien_2"));
        customPlotWidget2 = new QCustomPlot(dongdien_2);
        customPlotWidget2->setObjectName(QString::fromUtf8("customPlotWidget2"));
        customPlotWidget2->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget2->setMouseTracking(false);
        customPlotWidget2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi_2->addTab(dongdien_2, QString());
        sosanh_theta_2 = new QWidget();
        sosanh_theta_2->setObjectName(QString::fromUtf8("sosanh_theta_2"));
        customPlotWidget3 = new QWidget(sosanh_theta_2);
        customPlotWidget3->setObjectName(QString::fromUtf8("customPlotWidget3"));
        customPlotWidget3->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget3->setMouseTracking(false);
        customPlotWidget3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi_2->addTab(sosanh_theta_2, QString());
        tabWidget_1->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tableWidget_3 = new QTableWidget(tab_6);
        if (tableWidget_3->columnCount() < 6)
            tableWidget_3->setColumnCount(6);
        QFont font5;
        font5.setFamily(QString::fromUtf8("Times New Roman"));
        font5.setPointSize(10);
        font5.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font5);
        __qtablewidgetitem->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font5);
        __qtablewidgetitem1->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font5);
        __qtablewidgetitem2->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font5);
        __qtablewidgetitem3->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font5);
        __qtablewidgetitem4->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QFont font6;
        font6.setFamily(QString::fromUtf8("Times New Roman"));
        font6.setPointSize(10);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setUnderline(false);
        font6.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font6);
        __qtablewidgetitem5->setBackground(QColor(176, 176, 176));
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(10, 10, 1131, 511));
        tabWidget_1->addTab(tab_6, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1300, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_1->setCurrentIndex(1);
        dothi_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_4->setTitle(QString());
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\304\220I\341\273\200U KHI\341\273\202N ", nullptr));
        pushButton_ANGLE->setText(QCoreApplication::translate("MainWindow", "ANGLE", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "SETPOINT:", nullptr));
        pushButton_SPEED->setText(QCoreApplication::translate("MainWindow", "SPEED", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U TH\341\273\260C T\341\272\276", nullptr));
        label_angle->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "ANGLE:", nullptr));
        label_id->setText(QString());
        label_iq->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "I_d:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "I_q:", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U G\341\273\254I", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "SEND", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "DATA", nullptr));
        pushButton_clear_sent->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U NH\341\272\254N", nullptr));
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
        dothi_2->setTabText(dothi_2->indexOf(dienap_2), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        dothi_2->setTabText(dothi_2->indexOf(dongdien_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        dothi_2->setTabText(dothi_2->indexOf(sosanh_theta_2), QCoreApplication::translate("MainWindow", "Page", nullptr));
        tabWidget_1->setTabText(tabWidget_1->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Index", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Subindex", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        tabWidget_1->setTabText(tabWidget_1->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
