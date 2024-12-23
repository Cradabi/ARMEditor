#include "application/mainwindow.h"
#include "application/LoginDialog.h"

#include <QApplication>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

bool authenticate(const QString &username, const QString &password)
{
    QFile file("../user.cfg");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл user.cfg");
        return false;
    }

    QString storedUsername;
    QString storedPasswordHash;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("login=")) {
            storedUsername = line.mid(6).trimmed();
        } else if (line.startsWith("password=")) {
            storedPasswordHash = line.mid(9).trimmed();
        }
    }

    file.close();

    // Hash the input password using SHA-1
    QString inputPasswordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex());

    return (username == storedUsername && inputPasswordHash == storedPasswordHash);
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