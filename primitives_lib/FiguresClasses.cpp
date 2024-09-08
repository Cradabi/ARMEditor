#include "FiguresClasses.h"
#include <QDebug>

using namespace FiguresClasses;

Primitive::Primitive() = default;

void Primitive::draw(QPainter& painter) {
}

void Primitive::set_help_text(const std::string& help) {
    this->help_text = help;
}

std::string Primitive::get_type_object() {
    return this->type_object;
}

std::string Primitive::get_help_text() {
    return this->help_text;
}

int Primitive::get_angle() {
    return this->angle;
}

int Primitive::get_x() {
    return this->x;
}

int Primitive::get_y() {
    return this->y;
}

int Primitive::get_width() {
    return this->width;
}

int Primitive::get_height() {
    return this->height;
}

int Primitive::get_center_x() {
    return this->center_x;
}

int Primitive::get_center_y() {
    return this->center_y;
}

//далее идут функции меняющие настройки показывания различных элементов
void Primitive::show_help() {
    this->bool_show_help = true;
}

void Primitive::show() {
    this->bool_show = true;
}

void Primitive::hide_help() {
    this->bool_show_help = false;
}

void Primitive::hide() {
    this->bool_show = false;
}

bool Primitive::get_show_help() {
    return this->bool_show_help;
}

bool Primitive::get_show() {
    return this->bool_show;
}

uint32_t Primitive::get_id() {
    return this->id;
}

void Primitive::set_id(int id_c) {
    this->id = id_c;
}


std::string Primitive::get_library_name() {
    if (type_object == "Библиотечный объект") {
        return library_name;
    }
    return "Не библиотечный объект";
}

std::string Primitive::get_object_name() {
    if (type_object == "Библиотечный объект") {
        return object_name;
    }
    return "Не библиотечный объект";
}

std::string Primitive::get_text() {
    return this->text;
}

std::vector<std::vector<Primitive*> > Primitive::get_patterns() {
    return patterns;
}

void Primitive::set_condition(int cond) {
    condition = cond;
}

void Primitive::set_text(const std::string& text) {
    this->text = text;
}


//конструкторы класса линии получающие различные вводные
Line::Line(int st_x, int st_y, int end_x, int end_y, int hor_mirror, int vert_mirror, int angle)
    : Primitive::Primitive() {
    this->type_object = "Линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    this->angle = angle;
    change_center_cords(st_x, st_y, end_x, end_y);
}

Line::Line(int st_x, int st_y, int end_x, int end_y, const std::string& text, const std::string& help_text,
           bool bool_show, int style_line, int number_of_text, int line_width, int start_style_arrow,
           int end_style_arrow, const std::vector<int>& line_color, int hor_mirror, int vert_mirror, int angle)
    : Primitive::Primitive() {
    this->text = text;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->style_line = style_line;
    this->number_of_text = number_of_text;
    this->line_width = line_width;
    this->start_style_arrow = start_style_arrow;
    this->end_style_arrow = end_style_arrow;
    this->line_color = line_color;
    this->type_object = "Линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    this->angle = angle;
    change_center_cords(st_x, st_y, end_x, end_y);
}

Line::Line(int st_x, int st_y, int end_x, int end_y, const std::string& text, const std::string& help_text,
           bool bool_show, int style_line, int number_of_text, int line_width, int start_style_arrow,
           int end_style_arrow, const std::vector<int>& line_color, const std::string& font_name,
           int font_size, const std::vector<int>& font_color, int hor_mirror, int vert_mirror, int angle)
    : Primitive::Primitive() {
    this->text = text;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->style_line = style_line;
    this->number_of_text = number_of_text;
    this->line_width = line_width;
    this->start_style_arrow = start_style_arrow;
    this->end_style_arrow = end_style_arrow;
    this->line_color = line_color;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->type_object = "Линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    this->angle = angle;
    change_center_cords(st_x, st_y, end_x, end_y);
}

Line::Line(int st_x, int st_y, int end_x, int end_y, const std::string& text, const std::string& help_text,
           bool bool_show, int style_line, int number_of_text, int line_width, int start_style_arrow,
           int end_style_arrow, const std::vector<int>& line_color, const std::string& font_name,
           int font_size, const std::vector<int>& font_color, bool bold_font, bool italic_font, bool underlined_font,
           bool crossed_font, int hor_mirror, int vert_mirror, int angle) : Primitive::Primitive() {
    this->text = text;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->style_line = style_line;
    this->number_of_text = number_of_text;
    this->line_width = line_width;
    this->start_style_arrow = start_style_arrow;
    this->end_style_arrow = end_style_arrow;
    this->line_color = line_color;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->type_object = "Линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    this->angle = angle;
    change_center_cords(st_x, st_y, end_x, end_y);
}

