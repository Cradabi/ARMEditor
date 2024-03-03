#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include "mywidget.h"
#include "PARSERLIB/lib/SchemeFileParser.cpp"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenu>

int counter = 0;

MyWidget::MyWidget() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Scheme::SchemeParams tmp_scheme_params;

    SchemeFileParser parser(tmp_scheme_params);
    parser.parse("../PARSERLIB/schemes_exp/mellips.схема",
                 "../PARSERLIB/logs/SchemeLogs.txt");

    this->setFixedSize(tmp_scheme_params.width, tmp_scheme_params.height);

    view->resize(tmp_scheme_params.width, tmp_scheme_params.height);
    layout->addWidget(view);

    QPixmap pix(tmp_scheme_params.width, tmp_scheme_params.height);
    pix.fill(Qt::white);

    QPainter *painter = new QPainter(&pix);

    //painter->setPen(QColor(255, 34, 255, 255));
    // painter->drawRect(15,15,100,100);


    /*tmp_scheme_params.objects_vector.push_back(new LibraryObject(600, 300, 400, 250, 90, 0, 0, "huihui", "huihui2",
                                                                 {{new Rectangle(-200, -50, 100, 100, 45, 10, 3, {255, 0, 0}, "", true)},
                                                                  {new Line(-200, -125, 200, 150)}}, "", true, true));*/


    Scheme scheme(tmp_scheme_params);
    std::string text2 = "";
    std::vector<int> col2 = {255, 0, 0};
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);

    //TODO сделать удаление лэйаута, сцены и отображения
}


/*
void MyWidget::paintEvent(QPaintEvent* event) {
//    std::string text2 = "";
//    std::vector<int> col2 = {255, 0, 0};
//    std::vector<std::vector<int>> points = {{1120, 210},
//                                            {1150, 120},
//                                            {1350, 370},
//                                            {1000, 220}};
//    std::vector<std::vector<int>> points1 = {{500,  500},
//                                             {550,  550},
//                                             {600,  500},
//                                             {650,  550},
//                                             {700,  500},
//                                             {750,  550},
//                                             {800,  500},
//                                             {850,  550},
//                                             {900,  500},
//                                             {950,  550},
//                                             {1000, 500},
//                                             {1050, 550}};
//    std::string txt = "Текст";
//    std::string txt2 = "0,0";
//    std::string fn_name = "Arial Narrow";
//    std::string path = "/home/astra/ARMEditor/mez2_logo.jpg";
//    std::vector<int> telem_color = {0, 0, 0};
//    std::vector<int> telem_font = {0, 255, 0};
//    FiguresClasses::Telemeasure tel_m(400, 50, 48, 24, 0, txt2, txt, 0, telem_color, true, true, fn_name, 14,
//                                      telem_font, 1, 1, false, false, false, false, false);
//
//    Scheme::SchemeParams tmp_sch_params;    // Экземплр структуры параметров схемы
//
//    // Заполняем текущие параметры схемы
//    tmp_sch_params.width = 15360;
//    tmp_sch_params.height = 1200;
//    tmp_sch_params.objects_amount = 10;
//    tmp_sch_params.name_scheme = "Мультищитовая";
//    tmp_sch_params.objects_vector = {};
//    tmp_sch_params.objects_vector.push_back(new Line(100, 100, 450, 300));
//    tmp_sch_params.objects_vector.push_back(new Rectangle(600, 120, 300, 200));
//    tmp_sch_params.objects_vector.push_back(new Ellipse(50, 350, 300, 200, 0));
//    tmp_sch_params.objects_vector.push_back(new Arc(100, 650, 300, 200, 45, 0, 45));
//    tmp_sch_params.objects_vector.push_back(new Polygon(points, true));
//    tmp_sch_params.objects_vector.push_back(new CrookedLine(points1));
//    tmp_sch_params.objects_vector.push_back(new Text(300, 50, 1000, 432, txt));
//    tmp_sch_params.objects_vector.push_back(new Image(800, 700, 450, 140, path, 0));
//    tmp_sch_params.objects_vector.push_back(new TransitionPoint(1, 20, 50, 16, 16));
//    tmp_sch_params.objects_vector.push_back(new TransitionButton(1, 80, 30, 120, 50, 0));
//    tmp_sch_params.objects_vector.push_back(
//            new Telemeasure(400, 50, 48, 24, 0, txt2, txt, 0, telem_color, true, true, fn_name, 14,
//                            telem_font, 1, 1, false, false, false, false, false));
//    std::vector<int> col = {200, 200, 200};
//    FiguresClasses::Set set(1, 20, 20, 1, col);
//    tmp_sch_params.set_object = set;

    //tmp_sch_params.objects_vector = {pol, pol2, rect, el, arc, poly, crook, text, image, tr_p, tr_b, tel_m};
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

    Scheme::SchemeParams tmp_scheme_params;

//    SchemeFileParser parser(tmp_scheme_params);
//    parser.parse("/home/chekhov/Документы/GitHub/ARMEditor/PARSERLIB/schemes_exp/Эллипс.схема",
//                 "/home/chekhov/Документы/GitHub/ARMEditor/PARSERLIB/logs/SchemeLogs.txt");

    Scheme scheme(tmp_scheme_params);

    QPainter painter;
    painter.begin(this);
//    sch.add_object(new Line(100, 200, 450, 400, text2, text2, true, 1, 0, 12, 2, 4, col2));
    scheme.draw_scheme(painter);
    painter.end();

    std::cout << ++counter << '\n';
} */

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    MyWidget *widget = new MyWidget();
    ui->scrollArea->setWidget(widget);
    ui->listView->setVisible(this->panel_is_visible);
    ui->line_2->setVisible(this->panel_is_visible);

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));
    connect(ui->action_inspector, SIGNAL(triggered()), this, SLOT(slot_button_close()));

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

void MainWindow::resizeEvent(QResizeEvent *event) {
    int px_width = this->width();
    int px_height = this->height();
    QRect rect = QRect(0, 0, px_width, px_height -
                                       50); // Почему то центральный виджет (главный контейнер) обрезает все содержимое в самом низу
    ui->verticalLayoutWidget->setGeometry(rect);
}
