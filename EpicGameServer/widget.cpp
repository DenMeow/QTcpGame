/// Структура передачи данных
/// Передача данных через QDataStream
/// Рисование в реальном времени
/// Использование потоков
/// Отдельный класс для обработки рисования
/// Выбор цвета рисования
/// Звук (правильный ответ, результаты)

#include "widget.h"
#include "ui_widget.h"
#include <QSqlError>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) //конструктор
{
    ui->setupUi(this);
    setWindowTitle("Server [Gartic.io]");
    // будущий sql
    // dbTop = QSqlDatabase::addDatabase("QSQLITE");
    // dbTop.setDatabaseName("./dataBaseTop.db");
    // if(dbTop.open()) {
    //     qDebug() << "good";
    // }
    // query = new QSqlQuery(dbTop);
    // query -> exec("CREATE TABLE TopResult(Name TEXT, Result INT);");

    // model = new QSqlTableModel(this, dbTop);
    // model -> setTable("TopResult");
    // model -> select();

    ui -> inputEdit -> setPlaceholderText("Введите сообщение...");
    ui -> nameEdit -> setPlaceholderText("Server");
    ui -> colorButton ->setStyleSheet("color: " + colorSendMessage.name() + ";");
    ui -> pushButton_Send -> setEnabled(false);
    ui -> graphicsView -> setEnabled(false);
    ui -> pushButton_pen -> setEnabled(false);

    server = new QTcpServer();
    server -> setMaxPendingConnections(1);
    connect(server, &QTcpServer::newConnection, this, &Widget::server_New_Connect);

    scene = new paintScene();
    ui -> graphicsView -> setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Widget::slotTimer);
    timer -> start(100);

    send_image = new QTimer();
    connect(send_image, &QTimer::timeout, this, &Widget::handleSceneChanged);
    send_image -> start(100);

    connect(thread, SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(thread, SIGNAL(finish()), this, SLOT(checkThreads()));

    QPixmap pixmap("qrc:/image/pen2.png");  // Загрузка картинки
    pixmap = pixmap.scaled(ui -> pushButton_pen -> size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // Масштабирование картинки под размер кнопки
    ui -> pushButton_pen -> setStyleSheet("QPushButton { border-image: url(:/image/pen2.png); }");
}

void Widget::checkThreads() //если время закончилось...
{
    QString htmlText = "<p> Правильный ответ: " +question + "</p><ul>";
    for (int i = 0; i < userAnswer.size(); ++i) {
        htmlText += "<li>" + QString::number(i + 1) + " - " + userAnswer[i] + "</li>";
    }
    htmlText += "</ul>";
    if (countTrue == 0)
        htmlText += "Никто не угадал😢";

    QSoundEffect *victorySound = new QSoundEffect(this);
    victorySound->setSource(QUrl("qrc:/victory.wav"));
    victorySound->setVolume(0.5);
    victorySound->play();

    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(htmlText);
    msgBox.exec();

    ui -> pushButton -> setText("Начать игру");
    if (!stop)
        on_pushButton_clicked();
}

//запрет выходить за границу graphicView
void Widget::slotTimer()
{
    timer -> stop();
    scene -> setSceneRect(0,0,ui -> graphicsView -> width() - 20,ui -> graphicsView -> height() - 20);
}
void Widget::resizeEvent(QResizeEvent *event)
{
    timer -> start(100);
    QWidget::resizeEvent(event);
}


void Widget::keyPressEvent(QKeyEvent *event) //обработка нажатия return
{
    if ((event -> key() == Qt::Key_Return) and ui -> inputEdit -> text().length() > 0 and !sockets.isEmpty() and !ui -> inputEdit -> text().trimmed().isEmpty())
        on_pushButton_Send_clicked();
}

void Widget::on_colorButton_clicked() //выбор цвета
{
    colorSendMessage = QColorDialog::getColor(QColor(Qt::white),this,"Выберите цвет сообщений");
    ui -> colorButton ->setStyleSheet("color: " + colorSendMessage.name() + ";");
}


Widget::~Widget() //деструктор
{
    if(!sockets.isEmpty()) {
        QString text = userName + " отключился";

        // Отправляем обычное сообщение
        DataToSend m_data;
        m_data.color = Qt::black;
        m_data.message = text;
        m_data.dateTime = QDateTime::currentDateTime();
        m_data.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << m_data; // Сериализация данных

        for (QTcpSocket *client : sockets) {
            client -> write(buffer_array);
            client -> flush();
            client -> disconnectFromHost();
        }

        server -> close();
        server -> deleteLater();
    } else {
        server -> close();
        server -> deleteLater();
    }
    delete ui;
}

void Widget::on_pushButton_Listen_clicked() //кнопка подключения / отключения сервера
{
    if (ui->pushButton_Listen->text() == "Connect")
    {
        QHostAddress ip;
        if(!ip.setAddress(ui -> lineEdit_IP -> text())) {
            QMessageBox::warning(this, "Ошибка!", "Вы ввели некорректный IP адрес");
            return;
        }
        ushort port = ui->portServer->value();

        if(!server -> listen(QHostAddress::Any, port))
        {
            QMessageBox::critical(this,"Ошибка",server->errorString());
            return;
        }

        ui->pushButton_Listen->setText("Disconnect");
        ui -> textBrowser -> clear();
        ui -> textBrowser -> append("Вы включили сервер, теперь к вам может подключиться клиент!");

        ui -> groupBox -> setEnabled(false);
        if (ui -> inputEdit -> text().length() > 0 and !sockets.isEmpty()) {
            ui -> pushButton_Send -> setEnabled(true);
        }
        if (!ui -> nameEdit -> text().isEmpty())
            userName = ui -> nameEdit -> text();


    }
    else
    {
        if(!sockets.isEmpty()) {
            QString text = userName + " закрылся";

            // Отправляем обычное сообщение
            DataToSend m_data;
            m_data.color = Qt::black;
            m_data.message = text;
            m_data.dateTime = QDateTime::currentDateTime();
            m_data.name = userName;

            QByteArray buffer_array;
            QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
            dataStream << m_data; // Сериализация данных

            for (QTcpSocket *client : sockets) {
                client -> write(buffer_array);
                client -> flush();
                client -> disconnectFromHost();
            }

            server -> close();
        } else {
            server -> close();
        }

        ui -> textBrowser -> append("Вы отключили сервер!");
        thread -> is_exit = true;
        thread -> wait(500);

        ui -> pushButton_Listen -> setText("Connect");

        ui -> pushButton_Send -> setEnabled(false);
        ui -> groupBox -> setEnabled(true);

        scene -> clear();
    }
}

void Widget::on_pushButton_Send_clicked() //отправка сообщения
{
    QString text = userName + ": " + ui-> inputEdit -> text().toHtmlEscaped();

    // Отправляем обычное сообщение
    DataToSend m_data;
    m_data.color = colorSendMessage.name();
    m_data.message = text;
    m_data.dateTime = QDateTime::currentDateTime();
    m_data.name = userName;

    QByteArray buffer_array;
    QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
    dataStream << m_data; // Сериализация данных

    for (QTcpSocket *client : sockets) {
        client -> write(buffer_array);
        client -> flush();
    }

    QString messageText = text; // Текст сообщения
    QColor messageColor = colorSendMessage; // Цвет сообщения
    QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                   .arg(messageColor.name())
                                   .arg(m_data.dateTime.toString("hh:mm:ss"))
                                   .arg(messageText);

    ui -> textBrowser -> append(formattedMessage);

    ui->inputEdit->clear();
}


void Widget::server_New_Connect() //подключение клиента к серверу
{
    QTcpSocket *new_socket;
    new_socket = server -> nextPendingConnection();

    //проверка находится ли новый сокет в бане или уже игра началась
    if (banClients.indexOf(new_socket -> peerAddress().toString()) != -1 or ui -> pushButton -> text() == "Стоп Игра") {
        new_socket -> disconnectFromHost();
        new_socket -> close();
        return;
    }

    sockets.append(new_socket);

    //добавили нового пользователя в list и вектор подключенных пользователей
    ui->listClients -> addItem(new_socket -> peerAddress().toString());
    connectedUsers.push_back(new_socket -> peerAddress().toString());

    QString text = "Вы подключились к серверу: " + userName;

    // Отправляем обычное сообщение
    DataToSend m_data;
    m_data.color = Qt::black;
    m_data.message = text;
    m_data.dateTime = QDateTime::currentDateTime();
    m_data.name = userName;

    QByteArray buffer_array;
    QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
    dataStream << m_data; // Сериализация данных

    new_socket -> write(buffer_array);

    connect(new_socket, &QTcpSocket::readyRead, this, &Widget::readData);
    connect(new_socket, &QTcpSocket::disconnected, this, &Widget::socket_Disconnect);

    if (ui -> inputEdit -> text().length() > 0)
        ui -> pushButton_Send -> setEnabled(true);
}

void Widget::socket_Disconnect() //сигнал отключения
{
    QTcpSocket * close_c = static_cast<QTcpSocket*>(QObject::sender()); // так можно найти виновника отключения
    sockets.removeOne(close_c);

    ui -> listClients -> takeItem(connectedUsers.indexOf(close_c -> peerAddress().toString()));
    connectedUsers.remove(connectedUsers.indexOf(close_c -> peerAddress().toString()));

    // Отправляем обычное сообщение
    DataToSend m_data;
    m_data.color = Qt::black;
    m_data.message = "";
    m_data.dateTime = QDateTime::currentDateTime();
    m_data.name = userName;

    QByteArray buffer_array;
    QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
    dataStream << m_data; // Сериализация данных

    for (QTcpSocket *client : sockets) {
        client -> write(buffer_array);
        client -> flush();
    }

    ui -> pushButton_Send -> setEnabled(false);
}

void Widget::readData() //чтение данных
{
    QTcpSocket *new_socket;
    new_socket = (QTcpSocket*)sender(); //отслеживание того, что подал сигнал
    QDataStream in(new_socket);

    DataToSend recieveData;

    if(in.status() == QDataStream::Ok)
    {
        in.startTransaction();
        in >> recieveData;
        if(!in.commitTransaction()) {
            //return;
        }

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << recieveData;

        for (QTcpSocket *client : sockets) {
            if (client == new_socket) {
                continue;
            }
            client -> write(buffer_array);
            client -> flush();
        }

        QString messageText = recieveData.message;
        QColor messageColor = recieveData.color;
        QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                       .arg(messageColor.name())
                                       .arg(recieveData.dateTime.toString("hh:mm:ss"))
                                       .arg(messageText);

        ui -> textBrowser -> append(formattedMessage);

        //изменить на добавление в БД
        if (messageText.contains("УГАДАЛ!", Qt::CaseInsensitive) and userAnswer.indexOf(recieveData.name) == -1) {
            userAnswer.push_back(recieveData.name);
            ++countTrue;
        }
    }
}


void Widget::on_inputEdit_textChanged(const QString &arg1) //изменение отправляемого сообщения
{
    if (arg1.trimmed().isEmpty() or ui -> pushButton_Listen -> text() == "Connect" or sockets.isEmpty()) {
        ui -> pushButton_Send -> setEnabled(false);
        send = false;
    }
    else {
        ui -> pushButton_Send -> setEnabled(true);
        send = true;
    }
}

void Widget::on_listClients_itemDoubleClicked(QListWidgetItem *item) //бан выбранного пользователя
{
    ui -> banList -> addItem(item -> text());
    banClients.push_back((item -> text()));

    for (QTcpSocket *client : sockets) {
        if (client -> peerAddress().toString() == item -> text()) {
            QString text = "Вас забанил админ";

            // Отправляем обычное сообщение
            DataToSend m_data;
            m_data.color = Qt::black;
            m_data.message = text;
            m_data.dateTime = QDateTime::currentDateTime();
            m_data.name = userName;

            QByteArray buffer_array;
            QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
            dataStream << m_data; // Сериализация данных

            client -> write(buffer_array);

            client -> disconnectFromHost();
            client -> close();
            sockets.removeOne(client);
            break;
        }
    }
}

void Widget::on_banList_itemDoubleClicked(QListWidgetItem *item) //разбан выбранного пользователя
{
    ui -> banList -> takeItem(banClients.indexOf(item -> text()));
    banClients.remove(banClients.indexOf(item -> text()));
}


void Widget::on_pushButton_clicked() //начало игры
{
    if (!sockets.isEmpty()) {
        if (ui -> pushButton -> text() == "Начать игру") {
            userAnswer.clear();
            countTrue = 0;
            scene -> clear();

            int index = QRandomGenerator::global() -> bounded(0, words.size());
            ui -> label_word -> setText(words.at(index));
            question = words.at(index);

            thread -> count = 500;
            thread -> start();

            QSoundEffect *victorySound = new QSoundEffect(this);
            victorySound->setSource(QUrl("qrc:/start.wav"));
            victorySound->setVolume(0.5);
            victorySound->play();

            ui -> graphicsView -> setEnabled(true);
            ui -> pushButton_pen -> setEnabled(true);
            ui -> pushButton -> setText("Стоп Игра");

            DataToSend m_data;
            m_data.color = colorSendMessage;
            m_data.message = "Раунд начался";
            m_data.dateTime = QDateTime::currentDateTime();
            m_data.name = userName;
            m_data.answer = question;

            QByteArray buffer_array;
            QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
            dataStream << m_data; // Сериализация данных

            for (QTcpSocket *client : sockets) {
                client -> write(buffer_array);
            }
            stop = false;
        } else {
            thread -> is_exit = true;
            thread -> wait(500);
            stop = true;
            ui -> graphicsView -> setEnabled(false);
            ui -> pushButton_pen -> setEnabled(false);
        }
    } else {
        QMessageBox::information(this, "Ждите..","Подождите участников");
        ui -> pushButton_pen -> setEnabled(false);
    }
}

void Widget::handleSceneChanged() //отправка рисуночков
{
    if(ui -> pushButton -> text() == "Стоп Игра") {
        QPixmap pixmap = ui -> graphicsView -> grab();  // Получение QPixmap из QGraphicsView

        QImage image = pixmap.toImage();  // Преобразование QPixmap в QImage

        DataToSend m_data;
        m_data.message = "фотка";
        m_data.dateTime = QDateTime::currentDateTime();
        m_data.name = userName;
        m_data.image = image;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << m_data; // Сериализация данных

        for (QTcpSocket *client : sockets) {
            client -> write(buffer_array);
        }

        if(countTrue == sockets.size()) {
            thread -> is_exit = true;
            thread -> wait(500);
        }
    }
}

void Widget::on_pushButton_pen_clicked() //выбор ручки
{
    colorpen = QColorDialog::getColor(Qt::white, this, "Выберите цвет");
    if (colorpen.isValid()) {
        scene -> setPenColor(colorpen);
    }
}