void Line::draw(QPainter& painter) {
    painter.save();
    painter.translate(this->get_center_cord_x(), this->get_center_cord_y());
    painter.rotate(this->angle);
    QColor color_line = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
    QLineF linef(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                 this->get_end_x() - this->get_center_cord_x(), this->get_end_y() - this->get_center_cord_y());
    switch (this->get_start_style_arrow()) {
        case 0: {
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            break;
        }
        case 1: {
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_st_x() - this->get_center_cord_x(),
                              this->get_st_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()));
            if (this->get_line_width() == 1) {
                painter.rotate(15);
                painter.drawLine(0, 0, this->get_line_width() * 10, 0);
                painter.rotate(-30);
                painter.drawLine(0, 0, this->get_line_width() * 10, 0);
            } else {
                painter.rotate(15);
                painter.drawLine(0, 0, this->get_line_width() * 5, 0);
                painter.rotate(-30);
                painter.drawLine(0, 0, this->get_line_width() * 5, 0);
            }
            painter.restore();
        }
        break;
        case 2: {
            painter.setPen(QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::FlatCap,
                                Qt::MiterJoin));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_st_x() - this->get_center_cord_x(),
                              this->get_st_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()));
            painter.setBrush(color_line);
            if (this->get_line_width() * 3 >= 10 && this->get_line_width() / 2 >= 4) {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width() * 3, this->get_line_width() / 2),
                    QPoint(this->get_line_width() * 3, (-1) * (this->get_line_width() / 2))
                };
                painter.drawPolygon(qpoints1, 3);
            } else {
                QPoint qpoints1[3] = {QPoint(0, 0), QPoint(10, 4), QPoint(10, -4)};
                painter.drawPolygon(qpoints1, 3);
            }

            painter.restore();
        }
        break;
        case 3: {
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.setBrush(color_line);
            if (this->get_line_width() == 1) {
                painter.drawEllipse(this->get_st_x() - this->get_center_cord_x() - this->get_line_width() / 2,
                                    this->get_st_y() - this->get_center_cord_y() - this->get_line_width() / 2,
                                    this->get_line_width() * 2, this->get_line_width() * 2);
            } else {
                painter.drawEllipse(this->get_st_x() - this->get_center_cord_x() - this->get_line_width() / 2,
                                    this->get_st_y() - this->get_center_cord_y() - this->get_line_width() / 2,
                                    this->get_line_width(), this->get_line_width());
            }
        }
        break;
        case 4: {
            painter.setPen(QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::FlatCap,
                                Qt::MiterJoin));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_st_x() - this->get_center_cord_x(),
                              this->get_st_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()));
            painter.setBrush(color_line);
            if (this->get_line_width() == 1) {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width() * 3, this->get_line_width() * 3),
                    QPoint(this->get_line_width() * 3, (-3) * (this->get_line_width()))
                };
                painter.drawPolygon(qpoints1, 3);
            } else {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width(), this->get_line_width()),
                    QPoint(this->get_line_width(), (-1) * (this->get_line_width()))
                };
                painter.drawPolygon(qpoints1, 3);
            }

            painter.restore();
        }
        break;
    };
    switch (this->get_end_style_arrow()) {
        case 0:
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            break;
        case 1: {
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_end_x() - this->get_center_cord_x(),
                              this->get_end_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()) + 180);
            if (this->get_line_width() == 1) {
                painter.rotate(15);
                painter.drawLine(0, 0, this->get_line_width() * 10, 0);
                painter.rotate(-30);
                painter.drawLine(0, 0, this->get_line_width() * 10, 0);
            } else {
                painter.rotate(15);
                painter.drawLine(0, 0, this->get_line_width() * 5, 0);
                painter.rotate(-30);
                painter.drawLine(0, 0, this->get_line_width() * 5, 0);
            }

            painter.restore();
        }
        break;
        case 2: {
            painter.setPen(QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::FlatCap,
                                Qt::MiterJoin));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_end_x() - this->get_center_cord_x(),
                              this->get_end_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()) + 180);
            painter.setBrush(color_line);
            if (this->get_line_width() * 3 >= 10 && this->get_line_width() / 2 >= 4) {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width() * 3, this->get_line_width() / 2),
                    QPoint(this->get_line_width() * 3, (-1) * (this->get_line_width() / 2))
                };
                painter.drawPolygon(qpoints1, 3);
            } else {
                QPoint qpoints1[3] = {QPoint(0, 0), QPoint(10, 4), QPoint(10, -4)};
                painter.drawPolygon(qpoints1, 3);
            }
            painter.restore();
        }
        break;
        case 3:
            painter.setPen(
                QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.setBrush(color_line);
            if (this->get_line_width() == 1) {
                painter.drawEllipse(this->get_st_x() - this->get_center_cord_x() - this->get_line_width() / 2,
                                    this->get_st_y() - this->get_center_cord_y() - this->get_line_width() / 2,
                                    this->get_line_width() * 2, this->get_line_width() * 2);
            } else {
                painter.drawEllipse(this->get_st_x() - this->get_center_cord_x() - this->get_line_width() / 2,
                                    this->get_st_y() - this->get_center_cord_y() - this->get_line_width() / 2,
                                    this->get_line_width(), this->get_line_width());
            }
            break;
        case 4: {
            painter.setPen(QPen(color_line, this->get_line_width(), style_vector[this->get_style_line()], Qt::FlatCap,
                                Qt::MiterJoin));
            painter.drawLine(this->get_st_x() - this->get_center_cord_x(), this->get_st_y() - this->get_center_cord_y(),
                             this->get_end_x() - this->get_center_cord_x(),
                             this->get_end_y() - this->get_center_cord_y());
            painter.save();
            painter.translate(this->get_end_x() - this->get_center_cord_x(),
                              this->get_end_y() - this->get_center_cord_y());
            painter.rotate(-1 * (linef.angle()) + 180);
            painter.setBrush(color_line);
            if (this->get_line_width() == 1) {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width() * 3, this->get_line_width() * 3),
                    QPoint(this->get_line_width() * 3, (-3) * (this->get_line_width()))
                };
                painter.drawPolygon(qpoints1, 3);
            } else {
                QPoint qpoints1[3] = {
                    QPoint(0, 0), QPoint(this->get_line_width(), this->get_line_width()),
                    QPoint(this->get_line_width(), (-1) * (this->get_line_width()))
                };
                painter.drawPolygon(qpoints1, 3);
            }
            painter.restore();
        }
        break;
    }
    painter.restore();
}

//меняет координаты начала, конца, центра линии
void Line::change_center_cords(int st_x, int st_y, int end_x,
                               int end_y) {
    this->start_x = st_x;
    this->start_y = st_y;
    this->end_x = end_x;
    this->end_y = end_y;

    int x_cord = 0;
    int y_cord = 0;

    //начало изменений координат центра
    if (st_x >= end_x) {
        x_cord = end_x + floor(abs(st_x - end_x) / 2);
    } else {
        x_cord = st_x + floor(abs(st_x - end_x) / 2);
    }
    if (st_y >= end_y) {
        y_cord = end_y + floor(abs(st_y - end_y) / 2);
    } else {
        y_cord = st_y + floor(abs(st_y - end_y) / 2);
    }

    this->center_x = x_cord;
    this->center_y = y_cord;
}

//далее идут функции меняющие одноименные переменные класса линии
void Line::set_line_color(const std::vector<int>& lin_col) {
    this->line_color = lin_col;
}

void Line::set_line_width(int width) {
    this->line_width = width;
}

void Line::set_start_style_arrow(int st_arrow) {
    this->start_style_arrow = st_arrow;
}

void Line::set_end_style_arrow(int end_arrow) {
    this->end_style_arrow = end_arrow;
}

void Line::set_hor_mirror(bool hor_mirror) {
    this->horizontal_mirror = hor_mirror;
}

void Line::set_vert_mirror(bool vert_mirror) {
    this->vertical_mirror = vert_mirror;
}

void Line::set_text(const std::string& text) {
    this->text = text;
}

void Line::set_font_name(const std::string& fn_name) {
    this->font_name = fn_name;
}

void Line::set_font_size(int fn_size) {
    this->font_size = fn_size;
}

void Line::set_font_color(const std::vector<int>& fn_col) {
    this->font_color = fn_col;
}

void Line::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void Line::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void Line::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void Line::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void Line::set_font(const std::string& font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void Line::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
Line::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color, bool bold_font,
               bool italic_font,
               bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}

//далее идут функции по выводу одноименных переменных класса линии
std::vector<int> Line::get_line_color() {
    return this->line_color;
}

int Line::get_line_width() {
    return this->line_width;
}

int Line::get_start_style_arrow() {
    return this->start_style_arrow;
}

int Line::get_end_style_arrow() {
    return this->end_style_arrow;
}

int Line::get_style_line() {
    return this->style_line;
}

int Line::get_st_x() {
    //выводит координату x начала линии
    return this->start_x;
}

int Line::get_st_y() {
    //выводит координату y начала линии
    return this->start_y;
}

int Line::get_end_x() {
    //выводит координату x конца линии
    return this->end_x;
}

int Line::get_end_y() {
    //выводит координату y конца линии
    return this->end_y;
}

int Line::get_center_cord_x() {
    //возвращает x-координату центра
    return this->center_x;
}

int Line::get_center_cord_y() {
    //возвращает y-координату центра
    return this->center_y;
}

bool Line::get_hor_mirror() {
    return this->horizontal_mirror;
}

bool Line::get_vert_mirror() {
    return this->vertical_mirror;
}

int Line::get_font_size() {
    return this->font_size;
}

std::string Line::get_font_name() {
    return this->font_name;
}

bool Line::get_bold_font() {
    return this->bold_font;
}

bool Line::get_italic_font() {
    return this->italic_font;
}

bool Line::get_crossed_font() {
    return this->crossed_font;
}

bool Line::get_underlined_font() {
    return this->underlined_font;
}


std::vector<int> Line::get_font_color() {
    return this->font_color;
}

