#include "db_connection.h"

QSqlQuery connection_to_db()
{
    try
    {
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }

            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

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
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }
            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, number  FROM cp_names", db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, number FROM cp_names", db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}

QSqlQuery connection_to_db_with_lib()
{
    try
    {
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }
            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query(
                "SELECT id, name, cp_name_id, normal_state, failure_state, current_state, obj_type_id, obj_name_id FROM objects",
                db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query(
                "SELECT id, name, cp_name_id, normal_state, failure_state, current_state, obj_type_id, obj_name_id FROM objects",
                db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_measure()
{
    try
    {
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }
            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query(
                "SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id, normal_lower_limit, normal_upper_limit, critical_lower_limit, critical_upper_limit FROM objects",
                db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query(
                "SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id, normal_lower_limit, normal_upper_limit, critical_lower_limit, critical_upper_limit FROM objects",
                db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_signal()
{
    try
    {
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }
            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query("SELECT id, name, cp_name_id, obj_type_id, obj_name_id FROM objects", db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query("SELECT id, name, cp_name_id, obj_type_id, obj_name_id FROM objects", db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}


QSqlQuery connection_to_db_with_control()
{
    try
    {
        QStringList info_list = get_info_from_db_config();
        QString dbms_name = info_list[0];
        QString ip = info_list[1];
        QString db_name = info_list[2];
        QString db_user = info_list[3];
        QString db_password = info_list[4];
        int db_port = info_list[5].toInt();
        // Создание объекта соединения с базой данных
        QString connectionName = "db_connection";
        if (!QSqlDatabase::contains(connectionName))
        {
            QSqlDatabase db;
            if (dbms_name == "postgres")
            {
                db = QSqlDatabase::addDatabase("QPSQL", connectionName);
            }
            else
            {
                db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            }
            db.setHostName(ip);
            db.setDatabaseName(db_name);
            db.setUserName(db_user);
            db.setPassword(db_password);
            db.setPort(db_port);

            if (!db.open())
            {
                qWarning() << "Не удалось подключиться к базе данных";
            }
            QSqlQuery query(
                "SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id FROM objects",
                db);
            db.close();
            return query;
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::database(connectionName);
            QSqlQuery query(
                "SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id FROM objects",
                db);
            db.close();
            return query;
        }
    }
    catch (const std::exception& e)
    {
        exit(1);
    }
}

void update_table_lib(QString str, int int1, int int2, int int3, int int4, int id)
{
    QStringList info_list = get_info_from_db_config();
    QString dbms_name = info_list[0];
    QString ip = info_list[1];
    QString db_name = info_list[2];
    QString db_user = info_list[3];
    QString db_password = info_list[4];
    int db_port = info_list[5].toInt();
    QSqlDatabase db;
    if (dbms_name == "postgres")
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName(ip);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);
    db.setPort(db_port);

    if (!db.open())
    {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare(
        "UPDATE objects SET name = :value1, cp_name_id = :value2, normal_state = :value3, failure_state = :value4, current_state = :value5 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":value3", int2);
    query.bindValue(":value4", int3);
    query.bindValue(":value5", int4);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_mes(QString str, int int1, double double1, double double2, double double3, int id)
{
    QStringList info_list = get_info_from_db_config();
    QString dbms_name = info_list[0];
    QString ip = info_list[1];
    QString db_name = info_list[2];
    QString db_user = info_list[3];
    QString db_password = info_list[4];
    int db_port = info_list[5].toInt();
    QSqlDatabase db;
    if (dbms_name == "postgres")
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName(ip);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);
    db.setPort(db_port);

    qDebug() << str << int1 << double1 << double2;

    if (!db.open())
    {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare(
        "UPDATE objects SET name = :value1, cp_name_id = :value2, current_value = :value3, min_value = :value4, max_value = :value5 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":value3", double1);
    query.bindValue(":value4", double2);
    query.bindValue(":value5", double3);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_control(QString str, int int1, int id)
{
    QStringList info_list = get_info_from_db_config();
    QString dbms_name = info_list[0];
    QString ip = info_list[1];
    QString db_name = info_list[2];
    QString db_user = info_list[3];
    QString db_password = info_list[4];
    int db_port = info_list[5].toInt();
    QSqlDatabase db;
    if (dbms_name == "postgres")
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName(ip);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);
    db.setPort(db_port);

    if (!db.open())
    {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}

void update_table_sign(QString str, int int1, int id)
{
    QStringList info_list = get_info_from_db_config();
    QString dbms_name = info_list[0];
    QString ip = info_list[1];
    QString db_name = info_list[2];
    QString db_user = info_list[3];
    QString db_password = info_list[4];
    int db_port = info_list[5].toInt();
    QSqlDatabase db;
    if (dbms_name == "postgres")
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName(ip);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);
    db.setPort(db_port);

    if (!db.open())
    {
        qWarning() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
    query.bindValue(":value1", str);
    query.bindValue(":value2", int1);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Запрос выполнен успешно";
    }

    db.close();
}


QStringList get_info_from_db_config()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString filePath = "";
    int lastSlashIndex = appPath.lastIndexOf("/");
    if (lastSlashIndex != -1)
    {
        // Возвращаем подстроку до последнего слэша
        filePath = appPath.left(lastSlashIndex + 1);
        filePath += "db_lib/db_config.txt";
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open the file.";
        exit(0);
    }

    QTextStream in(&file);
    QString line;
    QStringList values;

    while (!in.atEnd())
    {
        line = in.readLine();
        int colonIndex = line.indexOf(':');
        if (colonIndex != -1)
        {
            QString value = line.mid(colonIndex + 1);
            values.append(value);
        }
    }

    file.close();
    return values;
}
