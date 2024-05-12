#pragma once

#include "QtSql"

QSqlQuery connection_to_db()
{
    try
    {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, current_state, current_value FROM objects", db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, current_state, current_value FROM objects", db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}

QSqlQuery connection_to_cp_db()
{
    try
    {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name FROM cp_groups", db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name FROM cp_groups", db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}
