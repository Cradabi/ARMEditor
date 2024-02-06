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
        FiguresClasses::Arc arc(500, 650, 300, 200, 0, 0, 45);
        QPainter painter;
        painter.begin(this);
        //начинаем отрисовку линий
        QColor color_line = {pol.get_line_color()[0], pol.get_line_color()[1], pol.get_line_color()[2]};
        painter.setPen(QPen(color_line, 24, Qt::DashDotLine, Qt::FlatCap));
        painter.drawLine(pol.get_st_x(), pol.get_st_y(), pol.get_end_x(), pol.get_end_y());
        if(pol.get_start_style_arrow() == 1){
            std::cout<<0;
        }else if(pol.get_start_style_arrow() == 2){
            std::cout<<0;
        }else if(pol.get_start_style_arrow() == 3){
            painter.drawEllipse(pol.get_end_x(), pol.get_end_y(), pol.get_line_width(), pol.get_line_width());
        }else if(pol.get_start_style_arrow() == 4){
            std::cout<<0;
        }
        if(pol.get_end_style_arrow() == 1){
            std::cout<<0;
        }else if(pol.get_end_style_arrow() == 2){
            std::cout<<0;
        }else if(pol.get_end_style_arrow() == 3){
            painter.drawEllipse(pol.get_end_x(), pol.get_end_y(), pol.get_line_width(), pol.get_line_width());
        }else if(pol.get_end_style_arrow() == 4){
            std::cout<<0;
        }
        //начинаем отрисовку прямоугольника
        if (rect.get_show()){
            if (rect.get_show_filling()){
                QColor filling_color = {rect.get_filling_color()[0], rect.get_filling_color()[1], rect.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_rect = {rect.get_line_color()[0], rect.get_line_color()[1], rect.get_line_color()[2]};
            painter.setPen(QPen(color_rect, 24, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.drawRect(QRect(rect.get_x() - round(rect.get_line_width() / 2), rect.get_y() - round(rect.get_line_width() / 2), rect.get_width() + round(rect.get_line_width() / 2), rect.get_height() + round(rect.get_line_width() / 2)));
            color_rect = {255, 0, 0};
            painter.setPen(QPen(color_rect, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(rect.get_x(), rect.get_y());
            painter.drawPoint(rect.get_x() + rect.get_width(), rect.get_y());
            painter.drawPoint(rect.get_x(), rect.get_y() + rect.get_height());
            painter.drawPoint(rect.get_x() + rect.get_width(), rect.get_y() + rect.get_height());
        }
        //начинаем отрисовку эллипса
        if (el.get_show()){
            if (el.get_show_filling()){
                QColor filling_color = {el.get_filling_color()[0], el.get_filling_color()[1], el.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_el = {el.get_line_color()[0], el.get_line_color()[1], el.get_line_color()[2]};
            painter.setPen(QPen(color_el, 24, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin));
            painter.drawEllipse(QRect(el.get_x() - round(el.get_line_width() / 2), el.get_y() - el.get_line_width() / 2, el.get_width() + el.get_line_width() / 2, el.get_height() + el.get_line_width()/2));
            color_el = {255, 0, 0};
            painter.setPen(QPen(color_el, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(el.get_x(), el.get_y() + el.get_height() / 2);
            painter.drawPoint(el.get_x() + el.get_width(), el.get_y() + el.get_height() / 2);
            painter.drawPoint(el.get_x() + el.get_width() / 2, el.get_y());
            painter.drawPoint(el.get_x() + el.get_width() / 2, el.get_y() + el.get_height());
        }
        //начинаем отрисовку дуги
        if (arc.get_show()){
            if (arc.get_show_filling()){
                QColor filling_color = {arc.get_filling_color()[0], arc.get_filling_color()[1], arc.get_filling_color()[2]};
                painter.setBrush(filling_color);
            }
            QColor color_arc = {arc.get_line_color()[0], arc.get_line_color()[1], arc.get_line_color()[2]};
            painter.setPen(QPen(color_arc, 24, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.drawPie(QRect(arc.get_x() - round(arc.get_line_width() / 2), arc.get_y() - arc.get_line_width() / 2, arc.get_width() + arc.get_line_width() / 2, arc.get_height() + arc.get_line_width()/2), ((360 - arc.get_start_angle())%360) * (-16), ((360 - arc.get_end_angle())%360) * (-16));
            color_arc = {255, 0, 0};
            painter.setPen(QPen(color_arc, 2, Qt::SolidLine, Qt::FlatCap));
            painter.drawPoint(arc.get_x(), arc.get_y() + arc.get_height() / 2);
            painter.drawPoint(arc.get_x() + arc.get_width(), arc.get_y() + arc.get_height() / 2);
            painter.drawPoint(arc.get_x() + arc.get_width() / 2, arc.get_y());
            painter.drawPoint(arc.get_x() + arc.get_width() / 2, arc.get_y() + arc.get_height());
        painter.end();
        }
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
