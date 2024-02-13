#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <lib/SchemeClass.h>
#include "mainwindow.h"


class MyWidget : public QWidget
{
    void paintEvent(QPaintEvent *event){
        FiguresClasses::Line pol(100, 100, 450, 300);
        FiguresClasses::Rectangle rect(600, 120, 300, 200);
        FiguresClasses::Ellipse el(50, 350, 300, 200, 0);
        FiguresClasses::Arc arc(100, 650, 300, 200, 45, 0, 45);
        std::vector <std::vector<int>> points = {{1120, 210}, {1150, 120}, {1350, 370}, {1000, 220}};
        std::vector <std::vector<int>> points1 = {{500, 500}, {550, 550}, {600, 500}, {650, 550}, {700, 500}, {750, 550}, {800, 500}, {850, 550}, {900, 500}, {950, 550}, {1000, 500}, {1050, 550}};
        FiguresClasses::Polygon poly(points, true);
        FiguresClasses::CrookedLine crook(points1);
        std::string txt = "Текст";
        FiguresClasses::Text text(300, 50, 1000, 432, txt);
        std::string path = "/home/astra/ARMEditor/mez2_logo.jpg";
        FiguresClasses::Image image(800, 700, 450, 140, path, 0);
        FiguresClasses::TransitionPoint tr_p(1, 20, 50, 16, 16);
        FiguresClasses::TransitionButton tr_b(1, 80, 30, 120, 50, 0);
        std::vector<FiguresClasses::Line> line_v = {pol};
        std::vector<FiguresClasses::Rectangle> rect_v = {rect};
        std::vector<FiguresClasses::Ellipse> el_v = {el};
        std::vector<FiguresClasses::Arc> arc_v = {arc};
        std::vector<FiguresClasses::Polygon> poly_v = {poly};
        std::vector<FiguresClasses::CrookedLine> crook_v = {crook};
        std::vector<FiguresClasses::Text> text_v = {text};
        std::vector<FiguresClasses::Image> image_v = {image};
        std::vector<FiguresClasses::TransitionPoint> tr_p_v = {tr_p};
        std::vector<FiguresClasses::TransitionButton> tr_b_v = {tr_b};
        std::vector<FiguresClasses::Telecontrol> telec_v = {};
        std::vector<FiguresClasses::Telemeasure> telem_v = {};
        std::vector<FiguresClasses::Telesignalisation> teles_v = {};
        std::string name_sch = "Мультищитовая";
        Scheme sch(1400, 900, name_sch, line_v, rect_v, el_v, arc_v, poly_v, crook_v, text_v, image_v, tr_p_v, tr_b_v, telec_v, telem_v, teles_v);
        QPainter painter;
        painter.begin(this);
        sch.draw_scheme(painter);
        painter.end();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget widget;
    widget.setFixedSize(1400, 900);

    widget.show();
    return app.exec();
}
