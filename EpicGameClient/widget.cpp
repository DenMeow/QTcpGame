#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) //конструктор
{
    ui->setupUi(this);
    setWindowTitle("Client [Gartic.io]");
    ui -> nameEdit -> setPlaceholderText("Client#___");
    ui -> inputEdit -> setPlaceholderText("Введите сообщение...");
    ui -> pushButton_Send -> setEnabled(false);

    m_socket = new QTcpSocket();

    connect(m_socket,&QTcpSocket::readyRead,this,&Widget::readData);
    connect(m_socket,&QTcpSocket::disconnected,this,&Widget::socket_disconnect);

    ui -> colorButton ->setStyleSheet("color: " + colorSendMessage.name() + ";");

    connect(thread, SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(thread, SIGNAL(finish()), this, SLOT(checkThreads()));
}

void Widget::keyPressEvent(QKeyEvent *event) //обработка нажатия return на клавиатуре
{
    if ((event -> key() == Qt::Key_Return) and send)
        on_pushButton_Send_clicked();
}


Widget::~Widget() //деструктор
{
    if (isServerConnected){
        // Отобразите прощальное сообщение в чате
        QString welcomeMessage = "Пользователь " + userName + "  ушел :( !";
        DataToSend welcomeData;
        welcomeData.dateTime = QDateTime::currentDateTime();
        welcomeData.message = welcomeMessage;
        welcomeData.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << welcomeData; // Сериализация данных

        m_socket -> write(buffer_array);
        m_socket -> disconnectFromHost();

        m_socket -> deleteLater();
    }
    else {
        m_socket->deleteLater();
    }
    delete ui;
}

void Widget::on_pushButton_Connect_clicked() //кнопка подключения / отключения
{
    QHostAddress IP;
    ushort port;

    if (ui->pushButton_Connect->text() == "Connect")
    {
        if (!IP.setAddress(ui->lineEdit_IP->text())) {
            QMessageBox::warning(this, "Ошибка!", "Вы ввели некорректный IP адрес");
            return;
        }
        port = ui->portServer->value();

        m_socket -> abort();
        m_socket -> connectToHost(IP,port);
        isServerConnected = true;
        if (!m_socket -> waitForConnected(3000) /*or !isServerConnected*/)
        {
            QMessageBox::information(this,"Ошибка","Сервер не слушает");
            isServerConnected = false;
            return;
        }

        ui -> textBrowser -> clear();
        ui -> textBrowser_2 -> clear();

        //считываем имя или даем случайное
        if(!ui -> nameEdit -> text().isEmpty())
            userName = ui -> nameEdit -> text();
        else
            userName = "Client #"+ QString::number(rand()%1002+1);

        // Отобразите приветственное сообщение в чате
        QString welcomeMessage = "Пользователь " + userName + "  подключился к серверу!";
        DataToSend welcomeData;
        welcomeData.dateTime = QDateTime::currentDateTime();
        welcomeData.message = welcomeMessage;
        welcomeData.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << welcomeData; // Сериализация данных

        m_socket -> write(buffer_array);

        ui -> groupBox -> setEnabled(false);
        if (ui -> inputEdit -> text().length() > 0) {
            ui -> pushButton_Send -> setEnabled(true);
        }

        ui -> pushButton_Connect -> setText("Disconnect");
    }
    else
    {
        // Отобразите прощальное сообщение в чате
        QString welcomeMessage = "Пользователь " + userName + "  ушел :( !";
        DataToSend welcomeData;
        welcomeData.dateTime = QDateTime::currentDateTime();
        welcomeData.message = welcomeMessage;
        welcomeData.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << welcomeData; // Сериализация данных

        m_socket -> write(buffer_array);
        m_socket -> disconnectFromHost();

        ui -> textBrowser -> append("Вы отключились от чата!");

        ui -> pushButton_Connect -> setText("Connect");
        ui -> pushButton_Send -> setEnabled(false);
        ui -> groupBox -> setEnabled(true);

        thread -> is_exit = true;
        thread -> wait(500);
    }
}

void Widget::on_pushButton_Send_clicked()  //отправление сообщения
{
    QString input = ui-> inputEdit -> text().toHtmlEscaped();
    qDebug() << question;
    if (!input.contains(question, Qt::CaseInsensitive)) {
        QString text = userName + ": " + input;

        // Отправляем обычное сообщение
        DataToSend m_data;
        m_data.color = colorSendMessage.name();
        m_data.message = text;
        m_data.dateTime = QDateTime::currentDateTime();
        m_data.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << m_data; // Сериализация данных

        m_socket -> write(buffer_array);
        m_socket -> flush();

        QString messageText = text; // Текст сообщения
        QColor messageColor = colorSendMessage; // Цвет сообщения
        QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                       .arg(messageColor.name())
                                       .arg(m_data.dateTime.toString("hh:mm:ss"))
                                       .arg(messageText);

        ui -> textBrowser -> append(formattedMessage);
    } else {
        QString text = userName + ": УГАДАЛ!";

        // Отправляем обычное сообщение
        DataToSend m_data;
        m_data.color = Qt::green;
        m_data.message = text;
        m_data.dateTime = QDateTime::currentDateTime();
        m_data.name = userName;

        QByteArray buffer_array;
        QDataStream dataStream(&buffer_array, QIODevice::WriteOnly);
        dataStream << m_data; // Сериализация данных

        m_socket -> write(buffer_array);
        m_socket -> flush();

        QString messageText = text; // Текст сообщения
        QColor messageColor = Qt::green; // Цвет сообщения
        QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                       .arg(messageColor.name())
                                       .arg(m_data.dateTime.toString("hh:mm:ss"))
                                       .arg(messageText);

        ui -> textBrowser -> append(formattedMessage);

        //вывод звука о том, что отгадал
        QSoundEffect *victorySound = new QSoundEffect(this);
        victorySound->setSource(QUrl("qrc:/ok.wav"));
        victorySound->setVolume(0.5);
        victorySound->play();
    }

    ui -> inputEdit -> clear();
}


void Widget::readData() //чтение данных
{
    m_socket = (QTcpSocket*)sender();
    QDataStream in(m_socket);

    DataToSend recieveData;

    if(in.status() == QDataStream::Ok)
    {
        in.startTransaction();
        in >> recieveData;
        if(!in.commitTransaction()) {
            //qDebug() << "сообщение не дошло";
            //return;
        }

        QString messageText = recieveData.message;
        QColor messageColor = recieveData.color;
        if (messageText == "Раунд начался") {
            question = recieveData.answer;
            thread -> count = 500;
            thread -> start();

            QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                           .arg(messageColor.name())
                                           .arg(recieveData.dateTime.toString("hh:mm:ss"))
                                           .arg(messageText);

            ui -> textBrowser -> append(formattedMessage);
        }
        else if (!recieveData.image.isNull()) {        //сервер дорисовал и прислал фотку
            ui -> textBrowser_2 -> clear();
            QImage image = recieveData.image;
            // Преобразование изображения в байтовый массив
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PNG");  // Сохранение изображения в формате PNG
            buffer.close();

            // Преобразование байтового массива в base64 строку
            QString base64Image = QString::fromLatin1(byteArray.toBase64().data());

            // Формируем HTML-тег для вставки изображения
            QString newText = "<div style='text-align:center;'><img src='data:image/png;base64," + base64Image + "' width='391' height='431' /></div>";

            ui -> textBrowser_2 -> append(newText);
        }
        else {
            QString formattedMessage = QString("<span style='color:%1;'>[%2] %3</span>")
                                           .arg(messageColor.name())
                                           .arg(recieveData.dateTime.toString("hh:mm:ss"))
                                           .arg(messageText);

            ui -> textBrowser -> append(formattedMessage);
        }
    }
}

void Widget::socket_disconnect() //отключение сервера
{
    isServerConnected = false;

    ui -> pushButton_Send -> setEnabled(false);
    ui -> pushButton_Connect -> setText("Connect");
    ui -> groupBox -> setEnabled(true);
    ui -> textBrowser_2 -> clear();
    thread -> is_exit = true;
    thread -> wait(500);
}


void Widget::on_colorButton_clicked() //кнопка выбора цвета
{
    colorSendMessage = QColorDialog::getColor(QColor(Qt::white),this,"Выберите цвет сообщений");
    ui -> colorButton ->setStyleSheet("color: " + colorSendMessage.name() + ";");
}

void Widget::on_inputEdit_textChanged(const QString &arg1) //изменение в строке ввода сообщений
{
    if (arg1.trimmed().isEmpty() or ui->pushButton_Connect->text() == "Connect") {
        ui -> pushButton_Send -> setEnabled(false);
        send = false;
    }
    else {
        ui -> pushButton_Send -> setEnabled(true);
        send = true;
    }
}