//конструкторы класса прямоугольника получающие различные вводные
Rectangle::Rectangle(int x, int y, int width, int height, int hor_mirror, int vert_mirror) : Primitive::Primitive() {
    this->type_object = "Прямоугольник";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Rectangle::Rectangle(int x, int y, int width, int height, int angle, int line_width, int style_line,
                     const std::vector<int>& line_color, const std::string& help_text, bool bool_show, int hor_mirror,
                     int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->type_object = "Прямоугольник";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Rectangle::Rectangle(int x, int y, int width, int height, int angle, int line_width, int style_line,
                     const std::vector<int>& line_color, const std::string& help_text, bool bool_show, int style_frame,
                     int style_gradient_filling, const std::vector<int>& filling_color, bool bool_show_filling,
                     int hor_mirror, int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->style_frame = style_frame;
    this->style_gradient_filling = style_gradient_filling;
    this->filling_color = filling_color;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Прямоугольник";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

void Rectangle::draw(QPainter& painter) {
    //начинаем отрисовку прямоугольника
    painter.save();
    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());

    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        painter.setPen(QPen(color_rect, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(QRect((-1) * (this->get_width() / 2), (-1) * (this->get_height() / 2), this->get_width(),
                               this->get_height()));
    }
    painter.restore();
}

//меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
void Rectangle::change_center_cords(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса прямоугольника
void Rectangle::set_angle(int angl) {
    this->angle = angl;
}

void Rectangle::set_line_width(int width) {
    this->line_width = width;
}

void Rectangle::set_line_color(const std::vector<int>& ln_col) {
    this->line_color = ln_col;
}

void Rectangle::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}

void Rectangle::set_style_frame(int st_frame) {
    if (st_frame >= 0 && st_frame < this->style_frame_list.size()) {
        this->style_frame = st_frame;
    }
}

void Rectangle::set_style_gradient_filling(int st_gradient) {
    if (st_gradient >= 0 && st_gradient < this->style_gradient_list.size()) {
        this->style_gradient_filling = st_gradient;
    }
}

void Rectangle::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

void Rectangle::set_hor_mirror(bool hor_mirror) {
    this->horizontal_mirror = hor_mirror;
}

void Rectangle::set_vert_mirror(bool vert_mirror) {
    this->vertical_mirror = vert_mirror;
}

//далее идут функции по выводу одноименных переменных класса прямоугольника
int Rectangle::get_style_frame() {
    return this->style_frame;
}

int Rectangle::get_line_width() {
    return this->line_width;
}

int Rectangle::get_style_line() {
    return this->style_line;
}

int Rectangle::get_style_gradient_filling() {
    return this->style_gradient_filling;
}

bool Rectangle::get_hor_mirror() {
    return this->horizontal_mirror;
}

bool Rectangle::get_vert_mirror() {
    return this->vertical_mirror;
}

std::vector<int> Rectangle::get_line_color() {
    return this->line_color;
}

std::vector<int> Rectangle::get_filling_color() {
    return this->filling_color;
}

void Rectangle::show_filling() {
    this->bool_show_filling = true;
}

void Rectangle::hide_filling() {
    this->bool_show_filling = false;
}

bool Rectangle::get_show_filling() {
    return this->bool_show_filling;
}

//конструкторы класса эллипса получающие различные вводные
Ellipse::Ellipse() : Primitive::Primitive() {
}

Ellipse::Ellipse(int x, int y, int width, int height, int angle, int hor_mirror, int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->type_object = "Эллипс";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Ellipse::Ellipse(int x, int y, int width, int height, int angle, int line_width, int style_line,
                 const std::vector<int>& line_color, const std::string& help_text, bool bool_show, int hor_mirror,
                 int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->type_object = "Эллипс";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Ellipse::Ellipse(int x, int y, int width, int height, int angle, int line_width, int style_line,
                 const std::vector<int>& line_color, const std::string& help_text, bool bool_show,
                 const std::vector<int>& filling_color, bool bool_show_filling, int hor_mirror, int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->filling_color = filling_color;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Эллипс";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

void Ellipse::draw(QPainter& painter) {
    //начинаем отрисовку эллипса
    painter.save();
    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        QColor color_el = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(color_el, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawEllipse(
            QRect((-1) * (this->get_width() / 2), (-1) * (this->get_height() / 2), this->get_width(),
                  this->get_height()));
    }
    painter.restore();
}

void
Ellipse::change_center_cords(int x, int y, int width,
                             int height) {
    //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса эллипса
void Ellipse::set_angle(int angl) {
    this->angle = angl;
}

void Ellipse::set_line_width(int line_width) {
    this->line_width = line_width;
}

void Ellipse::set_hor_mirror(bool hor_mirror) {
    this->horizontal_mirror = hor_mirror;
}

void Ellipse::set_vert_mirror(bool vert_mirror) {
    this->vertical_mirror = vert_mirror;
}

void Ellipse::set_line_color(const std::vector<int>& ln_col) {
    this->line_color = ln_col;
}

void Ellipse::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}


void Ellipse::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

//далее идут функции по выводу одноименных переменных класса эллипса
int Ellipse::get_style_line() {
    return this->style_line;
}

int Ellipse::get_line_width() {
    return this->line_width;
}

bool Ellipse::get_hor_mirror() {
    return this->horizontal_mirror;
}

bool Ellipse::get_vert_mirror() {
    return this->vertical_mirror;
}

std::vector<int> Ellipse::get_line_color() {
    return this->line_color;
}

std::vector<int> Ellipse::get_filling_color() {
    return this->filling_color;
}

//далее идут функции меняющие настройки показывания различных элементов
void Ellipse::show_filling() {
    this->bool_show_filling = true;
}

void Ellipse::hide_filling() {
    this->bool_show_filling = false;
}

bool Ellipse::get_show_filling() {
    return this->bool_show_filling;
}

//конструкторы класса дуги получающие различные вводные
Arc::Arc(int x, int y, int width, int height, int angle, int st_angle, int end_angle, int hor_mirror, int vert_mirror)
    : Ellipse::Ellipse() {
    this->type_object = "Дуга";
    this->start_angle = st_angle;
    this->end_angle = end_angle;
    this->angle = angle;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Arc::Arc(int x, int y, int width, int height, int angle, int st_angle, int end_angle, int line_width, int style_line,
         const std::vector<int>& line_color, const std::string& help_text, bool bool_show, int hor_mirror,
         int vert_mirror) : Ellipse::Ellipse() {
    this->type_object = "Дуга";
    this->start_angle = st_angle;
    this->end_angle = end_angle;
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

Arc::Arc(int x, int y, int width, int height, int angle, int st_angle, int end_angle, int line_width, int style_line,
         const std::vector<int>& line_color, const std::string& help_text, bool bool_show,
         const std::vector<int>& filling_color, bool bool_show_filling, int hor_mirror, int vert_mirror)
    : Ellipse::Ellipse() {
    this->type_object = "Дуга";
    this->start_angle = st_angle;
    this->end_angle = end_angle;
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->filling_color = filling_color;
    this->bool_show_filling = bool_show_filling;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(x, y, width, height);
}

void Arc::draw(QPainter& painter) {
    //начинаем отрисовку дуги
    painter.save();
    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        QColor color_arc = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        painter.setPen(QPen(color_arc, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setBrush(filling_color);
            painter.drawPie(QRect((-1) * (this->get_width() / 2), (-1) * (this->get_height() / 2), this->get_width(),
                                  this->get_height()), ((360 - this->get_start_angle()) % 360) * (-16),
                            ((360 - (this->end_angle - this->start_angle)) % 360) * (-16));
        } else {
            QColor color_arc = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
            QColor filling_color = {Qt::transparent};
            painter.setPen(QPen(color_arc, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap, Qt::RoundJoin));
            painter.setBrush(filling_color);
            painter.drawArc(QRect((-1) * (this->get_width() / 2), (-1) * (this->get_height() / 2), this->get_width(),
                                  this->get_height()), ((360 - this->get_start_angle()) % 360) * (-16),
                            ((360 - (this->end_angle - this->start_angle)) % 360) * (-16));
        }
    }
    painter.restore();
}

//далее идут функции меняющие одноименные переменные класса дуги
void Arc::set_arc_angles(int start_angle, int end_angle) {
    this->start_angle = start_angle;
    this->end_angle = end_angle;
}

void Arc::set_start_angle(int st_angle) {
    this->start_angle = st_angle;
}

void Arc::set_end_angle(int end_angle) {
    this->end_angle = end_angle;
}

//далее идут функции по выводу одноименных переменных класса дуги
int Arc::get_start_angle() {
    return this->start_angle;
}

int Arc::get_end_angle() {
    return this->end_angle;
}

std::vector<int> Arc::get_arc_angles() {
    return {this->start_angle, this->end_angle};
}

//конструкторы класса кривой линии получающие различные вводные
CrookedLine::CrookedLine() : Primitive::Primitive() {
}

CrookedLine::CrookedLine(const std::vector<std::vector<int> >& points_vector, int hor_mirror, int vert_mirror)
    : Primitive::Primitive() {
    this->type_object = "Кривая линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(points_vector);
}

CrookedLine::CrookedLine(const std::vector<std::vector<int> >& points_vector, int angle, int line_width, int style_line,
                         const std::string& help_text, const std::vector<int>& line_color,
                         const std::vector<int>& filling_color, bool bool_show, bool bool_show_filling, int hor_mirror,
                         int vert_mirror)
    : Primitive::Primitive() {
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->help_text = help_text;
    this->line_color = line_color;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Кривая линия";
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(points_vector);
}

void CrookedLine::draw(QPainter& painter) {
    //начинаем отрисовку кривой
    painter.save();
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setBrush(filling_color);
        }
        QColor color_crook = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        painter.setPen(
            QPen(color_crook, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap,
                 Qt::RoundJoin));
        QPoint qpoints[this->get_points().size()];
        for (int i = 0; i < this->get_points().size(); i++) {
            qpoints[i] = QPoint(this->get_points()[i][0],
                                this->get_points()[i][1]);
        }
        qDebug() << "Polyline";
        painter.drawPolyline(qpoints, this->get_points().size());
    }
    painter.restore();
}

void
CrookedLine::change_center_cords(
    const std::vector<std::vector<int> >& points_vector) {
    //меняет координаты начала, конца, центра многоугольника. Эта функция нужня для изменения размеров.

    if (!points_vector.size())
        return;

    this->points = points_vector;
    int max_x = 0;
    int max_y = 0;
    int min_x = points_vector[0][0];
    int min_y = points_vector[0][1];
    for (int i = 0; i < points_vector.size(); i++) {
        if (points_vector[i][0] < min_x) {
            min_x = points_vector[i][0];
        }
        if (points_vector[i][0] > max_x) {
            max_x = points_vector[i][0];
        }
        if (points_vector[i][1] < min_y) {
            min_y = points_vector[i][1];
        }
        if (points_vector[i][1] > max_y) {
            max_y = points_vector[i][1];
        }
    }
    this->x = min_x;
    this->y = min_y;
    this->width = max_x - min_x;
    this->height = max_y - min_y;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса кривой линии
void CrookedLine::set_angle(int angl) {
    this->angle = angl;
}

void CrookedLine::set_hor_mirror(bool hor_mirror) {
    this->horizontal_mirror = hor_mirror;
}

void CrookedLine::set_vert_mirror(bool vert_mirror) {
    this->vertical_mirror = vert_mirror;
}

void CrookedLine::set_line_color(const std::vector<int>& ln_col) {
    this->line_color = ln_col;
}

void CrookedLine::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}

void CrookedLine::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

//далее идут функции по выводу одноименных переменных класса кривой линии
int CrookedLine::get_style_line() {
    return this->style_line;
}

bool CrookedLine::get_hor_mirror() {
    return this->horizontal_mirror;
}

bool CrookedLine::get_vert_mirror() {
    return this->vertical_mirror;
}

int CrookedLine::get_line_width() {
    return this->line_width;
}

std::vector<int> CrookedLine::get_line_color() {
    return this->line_color;
}

std::vector<int> CrookedLine::get_filling_color() {
    return this->filling_color;
}

std::vector<std::vector<int> > CrookedLine::get_points() {
    return this->points;
}

//далее идут функции меняющие настройки показывания различных элементов
void CrookedLine::show_filling() {
    this->bool_show_filling = true;
}

void CrookedLine::hide_filling() {
    this->bool_show_filling = false;
}

bool CrookedLine::get_show_filling() {
    return this->bool_show_filling;
}

//конструкторы класса многоугольника получающие различные вводные
Polygon::Polygon(const std::vector<std::vector<int> >& points_vector, bool end_polygon, int hor_mirror, int vert_mirror)
    : CrookedLine::CrookedLine() {
    this->type_object = "Полигон";
    this->end_polygone = end_polygon;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(points_vector);
}

Polygon::Polygon(const std::vector<std::vector<int> >& points_vector, bool end_polygon, int angle, int line_width,
                 int style_line, const std::string& help_text, const std::vector<int>& line_color,
                 const std::vector<int>& filling_color, bool bool_show, bool bool_show_filling, int hor_mirror,
                 int vert_mirror)
    : CrookedLine::CrookedLine() {
    this->type_object = "Полигон";
    this->end_polygone = end_polygon;
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->help_text = help_text;
    this->line_color = line_color;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(points_vector);
}

void Polygon::draw(QPainter& painter) {
    //начинаем отрисовку полигона
    painter.save();
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_poly = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        painter.setPen(QPen(color_poly, this->get_line_width(), style_vector[this->get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        QPoint qpoints[this->get_points().size()];
        for (int i = 0; i < this->get_points().size(); i++) {
            qpoints[i] = QPoint(this->get_points()[i][0],
                                this->get_points()[i][1]);
        }
        painter.drawPolygon(qpoints, this->get_points().size());
        // if (this->get_end_polygon()) {
        //     qDebug() << "Polygon";
        //     painter.drawPolygon(qpoints, this->get_points().size());
        // }
        // else {
        //     qDebug() << "Polyline2";
        //     painter.drawPolyline(qpoints, this->get_points().size());
        // }
    }
    painter.restore();
}

bool Polygon::get_end_polygon() {
    return this->end_polygone;
}

void Polygon::set_end_polygon(bool end_pol) {
    this->end_polygone = end_pol;
}

TransitionPoint::TransitionPoint() : Primitive::Primitive() {
}

TransitionPoint::TransitionPoint(int number, int x, int y, int width,
                                 int height)
    : Primitive::Primitive() {
    // получает номер точки перехода, координаты, ширина, высота
    this->number_of_transition_point = number;
    this->type_object = "Точка перехода";
    change_center_cords(x, y, width, height);
}

TransitionPoint::TransitionPoint(int number, int x, int y, int width,
                                 int height, const std::vector<int>& filling_color, const std::string& help_text,
                                 bool bool_show,
                                 bool bool_show_filling) : Primitive::Primitive() {
    this->number_of_transition_point = number;
    this->filling_color = filling_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Точка перехода";
    change_center_cords(x, y, width, height);
}

void TransitionPoint::draw(QPainter& painter) {
    //начало отображения точки перехода
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(QRect(this->get_x(), this->get_y(), this->get_width(), this->get_height()));
        painter.drawEllipse(QPoint(this->get_center_x(), this->get_center_y()), 3, 3);
    }
}

void
TransitionPoint::change_center_cords(int x, int y, int width,
                                     int height) {
    //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса точки перехода
void TransitionPoint::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}

void TransitionPoint::set_point_number(int num) {
    this->number_of_transition_point = num;
}

//далее идут функции по выводу одноименных переменных класса кнопки перехода
int TransitionPoint::get_point_number() {
    return this->number_of_transition_point;
}

std::vector<int> TransitionPoint::get_filling_color() {
    return this->filling_color;
}

//далее идут функции меняющие настройки показывания различных элементов
void TransitionPoint::show_filling() {
    this->bool_show_filling = true;
}

void TransitionPoint::hide_filling() {
    this->bool_show_filling = false;
}

bool TransitionPoint::get_show_filling() {
    return this->bool_show_filling;
}

//конструкторы класса кнопки перехода получающие различные вводные
TransitionButton::TransitionButton(int number, int x, int y, int width, int height, int angle)
    : TransitionPoint::TransitionPoint() {
    this->number_of_transition_button = number;
    this->angle = angle;
    this->type_object = "Кнопка перехода";
    int number_transition_point = 0; //служебная переменная
    change_center_cords(x, y, width, height);
}

TransitionButton::TransitionButton(int number, int x, int y, int width, int height, int angle,
                                   const std::vector<int>& filling_color,
                                   const std::string& help_text, bool bool_show,
                                   bool bool_show_filling)
    : TransitionPoint::TransitionPoint() {
    this->number_of_transition_button = number;
    this->type_object = "Кнопка перехода";
    int number_transition_point = 0; //служебная переменная
    this->angle = angle;
    this->filling_color = filling_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    change_center_cords(x, y, width, height);
}

TransitionButton::TransitionButton(int number, int x, int y, int width, int height, int angle,
                                   const std::vector<int>& filling_color,
                                   const std::string& help_text, bool bool_show,
                                   bool bool_show_filling, const std::string& text, const std::string& font_name,
                                   int font_size,
                                   const std::vector<int>& font_color, int hAlignment, int vAlignment, bool bold_font,
                                   bool italic_font, bool underlined_font, bool crossed_font, bool auto_size_text)
    : TransitionPoint::TransitionPoint() {
    this->number_of_transition_button = number;
    this->type_object = "Кнопка перехода";
    int number_transition_point = 0; //служебная переменная
    this->angle = angle;
    this->filling_color = filling_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->text = text;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->hAlignment = hAlignment;
    this->vAlignment = vAlignment;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->auto_size_text = auto_size_text;
    change_center_cords(x, y, width, height);
}

void TransitionButton::draw(QPainter& painter) {
    //начало отображения кнопки перехода
    painter.save();
    QFont tr_b_font(this->get_font_name().c_str(), this->get_font_size());
    tr_b_font.setBold(this->get_bold_font());
    tr_b_font.setItalic(this->get_italic_font());
    tr_b_font.setUnderline(this->get_underlined_font());
    tr_b_font.setStrikeOut(this->get_crossed_font());
    if (this->get_auto_size_text()) {
        QFontMetrics fm(tr_b_font);
        int pxwidth = fm.width(this->get_text().c_str());
        int pxheight = fm.height();
        this->change_center_cords(this->get_x() - 4, this->get_y() - 4, pxwidth + 7, pxheight + 7);
    }
    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect(0, 0, 0);
        painter.setPen(QPen(color_rect, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                         this->get_height());
        QRect rect = QRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(),
                           this->get_width(),
                           this->get_height());
        QColor font_color = {this->get_font_color()[0], this->get_font_color()[1], this->get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(tr_b_font);
        painter.drawText(rect, h_alignment_vector[this->get_hAlignment()] |
                               v_alignment_vector[this->get_vAlignment()],
                         QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    }
    painter.restore();
}

//далее идут функции меняющие одноименные переменные класса кнопки перехода
void TransitionButton::set_angle(int angl) {
    this->angle = angl;
}

void TransitionButton::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void TransitionButton::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void TransitionButton::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void TransitionButton::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void TransitionButton::set_font(const std::string& font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void TransitionButton::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
TransitionButton::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color,
                           bool bold_font, bool italic_font,
                           bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}

void TransitionButton::set_auto_size_text(bool auto_size) {
    this->auto_size_text = auto_size;
}

void TransitionButton::set_text(const std::string& text) {
    this->text = text;
}

void TransitionButton::set_font_name(const std::string& font_name) {
    this->font_name = font_name;
}

void TransitionButton::set_font_size(int font_size) {
    this->font_size = font_size;
}

void TransitionButton::set_hAlignment(int hAlignment) {
    if (hAlignment >= 0 && hAlignment <= 3) {
        this->hAlignment = hAlignment;
    }
}

void TransitionButton::set_vAlignment(int vAlignment) {
    if (vAlignment >= 0 && vAlignment <= 3) {
        this->vAlignment = vAlignment;
    }
}

void TransitionButton::set_Alignment(const std::vector<int>& al) {
    if (al[0] >= 0 && al[0] <= 3 && al[1] >= 0 && al[1] <= 3) {
        this->hAlignment = al[0];
        this->vAlignment = al[1];
    }
}

void TransitionButton::set_button_number(int num) {
    this->number_of_transition_button = num;
}

void TransitionButton::set_font_color(const std::vector<int>& fn_col) {
    this->font_color = fn_col;
}

//далее идут функции по выводу одноименных переменных класса кнопки перехода

int TransitionButton::get_font_size() {
    return this->font_size;
}

int TransitionButton::get_button_number() {
    return this->number_of_transition_button;
}

bool TransitionButton::get_bold_font() {
    return this->bold_font;
}

bool TransitionButton::get_italic_font() {
    return this->italic_font;
}

bool TransitionButton::get_crossed_font() {
    return this->crossed_font;
}

bool TransitionButton::get_underlined_font() {
    return this->underlined_font;
}

bool TransitionButton::get_auto_size_text() {
    return this->auto_size_text;
}

std::string TransitionButton::get_font_name() {
    return this->font_name;
}

std::vector<int> TransitionButton::get_font_color() {
    return this->font_color;
}

int TransitionButton::get_hAlignment() {
    return this->hAlignment;
}

int TransitionButton::get_vAlignment() {
    return this->vAlignment;
}

std::vector<std::string> TransitionButton::get_alignment() {
    return {this->hAlignment_list[this->hAlignment], this->vAlignment_list[this->vAlignment]};
}

//конструкторы класса текста получающие различные вводные
Text::Text() : Primitive::Primitive() {
}

Text::Text(int x, int y, int width, int height, const std::string& text) : Primitive::Primitive() {
    this->text = text;
    this->type_object = "Текст";
    change_center_cords(x, y, width, height);
}

Text::Text(int x, int y, int width, int height, int angle, const std::string& text, const std::string& help_text,
           int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
           bool bool_show_filling)
    : Primitive::Primitive() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Текст";
    this->line_width = line_width;
    change_center_cords(x, y, width, height);
}

Text::Text(int x, int y, int width, int height, int angle, const std::string& text, const std::string& help_text,
           int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
           bool bool_show_filling,
           const std::string& font_name, int font_size,
           const std::vector<int>& font_color, int hAlignment, int vAlignment, bool bold_font,
           bool italic_font, bool underlined_font, bool crossed_font, bool auto_size_text,
           const std::vector<int>& pen_color) : Primitive::Primitive() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->hAlignment = hAlignment;
    this->vAlignment = vAlignment;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->auto_size_text = auto_size_text;
    this->type_object = "Текст";
    this->line_width = line_width;
    this->line_color = pen_color;
    change_center_cords(x, y, width, height);
}

void Text::draw(QPainter& painter) {
    painter.save();
    QFont text_font(this->get_font_name().c_str(), this->get_font_size());
    text_font.setBold(this->get_bold_font());
    text_font.setItalic(this->get_italic_font());
    text_font.setUnderline(this->get_underlined_font());
    QFontMetrics fm(text_font);
    QString text_to_measure(QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    int pxwidth = fm.horizontalAdvance(text_to_measure);
    int pxheight = fm.height();
    if (pxwidth > this->get_width() && pxheight > this->get_height()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_center_y() - pxheight / 2, pxwidth,
                                  pxheight);
    } else if (pxwidth > this->get_width()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_y(), pxwidth,
                                  this->get_height());
    } else if (pxheight > this->get_height()) {
        this->change_center_cords(this->get_x(),
                                  this->get_center_y() - pxheight / 2, this->get_width(),
                                  pxheight);
    }

    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    int new_angle = this->get_angle() % 360;
    while (new_angle < 0) {
        new_angle += 360;
    }
    if(new_angle > 90 && new_angle < 270){
        painter.scale(-1, -1);
    }
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        QPen pen;
        pen.setStyle(style_vector[this->get_style_line()]);
        pen.setWidth(this->get_line_width());
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        pen.setColor(color_rect);
        painter.drawRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                         this->get_height());
        QRect rect = QRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(),
                           this->get_width(),
                           this->get_height());
        QColor font_color = {this->get_font_color()[0], this->get_font_color()[1], this->get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[this->get_hAlignment()] |
                               v_alignment_vector[this->get_vAlignment()],
                         QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    }
    painter.restore();
}

void
Text::change_center_cords(int x, int y, int width,
                          int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса текста
void Text::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}

void Text::set_line_color(const std::vector<int>& ln_col) {
    this->line_color = ln_col;
}

void Text::set_line_width(int ln_width) {
    this->line_width = ln_width;
}

void Text::set_angle(int angl) {
    this->angle = angl;
}

void Text::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void Text::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void Text::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void Text::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void Text::set_font(const std::string& font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void Text::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
Text::set_font(const std::string& font_name, int font_size, const std::vector<int>& font_color, bool bold_font,
               bool italic_font,
               bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}

void Text::set_auto_size_text(bool auto_size) {
    this->auto_size_text = auto_size;
}

void Text::set_font_name(const std::string& font_name) {
    this->font_name = font_name;
}

void Text::set_font_size(int font_size) {
    this->font_size = font_size;
}

void Text::set_hAlignment(int hAlignment) {
    if (hAlignment >= 0 && hAlignment <= 3) {
        this->hAlignment = hAlignment;
    }
}

void Text::set_vAlignment(int vAlignment) {
    if (vAlignment >= 0 && vAlignment <= 3) {
        this->vAlignment = vAlignment;
    }
}

void Text::set_Alignment(const std::vector<int>& al) {
    if (al[0] >= 0 && al[0] <= 3 && al[1] >= 0 && al[1] <= 3) {
        this->hAlignment = al[0];
        this->vAlignment = al[1];
    }
}

void Text::set_font_color(const std::vector<int>& fn_col) {
    this->font_color = fn_col;
}

void Text::set_style_line(int style_line) {
    if (style_line >= 0 && style_line <= 9) {
        this->style_line = style_line;
    }
}

//далее идут функции по выводу одноименных переменных класса текста

int Text::get_style_line() {
    return this->style_line;
}

std::vector<int> Text::get_filling_color() {
    return this->filling_color;
}

std::vector<int> Text::get_line_color() {
    return this->line_color;
}

int Text::get_angle() {
    return this->angle;
}

int Text::get_line_width() {
    return this->line_width;
}

int Text::get_font_size() {
    return this->font_size;
}


bool Text::get_bold_font() {
    return this->bold_font;
}

bool Text::get_italic_font() {
    return this->italic_font;
}

bool Text::get_crossed_font() {
    return this->crossed_font;
}

bool Text::get_underlined_font() {
    return this->underlined_font;
}

bool Text::get_auto_size_text() {
    return this->auto_size_text;
}

std::string Text::get_font_name() {
    return this->font_name;
}

std::vector<int> Text::get_font_color() {
    return this->font_color;
}

int Text::get_hAlignment() {
    return this->hAlignment;
}

int Text::get_vAlignment() {
    return this->vAlignment;
}

std::vector<std::string> Text::get_alignment() {
    return {this->hAlignment_list[this->hAlignment], this->vAlignment_list[this->vAlignment]};
}

//далее идут функции меняющие настройки показывания различных элементов
void Text::show_filling() {
    this->bool_show_filling = true;
}

void Text::hide_filling() {
    this->bool_show_filling = false;
}

bool Text::get_show_filling() {
    return this->bool_show_filling;
}

//конструкторы класса прямоугольника получающие различные вводные
Image::Image(int x, int y, int width, int height, const std::string& im_path, int angle) : Primitive::Primitive() {
    this->image_path = im_path;
    this->angle = angle;
    this->type_object = "Картинка";
    change_center_cords(x, y, width, height);
}

Image::Image(int x, int y, int width, int height, const std::string& im_path, int angle, int line_width, int style_line,
             const std::vector<int>& line_color, const std::string& help_text, bool bool_show)
    : Primitive::Primitive() {
    this->image_path = im_path;
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->type_object = "Картинка";
    change_center_cords(x, y, width, height);
}

Image::Image(int x, int y, int width, int height, const std::string& im_path, int angle, int line_width, int style_line,
             const std::vector<int>& line_color, const std::string& help_text, bool bool_show, int style_frame,
             const std::vector<int>& filling_color, bool bool_show_filling) : Primitive::Primitive() {
    this->image_path = im_path;
    this->angle = angle;
    this->line_width = line_width;
    this->style_line = style_line;
    this->line_color = line_color;
    this->help_text = help_text;
    this->bool_show = bool_show;
    this->style_frame = style_frame;
    this->filling_color = filling_color;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Картинка";
    change_center_cords(x, y, width, height);
}

void Image::draw(QPainter& painter) {
    //начало отображения картинки
    painter.save();
    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        QRect target(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                     this->get_height());
        QRect source(0, 0, 0, 0);
        QPixmap pixmap(this->get_image_path().c_str());
        painter.drawPixmap(target, pixmap, source);
    }
    painter.restore();
}

//меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
void Image::change_center_cords(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

//далее идут функции меняющие одноименные переменные класса прямоугольника
void Image::set_angle(int angl) {
    this->angle = angl;
}

void Image::set_line_width(int width) {
    this->line_width = width;
}

void Image::set_line_color(const std::vector<int>& ln_col) {
    this->line_color = ln_col;
}

void Image::set_filling_color(const std::vector<int>& fil_col) {
    this->filling_color = fil_col;
}

void Image::set_style_frame(int st_frame) {
    if (st_frame >= 0 && st_frame < this->style_frame_list.size()) {
        this->style_frame = st_frame;
    }
}

void Image::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

void Image::set_image_path(const std::string& im_path) {
    this->image_path = im_path;
}

//далее идут функции по выводу одноименных переменных класса прямоугольника
std::string Image::get_image_path() {
    return this->image_path;
}

int Image::get_style_frame() {
    return this->style_frame;
}

int Image::get_line_width() {
    return this->line_width;
}

int Image::get_style_line() {
    return this->style_line;
}

std::vector<int> Image::get_line_color() {
    return this->line_color;
}

std::vector<int> Image::get_filling_color() {
    return this->filling_color;
}

//далее идут функции меняющие настройки показывания различных элементов
void Image::show_filling() {
    this->bool_show_filling = true;
}

void Image::hide_filling() {
    this->bool_show_filling = false;
}

bool Image::get_show_filling() {
    return bool_show_filling;
}

//конструкторы класса текста получающие различные вводные
Telecontrol::Telecontrol(int x, int y, int width, int height, const std::string& text) : Text::Text() {
    this->text = text;
    this->type_object = "Телеконтроль";
    change_center_cords(x, y, width, height);
}

Telecontrol::Telecontrol(int x, int y, int width, int height, int angle, const std::string& text,
                         const std::string& help_text,
                         int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
                         bool bool_show_filling)
    : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Телеконтроль";
    this->line_width = line_width;
    change_center_cords(x, y, width, height);
}

Telecontrol::Telecontrol(int x, int y, int width, int height, int angle, const std::string& text,
                         const std::string& help_text,
                         int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
                         bool bool_show_filling,
                         const std::string& font_name, int font_size,
                         const std::vector<int>& font_color, int hAlignment, int vAlignment, bool bold_font,
                         bool italic_font, bool underlined_font, bool crossed_font, bool auto_size_text,
                         const std::vector<int>& pen_color, int id_c)
    : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->hAlignment = hAlignment;
    this->vAlignment = vAlignment;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->auto_size_text = auto_size_text;
    this->type_object = "Телеконтроль";
    this->line_width = line_width;
    this->line_color = pen_color;
    if(id_c < 0)
    {
        id_c = abs(id_c);
    }
    this->id = id_c;
    change_center_cords(x, y, width, height);
}

void Telecontrol::draw(QPainter& painter) {
    painter.save();
    QFont text_font(this->get_font_name().c_str(), this->get_font_size());
    text_font.setBold(this->get_bold_font());
    text_font.setItalic(this->get_italic_font());
    text_font.setUnderline(this->get_underlined_font());
    QFontMetrics fm(text_font);
    QString text_to_measure(QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    int pxwidth = fm.horizontalAdvance(text_to_measure);
    int pxheight = fm.height();
    if (pxwidth > this->get_width() && pxheight > this->get_height()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_center_y() - pxheight / 2, pxwidth,
                                  pxheight);
    } else if (pxwidth > this->get_width()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_y(), pxwidth,
                                  this->get_height());
    } else if (pxheight > this->get_height()) {
        this->change_center_cords(this->get_x(),
                                  this->get_center_y() - pxheight / 2, this->get_width(),
                                  pxheight);
    }

    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        QPen pen;
        pen.setStyle(style_vector[this->get_style_line()]);
        pen.setWidth(this->get_line_width());
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        pen.setColor(color_rect);
        painter.drawRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                         this->get_height());
        QRect rect = QRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(),
                           this->get_width(),
                           this->get_height());
        QColor font_color = {this->get_font_color()[0], this->get_font_color()[1], this->get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[this->get_hAlignment()] |
                               v_alignment_vector[this->get_vAlignment()],
                         QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    }
    painter.restore();
}

