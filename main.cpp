#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <lib/FiguresClasses.cpp>
#include "mainwindow.h"


class MyWidget : public QWidget
{
    void paintEvent(QPaintEvent *event){
        FiguresClasses::Line pol(50, 50, 450, 300);
        FiguresClasses::Rectangle rect(600, 300, 300, 200);
        FiguresClasses::Ellipse el(50, 450, 300, 200, 0);
        FiguresClasses::Arc arc(500, 650, 300, 200, 45, 0, 45);
        std::vector <std::vector<int>> points = {{900, 200}, {950, 150}, {1350, 600}, {600, 350}};
        std::vector <std::vector<int>> points1 = {{90, 200}, {95, 150}, {135, 600}, {60, 350}};
        FiguresClasses::Polygon poly(points, false);
        FiguresClasses::CrookedLine crook(points1);
        QPainter painter;
        painter.begin(this);
        //начинаем отрисовку сетки
        QColor color_set = {200, 200, 200};
        painter.setPen(QPen(color_set, 1, Qt::DashLine, Qt::RoundCap));
        for (int i = 0; i < 1400; i+=10){
            painter.drawLine(i, 0, i, 900);
        }
        for (int i = 0; i < 900; i+=10){
            painter.drawLine(0, i, 1400, i);
        }
        //начинаем отрисовку линий
        QColor color_line = {pol.get_line_color()[0], pol.get_line_color()[1], pol.get_line_color()[2]};
        if (pol.get_style_line() == 0){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::NoPen, Qt::RoundCap));
        }else if (pol.get_style_line() == 1){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::SolidLine, Qt::RoundCap));
        }else if (pol.get_style_line() == 2){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::DashLine, Qt::RoundCap));
        }else if (pol.get_style_line() == 3){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::DotLine, Qt::RoundCap));
        }else if (pol.get_style_line() == 4){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::DashDotLine, Qt::RoundCap));
        }else if (pol.get_style_line() == 5){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap));
        }else if (pol.get_style_line() == 6){
            painter.setPen(QPen(color_line, pol.get_line_width(), Qt::CustomDashLine, Qt::RoundCap));
        }
        painter.drawLine(pol.get_st_x(), pol.get_st_y(), pol.get_end_x(), pol.get_end_y());
        if(pol.get_start_style_arrow() == 1){
            std::cout<<0;
        }else if(pol.get_start_style_arrow() == 2){
            std::cout<<0;
        }else if(pol.get_start_style_arrow() == 3){
            painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
        }else if(pol.get_start_style_arrow() == 4){
            std::cout<<0;
        }
        if(pol.get_end_style_arrow() == 1){
            std::cout<<0;
        }else if(pol.get_end_style_arrow() == 2){
            std::cout<<0;
        }else if(pol.get_end_style_arrow() == 3){
            painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
        }else if(pol.get_end_style_arrow() == 4){
            std::cout<<0;
        }
        color_line = {255, 0, 0};
        painter.setPen(QPen(color_line, 2, Qt::SolidLine, Qt::FlatCap));
        painter.drawPoint(pol.get_st_x(), pol.get_st_y());
        painter.drawPoint(pol.get_end_x(), pol.get_end_y());
        //начинаем отрисовку прямоугольника
        painter.save();
        painter.translate(rect.get_center_x(), rect.get_center_y());
        painter.rotate((-1)*rect.get_angle());

        if (rect.get_show()){
            if (rect.get_show_filling()){
                QColor filling_color = {rect.get_filling_color()[0], rect.get_filling_color()[1], rect.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_rect = {rect.get_line_color()[0], rect.get_line_color()[1], rect.get_line_color()[2]};
            if (rect.get_style_line() == 0){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::NoPen, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 1){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 2){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 3){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 4){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 5){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (rect.get_style_line() == 6){
                painter.setPen(QPen(color_rect, rect.get_line_width(), Qt::CustomDashLine, Qt::RoundCap, Qt::RoundJoin));
            }
            painter.drawRect(QRect((-1)*(rect.get_width()/2), (-1)*(rect.get_height()/2), rect.get_width(), rect.get_height()));
            color_rect = {255, 0, 0};
            painter.setPen(QPen(color_rect, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint((-1)*(rect.get_width()/2), (-1)*(rect.get_height()/2));
            painter.drawPoint((-1)*(rect.get_width()/2), rect.get_height()/2);
            painter.drawPoint(rect.get_width()/2, (-1)*(rect.get_height()/2));
            painter.drawPoint(rect.get_width()/2, rect.get_height()/2);
        }
        painter.restore();
        //начинаем отрисовку эллипса
        painter.save();
        painter.translate(el.get_center_x(), el.get_center_y());
        painter.rotate((-1)*el.get_angle());
        if (el.get_show()){
            if (el.get_show_filling()){
                QColor filling_color = {el.get_filling_color()[0], el.get_filling_color()[1], el.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_el = {el.get_line_color()[0], el.get_line_color()[1], el.get_line_color()[2]};
            if (el.get_style_line() == 0){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::NoPen, Qt::RoundCap, Qt::MiterJoin));
            }else if (el.get_style_line() == 1){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
            }else if (el.get_style_line() == 2){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (el.get_style_line() == 3){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (el.get_style_line() == 4){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (el.get_style_line() == 5){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (el.get_style_line() == 6){
                painter.setPen(QPen(color_el, el.get_line_width(), Qt::CustomDashLine, Qt::RoundCap, Qt::RoundJoin));
            }
            painter.drawEllipse(QRect((-1)*(el.get_width()/2), (-1)*(el.get_height()/2), el.get_width(), el.get_height()));
            color_el = {255, 0, 0};
            painter.setPen(QPen(color_el, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint((-1)*(el.get_width()/2), 0);
            painter.drawPoint(el.get_width()/2, 0);
            painter.drawPoint(0, (-1)*(el.get_height()/2));
            painter.drawPoint(0, el.get_height()/2);
        }
        //начинаем отрисовку дуги
        painter.restore();
        painter.save();
        painter.translate(arc.get_center_x(), arc.get_center_y());
        painter.rotate((-1)*arc.get_angle());
        if (arc.get_show()){
            QColor color_arc = {arc.get_line_color()[0], arc.get_line_color()[1], arc.get_line_color()[2]};
            if (arc.get_style_line() == 0){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::NoPen, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 1){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 2){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 3){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 4){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 5){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (arc.get_style_line() == 6){
                painter.setPen(QPen(color_arc, arc.get_line_width(), Qt::CustomDashLine, Qt::RoundCap, Qt::RoundJoin));
            }
            if (arc.get_show_filling()){
                QColor filling_color = {arc.get_filling_color()[0], arc.get_filling_color()[1], arc.get_filling_color()[2]};
                painter.setBrush(filling_color);
                painter.drawPie(QRect((-1)*(arc.get_width()/2), (-1)*(arc.get_height()/2), arc.get_width(), arc.get_height()), ((360 - arc.get_start_angle())%360)*(-16), ((360 - arc.get_end_angle())%360)*(-16));
            }else{
                painter.drawArc(QRect((-1)*(arc.get_width()/2), (-1)*(arc.get_height()/2), arc.get_width(), arc.get_height()), ((360 - arc.get_start_angle())%360)*(-16), ((360 - arc.get_end_angle())%360)*(-16));
            }

            color_arc = {255, 0, 0};
            painter.restore();
            painter.setPen(QPen(color_arc, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(arc.get_x(), arc.get_y() + arc.get_height()/2);
            painter.drawPoint(arc.get_x() + arc.get_width(), arc.get_y() + arc.get_height()/2);
            painter.drawPoint(arc.get_x() + arc.get_width()/2, arc.get_y());
            painter.drawPoint(arc.get_x() + arc.get_width()/2, arc.get_y() + arc.get_height());
        }

        //начинаем отрисовку полигона
        painter.save();
        painter.translate(poly.get_center_x(), poly.get_center_y());
        painter.rotate((-1)*poly.get_angle());
        if (poly.get_show()){
            if (poly.get_show_filling()){
                QColor filling_color = {poly.get_filling_color()[0], poly.get_filling_color()[1], poly.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_poly = {poly.get_line_color()[0], poly.get_line_color()[1], poly.get_line_color()[2]};
            if (poly.get_style_line() == 0){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::NoPen, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 1){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 2){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 3){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 4){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 5){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (poly.get_style_line() == 6){
                painter.setPen(QPen(color_poly, poly.get_line_width(), Qt::CustomDashLine, Qt::RoundCap, Qt::RoundJoin));
            }
            QPoint qpoints[poly.get_points().size()];
            for (int i = 0; i < poly.get_points().size(); i++){
                qpoints[i] = QPoint(poly.get_points()[i][0] - poly.get_center_x(), poly.get_points()[i][1] - poly.get_center_y());
            }
            if(poly.get_end_polygon()){
                painter.drawPolygon(qpoints, poly.get_points().size());
            }else{
                painter.drawPolyline(qpoints, poly.get_points().size());
            }
            painter.restore();
            color_poly = {255, 0, 0};
            painter.setPen(QPen(color_poly, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(poly.get_center_x(), poly.get_center_y());
            for (int i = 0; i < poly.get_points().size(); i++){
                painter.drawPoint(poly.get_points()[i][0], poly.get_points()[i][1]);
            }
        }
        painter.restore();
        //начинаем отрисовку кривой
        painter.save();
        painter.translate(crook.get_center_x(), crook.get_center_y());
        painter.rotate((-1)*crook.get_angle());
        if (crook.get_show()){
            if (crook.get_show_filling()){
                QColor filling_color = {crook.get_filling_color()[0], crook.get_filling_color()[1], crook.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_crook = {crook.get_line_color()[0], crook.get_line_color()[1], crook.get_line_color()[2]};
            if (crook.get_style_line() == 0){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::NoPen, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 1){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 2){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 3){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 4){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 5){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            }else if (crook.get_style_line() == 6){
                painter.setPen(QPen(color_crook, crook.get_line_width(), Qt::CustomDashLine, Qt::RoundCap, Qt::RoundJoin));
            }
            QPoint qpoints[crook.get_points().size()];
            for (int i = 0; i < crook.get_points().size(); i++){
                qpoints[i] = QPoint(crook.get_points()[i][0] - crook.get_center_x(), crook.get_points()[i][1] - crook.get_center_y());
            }
            painter.drawPolyline(qpoints, crook.get_points().size());
            painter.restore();
            color_crook = {255, 0, 0};
            painter.setPen(QPen(color_crook, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(crook.get_center_x(), crook.get_center_y());
            for (int i = 0; i < poly.get_points().size(); i++){
                painter.drawPoint(crook.get_points()[i][0], crook.get_points()[i][1]);
            }
        }
        painter.restore();
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
