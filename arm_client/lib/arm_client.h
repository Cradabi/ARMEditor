#pragma once


#include <QObject>
#include <QTcpSocket>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>

class arm_client : public QObject {
    Q_OBJECT
public:
    explicit arm_client(QObject *parent = nullptr);
    ~arm_client();

    void connectToServer(const QString &host, quint16 port);

    signals:
        void messageReceived(const QString &message);
    void errorOccurred(const QString &error);
    void connected();
    void disconnected();

    public slots:
        // void sendMessageToServer(const QString &message);

    void sendCommand(const QString &action, const QString &object);
    void sendInitCommand(const QString &id, const QString &driverType);
    void disconnectFromServer();

    private slots:
        void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};
