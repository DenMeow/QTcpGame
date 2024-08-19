/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_Connect;
    QGroupBox *groupBox;
    QLabel *label_IP_1;
    QLineEdit *lineEdit_IP;
    QPushButton *colorButton;
    QLineEdit *nameEdit;
    QSpinBox *portServer;
    QLabel *label_name;
    QLabel *label_port_1;
    QTextBrowser *textBrowser;
    QLineEdit *inputEdit;
    QPushButton *pushButton_Send;
    QLabel *label_3;
    QLabel *label_4;
    QTextBrowser *textBrowser_2;
    QProgressBar *progressBar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(598, 707);
        pushButton_Connect = new QPushButton(Widget);
        pushButton_Connect->setObjectName("pushButton_Connect");
        pushButton_Connect->setGeometry(QRect(60, 130, 471, 41));
        QFont font;
        font.setPointSize(17);
        pushButton_Connect->setFont(font);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 10, 471, 121));
        label_IP_1 = new QLabel(groupBox);
        label_IP_1->setObjectName("label_IP_1");
        label_IP_1->setGeometry(QRect(20, 70, 31, 31));
        label_IP_1->setFont(font);
        lineEdit_IP = new QLineEdit(groupBox);
        lineEdit_IP->setObjectName("lineEdit_IP");
        lineEdit_IP->setGeometry(QRect(50, 70, 125, 31));
        lineEdit_IP->setFont(font);
        lineEdit_IP->setFrame(false);
        lineEdit_IP->setAlignment(Qt::AlignCenter);
        colorButton = new QPushButton(groupBox);
        colorButton->setObjectName("colorButton");
        colorButton->setGeometry(QRect(220, 10, 131, 41));
        colorButton->setFont(font);
        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(53, 15, 151, 31));
        nameEdit->setFont(font);
        nameEdit->setMaxLength(20);
        portServer = new QSpinBox(groupBox);
        portServer->setObjectName("portServer");
        portServer->setGeometry(QRect(300, 70, 81, 31));
        portServer->setFont(font);
        portServer->setMaximum(60000);
        portServer->setValue(40000);
        label_name = new QLabel(groupBox);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(10, 20, 41, 21));
        label_name->setFont(font);
        label_port_1 = new QLabel(groupBox);
        label_port_1->setObjectName("label_port_1");
        label_port_1->setGeometry(QRect(240, 70, 61, 31));
        QFont font1;
        font1.setPointSize(19);
        label_port_1->setFont(font1);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setEnabled(true);
        textBrowser->setGeometry(QRect(10, 200, 181, 431));
        textBrowser->setFrameShape(QFrame::NoFrame);
        inputEdit = new QLineEdit(Widget);
        inputEdit->setObjectName("inputEdit");
        inputEdit->setGeometry(QRect(10, 660, 521, 41));
        inputEdit->setFont(font);
        inputEdit->setMaxLength(100000);
        pushButton_Send = new QPushButton(Widget);
        pushButton_Send->setObjectName("pushButton_Send");
        pushButton_Send->setGeometry(QRect(530, 660, 61, 41));
        pushButton_Send->setFont(font);
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 170, 171, 31));
        QFont font2;
        font2.setPointSize(16);
        label_3->setFont(font2);
        label_4 = new QLabel(Widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(340, 170, 181, 31));
        QFont font3;
        font3.setPointSize(18);
        font3.setBold(true);
        label_4->setFont(font3);
        textBrowser_2 = new QTextBrowser(Widget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setEnabled(true);
        textBrowser_2->setGeometry(QRect(200, 200, 391, 431));
        textBrowser_2->setFrameShape(QFrame::NoFrame);
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(200, 632, 391, 31));
        progressBar->setMaximum(500);
        progressBar->setValue(0);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("Widget", "Connect", nullptr));
        groupBox->setTitle(QString());
        label_IP_1->setText(QCoreApplication::translate("Widget", "IP", nullptr));
        lineEdit_IP->setText(QCoreApplication::translate("Widget", "127.0.0.1", nullptr));
        colorButton->setText(QCoreApplication::translate("Widget", "\320\233\320\270\321\207\320\275\321\213\320\271 \321\206\320\262\320\265\321\202", nullptr));
        label_name->setText(QCoreApplication::translate("Widget", "\320\230\320\274\321\217", nullptr));
        label_port_1->setText(QCoreApplication::translate("Widget", "\320\237\320\276\321\200\321\202:", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("Widget", "\342\236\244", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\320\236\320\275\320\273\320\260\320\271\320\275-\321\207\320\260\321\202:", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\320\243\320\263\320\260\320\264\320\260\320\271 \321\207\321\202\320\276 \321\215\321\202\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
