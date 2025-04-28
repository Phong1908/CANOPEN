/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
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
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_ANGLE;
    QLineEdit *lineEdit_value;
    QLabel *label_3;
    QPushButton *pushButton_SPEED;
    QGroupBox *groupBox_3;
    QLabel *label_angle;
    QLabel *label_5;
    QLabel *label_id;
    QLabel *label_iq;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_6;
    QTextBrowser *textBrowser_sent;
    QPushButton *pushButton_clear_sent;
    QGroupBox *groupBox_5;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_readData;
    QPushButton *pushButton_clear;
    QTabWidget *dothi;
    QWidget *dienap;
    QWidget *customPlotWidget1;
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
        MainWindow->resize(1302, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 0, 1291, 561));
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName("groupBox");
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
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 310, 301, 211));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        pushButton_ANGLE = new QPushButton(groupBox_2);
        pushButton_ANGLE->setObjectName("pushButton_ANGLE");
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
        lineEdit_value = new QLineEdit(groupBox_2);
        lineEdit_value->setObjectName("lineEdit_value");
        lineEdit_value->setGeometry(QRect(120, 50, 113, 31));
        lineEdit_value->setFont(font2);
        lineEdit_value->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 60, 91, 16));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_SPEED = new QPushButton(groupBox_2);
        pushButton_SPEED->setObjectName("pushButton_SPEED");
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
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(310, 310, 311, 211));
        groupBox_3->setFont(font1);
        groupBox_3->setTabletTracking(false);
        groupBox_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(170, 255, 255);"));
        label_angle = new QLabel(groupBox_3);
        label_angle->setObjectName("label_angle");
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
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 80, 111, 16));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_id = new QLabel(groupBox_3);
        label_id->setObjectName("label_id");
        label_id->setGeometry(QRect(140, 120, 161, 31));
        label_id->setFont(font3);
        label_id->setMouseTracking(false);
        label_id->setAcceptDrops(false);
        label_id->setAutoFillBackground(false);
        label_id->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_iq = new QLabel(groupBox_3);
        label_iq->setObjectName("label_iq");
        label_iq->setGeometry(QRect(140, 160, 161, 31));
        label_iq->setFont(font3);
        label_iq->setMouseTracking(false);
        label_iq->setAcceptDrops(false);
        label_iq->setAutoFillBackground(false);
        label_iq->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 127);"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 130, 111, 21));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 165, 111, 21));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(310, 70, 311, 231));
        groupBox_6->setFont(font1);
        groupBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser_sent = new QTextBrowser(groupBox_6);
        textBrowser_sent->setObjectName("textBrowser_sent");
        textBrowser_sent->setGeometry(QRect(10, 20, 291, 171));
        textBrowser_sent->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_clear_sent = new QPushButton(groupBox_6);
        pushButton_clear_sent->setObjectName("pushButton_clear_sent");
        pushButton_clear_sent->setGeometry(QRect(220, 200, 75, 24));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 70, 301, 231));
        groupBox_5->setFont(font1);
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 255, 255);"));
        textBrowser = new QTextBrowser(groupBox_5);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 20, 281, 171));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_readData = new QPushButton(groupBox_5);
        pushButton_readData->setObjectName("pushButton_readData");
        pushButton_readData->setGeometry(QRect(10, 200, 75, 24));
        pushButton_clear = new QPushButton(groupBox_5);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(210, 200, 75, 24));
        dothi = new QTabWidget(tab_3);
        dothi->setObjectName("dothi");
        dothi->setGeometry(QRect(630, 0, 641, 541));
        dienap = new QWidget();
        dienap->setObjectName("dienap");
        customPlotWidget1 = new QWidget(dienap);
        customPlotWidget1->setObjectName("customPlotWidget1");
        customPlotWidget1->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget1->setMouseTracking(false);
        customPlotWidget1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi->addTab(dienap, QString());
        dongdien = new QWidget();
        dongdien->setObjectName("dongdien");
        customPlotWidget2 = new QCustomPlot(dongdien);
        customPlotWidget2->setObjectName("customPlotWidget2");
        customPlotWidget2->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget2->setMouseTracking(false);
        customPlotWidget2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi->addTab(dongdien, QString());
        sosanh_theta = new QWidget();
        sosanh_theta->setObjectName("sosanh_theta");
        customPlotWidget3 = new QWidget(sosanh_theta);
        customPlotWidget3->setObjectName("customPlotWidget3");
        customPlotWidget3->setGeometry(QRect(10, 10, 621, 501));
        customPlotWidget3->setMouseTracking(false);
        customPlotWidget3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dothi->addTab(sosanh_theta, QString());
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tableWidget_2 = new QTableWidget(tab_4);
        if (tableWidget_2->columnCount() < 6)
            tableWidget_2->setColumnCount(6);
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Times New Roman")});
        font4.setPointSize(13);
        font4.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font4);
        __qtablewidgetitem->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font4);
        __qtablewidgetitem1->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font4);
        __qtablewidgetitem2->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font4);
        __qtablewidgetitem3->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font4);
        __qtablewidgetitem4->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Times New Roman")});
        font5.setPointSize(13);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setUnderline(false);
        font5.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font5);
        __qtablewidgetitem5->setBackground(QColor(176, 176, 176));
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(0, 0, 781, 511));
        tabWidget_2->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font4);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font4);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font4);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font4);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font4);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 801, 511));
        tabWidget_2->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1302, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(2);
        dothi->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\304\220I\341\273\200U KHI\341\273\202N ", nullptr));
        pushButton_ANGLE->setText(QCoreApplication::translate("MainWindow", "ANGLE", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SETPOINT:", nullptr));
        pushButton_SPEED->setText(QCoreApplication::translate("MainWindow", "SPEED", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U TH\341\273\260C T\341\272\276", nullptr));
        label_angle->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "ANGLE:", nullptr));
        label_id->setText(QString());
        label_iq->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "I_d:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "I_q:", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "D\341\273\256 LI\341\273\206U G\341\273\254I", nullptr));
        pushButton_clear_sent->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
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
        dothi->setTabText(dothi->indexOf(dienap), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        dothi->setTabText(dothi->indexOf(dongdien), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        dothi->setTabText(dothi->indexOf(sosanh_theta), QCoreApplication::translate("MainWindow", "Page", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
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
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
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
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