//далее идут функции меняющие одноименные переменные класса телеуправления
void Telecontrol::set_condition(int condition) {
    if (0 <= condition <= 1) {
        this->condition = condition;
    }
}

//далее идут функции по выводу одноименных переменных класса телеуправления
int Telecontrol::get_condition() {
    return this->condition;
}

//конструкторы класса текста получающие различные вводные
Telesignalisation::Telesignalisation(int x, int y, int width, int height, const std::string& text) : Text::Text() {
    this->text = text;
    this->type_object = "Телесигнализация";
    change_center_cords(x, y, width, height);
}

Telesignalisation::Telesignalisation(int x, int y, int width, int height, int angle, const std::string& text,
                                     const std::string& help_text,
                                     int style_line, int line_width, const std::vector<int>& filling_color,
                                     bool bool_show,
                                     bool bool_show_filling) : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Телесигнализация";
    this->line_width = line_width;
    change_center_cords(x, y, width, height);
}

Telesignalisation::Telesignalisation(int x, int y, int width, int height, int angle, const std::string& text,
                                     const std::string& help_text,
                                     int style_line, int line_width, const std::vector<int>& filling_color,
                                     bool bool_show,
                                     bool bool_show_filling,
                                     const std::string& font_name, int font_size,
                                     const std::vector<int>& font_color, int hAlignment, int vAlignment, bool bold_font,
                                     bool italic_font, bool underlined_font, bool crossed_font, bool auto_size_text,
                                     const std::vector<int>& pen_color, int id_c)
    : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->hAlignment = hAlignment;
    this->vAlignment = vAlignment;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->auto_size_text = auto_size_text;
    this->type_object = "Телесигнализация";
    this->line_width = line_width;
    this->line_color = pen_color;
    if(id_c < 0)
    {
        id_c = abs(id_c);
    }
    this->id = id_c;
    change_center_cords(x, y, width, height);
}

