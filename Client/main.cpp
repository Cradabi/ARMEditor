#include "application/mainwindow.h"
#include "application/LoginDialog.h"

#include <QApplication>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <nlohmann/json.hpp>

#include <QFile>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

void writeCurrentUserToConfig(const QString &username, const QString &passwordHash)
{
    QFile file("../user.cfg");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл user.cfg для записи");
        return;
    }

    QTextStream out(&file);
    out << "login=" << username << "\n";

    file.close();
}

bool authenticate(const QString &username, const QString &password)
{
    QFile file("../users.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл users.json");
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    QJsonObject root = doc.object();

    QJsonArray users = root["users"].toArray();
    for (const QJsonValue &userValue : users) {
        if (!userValue.isObject()) {
            continue;
        }
        QJsonObject user = userValue.toObject();
        if (user.contains("name") && user["name"].isString() &&
            user.contains("password") && user["password"].isString()) {

            QString storedUsername = user["name"].toString();
            QString storedPasswordHash = user["password"].toString();

            // Hash the input password using SHA-1
            QString inputPasswordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex());

            if (username == storedUsername && inputPasswordHash == storedPasswordHash) {
                writeCurrentUserToConfig(username, inputPasswordHash);
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Show login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // User cancelled login
    }

    QString username = loginDialog.getUsername();
    QString password = loginDialog.getPassword();

    if (!authenticate(username, password)) {
        QMessageBox::critical(nullptr, "Ошибка", "Неправильные имя пользователя или пароль");
        return 0;
    }

    // If authentication is successful, open the main window
    MainWindow mainWindow;
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.setMinimumSize(400, 400);
    mainWindow.show();

    return app.exec();
}