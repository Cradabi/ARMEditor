#pragma once

#include "QtSql"

QSqlQuery connection_to_db_with_lib() {
    try {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName)) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open()) {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, cp_name_id, normal_state, failure_state, current_state FROM objects", db);
            db.close();
            return query;
        } else {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, cp_name_id, normal_state, failure_state, current_state FROM objects", db);
            db.close();
            return query;
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_measure() {
    try {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName)) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open()) {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, cp_name_id, current_value, min_value, max_value FROM objects", db);
            db.close();
            return query;
        } else {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, cp_name_id, current_value, min_value, max_value FROM objects", db);
            db.close();
            return query;
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_signal() {
    try {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName)) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open()) {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, cp_name_id FROM objects", db);
            db.close();
            return query;
        } else {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, cp_name_id FROM objects", db);
            db.close();
            return query;
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_control() {
    try {
        // Создание объекта соединения с базой данных
        QString connectionName = "Postgres connection";
        if (!QSqlDatabase::contains(connectionName)) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            db.setHostName("localhost");
            db.setDatabaseName("postgres");
            db.setUserName("postgres");
            db.setPassword("Z123c123x");

            if (!db.open()) {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, cp_name_id, current_value, min_value, max_value FROM objects", db);
            db.close();
            return query;
        } else {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, cp_name_id, current_value, min_value, max_value FROM objects", db);
            db.close();
            return query;
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void update_table_lib(QString str, int int1, int int2, int int3, int int4, int id) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("Z123c123x");

    if (!db.open()) {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2, normal_state = :value3, failure_state = :value4, current_state = :value5 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":value3", int2);
    query.bindValue(":value4", int3);
    query.bindValue(":value5", int4);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_mes(QString str, int int1, double double1, double double2, double double3, int id) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("Z123c123x");

    qDebug() << str << int1 << double1 << double2;

    if (!db.open()) {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2, current_value = :value3, min_value = :value4, max_value = :value5 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":value3", double1);
    query.bindValue(":value4", double2);
    query.bindValue(":value5", double3);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_control(QString str, int int1, int id) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("Z123c123x");

    if (!db.open()) {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_sign(QString str, int int1, int id) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("Z123c123x");

    if (!db.open()) {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}