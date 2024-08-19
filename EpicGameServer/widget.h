#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include <QMessageBox>
#include <QTimer>
#include <QTextBrowser>
#include <QPixmap>
#include <QSoundEffect>

#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <DataToSend.h>
#include <paintscene.h>
#include <mythread.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void keyPressEvent(QKeyEvent * event);

    void server_New_Connect();
    void readData();
    void socket_Disconnect();

    void on_colorButton_clicked();

    void on_inputEdit_textChanged(const QString &arg1);

    void on_listClients_itemDoubleClicked(QListWidgetItem *item);

    void on_banList_itemDoubleClicked(QListWidgetItem *item);

    void slotTimer();

    void on_pushButton_clicked();

    void handleSceneChanged();

    void checkThreads();

    void on_pushButton_pen_clicked();

    void resizeEvent(QResizeEvent *event);

private:
    Ui::Widget *ui;

    QTcpServer *server;
    QList<QTcpSocket *> sockets; //лист с подключенными клиентами

    QString userName = "Server"; //дефолтное имя сервера
    QColor colorSendMessage = Qt::blue, colorpen = Qt::black; //дефолтный цвет сообщений сервера

    bool send = false;

    QVector <QString> banClients; //лист наказанных
    QVector <QString> connectedUsers; //лист клиентов
    QVector <QString> userAnswer = {"","","","","",""};

    QTimer *timer;
    QTimer *send_image;
    paintScene *scene;

    MyThread *thread = new MyThread();
    QStringList words = {
        "подпись", "вырез", "гранит", "кровать", "блузка", "фараон", "клапан", "ежик", "вымя", "турист",
        "колготки", "Карпов", "питание","свёрток", "дочерь", "шампунь", "броня", "заяй", "гимназист", "стрела",
        "подделка", "карта", "затычка", "решение", "алкоголь", "шуруп", "воровка", "колодец", "кабан", "кольцо",
        "полиция", "ловушка", "буква", "опера", "сектор", "математика", "пароварка", "невезение", "глубина", "штука",
        "справочник", "вождь", "хобот", "ширинка", "усталость", "служитель", "больница", "спальная", "видео", "рот",
        "просьба", "фишка", "рукопись", "ракетчик", "каблук", "шрифт", "палец", "нога", "халва", "черника",
        "незнайка", "компания", "работница", "мышь", "исследование", "кружка", "мороженое", "сиденье", "пулемёт", "печь",
        "солист", "свёкла", "волк", "зелье", "дума", "посылка", "коготь", "семафор", "робот", "различие",
        "плоскостопие", "двигатель", "сфера", "тюльпан", "автомат", "внедорожник", "самурай", "куб", "алгоритм", "ручка",
        "глаз", "медаль", "пульт", "поводок", "подлежащее", "ор", "бунт", "удочка", "лес", "диспетчер"
    };
    QString question;
    int countTrue = 0;
    bool stop = false;
    // QSqlDatabase dbTop;
    // QSqlQuery *query;
    // QSqlTableModel *model;
};

#endif // WIDGET_H
