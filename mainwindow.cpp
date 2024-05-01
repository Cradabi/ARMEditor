#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QTransform>
#include "mywidget.h"
#include "parser lib/lib/SchemeFileParser.cpp"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QLineEdit>
#include <QFileDialog>
#include "db lib/db_connection.cpp"

Scheme::SchemeParams current_scheme_params;

MyWidget::MyWidget()
{
    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MyView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    draw_new_scheme("../parser lib/schemes_exp/emptyscheme.схема");
}

void MyWidget::draw_new_scheme(const std::string& filepath)
{
    delete layout;
    delete scene;
    delete view;

    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MyView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Scheme::SchemeParams tmp_scheme_params;


    SchemeFileParser parser(tmp_scheme_params);
    if (!parser.parse(filepath))
    {
        parser.parse("../parser lib/schemes_exp/emptyscheme.схема");
    }
    QSqlQuery db_request_result = connection_to_db();
    QSqlQuery db_request_result_cp = connection_to_cp_db();
    std::string help_text;
    for (auto object : tmp_scheme_params.objects_vector)
    {
        if (object->get_type_object() == "Библиотечный объект")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_condition(db_request_result.value(2).toInt());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                        }
                    }
                }
            }
        }
        else if (object->get_type_object() == "Телеизмерение")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                        }
                    }
                }
            }
        }
        else if (object->get_type_object() == "Телеконтроль")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                        }
                    }
                }
            }
        }
        else if (object->get_type_object() == "Телесигнализация")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                        }
                    }
                }
            }
        }
    }

    this->setFixedSize(tmp_scheme_params.width, tmp_scheme_params.height);

    view->resize(tmp_scheme_params.width, tmp_scheme_params.height);
    layout->addWidget(view);

    QPixmap pix(tmp_scheme_params.width, tmp_scheme_params.height);
    QColor bgColor = {tmp_scheme_params.bgColor.red, tmp_scheme_params.bgColor.green, tmp_scheme_params.bgColor.blue};
    pix.fill(bgColor);

    QPainter* painter = new QPainter(&pix);

    Scheme scheme(tmp_scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
    current_scheme_params = tmp_scheme_params;
}

void MyView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << event->pos().x() << " " << event->pos().y();
        QPoint originalpoint(event->pos().x(), event->pos().y());

        // for (auto object : current_scheme_params.objects_vector)
        // {
        //     std::string tp_obj = object->get_type_object();
        //     if (tp_obj == "Библиотечный объект")
        //     {
        //         ;
        //     }else if (tp_obj == "Телеизмерение")
        //     {
        //         ;
        //     }else if (tp_obj == "Телеконтроль")
        //     {
        //         ;
        //     }else if (tp_obj == "Телесигнализация")
        //     {
        //         ;
        //     }
        // }

        QMenu *newWindow = new QMenu();

        int xOffset = 20;
        int yOffset = -20;
        newWindow->move(event->pos().x() + xOffset, event->pos().y() + yOffset);

        QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

        QHBoxLayout *row1Layout = new QHBoxLayout();
        QLabel *label1 = new QLabel("Label 1:");
        QLineEdit *lineEdit1 = new QLineEdit();
        row1Layout->addWidget(label1);
        row1Layout->addWidget(lineEdit1);

        QHBoxLayout *row2Layout = new QHBoxLayout();
        QLabel *label2 = new QLabel("Label 2:");
        QLineEdit *lineEdit2 = new QLineEdit();
        row2Layout->addWidget(label2);
        row2Layout->addWidget(lineEdit2);

        QPushButton *saveButton = new QPushButton("&Сохранить");

        mainLayout->addLayout(row1Layout);
        mainLayout->addLayout(row2Layout);
        mainLayout->addWidget(saveButton);

        newWindow->show();
    }
}


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new MyWidget();
    ui->scrollArea->setWidget(widget);
    ui->listView->setVisible(this->panel_is_visible);
    ui->line_2->setVisible(this->panel_is_visible);

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));
    connect(ui->action_inspector, SIGNAL(triggered()), this, SLOT(slot_button_close()));
    connect(ui->action_open, SIGNAL(triggered(bool)), this, SLOT(slot_open_file_manager()));

    //connect(ui->menu_file, SIGNAL(hovered()), this, SLOT(slot_menu_hover()));

    connect(this, &MainWindow::signal_from_close_button, this, &MainWindow::slot_change_panel_visibility);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_button_close()
{
    emit signal_from_close_button();
}

void MainWindow::slot_change_panel_visibility()
{
    this->panel_is_visible = not this->panel_is_visible;
    ui->listView->setVisible(this->panel_is_visible);
    ui->line_2->setVisible(this->panel_is_visible);
    if (this->panel_is_visible)
    {
        ui->pushButton_close->setText(">");
    }
    else
    {
        ui->pushButton_close->setText("<");
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    int px_width = this->width();
    int px_height = this->height();
    QRect rect = QRect(0, 0, px_width, px_height -
                       50); // Почему то центральный виджет (главный контейнер) обрезает все содержимое в самом низу
    ui->verticalLayoutWidget->setGeometry(rect);
}

void MainWindow::slot_open_file_manager()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Выберите файл .схема"),
                                                    "..",
                                                    ("*.схема"));
    std::string filepath = fileName.toStdString();
    std::cout << filepath << '\n';
    this->widget->draw_new_scheme(filepath);
}
