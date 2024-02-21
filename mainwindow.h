#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signal_from_button(int buttonID);    // Сигнал для передачи номер нажатой кнопки
    void signal_from_close_button();

private:
    Ui::MainWindow *ui;
    QVBoxLayout* verticalLayout;

    bool panel_is_visible = true;

private slots:
    void slot_button1();
    void slot_button2();
    void slot_button3();
    void slot_button4();

    void slot_button_close();

    void slot_button_clicked(int buttonID);
    void slot_change_panel_visibility();
};
#endif // MAINWINDOW_H