void Telesignalisation::draw(QPainter& painter) {
    painter.save();
    QFont text_font(this->get_font_name().c_str(), this->get_font_size());
    text_font.setBold(this->get_bold_font());
    text_font.setItalic(this->get_italic_font());
    text_font.setUnderline(this->get_underlined_font());
    QFontMetrics fm(text_font);
    QString text_to_measure(QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    int pxwidth = fm.horizontalAdvance(text_to_measure);
    int pxheight = fm.height();
    if (pxwidth > this->get_width() && pxheight > this->get_height()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_center_y() - pxheight / 2, pxwidth,
                                  pxheight);
    } else if (pxwidth > this->get_width()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_y(), pxwidth,
                                  this->get_height());
    } else if (pxheight > this->get_height()) {
        this->change_center_cords(this->get_x(),
                                  this->get_center_y() - pxheight / 2, this->get_width(),
                                  pxheight);
    }

    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        QPen pen;
        pen.setStyle(style_vector[this->get_style_line()]);
        pen.setWidth(this->get_line_width());
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        pen.setColor(color_rect);
        painter.drawRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                         this->get_height());
        QRect rect = QRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(),
                           this->get_width(),
                           this->get_height());
        QColor font_color = {this->get_font_color()[0], this->get_font_color()[1], this->get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[this->get_hAlignment()] |
                               v_alignment_vector[this->get_vAlignment()],
                         QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    }
    painter.restore();
}

