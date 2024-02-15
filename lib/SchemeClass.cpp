#include "SchemeClass.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>



Scheme::Scheme(int _width, int _height, const std::string& _name, const std::string& file_path, const std::string& bd, const std::string& server, int version, int scale, int scale_in_ARM, int fonts_number, int objects_number, int group_number,  const std::vector <FiguresClasses::Line>& _line, const std::vector <FiguresClasses::Rectangle>& _rect, const std::vector <FiguresClasses::Ellipse>& _el, const std::vector <FiguresClasses::Arc>& _arc, const std::vector <FiguresClasses::Polygon>& _poly, const std::vector <FiguresClasses::CrookedLine>& _crook, const std::vector <FiguresClasses::Text>& _text, const std::vector <FiguresClasses::Image>& _image, const std::vector <FiguresClasses::TransitionPoint>& _tr_p, const std::vector <FiguresClasses::TransitionButton>& _tr_b, const std::vector <FiguresClasses::Telecontrol>& _telec, const std::vector <FiguresClasses::Telemeasure>& _telem, const std::vector <FiguresClasses::Telesignalisation>& _teles){
    width = _width;
    height = _height;
    this->name_scheme = _name;
    this->file_path = file_path;
    this->bd_name = bd;
    this->server = server;
    this->version = version;
    this->scale = scale;
    this->scale_in_ARM = scale_in_ARM;
    this->fonts_number = fonts_number;
    this->objects_number = objects_number;
    this->groups_number = group_number;
    this->line_vector = _line;
    this->rectangle_vector = _rect;
    this->ellipse_vector = _el;
    this->arc_vector = _arc;
    this->polygon_vector = _poly;
    this->crooked_line_vector = _crook;
    this->text_vector = _text;
    this->image_vector = _image;
    this->tr_p_vector = _tr_p;
    this->tr_b_vector = _tr_b;
    this->telecontrol_vector = _telec;
    this->telemeasure_vector = _telem;
    this->telesignalisation_vector = _teles;
}

void Scheme::set_width(int width){
    this->width = width;
}

void Scheme::set_height(int height){
    this->height = height;
}

void Scheme::set_version(int version){
    this->version = version;
}

void Scheme::set_scale(int scale){
    this->scale = scale;
}

void Scheme::set_scale_in_ARM(int scale_in_ARM){
    this->scale_in_ARM = scale_in_ARM;
}

void Scheme::set_fonts_number(int fonts_numbers){
    this->fonts_number = fonts_number;
}

void Scheme::set_objects_number(int objects_number){
    this->objects_number = objects_number;
}

void Scheme::set_groups_number(int groups_number){
    this->groups_number = groups_number;
}

void Scheme::set_name_scheme(const std::string &name){
    this->name_scheme = name;
}

void Scheme::set_file_path(const std::string &file_path){
    this->file_path = file_path;
}

void Scheme::set_bd_name(const std::string &bd){
    this->bd_name = bd;
}

void Scheme::set_server(const std::string &server){
    this->server = server;
}

int Scheme::get_width(){
    return this->width;
}

int Scheme::get_height(){
    return this->height;
}

int Scheme::get_version(){
    return this->version;
}

int Scheme::get_scale(){
    return this->scale;
}

int Scheme::get_scale_in_ARM(){
    return this->scale_in_ARM;
}

int Scheme::get_fonts_number(){
    return this->fonts_number;
}

int Scheme::get_objects_number(){
    return this->objects_number;
}

int Scheme::get_groups_number(){
    this->groups_number;
}

std::string Scheme::get_name_scheme(){
    return this->name_scheme;
}

std::string Scheme::get_file_path(){
    return this->file_path;
}

std::string Scheme::get_bd_name(){
    return this->bd_name;
}

std::string Scheme::get_server(){
    return this->server;
}

