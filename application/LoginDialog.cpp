#include "LoginDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Вход в АРМ клиент");

    QLabel *usernameLabel = new QLabel("Имя пользователя:");
    usernameEdit = new QLineEdit;

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
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString LoginDialog::getUsername() const
{
    return usernameEdit->text();
}

QString LoginDialog::getPassword() const
{
    return passwordEdit->text();
}