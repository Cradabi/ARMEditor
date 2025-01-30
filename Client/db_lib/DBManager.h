#pragma once

#include <QtSql>
#include <QThread>
#include <QTimer>
#include <QDebug>

class DBManager {
public:
    static DBManager& getInstance();

    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

    // Методы получения данных
    QSqlQuery getObjects();
    QSqlQuery getCPObjects();
    QSqlQuery getLibraryObjects();
    QSqlQuery getLibraryObjectsShort();
    QSqlQuery getMeasurementObjects();
    QSqlQuery getSignalObjects();
    QSqlQuery getControlObjects();
    QSqlQuery getObjectsByCPId(int cpId);
    QStringList getPersonnelFIO();

    // Методы обновления
    bool updateLibraryObject(const QString& name, int cpNameId, int normalState,
                           int failureState, int currentState, int id);
    bool updateLibraryState(int currentState, int id);
    bool updateMeasurement(const QString& name, int cpNameId, double currentValue,
                          double minValue, double maxValue, int id);
    bool updateControl(const QString& name, int cpNameId, int id);
    bool updateSignal(const QString& name, int cpNameId, int id);

private:
    DBManager();
    ~DBManager() = default;

    bool initConnection();
    void closeConnection();
    QStringList loadConfig();

    QSqlDatabase db;
    QString connectionName;
    struct DBConfig {
        QString dbmsName;
        QString ip;
        QString dbName;
        QString user;
        QString password;
        int port;
    } config;
};