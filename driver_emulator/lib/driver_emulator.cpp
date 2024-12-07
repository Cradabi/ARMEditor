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
        QString errorMsg = "Не удалось запустить сервер: " + server->errorString();
        emit logMessage(errorMsg);
        return false;
    }

    connect(server, &QTcpServer::newConnection, this, &DriverEmulator::onNewConnection);
    QString successMsg = "Сервер запущен на порту " + QString::number(port);
    emit logMessage(successMsg);
    return true;
}

void DriverEmulator::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    if (!clientSocket) {
        emit logMessage("Ошибка: Не удалось получить подключение клиента.");
        return;
    }

    QString clientAddress = clientSocket->peerAddress().toString();
    emit logMessage("Новый клиент подключен: " + clientAddress);

    connect(clientSocket, &QTcpSocket::disconnected, this, &DriverEmulator::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &DriverEmulator::onReadyRead);

    clients[clientSocket] = ClientInfo(); // Инициализируем клиента
}

void DriverEmulator::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) {
        emit logMessage("Ошибка: Не удалось обработать отключение клиента.");
        return;
    }

    QString clientAddress = clientSocket->peerAddress().toString();
    emit logMessage("Клиент отключен: " + clientAddress);

    clients.remove(clientSocket);
    clientSocket->deleteLater();
}

void DriverEmulator::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) {
        emit logMessage("Ошибка: Не удалось прочитать данные от клиента.");
        return;
    }

    while (clientSocket->canReadLine()) {
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        emit logMessage("Получено сообщение от клиента: " + message);

        // Обработка команды
        handleCommand(clientSocket, message);
    }
}

void DriverEmulator::handleCommand(QTcpSocket *client, const QString &command) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(command.toUtf8());
    if (!jsonDoc.isObject()) {
        QString errorMsg = "Неверный формат команды: " + command;
        emit logMessage(errorMsg);
        sendToClient(client, "ERROR: Invalid command format");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("init")) {
        // Инициализация клиента
        QString id = jsonObj["id"].toString();
        QString driverType = jsonObj["driver"].toString();
        clients[client] = {id, driverType};

        QString initMsg = QString("Клиент инициализирован: ID = %1, Driver = %2").arg(id, driverType);
        emit logMessage(initMsg);
        sendToClient(client, "OK: Initialized");
    } else if (jsonObj.contains("command")) {
        // Обработка команды управления
        QString action = jsonObj["command"].toString();
        QString object = jsonObj["object"].toString();

        // Эмуляция выполнения команды
        QString response = QString("OK: Object %1 %2").arg(object, action);
        emit logMessage("Команда выполнена: " + response);

        sendToClient(client, response);
    } else {
        QString unknownMsg = "Неизвестная команда: " + command;
        emit logMessage(unknownMsg);
        sendToClient(client, "ERROR: Unknown command");
    }
}

void DriverEmulator::sendToClient(QTcpSocket *client, const QString &message) {
    client->write(message.toUtf8() + "\n");
}