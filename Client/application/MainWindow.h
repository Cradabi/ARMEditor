#pragma once

#include "MainWidget.h"
#include "orders_lib/OrdersRepository.h"

#include <iostream>

#include <QMainWindow>
#include <QDesktopWidget>
#include <QFileDialog>
#include <qlistwidget.h>
#include <nlohmann/json.hpp>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWidget *widget;

    OrderRepository Orders;

    quint16 max_order_id{0};

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void updateListWidgetFromJson();

    void setupConnections();

    void onItemClicked(QListWidgetItem *item);

    void ReadMessageReceivedtest(const QString &message);

signals:
    void sendCommannd(const QString &action, const QString &object);

    void onMessageReceived(const QString &message);

    void signal_from_button(int buttonID); // Сигнал для передачи номер нажатой кнопки
    void signal_from_close_button();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *verticalLayout;

    bool panel_is_visible = false;
    bool is_fullscreen = true;
    QString messageStatus;

    QThread* clientThread;
    arm_client* client;
    bool waitingForResponse;
    QString serverResponse;


    QDesktopWidget desk;

    QString getUserLogin(const QString &filePath);

    void removeOrderFromJson(const nlohmann::json &orderToRemove);

    quint16 readMaxOrderId(const QString &jsonFilePath);

private slots:
    void slot_button_close();

    void slot_change_panel_visibility();

    void resizeEvent(QResizeEvent *event);

    void slot_open_file_manager();
};
