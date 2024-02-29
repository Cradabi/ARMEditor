#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QDesktopWidget>

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
    bool is_fullscreen = true;

    QDesktopWidget desk;

private slots:
    void slot_button_close();

    void slot_change_panel_visibility();

    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H
