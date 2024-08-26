// Include necessary headers
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringList>
#include <QDebug>

// Database Interface
class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = default;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool exec(const QString& query) = 0;
    virtual QString lastError() = 0;
    virtual void prepare(const QString& query) = 0;
    virtual void bindValue(const QString& placeholder, const QVariant& value) = 0;
};

// Real Database Implementation
class RealDatabase : public DatabaseInterface {
public:
    RealDatabase(const QString& dbType, const QString& connectionName)
            : db(QSqlDatabase::addDatabase(dbType, connectionName)) {}

    bool open() override {
        return db.open();
    }

    void close() override {
        db.close();
    }

    bool exec(const QString& query) override {
        QSqlQuery q(db);
        return q.exec(query);
    }

    QString lastError() override {
        return db.lastError().text();
    }

    void prepare(const QString& query) override {
        q.prepare(query);
    }

    void bindValue(const QString& placeholder, const QVariant& value) override {
        q.bindValue(placeholder, value);
    }

private:
    QSqlDatabase db;
    QSqlQuery q;
};

// Mock Database Class
class MockDatabase : public DatabaseInterface {
public:
    MOCK_METHOD0(open, bool());
    MOCK_METHOD0(close, void());
    MOCK_METHOD1(exec, bool(const QString&));
    MOCK_METHOD0(lastError, QString());
    MOCK_METHOD1(prepare, void(const QString&));
    MOCK_METHOD2(bindValue, void(const QString&, const QVariant&));
};

// Function to Retrieve DB Config
QStringList get_info_from_db_config() {
    return {"mysql", "localhost", "arm", "newuser", "password", "3306"};
}

// Refactored Database Connection Functions
void connection_to_db(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, current_state, current_value FROM objects")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void connection_to_cp_db(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, number FROM cp_names")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void connection_to_db_with_lib(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, cp_name_id, normal_state, failure_state, current_state, obj_type_id, obj_name_id FROM objects")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void connection_to_db_with_measure(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id, normal_lower_limit, normal_upper_limit, critical_lower_limit, critical_upper_limit FROM objects")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void connection_to_db_with_signal(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, cp_name_id, obj_type_id, obj_name_id FROM objects")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void connection_to_db_with_control(DatabaseInterface* dbInterface) {
    try {
        if (dbInterface->open()) {
            if (!dbInterface->exec("SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id FROM objects")) {
                qWarning() << "Query execution failed: " << dbInterface->lastError();
            }
            dbInterface->close();
        } else {
            qWarning() << "Не удалось подключиться к базе данных";
        }
    } catch (const std::exception& e) {
        exit(1);
    }
}

void update_table_lib(DatabaseInterface* dbInterface, QString str, int int1, int int2, int int3, int int4, int id) {
    if (dbInterface->open()) {
        dbInterface->prepare("UPDATE objects SET name = :value1, cp_name_id = :value2, normal_state = :value3, failure_state = :value4, current_state = :value5 WHERE id = :id");
        dbInterface->bindValue(":value1", str);
        dbInterface->bindValue(":value2", int1);
        dbInterface->bindValue(":value3", int2);
        dbInterface->bindValue(":value4", int3);
        dbInterface->bindValue(":value5", int4);
        dbInterface->bindValue(":id", id);

        if (!dbInterface->exec("")) {
            qWarning() << "Ошибка выполнения запроса: " << dbInterface->lastError();
        } else {
            qDebug() << "Запрос выполнен успешно";
        }
        dbInterface->close();
    } else {
        qWarning() << "Не удалось подключиться к базе данных";
    }
}

void update_table_mes(DatabaseInterface* dbInterface, QString str, int int1, double double1, double double2, double double3, int id) {
    if (dbInterface->open()) {
        dbInterface->prepare("UPDATE objects SET name = :value1, cp_name_id = :value2, current_value = :value3, min_value = :value4, max_value = :value5 WHERE id = :id");
        dbInterface->bindValue(":value1", str);
        dbInterface->bindValue(":value2", int1);
        dbInterface->bindValue(":value3", double1);
        dbInterface->bindValue(":value4", double2);
        dbInterface->bindValue(":value5", double3);
        dbInterface->bindValue(":id", id);

        if (!dbInterface->exec("")) {
            qWarning() << "Ошибка выполнения запроса: " << dbInterface->lastError();
        } else {
            qDebug() << "Запрос выполнен успешно";
        }
        dbInterface->close();
    } else {
        qWarning() << "Не удалось подключиться к базе данных";
    }
}

void update_table_control(DatabaseInterface* dbInterface, QString str, int int1, int id) {
    if (dbInterface->open()) {
        dbInterface->prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
        dbInterface->bindValue(":value1", str);
        dbInterface->bindValue(":value2", int1);
        dbInterface->bindValue(":id", id);

        if (!dbInterface->exec("")) {
            qWarning() << "Ошибка выполнения запроса: " << dbInterface->lastError();
        } else {
            qDebug() << "Запрос выполнен успешно";
        }
        dbInterface->close();
    } else {
        qWarning() << "Не удалось подключиться к базе данных";
    }
}