//далее идут функции меняющие одноименные переменные класса телеуправления
void Telesignalisation::set_condition(int condition) {
    if (0 <= condition <= 1) {
        this->condition = condition;
    }
}

//далее идут функции по выводу одноименных переменных класса телеуправления
int Telesignalisation::get_condition() {
    return this->condition;
}

//конструкторы класса текста получающие различные вводные
Telemeasure::Telemeasure(int x, int y, int width, int height, const std::string& text) : Text::Text() {
    this->text = text;
    this->type_object = "Телеизмерение";
    change_center_cords(x, y, width, height);
}

Telemeasure::Telemeasure(int x, int y, int width, int height, int angle, const std::string& text,
                         const std::string& help_text,
                         int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
                         bool bool_show_filling)
    : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->type_object = "Телеизмерение";
    this->line_width = line_width;
    change_center_cords(x, y, width, height);
}

Telemeasure::Telemeasure(int x, int y, int width, int height, int angle, const std::string& text,
                         const std::string& help_text,
                         int style_line, int line_width, const std::vector<int>& filling_color, bool bool_show,
                         bool bool_show_filling,
                         const std::string& font_name, int font_size,
                         const std::vector<int>& font_color, int hAlignment, int vAlignment, bool bold_font,
                         bool italic_font, bool underlined_font, bool crossed_font, bool auto_size_text,
                         const std::vector<int>& pen_color, int id_c)
    : Text::Text() {
    this->angle = angle;
    this->text = text;
    this->help_text = help_text;
    this->style_line = style_line;
    this->filling_color = filling_color;
    this->bool_show = bool_show;
    this->bool_show_filling = bool_show_filling;
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->hAlignment = hAlignment;
    this->vAlignment = vAlignment;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
    this->auto_size_text = auto_size_text;
    this->type_object = "Телеизмерение";
    this->line_width = line_width;
    this->line_color = pen_color;
    if(id_c < 0)
    {
        id_c = abs(id_c);
    }
    this->id = id_c;
    change_center_cords(x, y, width, height);
}

