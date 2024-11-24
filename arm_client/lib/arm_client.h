#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class ClientWorker : public QObject {
Q_OBJECT

public:
    explicit ClientWorker(QObject *parent = nullptr);
    ~ClientWorker();

    QString sendMessage(const QString &message);

    void setupConnection(const QString &host, quint16 port);

    void start();
    void stop();

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);
    void messageReceived(const QString &message);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *socket;
    QThread *workerThread;
    QString host;
    quint16 port;
    QMutex mutex;
    QWaitCondition condition;
    QString lastResponse;
};