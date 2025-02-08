#pragma once

#include "MainWidget.h"
#include "orders_lib/OrdersRepository.h"

#include <iostream>

#include <QMainWindow>
#include <QDesktopWidget>
#include <QFileDialog>
#include <qlistwidget.h>
#include "OrderWidget.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Конструктор и деструктор
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Методы
    void updateListWidgetFromJson();
    void ReadMessageReceivedtest(const QString &message);

    quint16 max_order_id{0}; // Максимальный ID приказа

signals:
    // Сигналы
    void sendCommannd(const QString &action, const QString &object);
    void onMessageReceived(const QString &message);
    void signal_from_button(int buttonID); // Сигнал для передачи номера нажатой кнопки
    void signal_from_close_button();

private:
    // Переменные
    Ui::MainWindow *ui;
    QVBoxLayout *verticalLayout;

    bool panel_is_visible = false;
    bool is_fullscreen = true;
    QString messageStatus;

    QThread* clientThread;
    arm_client* client; // Клиент для взаимодействия с сервером
    bool waitingForResponse = false;
    QString serverResponse;

    QVBoxLayout* listLayout;

    QDesktopWidget desk;

    MainWidget *widget;
    OrderRepository Orders; // Репозиторий приказов

    // Приватные методы
    QString getUserLogin(const QString &filePath);
    void onOrderWidgetClicked(const QJsonObject &order); // Обработка клика на приказ
    void removeOrderFromJson(int orderIdToRemove); // Удаление приказа из JSON
    quint16 readMaxOrderId(const QString &jsonFilePath); // Чтение максимального ID приказа

    // Новые методы для работы с диалогами
    void openExecutionDialog(const QJsonObject &order, const QString &executor, bool viaRU); // Диалог выполнения приказа
    void openResponseDialog(const QJsonObject &order, const QString &executor, bool viaRU); // Диалог ожидания ответа

private slots:
    // Слоты
    void slot_button_close();
    void slot_change_panel_visibility();
    void resizeEvent(QResizeEvent *event);
    void slot_open_file_manager();
};