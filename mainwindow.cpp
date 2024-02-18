#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <lib/SchemeClass.cpp>
#include "mywidget.h"

void MyWidget::paintEvent(QPaintEvent *event) {

    FiguresClasses::Line pol(100, 100, 450, 300);
    FiguresClasses::Rectangle rect(600, 120, 300, 200);
    FiguresClasses::Ellipse el(50, 350, 300, 200, 0);
    FiguresClasses::Arc arc(100, 650, 300, 200, 45, 0, 45);
    std::vector<std::vector<int>> points = {{1120, 210},
                                            {1150, 120},
                                            {1350, 370},
                                            {1000, 220}};
    std::vector<std::vector<int>> points1 = {{500,  500},
                                             {550,  550},
                                             {600,  500},
                                             {650,  550},
                                             {700,  500},
                                             {750,  550},
                                             {800,  500},
                                             {850,  550},
                                             {900,  500},
                                             {950,  550},
                                             {1000, 500},
                                             {1050, 550}};
    FiguresClasses::Polygon poly(points, true);
    FiguresClasses::CrookedLine crook(points1);
    std::string txt = "Текст";
    std::string txt2 = "0,0";
    std::string fn_name = "Arial Narrow";
    FiguresClasses::Text text(300, 50, 1000, 432, txt);
    std::string path = "/home/astra/ARMEditor/mez2_logo.jpg";
    FiguresClasses::Image image(800, 700, 450, 140, path, 0);
    FiguresClasses::TransitionPoint tr_p(1, 20, 50, 16, 16);
    FiguresClasses::TransitionButton tr_b(1, 80, 30, 120, 50, 0);
    std::vector<int> telem_color = {0, 0, 0};
    std::vector<int> telem_font = {0, 255, 0};
    FiguresClasses::Telemeasure tel_m(400, 50, 48, 24, 0, txt2, txt, 0, telem_color, true, true, fn_name, 14,
                                      telem_font, 1, 1, false, false, false, false, false);

    Scheme::SchemeParams tmp_sch_params;    // Экземплр структуры параметров схемы

    // Заполняем текущие параметры схемы
    tmp_sch_params.width = 1400;
    tmp_sch_params.height = 900;
    tmp_sch_params.objects_amount = 10;
    tmp_sch_params.name_scheme = "Мультищитовая";
    tmp_sch_params.line_vector = {pol};
    tmp_sch_params.rectangle_vector = {rect};
    tmp_sch_params.ellipse_vector = {el};
    tmp_sch_params.arc_vector = {arc};
    tmp_sch_params.polygon_vector = {poly};
    tmp_sch_params.crooked_line_vector = {crook};
    tmp_sch_params.text_vector = {text};
    tmp_sch_params.image_vector = {image};
    tmp_sch_params.tr_p_vector = {tr_p};
    tmp_sch_params.tr_b_vector = {tr_b};
    tmp_sch_params.telemeasure_vector = {tel_m};

    Scheme sch(tmp_sch_params);     // Экземпляр схемы

    QPainter painter;
    painter.begin(this);
    sch.draw_scheme(painter);
    painter.end();
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //QLabel *lbl = new QLabel("Label", this);
    MyWidget *widget = new MyWidget();
    widget->setFixedSize(1400, 900);
    ui->scrollArea->setWidget(widget);
    //ui->frame->setObjectName();
    ui->frame->setStyleSheet("#frame {border: 2px solid black;}");
    //ui->horizontalLayout->addWidget(lbl);

}

MainWindow::~MainWindow() {
    delete ui;
}
