#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>

// Структура для хранения информации о подключенном клиенте
struct ClientInfo {
    QString id;
    QString driverType;
};

// Класс эмулятора драйвера
class DriverEmulator : public QObject {
    Q_OBJECT

public:
    explicit DriverEmulator(QObject *parent = nullptr);
    ~DriverEmulator();

    // Запускает сервер на указанном порту
    bool startServer(quint16 port);

    private slots:
        // Слоты для обработки событий
        void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer *server;                          // Сервер
    QHash<QTcpSocket *, ClientInfo> clients;     // Хранение информации о клиентах

    // Обработка команд от клиента
    void handleCommand(QTcpSocket *client, const QString &command);
};