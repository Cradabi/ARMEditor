#include "LoginDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
        : QDialog(parent)
{
    setWindowTitle("Вход в АРМ клиент");

    QLabel *usernameLabel = new QLabel("Имя пользователя:");
    usernameComboBox = new QComboBox;

    QLabel *passwordLabel = new QLabel("Пароль:");
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Принять смену");
    cancelButton = new QPushButton("Отмена");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameComboBox);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    loadUsernamesFromJson("../users.json"); // Загрузка имен пользователей из JSON файла
}

QString LoginDialog::getUsername() const
{
    return usernameComboBox->currentText();
}

QString LoginDialog::getPassword() const
{
    return passwordEdit->text();
}

void LoginDialog::loadUsernamesFromJson(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл users.json");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    QJsonObject root = doc.object();

    QJsonArray users = root["users"].toArray();
    for (const QJsonValue &userValue : users) {
        if (userValue.isObject()) {
            QJsonObject user = userValue.toObject();
            if (user.contains("name") && user["name"].isString()) {
                usernameComboBox->addItem(user["name"].toString());
            }
        }
    }
}