#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include "mywidget.h"
#include "parser lib/lib/SchemeFileParser.cpp"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>
#include <QFileDialog>

MyWidget::MyWidget() {
    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    draw_new_scheme("../parser lib/schemes_exp/emptyscheme.схема");
}

void MyWidget::draw_new_scheme(const std::string& filepath) {
    Scheme::SchemeParams tmp_scheme_params;

    SchemeFileParser parser(tmp_scheme_params);
    if (!parser.parse(filepath)) {
        draw_new_scheme("../parser lib/schemes_exp/emptyscheme.схема");
        return;
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
}

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
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

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_button_close() {
    emit signal_from_close_button();
}

void MainWindow::slot_change_panel_visibility() {
    this->panel_is_visible = not this->panel_is_visible;
    ui->listView->setVisible(this->panel_is_visible);
    ui->line_2->setVisible(this->panel_is_visible);
    if (this->panel_is_visible) {
        ui->pushButton_close->setText(">");
    } else {
        ui->pushButton_close->setText("<");
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    int px_width = this->width();
    int px_height = this->height();
    QRect rect = QRect(0, 0, px_width, px_height -
                                       50); // Почему то центральный виджет (главный контейнер) обрезает все содержимое в самом низу
    ui->verticalLayoutWidget->setGeometry(rect);
}

void MainWindow::slot_open_file_manager() {
    QString fileName = QFileDialog::getOpenFileName(this, ("Выберите файл .схема"),
                                                    "..",
                                                    ("*.схема"));
    std::string filepath = fileName.toStdString();
    std::cout << filepath << '\n';
    this->widget->draw_new_scheme(filepath);
}