void update_table_sign(DatabaseInterface* dbInterface, QString str, int int1, int id) {
    if (dbInterface->open()) {
        dbInterface->prepare("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id");
        dbInterface->bindValue(":value1", str);
        dbInterface->bindValue(":value2", int1);
        dbInterface->bindValue(":id", id);

        if (!dbInterface->exec("")) {
            qWarning() << "Ошибка выполнения запроса: " << dbInterface->lastError();
        } else {
            qDebug() << "Запрос выполнен успешно";
        }
        dbInterface->close();
    } else {
        qWarning() << "Не удалось подключиться к базе данных";
    }
}

// Unit Tests
TEST(GetInfoFromDbConfigTest, ReturnsCorrectValues) {
    QStringList expected = {"mysql", "localhost", "arm", "newuser", "password", "3306"};
    QStringList result = get_info_from_db_config();
    EXPECT_EQ(expected, result);
}

TEST(ConnectionToDbTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, current_state, current_value FROM objects")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_db(&mockDb);
}

TEST(ConnectionToDbTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_db(&mockDb);
}

TEST(ConnectionToCpDbTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, number FROM cp_names")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_cp_db(&mockDb);
}

TEST(ConnectionToCpDbTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_cp_db(&mockDb);
}

TEST(ConnectionToDbWithLibTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, cp_name_id, normal_state, failure_state, current_state, obj_type_id, obj_name_id FROM objects")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_db_with_lib(&mockDb);
}

TEST(ConnectionToDbWithLibTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_db_with_lib(&mockDb);
}

TEST(ConnectionToDbWithMeasureTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id, normal_lower_limit, normal_upper_limit, critical_lower_limit, critical_upper_limit FROM objects")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_db_with_measure(&mockDb);
}

TEST(ConnectionToDbWithMeasureTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_db_with_measure(&mockDb);
}

TEST(ConnectionToDbWithSignalTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, cp_name_id, obj_type_id, obj_name_id FROM objects")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_db_with_signal(&mockDb);
}

TEST(ConnectionToDbWithSignalTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_db_with_signal(&mockDb);
}

TEST(ConnectionToDbWithControlTest, ExecutesQuerySuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, exec(QString::fromStdString("SELECT id, name, cp_name_id, current_value, min_value, max_value, obj_type_id, obj_name_id FROM objects")))
            .WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    connection_to_db_with_control(&mockDb);
}

TEST(ConnectionToDbWithControlTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    connection_to_db_with_control(&mockDb);
}

TEST(UpdateTableLibTest, ExecutesUpdateSuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, prepare(QString::fromStdString("UPDATE objects SET name = :value1, cp_name_id = :value2, normal_state = :value3, failure_state = :value4, current_state = :value5 WHERE id = :id")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value1"), QVariant("TestName")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value2"), QVariant(1)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value3"), QVariant(2)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value4"), QVariant(3)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value5"), QVariant(4)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":id"), QVariant(123)));
    EXPECT_CALL(mockDb, exec(QString::fromStdString(""))).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    update_table_lib(&mockDb, "TestName", 1, 2, 3, 4, 123);
}

TEST(UpdateTableLibTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    update_table_lib(&mockDb, "TestName", 1, 2, 3, 4, 123);
}

TEST(UpdateTableMesTest, ExecutesUpdateSuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, prepare(QString::fromStdString("UPDATE objects SET name = :value1, cp_name_id = :value2, current_value = :value3, min_value = :value4, max_value = :value5 WHERE id = :id")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value1"), QVariant("TestName")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value2"), QVariant(1)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value3"), QVariant(5.0)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value4"), QVariant(6.0)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value5"), QVariant(7.0)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":id"), QVariant(123)));
    EXPECT_CALL(mockDb, exec(QString::fromStdString(""))).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    update_table_mes(&mockDb, "TestName", 1, 5.0, 6.0, 7.0, 123);
}

TEST(UpdateTableMesTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    update_table_mes(&mockDb, "TestName", 1, 5.0, 6.0, 7.0, 123);
}

TEST(UpdateTableControlTest, ExecutesUpdateSuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, prepare(QString::fromStdString("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value1"), QVariant("ControlName")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value2"), QVariant(10)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":id"), QVariant(456)));
    EXPECT_CALL(mockDb, exec(QString::fromStdString(""))).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    update_table_control(&mockDb, "ControlName", 10, 456);
}

TEST(UpdateTableControlTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    update_table_control(&mockDb, "ControlName", 10, 456);
}

TEST(UpdateTableSignTest, ExecutesUpdateSuccessfully) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, prepare(QString::fromStdString("UPDATE objects SET name = :value1, cp_name_id = :value2 WHERE id = :id")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value1"), QVariant("SignName")));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":value2"), QVariant(20)));
    EXPECT_CALL(mockDb, bindValue(QString::fromStdString(":id"), QVariant(789)));
    EXPECT_CALL(mockDb, exec(QString::fromStdString(""))).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockDb, close()).Times(1);

    update_table_sign(&mockDb, "SignName", 20, 789);
}

TEST(UpdateTableSignTest, FailsToOpenDatabase) {
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, open()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockDb, close()).Times(0);

    update_table_sign(&mockDb, "SignName", 20, 789);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
