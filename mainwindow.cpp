#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <lib/SchemeClass.cpp>
#include "mywidget.h"

void MyWidget::paintEvent(QPaintEvent *event) {
    std::string text2 = "";
    std::vector <int> col2 = {255, 0, 0};
    FiguresClasses::Line pol(100, 100, 450, 300);
    FiguresClasses::Line pol2(100, 200, 450, 400, text2, text2, true, 1, 0, 12, 2, 4, col2);
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
    tmp_sch_params.width = 15360;
    tmp_sch_params.height = 1200;
    tmp_sch_params.objects_amount = 10;
    tmp_sch_params.name_scheme = "Мультищитовая";
    tmp_sch_params.line_vector = {pol, pol2};
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
    //чтобы отобразить тестовую большую схему надо раскоментить текст нижу
    //for (int i = 0; i < 4000; i++){
      //  if((i%5) == 0){
        //    FiguresClasses::Line pol2(i*30, 30, i*30+100, 100, text2, text2, true, 1, 0, 12, 2, 4, col2);
          //  tmp_sch_params.line_vector.push_back(pol2);
        //} else if((i%5) == 1){
          //  FiguresClasses::Rectangle rect(i*30, 120, 250, 250);
        //    tmp_sch_params.rectangle_vector.push_back(rect);
        //}else if((i%5) == 2){
          //  FiguresClasses::Ellipse el(i*30, 560, 100, 100, 0);
           // tmp_sch_params.ellipse_vector.push_back(el);
        //}else if((i%5) == 3){
          //  FiguresClasses::Arc arc(i*30, 750, 200, 200, 45, 0, 45);
           // tmp_sch_params.arc_vector.push_back(arc);
        //}else if((i%5) == 4){
         //   FiguresClasses::Image image(i*150, 700, 450, 140, path, 0);
           // tmp_sch_params.image_vector.push_back(image);
        //}
    //}

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
    widget->setFixedSize(1536, 1200);
    ui->scrollArea->setWidget(widget);
    //ui->frame->setObjectName();
    //ui->frame->setStyleSheet("#frame {border: 2px solid black;}");
    //ui->horizontalLayout->addWidget(lbl);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_button1()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slot_button2()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slot_button3()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slot_button4()));

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));

    connect(this, &MainWindow::signal_from_button, this, &MainWindow::slot_button_clicked);
    connect(this, &MainWindow::signal_from_close_button, this, &MainWindow::slot_change_panel_visibility);


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_button1() {
    emit signal_from_button(1);
}

void MainWindow::slot_button2() {
    emit signal_from_button(2);
}

void MainWindow::slot_button3() {
    emit signal_from_button(3);
}

void MainWindow::slot_button4() {
    emit signal_from_button(4);
}

void MainWindow::slot_button_close() {
    emit signal_from_close_button();
}


void MainWindow::slot_button_clicked(int buttonID) {
    QMessageBox::information(this,
                             "Уведомление о нажатой кнопке",
                             "Нажата кнопка под номером " + QString::number(buttonID));
}

void MainWindow::slot_change_panel_visibility() {
    if (this->panel_is_visible) {
        this->panel_is_visible = false;
        ui->listView->setVisible(false);
        ui->line_2->setVisible(false);
        QLayoutItem *d_item1;
        QLayoutItem *d_item2;
        d_item2 = ui->horizontalLayout->layout()->takeAt(2);
        ui->horizontalLayout->layout()->removeItem(d_item2);
        d_item1 = ui->horizontalLayout->layout()->takeAt(1);
        ui->horizontalLayout->layout()->removeItem(d_item1);
    } else {
        this->panel_is_visible = true;
        ui->listView->setVisible(true);
        ui->line_2->setVisible(true);
        ui->horizontalLayout->addWidget(ui->line_2);
        ui->horizontalLayout->addWidget(ui->listView);
    }
}
