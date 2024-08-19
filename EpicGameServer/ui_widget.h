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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QListWidget *banList;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QLineEdit *inputEdit;
    QPushButton *pushButton_Listen;
    QGroupBox *groupBox;
    QLabel *label_port_1;
    QSpinBox *portServer;
    QPushButton *colorButton;
    QLabel *label_name;
    QLineEdit *nameEdit;
    QLabel *label_IP_1;
    QLineEdit *lineEdit_IP;
    QListWidget *listClients;
    QPushButton *pushButton_Send;
    QLabel *label;
    QGraphicsView *graphicsView;
    QLabel *label_3;
    QLabel *label_4;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QLabel *label_word;
    QPushButton *pushButton_pen;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(746, 709);
        banList = new QListWidget(Widget);
        banList->setObjectName("banList");
        banList->setGeometry(QRect(610, 500, 111, 141));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(610, 210, 111, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setEnabled(true);
        textBrowser->setGeometry(QRect(20, 210, 181, 431));
        textBrowser->setFrameShape(QFrame::NoFrame);
        inputEdit = new QLineEdit(Widget);
        inputEdit->setObjectName("inputEdit");
        inputEdit->setGeometry(QRect(20, 660, 151, 41));
        QFont font1;
        font1.setPointSize(17);
        inputEdit->setFont(font1);
        inputEdit->setMaxLength(100000);
        pushButton_Listen = new QPushButton(Widget);
        pushButton_Listen->setObjectName("pushButton_Listen");
        pushButton_Listen->setGeometry(QRect(150, 130, 481, 41));
        pushButton_Listen->setFont(font1);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(150, 10, 481, 121));
        label_port_1 = new QLabel(groupBox);
        label_port_1->setObjectName("label_port_1");
        label_port_1->setGeometry(QRect(260, 70, 61, 31));
        QFont font2;
        font2.setPointSize(19);
        label_port_1->setFont(font2);
        portServer = new QSpinBox(groupBox);
        portServer->setObjectName("portServer");
        portServer->setGeometry(QRect(320, 70, 81, 31));
        portServer->setFont(font1);
        portServer->setMaximum(60000);
        portServer->setValue(40000);
        colorButton = new QPushButton(groupBox);
        colorButton->setObjectName("colorButton");
        colorButton->setGeometry(QRect(260, 20, 141, 41));
        colorButton->setFont(font1);
        label_name = new QLabel(groupBox);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(10, 30, 41, 21));
        label_name->setFont(font1);
        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(53, 25, 151, 31));
        nameEdit->setFont(font1);
        nameEdit->setMaxLength(20);
        label_IP_1 = new QLabel(groupBox);
        label_IP_1->setObjectName("label_IP_1");
        label_IP_1->setGeometry(QRect(10, 70, 31, 31));
        label_IP_1->setFont(font1);
        lineEdit_IP = new QLineEdit(groupBox);
        lineEdit_IP->setObjectName("lineEdit_IP");
        lineEdit_IP->setGeometry(QRect(54, 70, 151, 31));
        lineEdit_IP->setFont(font1);
        lineEdit_IP->setFrame(false);
        lineEdit_IP->setAlignment(Qt::AlignCenter);
        listClients = new QListWidget(Widget);
        listClients->setObjectName("listClients");
        listClients->setGeometry(QRect(610, 230, 111, 251));
        pushButton_Send = new QPushButton(Widget);
        pushButton_Send->setObjectName("pushButton_Send");
        pushButton_Send->setGeometry(QRect(170, 660, 61, 41));
        pushButton_Send->setFont(font1);
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(610, 480, 111, 21));
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(210, 210, 391, 431));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 180, 111, 31));
        QFont font3;
        font3.setPointSize(16);
        label_3->setFont(font3);
        label_4 = new QLabel(Widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(280, 180, 91, 31));
        QFont font4;
        font4.setPointSize(18);
        font4.setBold(true);
        label_4->setFont(font4);
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(210, 640, 391, 23));
        progressBar->setMaximum(500);
        progressBar->setValue(0);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(260, 660, 311, 41));
        label_word = new QLabel(Widget);
        label_word->setObjectName("label_word");
        label_word->setGeometry(QRect(370, 180, 151, 31));
        label_word->setFont(font4);
        pushButton_pen = new QPushButton(Widget);
        pushButton_pen->setObjectName("pushButton_pen");
        pushButton_pen->setGeometry(QRect(210, 210, 51, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\320\233\320\270\321\201\321\202 \320\272\320\273\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        pushButton_Listen->setText(QCoreApplication::translate("Widget", "Connect", nullptr));
        groupBox->setTitle(QString());
        label_port_1->setText(QCoreApplication::translate("Widget", "\320\237\320\276\321\200\321\202:", nullptr));
        colorButton->setText(QCoreApplication::translate("Widget", "\320\233\320\270\321\207\320\275\321\213\320\271 \321\206\320\262\320\265\321\202", nullptr));
        label_name->setText(QCoreApplication::translate("Widget", "\320\230\320\274\321\217", nullptr));
        label_IP_1->setText(QCoreApplication::translate("Widget", "IP", nullptr));
        lineEdit_IP->setText(QCoreApplication::translate("Widget", "127.0.0.1", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("Widget", "\342\236\244", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\320\221\320\260\320\275 \320\273\320\270\321\201\321\202", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\320\236\320\275\320\273\320\260\320\271\320\275-\321\207\320\260\321\202:", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\320\235\320\260\321\200\320\270\321\201\321\203\320\271:", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\263\321\200\321\203", nullptr));
        label_word->setText(QString());
        pushButton_pen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
