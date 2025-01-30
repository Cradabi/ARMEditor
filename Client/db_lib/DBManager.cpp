#include "DBManager.h"

DBManager& DBManager::getInstance() {
    static DBManager instance;
    return instance;
}

DBManager::DBManager() : connectionName("MainConnection") {
    try {
        auto configData = loadConfig();
        config = {
            configData[0], configData[1], configData[2],
            configData[3], configData[4], configData[5].toInt()
        };
    }
    catch (const std::exception& e) {
        qDebug() << "Failed to initialize DB manager:" << e.what();
        throw;
    }
}

bool DBManager::initConnection() {
    try {
        if (QSqlDatabase::contains(connectionName)) {
            db = QSqlDatabase::database(connectionName);
            return true;
        }

        db = QSqlDatabase::addDatabase(
            config.dbmsName == "postgres" ? "QPSQL" : "QMYSQL",
            connectionName
        );

        db.setHostName(config.ip);
        db.setDatabaseName(config.dbName);
        db.setUserName(config.user);
        db.setPassword(config.password);
        db.setPort(config.port);

        if (!db.open()) {
            qDebug() << "Failed to open database connection:" << db.lastError().text();
            return false;
        }
        return true;
    }
    catch (const std::exception& e) {
        qDebug() << "Connection error:" << e.what();
        return false;
    }
}

void DBManager::closeConnection() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlQuery DBManager::getObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, current_state, current_value FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getCPObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, number FROM cp_names");

    if (!query.exec()) {
        qDebug() << "Failed to execute CP objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getLibraryObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, cp_name_id, normal_state, failure_state, "
                 "current_state, obj_type_id, obj_name_id, control_type FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute library objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getLibraryObjectsShort() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT name, cp_name_id, normal_state, failure_state, current_state, control_type FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute short library objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getMeasurementObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, cp_name_id, current_value, min_value, max_value, "
                 "obj_type_id, obj_name_id, normal_lower_limit, normal_upper_limit, "
                 "critical_lower_limit, critical_upper_limit FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute measurement objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getSignalObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, cp_name_id, obj_type_id, obj_name_id FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute signal objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QSqlQuery DBManager::getControlObjects() {
    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name, cp_name_id, current_value, min_value, max_value, "
                 "obj_type_id, obj_name_id FROM objects");

    if (!query.exec()) {
        qDebug() << "Failed to execute control objects query:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

bool DBManager::updateLibraryObject(const QString& name, int cpNameId,
                                  int normalState, int failureState,
                                  int currentState, int id) {
    if (name.isEmpty() || id <= 0) {
        qDebug() << "Invalid parameters for library object update";
        return false;
    }

    if (!initConnection()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare(
        "UPDATE objects SET name = :name, cp_name_id = :cpId, "
        "normal_state = :normal, failure_state = :failure, "
        "current_state = :current WHERE id = :id"
    );

    query.bindValue(":name", name);
    query.bindValue(":cpId", cpNameId);
    query.bindValue(":normal", normalState);
    query.bindValue(":failure", failureState);
    query.bindValue(":current", currentState);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update library object:" << query.lastError().text();
        closeConnection();
        return false;
    }

    qDebug() << "Successfully updated library object with id:" << id;
    closeConnection();
    return true;
}

bool DBManager::updateLibraryState(int currentState, int id) {
    if (id <= 0) {
        qDebug() << "Invalid id for library state update";
        return false;
    }

    if (!initConnection()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE objects SET current_state = :current WHERE id = :id");

    query.bindValue(":current", currentState);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update library state:" << query.lastError().text();
        closeConnection();
        return false;
    }

    qDebug() << "Successfully updated library state for id:" << id;
    closeConnection();
    return true;
}

bool DBManager::updateMeasurement(const QString& name, int cpNameId,
                                double currentValue, double minValue,
                                double maxValue, int id) {
    if (name.isEmpty() || id <= 0) {
        qDebug() << "Invalid parameters for measurement update";
        return false;
    }

    if (!initConnection()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare(
        "UPDATE objects SET name = :name, cp_name_id = :cpId, "
        "current_value = :current, min_value = :min, "
        "max_value = :max WHERE id = :id"
    );

    query.bindValue(":name", name);
    query.bindValue(":cpId", cpNameId);
    query.bindValue(":current", currentValue);
    query.bindValue(":min", minValue);
    query.bindValue(":max", maxValue);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update measurement:" << query.lastError().text();
        closeConnection();
        return false;
    }

    qDebug() << "Successfully updated measurement with id:" << id;
    closeConnection();
    return true;
}

bool DBManager::updateControl(const QString& name, int cpNameId, int id) {
    if (name.isEmpty() || id <= 0) {
        qDebug() << "Invalid parameters for control update";
        return false;
    }

    if (!initConnection()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE objects SET name = :name, cp_name_id = :cpId WHERE id = :id");

    query.bindValue(":name", name);
    query.bindValue(":cpId", cpNameId);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update control:" << query.lastError().text();
        closeConnection();
        return false;
    }

    qDebug() << "Successfully updated control with id:" << id;
    closeConnection();
    return true;
}

bool DBManager::updateSignal(const QString& name, int cpNameId, int id) {
    if (name.isEmpty() || id <= 0) {
        qDebug() << "Invalid parameters for signal update";
        return false;
    }

    if (!initConnection()) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE objects SET name = :name, cp_name_id = :cpId WHERE id = :id");

    query.bindValue(":name", name);
    query.bindValue(":cpId", cpNameId);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update signal:" << query.lastError().text();
        closeConnection();
        return false;
    }

    qDebug() << "Successfully updated signal with id:" << id;
    closeConnection();
    return true;
}

QSqlQuery DBManager::getObjectsByCPId(int cpId) {
    if (cpId <= 0) {
        qDebug() << "Invalid CP ID";
        return QSqlQuery();
    }

    if (!initConnection()) {
        return QSqlQuery();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, name FROM objects WHERE cp_name_id = :cpId");
    query.bindValue(":cpId", cpId);

    if (!query.exec()) {
        qDebug() << "Failed to get objects by CP ID:" << query.lastError().text();
    }

    closeConnection();
    return query;
}

QStringList DBManager::loadConfig() {
    QString configPath = "../db_lib/db_connection.cfg";
    QFile file(configPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open config file: " + configPath.toStdString());
    }

    QStringList values;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        int colonIndex = line.indexOf(':');
        if (colonIndex != -1) {
            values.append(line.mid(colonIndex + 1).trimmed());
        }
    }

    if (values.size() != 6) {
        throw std::runtime_error("Invalid config file format");
    }

    return values;
}

QStringList DBManager::getPersonnelFIO() {
    QStringList fioList;

    if (!initConnection()) {
        return fioList;
    }

    QSqlQuery query(db);
    query.prepare("SELECT fio FROM personal");

    if (!query.exec()) {
        qDebug() << "Failed to execute personnel query:" << query.lastError().text();
        closeConnection();
        return fioList;
    }

    while (query.next()) {
        fioList.append(query.value(0).toString());
    }

    closeConnection();
    return fioList;
}