void Telemeasure::draw(QPainter& painter) {
    painter.save();
    QFont text_font(this->get_font_name().c_str(), this->get_font_size());
    text_font.setBold(this->get_bold_font());
    text_font.setItalic(this->get_italic_font());
    text_font.setUnderline(this->get_underlined_font());
    QFontMetrics fm(text_font);
    QString text_to_measure(QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    int pxwidth = fm.horizontalAdvance(text_to_measure);
    int pxheight = fm.height();
    if (pxwidth > this->get_width() && pxheight > this->get_height()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_center_y() - pxheight / 2, pxwidth,
                                  pxheight);
    } else if (pxwidth > this->get_width()) {
        this->change_center_cords(this->get_center_x() - pxwidth / 2,
                                  this->get_y(), pxwidth,
                                  this->get_height());
    } else if (pxheight > this->get_height()) {
        this->change_center_cords(this->get_x(),
                                  this->get_center_y() - pxheight / 2, this->get_width(),
                                  pxheight);
    }

    painter.translate(this->get_center_x(), this->get_center_y());
    painter.rotate((-1) * this->get_angle());
    if (this->get_show()) {
        if (this->get_show_filling()) {
            QColor filling_color = {
                this->get_filling_color()[0], this->get_filling_color()[1],
                this->get_filling_color()[2]
            };
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        } else {
            QColor filling_color = {Qt::transparent};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {this->get_line_color()[0], this->get_line_color()[1], this->get_line_color()[2]};
        QPen pen;
        pen.setStyle(style_vector[this->get_style_line()]);
        pen.setWidth(this->get_line_width());
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        pen.setColor(color_rect);
        painter.drawRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(), this->get_width(),
                         this->get_height());
        QRect rect = QRect(this->get_x() - this->get_center_x(), this->get_y() - this->get_center_y(),
                           this->get_width(),
                           this->get_height());
        QColor font_color = {this->get_font_color()[0], this->get_font_color()[1], this->get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[this->get_hAlignment()] |
                               v_alignment_vector[this->get_vAlignment()],
                         QTextCodec::codecForName("cp1251")->toUnicode(this->get_text().c_str()));
    }
    painter.restore();
}