void Scheme::draw_line(FiguresClasses::Line &pol, QPainter &painter){
    QColor color_line = {pol.get_line_color()[0], pol.get_line_color()[1], pol.get_line_color()[2]};
    painter.setPen(QPen(color_line, pol.get_line_width(), this->style_vector[pol.get_style_line()], Qt::RoundCap));
    painter.drawLine(pol.get_st_x(), pol.get_st_y(), pol.get_end_x(), pol.get_end_y());
    if(pol.get_start_style_arrow() == 1){
        painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_start_style_arrow() == 2){
        painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_start_style_arrow() == 3){
        painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_start_style_arrow() == 4){
        painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }
    if(pol.get_end_style_arrow() == 1){
        painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_end_style_arrow() == 2){
        painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_end_style_arrow() == 3){
        painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }else if(pol.get_end_style_arrow() == 4){
        painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2, pol.get_line_width(), pol.get_line_width());
    }
}

void Scheme::draw_rect(FiguresClasses::Rectangle &rect, QPainter &painter){
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
        painter.setPen(QPen(color_rect, rect.get_line_width(), this->style_vector[rect.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(QRect((-1)*(rect.get_width()/2), (-1)*(rect.get_height()/2), rect.get_width(), rect.get_height()));
    }
    painter.restore();
}


void Scheme::draw_ellipse(FiguresClasses::Ellipse &el, QPainter &painter){
    //начинаем отрисовку эллипса
    painter.save();
    painter.translate(el.get_center_x(), el.get_center_y());
    painter.rotate((-1)*el.get_angle());
    if (el.get_show()){
        QColor color_el = {el.get_line_color()[0], el.get_line_color()[1], el.get_line_color()[2]};
        if (el.get_show_filling()){
            QColor filling_color = {el.get_filling_color()[0], el.get_filling_color()[1], el.get_filling_color()[2]};
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(color_el, el.get_line_width(), this->style_vector[el.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawEllipse(QRect((-1)*(el.get_width()/2), (-1)*(el.get_height()/2), el.get_width(), el.get_height()));
    }
    painter.restore();
}


void Scheme::draw_arc(FiguresClasses::Arc &arc, QPainter &painter){
    //начинаем отрисовку дуги
    painter.save();
    painter.translate(arc.get_center_x(), arc.get_center_y());
    painter.rotate((-1)*arc.get_angle());
    if (arc.get_show()){
        QColor color_arc = {arc.get_line_color()[0], arc.get_line_color()[1], arc.get_line_color()[2]};
        painter.setPen(QPen(color_arc, arc.get_line_width(), this->style_vector[arc.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        if (arc.get_show_filling()){
            QColor filling_color = {arc.get_filling_color()[0], arc.get_filling_color()[1], arc.get_filling_color()[2]};
            painter.setBrush(filling_color);
            painter.drawPie(QRect((-1)*(arc.get_width()/2), (-1)*(arc.get_height()/2), arc.get_width(), arc.get_height()), ((360 - arc.get_start_angle())%360)*(-16), ((360 - arc.get_end_angle())%360)*(-16));
        }else{
            painter.drawArc(QRect((-1)*(arc.get_width()/2), (-1)*(arc.get_height()/2), arc.get_width(), arc.get_height()), ((360 - arc.get_start_angle())%360)*(-16), ((360 - arc.get_end_angle())%360)*(-16));
        }
    }
    painter.restore();
}

void Scheme::draw_polygon(FiguresClasses::Polygon &poly, QPainter &painter){
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
        painter.setPen(QPen(color_poly, poly.get_line_width(), this->style_vector[poly.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        QPoint qpoints[poly.get_points().size()];
        for (int i = 0; i < poly.get_points().size(); i++){
            qpoints[i] = QPoint(poly.get_points()[i][0] - poly.get_center_x(), poly.get_points()[i][1] - poly.get_center_y());
        }
        if(poly.get_end_polygon()){
            painter.drawPolygon(qpoints, poly.get_points().size());
        }else{
            painter.drawPolyline(qpoints, poly.get_points().size());
        }
    }
    painter.restore();
}

void Scheme::draw_crooked_line(FiguresClasses::CrookedLine &crook, QPainter &painter){
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
        painter.setPen(QPen(color_crook, crook.get_line_width(), this->style_vector[crook.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        QPoint qpoints[crook.get_points().size()];
        for (int i = 0; i < crook.get_points().size(); i++){
            qpoints[i] = QPoint(crook.get_points()[i][0] - crook.get_center_x(), crook.get_points()[i][1] - crook.get_center_y());
        }
        painter.drawPolyline(qpoints, crook.get_points().size());
    }
    painter.restore();
}

void Scheme::draw_text(FiguresClasses::Text &text, QPainter &painter){
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if(text.get_auto_size_text()){
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width()/2 - 2, text.get_y() - text.get_line_width()/2 - 2, pxwidth + text.get_line_width() + 5, pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1)*text.get_angle());
    if(text.get_show()){
        if (text.get_show_filling()){
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1], text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), this->style_vector[text.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, this->h_alignment_vector[text.get_hAlignment()]|this->v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_image(FiguresClasses::Image &image, QPainter &painter){
    //начало отображения картинки
    painter.save();
    painter.translate(image.get_center_x(), image.get_center_y());
    painter.rotate((-1)*image.get_angle());
    if(image.get_show()){
        QRect target(image.get_x() - image.get_center_x(), image.get_y() - image.get_center_y(), image.get_width(), image.get_height());
        QRect source(0, 0, 0, 0);
        QPixmap pixmap(image.get_image_path().c_str());
        painter.drawPixmap(target, pixmap, source);
    }
    painter.restore();
}

void Scheme::draw_transition_point(FiguresClasses::TransitionPoint &tr_p, QPainter &painter){
    //начало отображения точки перехода
    if(tr_p.get_show()){
        if (tr_p.get_show_filling()){
            QColor filling_color = {tr_p.get_filling_color()[0], tr_p.get_filling_color()[1], tr_p.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(QRect(tr_p.get_x(), tr_p.get_y(), tr_p.get_width(), tr_p.get_height()));
        painter.drawEllipse(QPoint(tr_p.get_center_x(), tr_p.get_center_y()), 3, 3);
    }
}

void Scheme::draw_transition_button(FiguresClasses::TransitionButton &tr_b, QPainter &painter){
    //начало отображения кнопки перехода
    painter.save();
    QFont tr_b_font(tr_b.get_font_name().c_str(), tr_b.get_font_size());
    tr_b_font.setBold(tr_b.get_bold_font());
    tr_b_font.setItalic(tr_b.get_italic_font());
    tr_b_font.setUnderline(tr_b.get_underlined_font());
    tr_b_font.setStrikeOut(tr_b.get_crossed_font());
    if(tr_b.get_auto_size_text()){
        QFontMetrics fm(tr_b_font);
        int pxwidth = fm.width(tr_b.get_text().c_str());
        int pxheight = fm.height();
        tr_b.change_center_cords(tr_b.get_x() - 4, tr_b.get_y() - 4, pxwidth + 7, pxheight + 7);
    }
    painter.translate(tr_b.get_center_x(), tr_b.get_center_y());
    painter.rotate((-1)*tr_b.get_angle());
    if(tr_b.get_show()){
        if (tr_b.get_show_filling()){
            QColor filling_color = {tr_b.get_filling_color()[0], tr_b.get_filling_color()[1], tr_b.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect(0, 0, 0);
        painter.setPen(QPen(color_rect, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(tr_b.get_x() - tr_b.get_center_x(), tr_b.get_y() - tr_b.get_center_y(), tr_b.get_width(), tr_b.get_height());
        QRect rect = QRect(tr_b.get_x() - tr_b.get_center_x(), tr_b.get_y() - tr_b.get_center_y(), tr_b.get_width(), tr_b.get_height());
        QColor font_color = {tr_b.get_font_color()[0], tr_b.get_font_color()[1], tr_b.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(tr_b_font);
        painter.drawText(rect, this->h_alignment_vector[tr_b.get_hAlignment()]|this->v_alignment_vector[tr_b.get_vAlignment()], tr_b.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_set(QPainter &painter){
    QColor color_set = {200, 200, 200};
    painter.setPen(QPen(color_set, 1, Qt::DashLine, Qt::RoundCap));
    for (int i = 0; i < this->width; i+=10){
        painter.drawLine(i, 0, i, this->height);
    }
    for (int i = 0; i < this->height; i+=10){
        painter.drawLine(0, i, this->width, i);
    }
}

void Scheme::draw_telecontrol(FiguresClasses::Telecontrol &text, QPainter &painter){
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if(text.get_auto_size_text()){
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width()/2 - 2, text.get_y() - text.get_line_width()/2 - 2, pxwidth + text.get_line_width() + 5, pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1)*text.get_angle());
    if(text.get_show()){
        if (text.get_show_filling()){
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1], text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), this->style_vector[text.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, this->h_alignment_vector[text.get_hAlignment()]|this->v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_telemeasure(FiguresClasses::Telemeasure &text, QPainter &painter){
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if(text.get_auto_size_text()){
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width()/2 - 2, text.get_y() - text.get_line_width()/2 - 2, pxwidth + text.get_line_width() + 5, pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1)*text.get_angle());
    if(text.get_show()){
        if (text.get_show_filling()){
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1], text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), this->style_vector[text.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, this->h_alignment_vector[text.get_hAlignment()]|this->v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_telesignalisation(FiguresClasses::Telesignalisation &text, QPainter &painter){
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if(text.get_auto_size_text()){
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width()/2 - 2, text.get_y() - text.get_line_width()/2 - 2, pxwidth + text.get_line_width() + 5, pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1)*text.get_angle());
    if(text.get_show()){
        if (text.get_show_filling()){
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1], text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), this->style_vector[text.get_style_line()], Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(), text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, this->h_alignment_vector[text.get_hAlignment()]|this->v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_scheme(QPainter &painter){
    this->draw_set(painter);
    for (int i = 0; i < this->line_vector.size(); i++){
        this->draw_line(line_vector[i], painter);
    }
    for (int i = 0; i < this->rectangle_vector.size(); i++){
        this->draw_rect(rectangle_vector[i], painter);
    }
    for (int i = 0; i < this->ellipse_vector.size(); i++){
        this->draw_ellipse(ellipse_vector[i], painter);
    }
    for (int i = 0; i < this->arc_vector.size(); i++){
        this->draw_arc(arc_vector[i], painter);
    }
    for (int i = 0; i < this->line_vector.size(); i++){
        this->draw_line(line_vector[i], painter);
    }
    for (int i = 0; i < this->polygon_vector.size(); i++){
        this->draw_polygon(polygon_vector[i], painter);
    }
    for (int i = 0; i < this->crooked_line_vector.size(); i++){
        this->draw_crooked_line(crooked_line_vector[i], painter);
    }
    for (int i = 0; i < this->text_vector.size(); i++){
        this->draw_text(text_vector[i], painter);
    }
    for (int i = 0; i < this->image_vector.size(); i++){
        this->draw_image(image_vector[i], painter);
    }
    for (int i = 0; i < this->tr_p_vector.size(); i++){
        this->draw_transition_point(tr_p_vector[i], painter);
    }
    for (int i = 0; i < this->tr_b_vector.size(); i++){
        this->draw_transition_button(tr_b_vector[i], painter);
    }
    for (int i = 0; i < this->telecontrol_vector.size(); i++){
        this->draw_telecontrol(telecontrol_vector[i], painter);
    }
    for (int i = 0; i < this->telemeasure_vector.size(); i++){
        this->draw_telemeasure(telemeasure_vector[i], painter);
    }
    for (int i = 0; i < this->telesignalisation_vector.size(); i++){
        this->draw_telesignalisation(telesignalisation_vector[i], painter);
    }
}





