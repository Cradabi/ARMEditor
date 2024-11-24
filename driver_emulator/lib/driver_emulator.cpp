#include "driver_emulator.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

DriverEmulator::DriverEmulator(QObject *parent)
    : QObject(parent), server(new QTcpServer(this)) {}

DriverEmulator::~DriverEmulator() {
    if (server->isListening()) {
        server->close();
    }
    qDeleteAll(clients.keys());
}

bool DriverEmulator::startServer(quint16 port) {
    if (!server->listen(QHostAddress::Any, port)) {
        qCritical() << "Не удалось запустить сервер: " << server->errorString();
        return false;
    }

    connect(server, &QTcpServer::newConnection, this, &DriverEmulator::onNewConnection);
    qDebug() << "Сервер запущен на порту" << port;
    return true;
}

void DriverEmulator::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    if (!clientSocket) {
        return;
    }

    qDebug() << "Новый клиент подключен:" << clientSocket->peerAddress().toString();

    // Подключаем сигналы для обработки клиента
    connect(clientSocket, &QTcpSocket::disconnected, this, &DriverEmulator::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &DriverEmulator::onReadyRead);

    // Инициализируем клиента по умолчанию
    clients[clientSocket] = ClientInfo();
}

void DriverEmulator::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) {
        return;
    }

    qDebug() << "Клиент отключен:" << clientSocket->peerAddress().toString();
    clients.remove(clientSocket);
    clientSocket->deleteLater();
}

void DriverEmulator::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) {
        return;
    }

    while (clientSocket->canReadLine()) {
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        qDebug() << "Получено сообщение от клиента:" << message;

        // Обработка команды
        handleCommand(clientSocket, message);
    }
}

void DriverEmulator::handleCommand(QTcpSocket *client, const QString &command) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(command.toUtf8());
    if (!jsonDoc.isObject()) {
        qWarning() << "Неверный формат команды:" << command;
        client->write("ERROR: Invalid command format\n");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("init")) {
        // Инициализация клиента
        QString id = jsonObj["id"].toString();
        QString driverType = jsonObj["driver"].toString();
        clients[client] = {id, driverType};

        qDebug() << "Клиент инициализирован: ID =" << id << ", Driver =" << driverType;
        client->write("OK: Initialized\n");
    } else if (jsonObj.contains("command")) {
        // Обработка команды управления
        QString action = jsonObj["command"].toString();
        QString object = jsonObj["object"].toString();

        // Эмуляция выполнения команды
        QString response = QString("OK: Object %1 %2").arg(object, action);
        qDebug() << "Команда выполнена:" << response;

        client->write(response.toUtf8() + "\n");
    } else {
        qWarning() << "Неизвестная команда:" << command;
        client->write("ERROR: Unknown command\n");
    }
}