void Telemeasure::set_text(const std::string& t) {
    text = t;
}


//далее идут функции меняющие одноименные переменные класса телеуправления
void Telemeasure::set_device_type(int device_type) {
    this->device_type = device_type;
}

//далее идут функции по выводу одноименных переменных класса телеуправления
int Telemeasure::get_device_type() {
    return this->device_type;
}

Set::Set() : Primitive::Primitive() {
}

Set::Set(int ln_width, int ln_width2, int ln_width3, int hor_space, int vert_space, int hor_space2, int vert_space2,
         int hor_space3, int vert_space3,
         int ln_style, const std::vector<int>& ln_color)
    : Primitive::Primitive() {
    line_width = ln_width;
    line_width2 = ln_width2;
    line_width3 = ln_width3;
    horizontal_space = hor_space;
    vertical_space = vert_space;
    horizontal_space2 = hor_space2;
    vertical_space2 = vert_space2;
    horizontal_space3 = hor_space3;
    vertical_space3 = vert_space3;
    line_style = ln_style;
    line_color = ln_color;
}

void Set::draw(QPainter& painter, int scheme_width, int scheme_height) {
    if (bool_show) {
        QColor color_set = {line_color[0], line_color[1], line_color[2]};
        painter.setPen(QPen(color_set, line_width, style_vector[line_style], Qt::RoundCap));
        for (int i = 0; i < scheme_width; i += horizontal_space) {
            painter.drawLine(i, 0, i, scheme_height);
        }
        for (int i = 0; i < scheme_height; i += vertical_space) {
            painter.drawLine(0, i, scheme_width, i);
        }
        painter.setPen(QPen(color_set, line_width2, Qt::DashLine, Qt::RoundCap));
        for (int i = 0; i < scheme_width; i += horizontal_space2) {
            painter.drawLine(i, 0, i, scheme_height);
        }
        for (int i = 0; i < scheme_height; i += vertical_space2) {
            painter.drawLine(0, i, scheme_width, i);
        }
        painter.setPen(QPen(color_set, line_width3, Qt::DotLine, Qt::RoundCap));
        for (int i = 0; i < scheme_width; i += horizontal_space3) {
            painter.drawLine(i, 0, i, scheme_height);
        }
        for (int i = 0; i < scheme_height; i += vertical_space3) {
            painter.drawLine(0, i, scheme_width, i);
        }
    }
}

void Set::set_line_width(int ln_width) {
    line_width = ln_width;
}

void Set::set_horizontal_space(int hor_space) {
    horizontal_space = hor_space;
}

void Set::set_vertical_space(int ver_space) {
    vertical_space = ver_space;
}

void Set::set_line_style(int ln_style) {
    line_style = ln_style;
}

void Set::set_line_color(std::vector<int>& col) {
    line_color = col;
}

int Set::get_line_width() {
    return line_width;
}

int Set::get_horizontal_space() {
    return horizontal_space;
}

int Set::get_vertical_space() {
    return vertical_space;
}

int Set::get_line_style() {
    return line_style;
}

std::vector<int> Set::get_line_color() {
    return line_color;
}

Point::Point() : Primitive() {
    type_object = "Point";
}

Point::Point(int x, int y, int ln_width, const std::vector<int>& ln_color) : Point() {
    type_object = "Point";
    this->x = x;
    this->y = y;
    line_width = ln_width;
    line_color = ln_color;
}

void Point::draw(QPainter& painter) {
    QColor col = QColor(line_color[0], line_color[1], line_color[2]);
    painter.setPen(QPen(col, line_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPoint(this->x, this->y);
}

void Point::change_cords(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::set_line_width(int ln_width) {
    line_width = ln_width;
}

void Point::set_line_color(std::vector<int> ln_color) {
    line_color = ln_color;
}

int Point::get_line_width() {
    return line_width;
}

std::vector<int> Point::get_line_color() {
    return line_color;
}

LibraryObject::LibraryObject() : Primitive() {
    type_object = "Библиотечный объект";
}

LibraryObject::LibraryObject(int x, int y, int width, int height, int angle, int id, int condition,
                             const std::string& lib_name, const std::string& obj_name,
                             const std::vector<std::vector<Primitive*> >& patterns, const std::string& help_text,
                             bool show, bool show_help, int hor_mirror, int vert_mirror) : Primitive() {
    type_object = "Библиотечный объект";
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->angle = angle;
    if(id < 0)
    {
        id = abs(id);
    }
    this->id = id;
    this->condition = condition;
    this->library_name = lib_name;
    this->object_name = obj_name;
    this->patterns = patterns;
    this->help_text = help_text;
    this->bool_show = show;
    this->bool_show_help = show_help;
    this->horizontal_mirror = hor_mirror;
    this->vertical_mirror = vert_mirror;
    change_center_cords(this->x, this->y, this->width, this->height);
}

void LibraryObject::draw(QPainter& painter) {
    if (this->bool_show) {
        painter.save();
        painter.translate(this->center_x, this->center_y);
        // painter.rotate((360 - this->angle) % 360);
        // int new_angle = this->get_angle() % 360;
        // while (new_angle < 0) {
        //     new_angle += 360;
        // }
        // if(new_angle > 90 && new_angle < 270){
        //     painter.rotate(new_angle + 180);
        // }else
        // {
        //     painter.rotate(new_angle);
        // }
        painter.rotate(this->angle % 360);
        // qDebug() << this->angle;
        if (condition < patterns.size() && condition >= 0) {
            for (auto obj: patterns[condition]) {
                obj->draw(painter);
            }
        }
        painter.restore();
    }
}

void LibraryObject::change_center_cords(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

void LibraryObject::set_angle(int angle) {
    this->angle = angle;
}

void LibraryObject::set_library_name(const std::string& lib_name) {
    library_name = lib_name;
}

void LibraryObject::set_object_name(const std::string& obj_name) {
    object_name = obj_name;
}

void LibraryObject::set_patterns(const std::vector<std::vector<Primitive*> >& patterns) {
    this->patterns = patterns;
}

void LibraryObject::set_hor_mirror(bool hor_mirror) {
    this->horizontal_mirror = hor_mirror;
}

void LibraryObject::set_vert_mirror(bool vert_mirror) {
    this->vertical_mirror = vert_mirror;
}

void LibraryObject::add_pattern(const std::vector<Primitive*> pattern) {
    this->patterns.push_back(pattern);
}

bool LibraryObject::get_hor_mirror() {
    return this->horizontal_mirror;
}

bool LibraryObject::get_vert_mirror() {
    return this->vertical_mirror;
}

int LibraryObject::get_condition() {
    return condition;
}
