#include <gtest/gtest.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDebug>


// Заглушка для get_info_from_db_config
QStringList get_info_from_db_config()
{
    return {"mysql", "localhost", "arm", "newuser", "password", "3306"};
}

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



class DatabaseTest : public ::testing::Test {

};


TEST_F(DatabaseTest, ConnectionToDb_DataGrip) {
    QSqlQuery query = connection_to_db();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString current_state = query.value(2).toString();
        QString current_value = query.value(3).toString();

        qDebug() << id << name << current_state << current_value;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, ConnectionToCpDb_DataGrip) {
    QSqlQuery query = connection_to_cp_db();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString number = query.value(2).toString();

        qDebug() << id << name << number;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, ConnectionToDbWithLib_DataGrip) {
    QSqlQuery query = connection_to_db_with_lib();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString cp_name_id = query.value(2).toString();
        QString normal_state = query.value(3).toString();
        QString failure_state = query.value(4).toString();
        QString current_state = query.value(5).toString();
        QString obj_type_id = query.value(6).toString();
        QString obj_name_id = query.value(7).toString();

        qDebug() << id << name << cp_name_id << normal_state << failure_state << current_state << obj_type_id << obj_name_id;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, ConnectionToDbWithMeasure_DataGrip) {
    QSqlQuery query = connection_to_db_with_measure();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString cp_name_id = query.value(2).toString();
        QString current_value = query.value(3).toString();
        QString min_value = query.value(4).toString();
        QString max_value = query.value(5).toString();
        QString obj_type_id = query.value(6).toString();
        QString obj_name_id = query.value(7).toString();
        QString normal_lower_limit = query.value(8).toString();
        QString normal_upper_limit = query.value(9).toString();
        QString critical_lower_limit = query.value(10).toString();
        QString critical_upper_limit = query.value(11).toString();

        qDebug() << id << name << cp_name_id << current_value << min_value << max_value << obj_type_id << obj_name_id << normal_lower_limit << normal_upper_limit << critical_lower_limit << critical_upper_limit;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, ConnectionToDbWithSignal_DataGrip) {
    QSqlQuery query = connection_to_db_with_signal();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString cp_name_id = query.value(2).toString();
        QString obj_type_id = query.value(3).toString();
        QString obj_name_id = query.value(4).toString();

        qDebug() << id << name << cp_name_id << obj_type_id << obj_name_id;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, ConnectionToDbWithControl_DataGrip) {
    QSqlQuery query = connection_to_db_with_control();

    int count = 0;
    while (query.next()) {
        count++;
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString cp_name_id = query.value(2).toString();
        QString current_value = query.value(3).toString();
        QString min_value = query.value(4).toString();
        QString max_value = query.value(5).toString();
        QString obj_type_id = query.value(6).toString();
        QString obj_name_id = query.value(7).toString();


        qDebug() << id << name << cp_name_id << current_value << min_value << max_value << obj_type_id << obj_name_id;
    }
    EXPECT_FALSE(count == 0);
}

TEST_F(DatabaseTest, UpdateTableLib_DataUpdate) {
    QSqlQuery query = connection_to_db_with_lib();

    query.next();
    
    update_table_lib("test", 1, 1, 1, 1, query.value(0).toInt());
    
    QSqlQuery query1 = connection_to_db_with_lib();

    query1.next();

    EXPECT_FALSE(query.value(1).toString() == query1.value(1).toString());
}

TEST_F(DatabaseTest, UpdateTableMes_DataUpdate) {
    QSqlQuery query = connection_to_db_with_measure();

    query.next();

    update_table_mes("test", 1, 1, 1, 1, query.value(0).toInt());

    QSqlQuery query1 = connection_to_db_with_measure();

    query1.next();

    EXPECT_FALSE(query.value(1).toString() == query1.value(1).toString());
}

TEST_F(DatabaseTest, UpdateTableCon_DataUpdate) {
    QSqlQuery query = connection_to_db_with_control();

    query.next();

    update_table_control("test", 1, query.value(0).toInt());

    QSqlQuery query1 = connection_to_db_with_control();

    query1.next();

    EXPECT_FALSE(query.value(1).toString() == query1.value(1).toString());
}

TEST_F(DatabaseTest, UpdateTableSign_DataUpdate) {
    QSqlQuery query = connection_to_db_with_signal();

    query.next();

    update_table_sign("test", 1, query.value(0).toInt());

    QSqlQuery query1 = connection_to_db_with_signal();

    query1.next();

    EXPECT_FALSE(query.value(1).toString() == query1.value(1).toString());
}