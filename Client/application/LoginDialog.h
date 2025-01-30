#pragma once

#include <QDialog>
#include <QComboBox>

class QLineEdit;
class QPushButton;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;
    void clearPassword();

private:
    void loadUsernamesFromJson(const QString &filename);
    QLineEdit *usernameEdit;
    QComboBox *usernameComboBox;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
};
