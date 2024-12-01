#include "arm_client.h"
#include <QDebug>

arm_client::arm_client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::readyRead, this, &arm_client::onReadyRead);
    //connect(socket, &QTcpSocket::errorOccurred, this, &arm_client::onErrorOccurred);
    connect(socket, &QTcpSocket::connected, this, &arm_client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &arm_client::disconnected);

    qDebug() << "arm_client created";
}

arm_client::~arm_client() {
    if (socket->isOpen()) {
        qDebug() << "Disconnecting and closing socket in destructor";
        socket->disconnectFromHost();
        socket->close();
    }
    delete socket;

    qDebug() << "arm_client destroyed";
}

void arm_client::connectToServer(const QString &host, quint16 port) {
    qDebug() << "Trying to connect to server at" << host << "on port" << port;
    if (socket->isOpen()) {
        qDebug() << "Socket already open, disconnecting from current host";
        socket->disconnectFromHost();
    }
    socket->connectToHost(host, port);

    sendInitCommand(0, "A.M.T.");
}

// void arm_client::sendMessageToServer(const QString &message) {
//     if (socket->isOpen()) {
//         qDebug() << "Sending message to server:" << message;
//         socket->write(message.toUtf8());
//         socket->flush();
//     } else {
//         qDebug() << "Error: Socket is not connected, cannot send message";
//         emit errorOccurred("Socket is not connected.");
//     }
// }

void arm_client::sendInitCommand(const QString &id, const QString &driverType) {
    // Формируем JSON-команду
    QJsonObject jsonObj;
    jsonObj["init"] = true;
    jsonObj["id"] = id;
    jsonObj["driver"] = driverType;

    QJsonDocument jsonDoc(jsonObj);
    QString message = jsonDoc.toJson(QJsonDocument::Compact);

    // Отправляем команду
    socket->write(message.toUtf8() + "\n"); // Добавляем \n для разделения сообщений
    socket->flush();
    qDebug() << "Отправлена команда инициализации:" << message;
}

void arm_client::sendCommand(const QString &action, const QString &object) {
    // Формируем JSON-команду
    QJsonObject jsonObj;
    jsonObj["command"] = action;
    jsonObj["object"] = object;

    QJsonDocument jsonDoc(jsonObj);
    QString message = jsonDoc.toJson(QJsonDocument::Compact);

    // Отправляем команду
    socket->write(message.toUtf8() + "\n"); // Добавляем \n для разделения сообщений
    socket->flush();
    qDebug() << "Отправлена команда управления:" << message;
}


void arm_client::disconnectFromServer() {
    if (socket->isOpen()) {
        qDebug() << "Disconnecting from server";
        socket->disconnectFromHost();
    } else {
        qDebug() << "Socket is already closed, no need to disconnect";
    }
}

void arm_client::onReadyRead() {
    qDebug() << "Data available to read from server";
    while (socket->canReadLine()) {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        qDebug() << "Received message from server:" << line;
        emit messageReceived(line);
    }
}

void arm_client::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    qDebug() << "Socket error occurred:" << socket->errorString();
    emit errorOccurred(socket->errorString());
}