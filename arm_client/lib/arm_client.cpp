#include "arm_client.h"
#include <QDebug>

ClientWorker::ClientWorker(QObject *parent)
        : QObject(parent), socket(nullptr), workerThread(new QThread(this)), port(0) {
    moveToThread(workerThread);

    connect(workerThread, &QThread::started, this, [this]() {
        socket = new QTcpSocket();

        connect(socket, &QTcpSocket::connected, this, &ClientWorker::onConnected);
        connect(socket, &QTcpSocket::disconnected, this, &ClientWorker::onDisconnected);
        connect(socket, &QTcpSocket::readyRead, this, &ClientWorker::onReadyRead);

        socket->connectToHost(host, port);
    });

    connect(workerThread, &QThread::finished, this, [this]() {
        if (socket) {
            socket->disconnectFromHost();
            socket->deleteLater();
            socket = nullptr;
        }
    });
}

ClientWorker::~ClientWorker() {
    stop();
}

void ClientWorker::setupConnection(const QString &host, quint16 port) {
    this->host = host;
    this->port = port;
}

void ClientWorker::start() {
    if (!workerThread->isRunning()) {
        workerThread->start();
    }
}

void ClientWorker::stop() {
    if (workerThread->isRunning()) {
        workerThread->quit();
        workerThread->wait();
    }
}

void ClientWorker::onConnected() {
    qDebug() << "Клиент подключен к серверу";
    emit connected();
}

void ClientWorker::onDisconnected() {
    qDebug() << "Клиент отключен от сервера";
    emit disconnected();
}

void ClientWorker::onReadyRead() {
    while (socket->canReadLine()) {
        QString response = QString::fromUtf8(socket->readLine()).trimmed();
        qDebug() << "Ответ от сервера:" << response;

        mutex.lock();
        lastResponse = response;
        condition.wakeAll();
        mutex.unlock();

        emit messageReceived(response);
    }
}

QString ClientWorker::sendMessage(const QString &message) {
    QMutexLocker locker(&mutex);
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8() + "\n");
        socket->flush();

        // Ожидание ответа
        if (!condition.wait(&mutex, 5000)) {
            return "ERROR: Timeout waiting for response";
        }

        return lastResponse;
    }

    return "ERROR: Not connected to server";
}