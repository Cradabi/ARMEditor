#pragma once

#include "MainWidget.h"

#include <iostream>

#include <QMainWindow>
#include <QDesktopWidget>
#include <QFileDialog>
#include <qlistwidget.h>
#include <nlohmann/json.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWidget *widget;

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void updateListWidgetFromJson();

void setupConnections();

void onItemDoubleClicked(QListWidgetItem *item);

    void ReadMessageReceivedtest(const QString &message);

signals:
    void sendCommannd(const QString &action, const QString &object);
    void onMessageReceived(const QString &message);

    void signal_from_button(int buttonID);    // Сигнал для передачи номер нажатой кнопки
    void signal_from_close_button();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *verticalLayout;

    bool panel_is_visible = false;
    bool is_fullscreen = true;
    QString messageStatus;


    QDesktopWidget desk;

    QString getUserLogin(const QString &filePath);

void removeOrderFromJson(const nlohmann::json &orderToRemove);

private slots:

    void slot_button_close();

    void slot_change_panel_visibility();

    void resizeEvent(QResizeEvent *event);

    void slot_open_file_manager();
};